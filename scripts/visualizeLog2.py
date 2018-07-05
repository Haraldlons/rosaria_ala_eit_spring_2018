import pandas as pd
import matplotlib.pyplot as plt
import numpy as np 
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

df = pd.read_csv('data/lightdata3.csv', parse_dates=True)
cmap = cm.get_cmap('RdYlBu') # Colour map (there are many others)

threedee = plt.figure().gca(projection='3d')
threedee.scatter(df['x'], df[' y'], df[' light_intensity'],c=df[' light_intensity'], cmap=cmap)
threedee.set_xlabel("x")
threedee.set_ylabel("y")
threedee.set_zlabel("Light Intensity")
plt.show()