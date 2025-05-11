import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

# Load data
data = []
with open("output.txt", "r") as file:
    for line in file:
        x, y = map(float, line.strip().split())
        data.append((x, y))

df = pd.DataFrame(data, columns=["X", "Y"])
df["Y"] = df["Y"].astype(float)
df = df[df["Y"] > 0.005]  # Removes zero or nearly-zero times


# Group and aggregate by input size
summary = df.groupby("X").agg(
    best_case=('Y', lambda y: np.percentile(y, 10)),  # Ignore near-zero
    average_case=('Y', 'mean'),
    worst_case=('Y', lambda y: np.percentile(y, 90))
).reset_index()


# Plotting
plt.figure(figsize=(20,10))
plt.ylim(-0.0001, 0.2)
sns.scatterplot(data=df, x="X", y="Y", alpha=0.3, label="Measured Times")

# Plot best, average, and worst case lines
plt.plot(summary["X"], summary["best_case"], label="Best Case (min)", linestyle="--", color="green", marker='o')
plt.plot(summary["X"], summary["average_case"], label="Average Case (mean)", linestyle="-", color="orange", marker='o')
plt.plot(summary["X"], summary["worst_case"], label="Worst Case (max)", linestyle="--", color="red", marker='o')

# Labels and style
plt.xlabel("Array Size", fontsize=12, style='italic')
plt.ylabel("Elapsed Time (s)", fontsize=12, style='italic')
plt.title("Empirical Time Complexity Analysis", fontsize=14)
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
