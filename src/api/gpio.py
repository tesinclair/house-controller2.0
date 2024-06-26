import board
import neopixel
import RPi.GPIO as gpio
import time
import sys
import queue
import random
import ast

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

    - Notifier: This is a 10 pin led that will be used for errors and logging // Currently Not used
        Methods:
            - __new__: ensure that only one instance is active at a time. Set the activeNotifier
            - getActiveNotifier: returns the currently active notifier, if none exist, one is created
            - error: Will flash 5 times
            - newReq: Will flow from left to right 5 times
            - rejectedReq: Will collapse 5 times

For reference, I am using camelCase not snake_case simply because I don't like snake_case

"""

class LedStrip():
    instance=None

    def __new__(cls, q, delay=0.01):
        if cls.instance:
            return cls.instance
        else:
            cls.instance = super().__new__(cls)
            return cls.instance

    def __init__(self, q, delay=0.01):
        self.numPixels = 100
        self.delay = delay
        self.brightness = 1
        self.queue = q
        self.pixels = None

        # -=-=-=- All Pixels are RBG not RGB -=-=-=-

        self.red = (255, 0, 0)
        self.green = (0, 0, 255)
        self.blue = (0, 255, 0)
        self.purple = (211, 240, 50)
        self.blank = (0, 0, 0)
        self.white = (255, 255, 255)
        self.palleteA = [(189, 145, 147), (191, 71, 11), (198, 67, 33), (110, 209, 180), (108, 237, 190)]
        self.palleteB = [(255, 255, 255), (132, 198, 220), (165, 214, 255), (255, 158, 166), (255, 107, 104)]
        self.palleteC = [(3, 107, 26), (3, 96, 56), (8, 167, 124), (0, 133, 67), (5, 220, 178)]
        self.palleteD = [(135, 88, 0), (164, 63, 48), (194, 174, 140), (208, 160, 171), (117, 171, 154)]
        self.colors = [self.palleteA, self.palleteB, self.palleteC, self.palleteD]


    def __enter__(self):
        self.pixels = neopixel.NeoPixel(board.D18, self.numPixels, auto_write=False)
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

    def check(self):
        return self.queue.empty()

    def next(self, func, color = None, pallete=None):
        code, arg = self.queue.get().split(":")

        if code == "func":
            pallete = random.choice(self.colors)

            if arg.startswith("colorwheel"):
                arg, arg1 = arg.split("#")
                arg1 = ast.literal_eval(arg1)
                arg1 = (arg1[0], arg1[2], arg1[1])
            match arg:
                case "flow":
                    self.flow(pallete)
                case "alternate":
                    self.alternate(pallete)
                case "virginLights":
                    self.virginLights()
                case "collapse":
                    self.collapse(pallete)
                case "nightLight":
                    self.light(self.purple)
                case "white":
                    self.light()
                case "red":
                    self.light(self.red)
                case "blue":
                    self.light(self.blue)
                case "green":
                    self.light(self.green)
                case "pulse":
                    self.pulse(pallete)
                case "colorwheel":
                    self.light(arg1)
                case "wait":
                    # Used to reset recursion.
                    return True
                case "quit":
                    return False

        elif code == "brightness":
            arg = float(arg)
            arg = arg / 100
            if arg == 0:
                arg = 0.005
            self.setBrightness(arg)

            if color:
                func(color)
            elif pallete:
                func(pallete)
            else:
                func()

    def light(self, color=None):
        if not color: color = self.white
        self.pixels.fill(tuple(round(x*self.brightness) for x in color))
        self.pixels.show()

        while self.check():
            pass

        self.next(self.light, color)

    def pulse(self, pallete):
        palleteIndex = 0
        while self.check():
            palleteIndex = palleteIndex % len(pallete)
            color = pallete[palleteIndex]
            i = 0

            while i < self.brightness:
                self.pixels.fill(tuple(round(x*i) for x in color))
                self.pixels.show()
                i += 0.01
                time.sleep(self.delay)

            while i > 0:
                self.pixels.fill(tuple(round(x*i) for x in color))
                self.pixels.show()
                i -= 0.01
                time.sleep(self.delay)

            palleteIndex += 1
            
        
        self.next(self.pulse, pallete=pallete)

    def virginLights(self):
        i = 0
        while self.check():
            i = i % 100
            offset = i
            redL = 0 + offset
            redR = (self.numPixels//3 + offset) - 1
            greenL = self.numPixels//3 + offset
            greenR = ((self.numPixels * 2)//3 + offset) - 1
            blueL = (self.numPixels * 2)//3 + offset
            blueR = (self.numPixels + offset) - 1

            for j in range(redL, redR):
                temp = j % 100
                self.pixels[temp] = tuple([round(x*self.brightness) for x in self.red])
            for j in range(greenL, greenR):
                temp = j % 100
                self.pixels[temp] = tuple([round(x*self.brightness) for x in self.green])
            for j in range(blueL, blueR):
                temp = j % 100
                self.pixels[temp] = tuple([round(x*self.brightness) for x in self.blue])

            self.pixels.show()
            time.sleep(self.delay)

            i += 1

        self.next(self.virginLights)

    def flow(self, pallete):
        self.pixels.fill(self.blank)
        i = 0
        palleteIndex = 0
        while self.check():
            i = i % self.numPixels
            palleteIndex = palleteIndex % len(pallete)
            color = pallete[palleteIndex]
            color = tuple([round(x*self.brightness) for x in color])

            self.pixels[i] = color
            self.pixels.show()
            self.pixels.fill(self.blank)
            time.sleep(self.delay)
            i += 1
            palleteIndex += 1

        self.next(self.flow, pallete)

    def collapse(self, pallete):
        i = 0
        palleteIndex = 0
        while self.check():
            i = i % (self.numPixels//2)
            palleteIndex = palleteIndex % len(pallete)
            color = pallete[palleteIndex]
            color = tuple([round(x*self.brightness) for x in color])

            self.pixels[i] = color
            self.pixels[-(1 + i)] = color

            self.pixels.show()
            self.pixels.fill(self.blank)
            time.sleep(self.delay)
            i += 1
            palleteIndex += 1

        self.next(self.collapse, pallete)

    def alternate(self, pallete):
        palleteIndex = 0
        while self.check():
            palleteIndex = palleteIndex % len(pallete)
            color = pallete[palleteIndex]
            color = tuple([round(x*self.brightness) for x in color])
            for i in range(self.numPixels):
                if i % 2 == 0:
                    self.pixels[i] = color
                else:
                    self.pixels[i] = self.blank
            time.sleep(self.delay*10)
            self.pixels.show()

            for i in range(self.numPixels):
                if i % 2 != 0:
                    self.pixels[i] = color
                else:
                    self.pixels[i] = self.blank
            time.sleep(self.delay*10)
            self.pixels.show()

            palleteIndex += 1

        self.next(self.alternate, pallete)

    def wait(self):
        self.pixels.fill(self.blank)
        self.pixels.show()

        while self.check():
            pass

        self.next(self.wait)

    def setBrightness(self, brightness):
        self.brightness = brightness

# UNUSED

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


