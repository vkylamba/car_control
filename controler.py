import serial
import time
import sys

if __name__ == '__main__':
    if len(sys.argv) != 2:
        sys.exit("usage: controller.py device")
    device = sys.argv[1]
    print("Device is {}".format(device))
    dev = serial.Serial(device, timeout=1.0, baudrate=9600)
    time.sleep(3)
    key = None

    dev.write("S")
    time.sleep(0.5)
    dev.write("f")
    time.sleep(0.5)
    dev.write("b")
    time.sleep(0.5)
    dev.write("l")
    time.sleep(0.5)
    dev.write("r")
    time.sleep(0.5)
    dev.write("s")
