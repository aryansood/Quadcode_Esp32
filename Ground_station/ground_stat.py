import sys
import numpy as np
import pyqtgraph as pg
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget
from PyQt5.QtCore import QTimer, QThread, pyqtSignal

comm_list = ["Communication startup","Control Center","Calibration setup","Attitude 3d","Sensor plot","State values"]