import unittest
import unittest.mock as mock
from unittest.mock import patch
import time
from gpio import LedStrip, Notifier

class TestNotifier(unittest.TestCase):
    
    def testGetActiveNotifier(self):
        notifier = Notifier.getActiveNotifier()

        self.assertIsInstance(notifier, Notifier)
        self.assertIs(notifier, Notifier.getActiveNotifier())
        
        with notifier:
            self.assertEqual(gpio.getmode(), gpio.BOARD)
            self.assertEqual(gpio.input(notifier.pins), 0)

        self.assertEqual(gpio.input(notifier.pins), 0)

    def testError(self):
        notifier = Notifier.getActiveNotifier()

        with notifier:
            notifier.error()

    def testNewReq(self):
        notifier = Notifier.getActiveNotifier()

        with notifier:
            notifier.newReq()

    def testRejectReq(self):
        notifier = Notifier.getActiveNotifier()

        with notifier:
            notifier.rejectReq()

    def testBadOptions(self):
        notifier = Notifier.getActiveNotifier()

        with notifier:
            notifier.badOptions()

class TestLedStrip(unittest.TestCase):

    @patch.object(Notifier, 'error') 
    def testContext(self, mock_err):
        ledStrip = LedStrip()
        with self.assertRaises(Exception):
            with ledStrip:
                self.assertIsNotNone(ledStrip.pixels)
                raise Exception("Test Exit print")

        self.assertTrue(mock_err.called)

    def testVirginLights(self):
        ledStrip = LedStrip()

        with ledStrip:
            ledStrip.virginLights(5)

    def testNightLights(self):
        ledStrip = LedStrip()

        with ledStrip:
            ledStrip.nightLights()
            ledStrip.nightLights((150, 150, 40))

    def testFlow(self):
        ledStrip = LedStrip()

        with ledStrip:
            ledStrip.flow()
            ledStrip.flow((150, 150, 40))

    def testCollapse(self):
        ledStrip = LedStrip()

        with ledStrip:
            ledStrip.collapse()
            ledStrip.collapse((150, 150, 40))

    def testAlternate(self):
        ledStrip = LedStrip()

        with ledStrip:
            ledStrip.alternate()
            ledStrip.alternate((150, 150, 40))

    def testSetBrightness(self):
        ledStrip = LedStrip()

        with ledStrip:
            ledStrip.light() # Make them white
            
            ledStrip.setBrightness(brightness = 0.2)
            

            
if __name__ == "__main__":
    unittest.main()

