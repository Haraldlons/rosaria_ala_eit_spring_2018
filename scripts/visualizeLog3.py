import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

df = pd.read_csv('data/lightLog.csv')
cm = plt.get_cmap("RdYlGn")

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

col = np.arange(30)
for i in range(df.shape[0]):
	row = df.iloc[i]
	ax.scatter(row.loc['x'], row.loc[' y'], row.loc[' light_intensity'], cmap=cm)
plt.colorbar(sc)

fig.savefig("hei", bbox_inches='tight')

plt.show()

def scatter3d(x,y,z, cs, colorsMap='jet'):
    cm = plt.get_cmap(colorsMap)
    
    cNorm = matplotlib.colors.Normalize(vmin=min(cs), vmax=max(cs))
    scalarMap = cmx.ScalarMappable(norm=cNorm, cmap=cm)
    fig = plt.figure()
    ax = Axes3D(fig)
    ax.scatter(x, y, z, c=scalarMap.to_rgba(cs))
    scalarMap.set_array(cs)
    fig.colorbar(scalarMap)
    plt.show()

