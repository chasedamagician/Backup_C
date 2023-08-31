import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_csv("test2.csv", header= None)
sns.lineplot(data=df)
plt.show()