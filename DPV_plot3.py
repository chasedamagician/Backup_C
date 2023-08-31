import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_csv("test11.csv", names= ["x","y"])
sns.lineplot(data=df,x="x",y="y")
plt.show()