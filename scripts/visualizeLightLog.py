import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

df = pd.read_csv('data/lightLog.csv')
cm = plt.cm.get_cmap('RdYlBu')

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

for i in range(df.shape[0]):
	row = df.iloc[i]
	ax.scatter(row.loc['x'], row.loc[' y'], row.loc[' light_intensity'], cmap=cm)
plt.colorbar(sc)

fig.savefig("hei", bbox_inches='tight')

plt.show()