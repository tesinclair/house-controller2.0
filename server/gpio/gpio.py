import board
import neopixel
import RPi.GPIO as gpio
import time
import sys

sys.path.append("./utils")
import utils

"""
Main Gpio Controller File

Classes: 
    Universal Methods:
        - __enter__: responsible for initial setup of the device, returns None if an error occurs
        - __init__: Come on...
        - __exit__: handles safe destruction

    - LedStrip: This is the strip light that covers most of the room
        Methods:
            - virginLights: Make the lights do rgb gamer stuff
            - nightLights: Make the lights a cool purple
            - collapse: creates a collapse from the sides of the leds to the centre
            - flow: creates a flow from one side to the other
            - alternate: creates an alternating pattern from one side to the other
            - setBrightness: changes the self.brightness to value self.brightness 

    - Notifier: This is a 10 pin led that will be used for errors and logging
        Methods:
            - __new__: ensure that only one instance is active at a time. Set the activeNotifier
            - getActiveNotifier: returns the currently active notifier, if none exist, one is created
            - error: Will flash 5 times
            - newReq: Will flow from left to right 5 times
            - rejectedReq: Will collapse 5 times

For reference, I am using camelCase not snake_case simply because I don't like snake_case

"""

class Notifier():

    activeNotifier = None
    ON = gpio.LOW
    OFF = gpio.HIGH
    
    def __new__(cls):
        if cls.activeNotifier:
            utils.Logger.log("", "Too Many Notifiers", "[NONE]")
            return None
        cls.activeNotifier = super().__new__(cls)
        return cls.activeNotifier

    def __init__(self):
        self.numPins = 10
        self.delay = 0.2
        self.iterations = 5

    def __enter__(self):
        if gpio.getmode() == 11:
            gpio.setmode(gpio.BCM)
            self.PINS = [17, 18, 27, 23, 22, 24, 5, 25, 6, 12]

        else:
            gpio.setmode(gpio.BOARD)
            self.PINS = [11, 12, 13, 16, 15, 18, 29, 22, 31, 32]

        gpio.setup(self.PINS, gpio.OUT)
        gpio.output(self.PINS, self.OFF)
        return self

    def __exit__(self, exType, exVal, traceback):
        if exType:
            utils.Logger.log(exType, exVal, traceback)

        gpio.output(self.PINS, self.OFF)
        gpio.setup(self.PINS, gpio.IN)
        gpio.cleanup()

    @classmethod
    def getActiveNotifier(cls):
        if cls.activeNotifier:
            return cls.activeNotifier
        else:
            return cls.__new__(cls)
    
    def error(self):
        for _ in range(self.iterations):
            gpio.output(self.PINS, self.ON)
            time.sleep(self.delay)
            gpio.output(self.PINS, self.OFF)
            time.sleep(self.delay)

    def newReq(self):
        for _ in range(self.iterations):
            for pin in self.PINS:
                gpio.output(pin, self.ON)
                time.sleep(self.delay)
                gpio.output(pin, self.OFF)

    def rejectedReq(self):
        for _ in range(self.iterations):
            for i in range(int(self.numPins/2)): 
                pinL = self.PINS[i]
                pinR = self.PINS[-(1 + i)] # Start from right at [-1]

                gpio.output(pinL, self.ON)
                gpio.output(pinR, self.ON)
                time.sleep(self.delay)
                gpio.output(pinL, self.OFF)
                gpio.output(pinR, self.OFF)

    def badOptions(self):
        for _ in range(self.iterations):
            for i in range(len(self.PINS)):
                if i % 2 == 0:
                    gpio.output(self.PINS[i], self.ON)
                else:
                    gpio.output(self.PINS[i], self.OFF)

            time.sleep(self.delay/2)

            for i in range(len(self.PINS)):
                if i % 2 != 0:
                    gpio.output(self.PINS[i], self.ON)
                else:
                    gpio.output(self.PINS[i], self.OFF)

            time.sleep(self.delay/2)
                    
