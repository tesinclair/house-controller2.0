from fastapi import FastAPI, Request, Depends, HTTPException, Response
from fastapi.responses import RedirectResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
import uvicorn
import socket

# ERROR HANDLING

def check(err: int):
    if err != None:
        return HTTPException(status_code=503, detail="There was an error processing the request, please try again")
    else:
        return RedirectResponse("/")

# SOCKETS

def sockCommand(cmd):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        SOCKADDR = ("127.0.0.1", 7777)
        sock.connect(SOCKADDR)

        print(f"[SOCKET]: Connected to {sock}")

        try:
            print(f"[SOCKET]: Sending {cmd} ({bytes(cmd, 'UTF-8')}) to {sock}")
            sock.sendall(bytes(cmd, 'UTF-8'))
        except Exception as e:
            print(f"[SOCKET ERR]: {e}")
            return -1

        data = sock.recv(1024)

        if not data:
            return -1

        data = data.decode('UTF-8')

        print(f"[SOCKET]: {data}")
    
        if data == "OK":
            return None
        else:
            return 1

# API

app = FastAPI()

app.mount("/templates/static", StaticFiles(directory="templates/static"), name="static")

templates = Jinja2Templates(directory="templates")

# ROOT

@app.get("/")
async def root(request: Request, response: Response):
    with open("hidden/whitelist.txt", "r") as f:
        if request.client.host in f.read():
                #with open("hidden/auth.txt", "r") as auth:
                    #authToken = auth.readLine()
                    #response.headers["Auth-token"] = authToken
            return templates.TemplateResponse(
                    request=request, name="index.html", context={}
                    )
        else:
            return HTTPException(status_code=403, detail=f"Forbidden, unrecognized ip: {request.client.host}")


# MIDDLEWARE

#@app.middleware("http")
async def checkAuth(request: Request, next):
    if request.url.path == "/":
        return next(request)

    token = request.headers.get("Authorization")

    with open("hidden/auth.txt", "r") as auth:
        if token != f"Bearer {auth.readLine()}":
            return HTTPException(status_code=401, detail=f"Token is not authorized or was not supplied. Token: {token}")

        else:
            return next(request)


# ROUTES

@app.get("/program")
async def getFlow(func: str):
    allowed_functions = ["flow", "alternate", "collapse", "nightLight", "virginLights", "light", "red", "blue", "green", "pulse", "stop", "quit"]

    if func not in allowed_functions:
        return HTTPException(status_code=400, detail=f"Not an allowed function: {func}")
    
    err = sockCommand(f"func:{func}")
    return check(err)

@app.get("/set")
async def setBrightness(brightness: float = None):
    err = sockCommand(f"brightness:{brightness}")
    return check(err)

if __name__ == "__main__":
    uvicorn.run("server:app", port=6767, host="0.0.0.0", log_level="info")

