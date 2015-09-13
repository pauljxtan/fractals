#!/usr/bin/python

# TODO:
#     interactive plot (zoom in/out, etc.)
#     generic IFS

import matplotlib
# use the Tk backend
matplotlib.use('TkAgg')
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from mpl_toolkits.mplot3d import Axes3D
import subprocess
import time

from Tkinter import (Button, DoubleVar, END, Entry, Frame, IntVar, Label,
                     OptionMenu, StringVar, Tk, W)

fractals = {
    "Barnsley's fern"       : 'barnsley',
    "Cantor set"            : 'cantor',
    "Heighway's dragon"     : 'heighway',
    "Koch curve"            : 'koch_curve',
    "Maple leaf"            : 'maple_leaf',
    "Sierpinski's triangle" : 'sierpinski',
}

class OdeIntGui(object):
    def __init__(self, master):
        self.frame = Frame(master)
        self.frame.grid()

        #--- Subframes
        self.frame_menus = Frame(self.frame)
        self.frame_entries = Frame(self.frame)
        self.frame_canvas = Frame(self.frame)
        self.frame_buttons = Frame(self.frame)

        self.frame_menus.grid(row=0)
        self.frame_entries.grid(row=1)
        self.frame_canvas.grid(row=2)
        self.frame_buttons.grid(row=3)
        #---

        #--- String variables
        self.fractal = StringVar(self.frame_menus)
        # SET DEFAULTS HERE
        self.fractal.set("Barnsley's fern")
        self.prev_fractal = self.fractal.get()
        #---

        #--- Integer variables
        self.niter = IntVar(self.frame_entries)
        #---

        #--- Menu subframe
        self.label_fractals = Label(self.frame_menus, text="Fractal:")
        self.menu_fractals = OptionMenu(self.frame_menus, self.fractal,
                                        *fractals.keys(),
                                        command=self.menu_onclick)
        self.label_niter = Label(self.frame_menus,
                                 text="Number of iterations:")
        self.entry_niter = Entry(self.frame_menus, textvariable=self.niter,
                                 width=5)

        self.label_fractals.grid(row=0, column=0)
        self.menu_fractals.grid(row=0, column=1)
        self.label_niter.grid(row=0, column=2)
        self.entry_niter.grid(row=0, column=3)
        #---

        #--- Canvas subframe
        self.figure = Figure(figsize=(7.8, 4.9))
        self.canvas = FigureCanvasTkAgg(self.figure, master=self.frame_canvas)

        self.canvas.get_tk_widget().grid(row=2, column=0)
        #---

        #--- Button subframe
        self.button_plot = Button(self.frame_buttons, text="Plot",
                                  command=self.plot)
        self.button_clear = Button(self.frame_buttons, text="Clear",
                                   command=self.clear_figure)
        self.button_quit = Button(self.frame_buttons, text="Quit",
                                  command=self.frame.quit)
        
        self.button_plot.grid(row=3, column=0)
        self.button_clear.grid(row=3, column=1)
        self.button_quit.grid(row=3, column=2)
        #---
    
    def menu_onclick(self, event):
        print "%s with %s iterations" % (self.fractal.get(), self.niter.get())

        self.clear_figure()
        prev_fractal = self.fractal.get()

    def plot(self):
        cmd = ("../src/draw -f %s -n %s"
               % (fractals[self.fractal.get()], self.niter.get()))
        print cmd
        
        print "Computing..."

        t0 = time.clock()
        # heard "shell=True" might not be safe?
        integration = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
        t1 = time.clock()
        print "Finished in %.9f s" % (t1 - t0)
        
        print "Processing data..."
        integration_stdout = integration.communicate()[0]

        print "Plotting..."
        data = []
        for line in integration_stdout.split("\n"):
            if line != "":
                data.append(map(float, line.strip().split(" ")))
        arrays = zip(*data)
        self.graph = self.figure.add_subplot(111)
        self.graph.scatter(arrays[0], arrays[1], s=1)
        self.canvas.draw()

    def clear_figure(self):
        self.figure.clear()
        self.canvas.draw()

def center(win):
    win.update_idletasks()
    width = win.winfo_width()
    height = win.winfo_height()
    x = (win.winfo_screenwidth() // 2) - (width // 2)
    y = (win.winfo_screenheight() // 2) - (height // 2)
    win.geometry('{}x{}+{}+{}'.format(width, height, x, y))

def main():
    root = Tk()
    root.geometry('640x480')
    root.title("fractals GUI")
    center(root)
    odeintgui = OdeIntGui(root)
    root.mainloop()

if __name__ == '__main__':
    main()