class LedStrip():
    instance=None

    def __new__(cls, delay=0.2):
        if cls.instance:
            return cls.instance()
        else:
            cls.instance = super().__new__(cls, delay)
            return cls.instance()

    def __init__(self, delay=0.2):
        self.numPixels = 100
        self.pixels = None
        self.delay = delay
        self.brightness = 1
        self.queue = []
        self.run = False
        # -=-=-=- All Pixels are RBG not RGB -=-=-=-
        self.red = (255, 0, 0)
        self.green = (0, 0, 255)
        self.blue = (0, 255, 0)
        self.purple = (211, 240, 50)
        self.blank = (0, 0, 0)
        self.white = (255, 255, 255)
        self.defaultColor = self.purple

    def __enter__(self):
        self.pixels = neopixel.NeoPixel(board.D18, self.numPixels, self.brightness=1, auto_write=False)
        self.pixels.fill(self.blank)
        self.pixels.show()
        return self

    def __exit__(self, exType, exVal, traceback):
        if exType == "Not using at the moment":
            with Notifier.getActiveNotifier() as err:
                try: 
                    err.error()
                except: 
                    Exception: print("Failed to display Error")
                
            try:
                utils.Logger.log(exType, exVal, traceback)
            except:
                with Notifier.getActveNotifier() as err:
                    err.error()

        self.pixels.fill(self.blank)
        self.pixels.show()
        self.pixels.deinit()

    async def handleProgram(self, func, color=None):
        self.run = False

        if func == "stop":
            return;

        match func:
            case "light":
                self.queue.append(self.light)

            case "nightLight":
                self.queue.append(self.nightLight)

            case "virginLights":
                self.queue.append(self.virginLights)

            case "flow":
                self.queue.append(self.flow)

            case "collapse":
                self.queue.append(self.collapse)

            case "alternate":
                self.queue.append(self.alternate)

    async def next(self):
        if self.run == True:
            raise ValueError("Huhhhh???")

        if len(self.queue) <= 0:
            return;

        self.run = True
        await self.queue.pop(0)()

    async def light(self, color=None):
        if not color: color = self.white
        self.pixels.fill(tuple([x*self.brightness for x in self.white]))
        self.pixels.show()

        while self.run:
            pass

        self.next()

    async def virginLights(self):
        i = 0
        while self.run:
       
            offset = i*4

            redL = (0 + offset)
            redR = ((self.numPixels//3 + offset) - 1)
            greenL = (self.numPixels//3 + offset)
            greenR = (((self.numPixels * 2)//3 + offset) - 1)
            blueL = ((self.numPixels * 2)//3 + offset)
            blueR = ((self.numPixels + offset) - 1)

            for j in range(redL, redR):
                temp = j
                temp = temp % 100
                self.pixels[temp] = tuple([x*self.brightness for x in self.red])
            for j in range(greenL, greenR):
                temp = j
                temp = temp % 100
                self.pixels[temp] = tuple([x*self.brightness for x in self.green])
            for j in range(blueL, blueR):
                temp = j
                temp = temp % 100
                self.pixels[temp] = tuple([x*self.brightness for x in self.blue])
            self.pixels.show()
            time.sleep(self.delay)
            i += 1

        self.next()
    
    async def nightLight(self, color=None):
        if not color: color = self.defaultColor 
        color = tuple([x*self.brightness for x in color])

        self.pixels.fill((0, 0, 0))
        self.pixels.show()
        self.pixels.fill(color)
        self.pixels.show()

        while self.run:
            pass

        self.next()

    async def flow(self, color=None):
        while self.run:
            if not color: color = self.defaultColor # Generally I hate inline if statements, but this is fine
            color = tuple([x*self.brightness for x in color])

            dimColor = tuple([x//2 for x in color])

            self.pixels.fill(dimColor)

            for i in range(self.numPixels):
                self.pixels[i] = color
                self.pixels.show()
                self.pixels.fill(dimColor)
                time.sleep(self.delay)

        self.next()

    async def collapse(self, color=None):
        while self.run:
            if not color: color = self.defaultColor
            color = tuple([x*self.brightness for x in color])

            dimColor = tuple([x//2 for x in color])

            self.pixels.fill(dimColor)
            for i in range(int(self.numPixels/2)):
                pixelL = self.pixels[i]
                pixelR = self.pixels[-(1 + i)]
                pixelL = color
                pixelR = color
                self.pixels.show()
                self.pixels.fill(dimColor)
                time.sleep(self.delay)

        self.next()

    async def alternate(self, color=None):
        while self.run:
            if not color: color = self.defaultColor
            color = tuple([x*self.brightness for x in color])

            dimColor = tuple([x//2 for x in color])

            for i in range(self.numPixels):
                if i % 2 == 0:
                    self.pixels[i] = color
                else:
                    self.pixels[i] = dimColor
            time.sleep(self.delay)
            self.pixels.show()

            for i in range(self.numPixels):
                if i % 2 != 0:
                    self.pixels[i] = color
                else:
                    self.pixels[i] = dimColor
            time.sleep(self.delay)
            self.pixels.show()

        self.next()

    async def setBrightness(self, brightness=1):
        self.brightness = self.brightness

if __name__ == "__main__":
    with LedStrip() as led:
        try:
            await led.virginLights()
        except KeyboardInterrupt:
            print("Ending")

