import numpy as np
import matplotlib.pyplot as plt
from io import StringIO

# Read file
with open("./build/data.csv", "r") as f:
    raw_data = f.read()

# Split by object
object_chunks = [chunk.strip() for chunk in raw_data.split("*") if chunk.strip()]
print(object_chunks)

parsed_objects = []

for i, chunk in enumerate(object_chunks):
    lines = [line for line in chunk.splitlines() if line.strip(',').strip()]
    if not lines:
        print(f"Object {i+1} has no valid lines.")
        continue

    try:
        # Parse the data
        data = np.genfromtxt(StringIO("\n".join(lines)), delimiter=",", filling_values=np.nan)

        # Check for abnormal or overflow values
        if np.any(np.abs(data) > 1e10):
            print(f"Warning: Object {i+1} contains unusually large values, replacing with NaN.")
            data[np.abs(data) > 1e10] = np.nan

        # If data has only one row, reshape it
        if data.ndim == 1:
            data = np.expand_dims(data, axis=0)

        # Ensure the object has enough rows
        if data.shape[0] >= 2:
            parsed_objects.append(data)
            print(f"Parsed Object {i+1}: shape {data.shape}")
        else:
            print(f"Object {i+1} skipped — not enough rows.")
    except Exception as e:
        print(f"Error parsing Object {i+1}: {e}")

# Plotting
if not parsed_objects:
    print("No valid object data parsed.")
else:
    plt.figure(figsize=(10, 8))

    for idx, data in enumerate(parsed_objects):
        x = data[0, :]
        y = data[1, :]
        valid_indices = np.isfinite(x) & np.isfinite(y)
        x_valid = x[valid_indices]
        y_valid = y[valid_indices]

        plt.scatter(x_valid, y_valid, label=f"Object {idx + 1}", s=10)  # Changed to scatter

    plt.title("2D Trajectories of All Objects (Scatter Plot)")
    plt.xlabel("X Position")
    plt.ylabel("Y Position")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("all_objects_one_scatter_plot.png")
    plt.show()