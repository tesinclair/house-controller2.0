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
            - setBrightness: changes the brightness to value brightness unless isdegree, in which case it alters brightness by degree

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
    
    def __new__(cls):
        if cls.activeNotifier:
            utils.Logger.log("", "Too Many Notifiers", "[NONE]")
            return None
        cls.activeNotifier = super().__new__(cls)
        return cls.activeNotifier

    def __init__(self):
        self.nimPins = 10
        self.pins = [17, 18, 27, 23, 22, 24, 5, 25, 6, 12]
        # The way the led is set up requires this
        self.on = gpio.LOW
        self.off = gpio.HIGH 
        self.delay = 0.2
        self.iterations = 5

    def __enter__(self):
        if gpio.getmode != gpio.BOARD:
            gpio.setmode(gpio.BOARD)
        gpio.setup(self.pins, gpio.OUT)
        gpio.output(self.pins, self.off)
        return self

    def __exit__(self, exType, exVal, traceback):
        if exType:
            utils.Logger.log(exType, exVal, traceback)

        gpio.output(self.pins, self.off)
        gpio.setup(self.pins, gpio.IN)
        gpio.cleanup()

    @classmethod
    def getActiveNotifier(cls):
        if cls.activeNotifier:
            return cls.activeNotifier
        else:
            return cls.__new__(cls)
    
    def error(self):
        for _ in range(self.iterations):
            gpio.output(self.pins, self.on)
            time.sleep(self.delay)
            gpio.output(self.pins, self.off)
            time.sleep(self.delay)

    def newReq(self):
        for _ in range(self.iterations):
            for pin in self.pins:
                gpio.output(pin, self.on)
                time.sleep(self.delay)
                gpio.output(pin, self.off)

    def rejectedReq(self):
        for _ in range(self.iterations):
            for i in range(len(self.pins)/2 - 1): 
                pinL = self.pins[i]
                pinR = self.pins[-(1 + i)] # Start from right at [-1]

                gpio.output(pinL, self.on)
                gpio.output(pinR, self.on)
                time.sleep(self.delay)
                gpio.output(pinL, self.off)
                gpio.output(pinR, self.off)


class LedStrip():
    def __init__(self):
        self.numPixels = 100
        self.pixels = None
        self.delay = 0.2
        self.red = (255, 0, 0)
        self.green = (0, 255, 0)
        self.blue = (0, 0, 255)
        self.purple = (211, 50, 240)
        self.blank = (0, 0, 0)
        self.white = (255, 255, 255)
        self.defaultColor = self.purple

    def __enter__(self):
        self.pixels = neopixel.NeoPixel(board.D10, self.numPixels)
        self.pixels.brightness = 0.8
        self.pixels.fill(self.blank)
        self.pixels.show()
        return self

    def __exit__(self, exType, exVal, traceback):
        if exType:
            with Notifier.getActiveNotifier() as err:
                err.error()
            try:
                utils.Logger.log(exType, exVal, traceback)
            except:
                with Notifier.getActveNotifier() as err:
                    err.error()

        self.pixels.brightness = 0
        self.pixels.fill(self.blank)
        self.pixels.show()
        self.pixels.deinit()

    def virginLights(self, offset):
        redL = (0 + offset) % self.numPixels # prevent overflow
        redR = ((self.numPixels//3 + offset) - 1) % self.numPixels
        greenL = (self.numPixels//3 + offset) % self.numPixels
        greenR = (((self.numPixels * 2)//3 + offset) - 1) % self.numPixels
        blueL = ((self.numPixels * 2)//3 + offset) % self.numPixels
        blueR = ((self.numPixels + offset) - 1) % self.numPixels

        self.pixels[redL:redR].fill(self.red)
        self.pixels[greenL:greenR].fill(self.green)
        self.pixels[blueL:blueR].fill(self.blue)
        self.pixels.show()
        time.sleep(self.delay)
    
    def nightLights(self, color=None):
        if not color: color = self.defaultColor
        self.pixels.fill(color)
        self.pixels.show()

    def flow(self, color=None):
        if not color: color = self.defaultColor # Generally I hate inline if statements, but this is fine
        
        self.pixels.fill(color)

        for i in range(self.numPixels) - 1:
            tempBrightness = self.pixels.brightness
            self.pixels.brightness = tempBrightness/2

            self.pixels[i].brightness = tempBrightness
            self.pixels.show()
            time.sleep(self.delay)

    def collapse(self, color=None):
        if not color: color = self.defaultColor
        
        self.pixels.fill(color)
        for i in range(self.numPixels)/2 - 1:
            tempBrightness = self.pixels.brightness
            self.pixels.brightness = tempBrightness/2

            pixelL = self.pixels[i]
            pixelR = self.pixels[-(1 + i)]
            pixelL.brightness = tempBrightness
            pixelR.brightness = tempBrightness
            self.pixels.show()
            time.sleep(self.delay)


    def alternate(self, color=None):
        if not color: color = self.defaultColor

        self.pixels.fill(color)

        tempBrightness = self.pixels.brightness
        self.pixels.brightness = tempBrightness/2
        
        for i in range(self.numPixels):
            if i % 2 == 0:
                self.pixels[i].brightness = tempBrightness
            else:
                self.pixels[i].brightness = tempBrightness/2
        self.pixels.show()
        time.sleep(self.delay/2)

        for i in range(self.numPixels):
            if i % 2 != 0:
                self.pixels[i].brightness = tempBrightness
            else:
                self.pixels[i].brightness = tempBrightness/2
        self.pixels.show()
        time.sleep(self.dealy/2)

    def setBrightness(self, brightness=0.8, isDegree=False, degree=0.1):
        if isDegree:
            self.pixels.brightness = self.pixels.brightness + degree
        else:
            self.pixels.brightness = brightness

def usage():
    pass 

def main():
    pass

if __name__ == "__main__":
    main()

