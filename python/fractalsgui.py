#!/usr/bin/python

# TODO:
#     generic IFS

import matplotlib
# use the Tk backend
matplotlib.use('TkAgg')
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from mpl_toolkits.mplot3d import Axes3D
import os
import subprocess
import sys
import time
import Tkinter as tk

# Map fractals to odeint function names
fractals = {
    "Barnsley's fern"       : 'barnsley',
    #"Cantor set"            : 'cantor',
    "Heighway's dragon"     : 'heighway',
    "Koch curve"            : 'koch_curve',
    "Maple leaf"            : 'maple_leaf',
    "Sierpinski's triangle" : 'sierpinski',
}

class OdeIntGui(object):
    def __init__(self, master, program_path):
        self.program_path = program_path

        #---- Main frame
        self.frame = tk.Frame(master)
        self.frame.pack(expand=True, fill=tk.BOTH)
        #----
        #---- Subframes
        self.frame_menus = tk.Frame(self.frame)
        self.frame_entries = tk.Frame(self.frame)
        self.frame_canvas = tk.Frame(self.frame)
        self.frame_buttons = tk.Frame(self.frame)

        self.frame_menus.pack(expand=True, fill=tk.BOTH, padx=8)
        self.frame_entries.pack(expand=True, fill=tk.BOTH, padx=8)
        self.frame_canvas.pack(expand=True, fill=tk.BOTH, padx=8)
        self.frame_buttons.pack(expand=True, fill=tk.BOTH, padx=8, pady=8)
        #----
        #---- String variables
        self.fractal = tk.StringVar(self.frame_menus)
        # SET DEFAULTS HERE
        self.fractal.set("Barnsley's fern")
        self.prev_fractal = self.fractal.get()
        #----
        #---- Integer variables
        self.niter = tk.IntVar(self.frame_entries)
        #----
        #---- Menu subframe
        self.label_fractals = tk.Label(self.frame_menus, text="Fractal:")
        self.menu_fractals = tk.OptionMenu(self.frame_menus, self.fractal,
                                           *fractals.keys(),
                                           command=self.menu_onclick)
        self.label_niter = tk.Label(self.frame_menus,
                                    text="Number of iterations:")
        self.entry_niter = tk.Entry(self.frame_menus, textvariable=self.niter,
                                    width=5)

        self.label_fractals.pack(expand=True, fill=tk.BOTH, side=tk.LEFT)
        self.menu_fractals.pack(expand=True, fill=tk.BOTH, side=tk.LEFT)
        self.label_niter.pack(expand=True, fill=tk.BOTH, side=tk.LEFT)
        self.entry_niter.pack(expand=True, fill=tk.BOTH, side=tk.LEFT)
        #----
        #---- Canvas subframe
        self.figure = Figure(figsize=(7.8, 4.5))
        self.canvas = FigureCanvasTkAgg(self.figure, self.frame_canvas)

        self.canvas.get_tk_widget().pack(expand=True, fill=tk.BOTH)

        self.toolbar = NavigationToolbar2TkAgg(self.canvas, self.frame_canvas)
        self.toolbar.update()
        self.canvas._tkcanvas.pack(expand=True, fill=tk.BOTH)
        #----
        #---- Button subframe
        self.button_plot = tk.Button(self.frame_buttons, text="Plot",
                                     command=self.plot)
        self.button_clear = tk.Button(self.frame_buttons, text="Clear",
                                      command=self.clear_figure)
        self.button_quit = tk.Button(self.frame_buttons, text="Quit",
                                     command=self.frame.quit)
        
        self.button_plot.pack(expand=True, fill=tk.BOTH, side=tk.LEFT)
        self.button_clear.pack(expand=True, fill=tk.BOTH, side=tk.LEFT)
        self.button_quit.pack(expand=True, fill=tk.BOTH, side=tk.LEFT)
        #----
    
    def menu_onclick(self, event):
        print "%s with %s iterations" % (self.fractal.get(), self.niter.get())

        self.clear_figure()
        prev_fractal = self.fractal.get()

    def plot(self):
        cmd = ("%s -f %s -n %s" % (self.program_path,
                                   fractals[self.fractal.get()],
                                   self.niter.get()))
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
    """Centers the window on the screen."""
    win.update_idletasks()
    width = win.winfo_width()
    height = win.winfo_height()
    x = (win.winfo_screenwidth() // 2) - (width // 2)
    y = (win.winfo_screenheight() // 2) - (height // 2)
    win.geometry('{}x{}+{}+{}'.format(width, height, x, y))

def print_usage():
    print "python fractalsgui.py [program_path]"

def main():
    if len(sys.argv) == 1:
        print "Program path not given; defaulting to ../src/draw"
        program_path = "../src/draw"
    elif len(sys.argv) == 2:
        program_path = sys.argv[1]
        print "Using " + program_path
    else:
        print_usage()
        sys.exit(0)

    if not os.path.isfile(program_path):
        raise ValueError("File " + program_path + " does not exist")
    
    root = tk.Tk()
    root.geometry('640x480')
    root.title("fractals GUI")
    #center(root)
    odeintgui = OdeIntGui(root, program_path)
    root.mainloop()

if __name__ == '__main__':
    main()
