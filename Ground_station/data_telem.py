import tkinter as tk
from tkinter import ttk
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

plt.style.use('dark_background')

class DynamicPlot(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title("Dynamic Plot in Tkinter + Matplotlib")

        # Create a matplotlib figure
        self.fig, self.ax = plt.subplots(figsize=(5, 4))

        self.canvas = FigureCanvasTkAgg(self.fig, self)
        self.canvas.draw()
        self.canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)

        # Initial plot data
        self.x = np.linspace(0, 2 * np.pi, 100)
        self.y = np.sin(self.x)
        self.line, = self.ax.plot(self.x, self.y, "r-")

        # Start the update process
        self.update_plot()

    def update_plot(self):
        # Shift sine wave
        self.y = np.roll(self.y, -1)
        self.line.set_ydata(self.y)
        self.canvas.draw_idle()

        # Schedule the next update
        self.after(10, self.update_plot)  # Update every 100ms

if __name__ == "__main__":
    app = DynamicPlot()
    app.mainloop()
