import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_csv("test.csv", header= None)
sns.lineplot(data=df)
plt.show()