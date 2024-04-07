import neopixel
import board
import time

p = neopixel.NeoPixel(board.D18, 100, pixel_order=neopixel.RGB)
for i in range(100):
    offset = i
    redL = (0 + offset) % 100 # prevent overflow
    redR = ((100//3 + offset)) % 100
    greenL = (100//3 + offset) % 100
    greenR = (((100 * 2)//3 + offset)) % 100
    blueL = ((100 * 2)//3 + offset) % 100
    blueR = ((100 + offset))

    for i in range(100):
        if i >=redL and i < redR:
            p[i] = (255, 0, 0)

        if i >= greenL and i < greenR:
            p[i] = (0, 255, 0)

        if i >= blueL and i < blueR:
            p[i] = (0, 0, 255)
    p.show()
p.deinit()
