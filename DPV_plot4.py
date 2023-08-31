import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_csv("DPV_test(2).csv", names= ["x","y"])
sns.lineplot(data=df,x="x",y="y")
plt.show()