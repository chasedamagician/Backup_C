import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_csv("test25.csv", names= ["x","y"])
sns.scatterplot(data=df,x="x",y="y")
plt.show()