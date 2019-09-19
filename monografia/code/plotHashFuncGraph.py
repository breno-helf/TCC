import numpy as np
import matplotlib.pyplot as plt
import random as random
from matplotlib.patches import Patch
from matplotlib.lines import Line2D


fig, ax = plt.subplots()
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.1,
                 box.width, box.height * 0.9])


data = open('1031Results.txt', 'r').readlines()


fileToColor = {'data/dic_Shakespeare.txt': 'bo',
               'data/dic_common_words.txt': 'g+',
               'data/dic_fr.txt': 'g^',
               'data/dic_ip.txt': 'm+',
               'data/dic_numbers.txt': 'm^',
               'data/dic_postfix.txt': 'c^',
               'data/dic_prefix.txt': 'c+',
               'data/dic_variables.txt': 'yo',
               'data/dic_win32.txt': 'ko'}

axes = plt.gca()
axes.set_ylim([0,6.5])
axes.set_xlim([0,10])

# Plotting horizontal lines
plt.plot(np.linspace(0, 25, 200), [1.05] * 200, 'r--')
plt.plot(np.linspace(0, 25, 200), [0.95] * 200, 'r--')
plt.plot(np.linspace(0, 25, 200), [6.00] * 200, 'r--')

curFile = ''
curColor = ''
curX = .5
for line in data:
    if (line[-5:-1] == '.txt'):
        curFile = line[:-1]
        curColor = fileToColor[curFile]
        curX = .5
        continue
    
    func, y = tuple(line.split())
    plt.plot(curX, min(float(y), 6 + random.random() / 2), curColor) 
    curX += 1
plt.show()
