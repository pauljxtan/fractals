#!/usr/bin/env python

import matplotlib.pyplot as plt
import sys

def main():
    # Set the frameskip (plot every n-th frame)
    frame_skip = int(sys.argv[1])

    # Enable interactive mode
    plt.ion()

    # Set up figure
    fig = plt.figure()
    sp = fig.add_subplot(111)
    
    frame_count = 0
    while True:
        line = sys.stdin.readline()
        
        # Check if end of simulation
        if line == '':
            break

        frame_count += 1
        # Check if frame should be skipped
        if frame_count % frame_skip != 0:
            continue

        # Process data
        data = map(float, line.strip().split(" "))

        # Update plot
        sp.set_title("t = %d" % frame_count)
        sp.scatter(data[0], data[1], s=1)

        # Save to file
        #plt.savefig("./frames/%07d.png" % framecount)

        plt.draw()

if __name__ == "__main__":
    sys.exit(main())
