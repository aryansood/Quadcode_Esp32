import sys
import numpy as np
import pyqtgraph as pg
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget
from PyQt5.QtCore import QTimer, QThread, pyqtSignal


class Worker(QThread):
    new_plot_signal = pyqtSignal()

    def run(self):
        while True:
            user_input = input("Enter a command: ")
            if user_input.lower() == 'hello':
                self.new_plot_signal.emit()


class SineWavePlotter(QMainWindow):
    def __init__(self):
        super().__init__()

        self.plot_widget = pg.PlotWidget()
        self.setCentralWidget(self.plot_widget)

        self.x = np.linspace(0, 6 * np.pi, 1000)
        self.y = np.sin(self.x)

        self.curve = self.plot_widget.plot(self.x, self.y, pen='g')

        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_plot)
        self.timer.start(50)  # Update every 50 milliseconds

        self.setWindowTitle('Animated Sine Wave')

    def update_plot(self):
        self.x += 0.1
        self.y = np.sin(self.x)
        self.curve.setData(self.x, self.y)


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)
        self.layout = QVBoxLayout(self.central_widget)

        self.sine_wave_plotter_list = []

        self.terminal_listener = Worker()
        self.terminal_listener.new_plot_signal.connect(self.create_new_plot)
        self.terminal_listener.start()

    def create_new_plot(self):
        new_plotter = SineWavePlotter()
        new_plotter.show()
        self.sine_wave_plotter_list.append(new_plotter)


def main():
    app = QApplication(sys.argv)
    main_window = MainWindow()
    main_window.show()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
