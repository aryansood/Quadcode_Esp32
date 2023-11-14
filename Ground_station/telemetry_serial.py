'''import numpy as np
import serial
import threading
import time

serial_port = ['/dev/ttyUSB0','/dev/ttyUSB1']
serial_baudrate = [9600, 115200]
ser = serial.Serial(serial_port[0],serial_baudrate[0],timeout=.1)
#ser.open()

try:
    while True:
        if ser.in_waiting > 0:
            received_data = ser.readline()
            print(f"Received: {received_data}")
except KeyboardInterrupt:
    pass

ser.close()'''
import serial
import time

# Define the serial port and baud rate
ser = serial.Serial('/dev/ttyUSB0', 115200)  # Replace 'COMX' with your actual serial port

# Function to send data over serial
def send_data(data):
    ser.write(data)

# Function to read data from serial
def read_data():
    return ser.readline().decode('utf-8').strip()


while True:
    received_data = read_data()
    if received_data:
        print("Received:", received_data)
    time.sleep(10)

