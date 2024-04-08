from fastapi import FastApi, Request, Depends, HTTPException
import LedStrip

# ERROR HANDLING

def check(err: int):
    if err != None:
        return HTTPException(status_code=503, detail="There was an error processing the request, please try again")
    else:
        return {'status': 200, 'message': 'OK'}

# API

app = FastApi()

# ROOT

@app.get("/")
async def root(request: Request):
    with open("hidden/whitelist.txt", "r") as f:
        for line in f.read():
            if request.client == line:
                with open("hidden/auth.txt", "r") as auth:
                    return {'status': 200, 'message': f'Authorized: {auth.readLine()}'}
            else:
                return HTTPException(status_code=403, detail=f"Forbidden, unrecognized ip: {request.client}")


# MIDDLEWARE

@app.middleware("http")
async def checkAuth(request: Request, next):
    if request.url.path == "/":
        return next(request)

    token = request.headers["Authorization"]

    with open("hidden/auth.txt", "r") as auth:
        if token != f"Bearer {auth.readLine()}":
            return HTTPException(status_code=401, detail=f"Token is not authorized or was not supplied. Token: {token}")

        else:
            return next(request)


# ROUTES

@app.get("/program")
async def getFlow(func: str, color: tuple = None, brightness: float = None):
    allowed_functions = ["flow", "alternate", "collapse", "nightLights", "virginLights", "light"]

    if func not in allowed_functions:
        return HTTPException(status_code=400, detail=f"Not an allowed function: {func}")

    with LedStrip() as led:
        err = led.handleProgram(func, color, brightness)

        return check(err)

@app.get("/brightness")
async def setBrightness(brightness: float = None):
    with LedStrip() as led:
        err = led.setBrightness(brightness) if brightness else led.setBrightness()
        
        return check(err)


