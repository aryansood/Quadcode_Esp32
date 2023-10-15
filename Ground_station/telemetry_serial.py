import numpy as np
import serial
import threading
import time


ser = serial.Serial()
ser.baudrate = 115200
ser.port = 'COM1'
ser.open()

class Serial_Read():
    def ciao():
        a = 0
