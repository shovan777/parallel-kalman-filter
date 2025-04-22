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

        # Check for abnormal or overflow values (e.g., values that are too large or too small)
        if np.any(np.abs(data) > 1e10):  # Replace with a threshold value suitable for your data
            print(f"Warning: Object {i+1} contains unusually large values, replacing with NaN.")
            data[np.abs(data) > 1e10] = np.nan  # Replace abnormal values with NaN

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
        # Exclude NaN values before plotting
        x = data[0, :]
        y = data[1, :]
        
        # Remove NaN values
        valid_indices = np.isfinite(x) & np.isfinite(y)
        x_valid = x[valid_indices]
        y_valid = y[valid_indices]
        
        plt.plot(x_valid, y_valid, label=f"Object {idx + 1}", linewidth=2)

    plt.title("2D Trajectories of All Objects")
    plt.xlabel("X Position")
    plt.ylabel("Y Position")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("all_objects_one_plot.png")
    plt.show()


# import numpy as np
# import matplotlib.pyplot as plt
# from io import StringIO

# # Read file
# with open("./build/data.csv", "r") as f:
#     raw_data = f.read()

# # Split by object
# object_chunks = [chunk.strip() for chunk in raw_data.split("*") if chunk.strip()]
# print(object_chunks)

# parsed_objects = []

# for i, chunk in enumerate(object_chunks):
#     lines = [line for line in chunk.splitlines() if line.strip(',').strip()]
#     if not lines:
#         print(f"Object {i+1} has no valid lines.")
#         continue

#     try:
#         data = np.genfromtxt(StringIO("\n".join(lines)), delimiter=",", filling_values=np.nan)
#         if data.ndim == 1:
#             data = np.expand_dims(data, axis=0)
#         if data.shape[0] >= 2:
#             parsed_objects.append(data)
#             print(f"Parsed Object {i+1}: shape {data.shape}")
#         else:
#             print(f"Object {i+1} skipped — not enough rows.")
#     except Exception as e:
#         print(f"Error parsing Object {i+1}: {e}")

# # Plotting
# if not parsed_objects:
#     print("No valid object data parsed.")
# else:
#     plt.figure(figsize=(10, 8))

#     for idx, data in enumerate(parsed_objects):
#         x = data[0, :]
#         y = data[1, :]
#         plt.plot(x, y, label=f"Object {idx + 1}", linewidth=2)

#     plt.title("2D Trajectories of All Objects")
#     plt.xlabel("X Position")
#     plt.ylabel("Y Position")
#     plt.legend()
#     plt.grid(True)
#     plt.tight_layout()
#     plt.savefig("all_objects_one_plot.png")
#     plt.show()


# import numpy as np
# import matplotlib.pyplot as plt
# from io import StringIO

# # Read and parse the file
# with open("./build/data.csv", "r") as f:
#     raw_data = f.read()

# # Split into object chunks
# object_chunks = [chunk.strip() for chunk in raw_data.split("*") if chunk.strip()]

# parsed_objects = []

# for chunk in object_chunks:
#     lines = [line for line in chunk.splitlines() if line.strip(',').strip()]
#     if not lines:
#         continue

#     try:
#         data = np.genfromtxt(StringIO("\n".join(lines)), delimiter=",", filling_values=np.nan)
#         if data.ndim == 1:
#             data = np.expand_dims(data, axis=0)
#         if data.shape[0] >= 2:
#             parsed_objects.append(data)
#     except Exception as e:
#         print(f"Error parsing chunk: {e}")

# # Plot all objects on the same figure
# if not parsed_objects:
#     print("No valid data found.")
# else:
#     plt.figure(figsize=(10, 8))

#     for idx, data in enumerate(parsed_objects):
#         x = data[0, :]
#         y = data[1, :]
#         plt.plot(x, y, label=f"Object {idx + 1}", linewidth=2)

#     plt.title("2D Trajectories of All Objects")
#     plt.xlabel("X Position")
#     plt.ylabel("Y Position")
#     plt.legend()
#     plt.grid(True)
#     plt.tight_layout()
#     plt.savefig("all_objects_one_plot.png")
#     plt.show()

# import numpy as np
# import matplotlib.pyplot as plt

# from io import StringIO

# # Read the file and split by '*'
# with open("./build/data.csv", "r") as f:
#     raw_data = f.read()

# # Split into chunks using '*' as the delimiter
# object_chunks = raw_data.split("*")

# # Filter out empty or whitespace-only chunks
# object_chunks = [chunk.strip() for chunk in object_chunks if chunk.strip()]

# # Store parsed data
# parsed_objects = []

# for chunk in object_chunks:
#     # Remove any lines that are just commas or whitespace
#     clean_lines = [line for line in chunk.splitlines() if line.strip(',').strip()]
    
#     if not clean_lines:
#         continue

#     try:
#         data = np.genfromtxt(StringIO("\n".join(clean_lines)), delimiter=",", filling_values=np.nan)
        
#         if data.ndim == 1:
#             data = np.expand_dims(data, axis=0)
        
#         if data.shape[0] >= 2:  # Must have at least two rows to extract X and Y
#             parsed_objects.append(data)
#         else:
#             print("Skipped a chunk due to insufficient rows.")

#     except Exception as e:
#         print(f"Error parsing chunk: {e}")

# # Plotting
# num_objects = len(parsed_objects)
# if num_objects == 0:
#     print("No valid object data found.")
# else:
#     cols = min(3, num_objects)
#     rows = (num_objects + cols - 1) // cols  # ceiling division for rows

#     fig, axs = plt.subplots(rows, cols, figsize=(5 * cols, 4 * rows), squeeze=False)

#     for idx, data in enumerate(parsed_objects):
#         row = idx // cols
#         col = idx % cols
#         ax = axs[row][col]

#         x_values = data[0, :]
#         y_values = data[1, :]

#         ax.plot(x_values, y_values, color='blue', linewidth=2, linestyle='dashed')
#         ax.set_title(f'Object {idx + 1}')
#         ax.set_xlabel('X position')
#         ax.set_ylabel('Y position')

#     # Hide unused subplots
#     for idx in range(num_objects, rows * cols):
#         fig.delaxes(axs[idx // cols][idx % cols])

#     fig.suptitle('2D Plots of State Vectors for All Objects', fontsize=16)
#     plt.tight_layout(rect=[0, 0.03, 1, 0.95])  # Adjust layout to fit title
#     plt.savefig('all_objects_subplot.png')
#     plt.show()

# import numpy as np
# import matplotlib.pyplot as plt
# from io import StringIO

# # Read and filter lines before the first star, skipping empty lines
# lines = []
# with open("./build/data.csv", "r") as f:
#     for line in f:
#         if '*' in line:  # Stop reading if a star is encountered
#             break
#         if line.strip():  # Only add non-empty lines
#             lines.append(line)

# # Join the lines and pass to StringIO to simulate a file-like object
# data_string = "".join(lines)

# # Remove any trailing empty lines (or lines that contain only commas)
# data_string = "\n".join([line for line in data_string.splitlines() if line.strip(',')])

# # Now, we will use np.genfromtxt to read the data and handle malformed rows
# try:
#     data = np.genfromtxt(StringIO(data_string), delimiter=",", skip_header=0, filling_values=np.nan)
    
#     # Check if the data loaded successfully and has multiple rows
#     if data.size > 0 and data.shape[0] > 1:  # Ensure there are multiple rows
#         print(f"Data loaded successfully with shape {data.shape}.")
        
#         # Extract the first two rows (not columns) of each state vector
#         x_values = data[0, :]  # First row (state vector 1)
#         print(x_values)
#         y_values = data[1, :]  # Second row (state vector 2)
#         print(y_values)
        
#         # Create a 2D scatter plot using the first two rows
#         plt.plot(x_values, y_values, color = 'blue', linewidth=3, linestyle='dashed')
        
#         # Label the axes and title
#         plt.xlabel('X position')
#         plt.ylabel('Y position')
#         plt.title('2D Scatter Plot of State Vector X and Y positions')
        
#         # Save the plot to a file (for example, in PNG format)
#         plt.savefig('state_vectors_scatterplot.png')  # You can specify a different path or format
#         print("Scatter plot saved as 'state_vectors_scatterplot.png'.")

#         # Optionally, display the plot
#         plt.show()

#     else:
#         print("Data doesn't have the expected number of rows.")
# except ValueError as e:
#     print("Error in loading data:", e)
#     print("Check if there are malformed rows or excessive columns.")





# import numpy as np
# import matplotlib.pyplot as plt
# from io import StringIO

# # Read and filter lines before the first star, skipping empty lines
# lines = []
# with open("./build/data.csv", "r") as f:
#     for line in f:
#         # Stop reading if a star is encountered
#         if '*' in line:
#             break
#         # Only add non-empty lines
#         if line.strip():  # Strip leading/trailing whitespace before checking
#             lines.append(line)

# # Ensure the lines are valid for numpy loading
# # Join the lines and pass to StringIO to simulate a file-like object
# data_string = "".join(lines)
# # Print the first few lines of the data for debugging
# print("First few lines of the data:", data_string[:200])

# # Use StringIO (Python 3) to read the data into numpy
# data = np.loadtxt(StringIO(data_string), delimiter=",")

# # You can now use `data` for plotting or other analysis
# # For example, plot the data if it's 2D (e.g., two columns)
# plt.plot(data[:, 0], data[:, 1])
# plt.xlabel('X-axis Label')
# plt.ylabel('Y-axis Label')
# plt.title('Plot of Object 1 Data')
# plt.show()


# import numpy as np
# import matplotlib.pyplot as plt
# from io import StringIO

# # Read and filter lines before the first star
# lines = []
# with open("./build/data.csv", "r") as f:
#     for line in f:
#         # Check if a star is found in the line
#         if '*' in line:
#             break  # Stop reading if a star is encountered
#         lines.append(line)

# # Use StringIO (Python 3) directly to read the data into numpy
# data = np.loadtxt(StringIO("".join(lines)), delimiter=",")

# # You can now use `data` for plotting or other analysis
# # For example, plot the data if it's 2D (e.g., two columns)
# plt.plot(data[:, 0], data[:, 1])
# plt.xlabel('X-axis Label')
# plt.ylabel('Y-axis Label')
# plt.title('Plot of Object 1 Data')
# plt.show()

# import numpy as np
# import pandas as pd
# import matplotlib.pyplot as plt

# # Save to a temporary string buffer
# from io import StringIO  # Correct import for Python 3

# # Read and filter lines before the *
# lines = []
# with open("./build/data.csv", "r") as f:
#     for line in f:
#         if '*' in line.strip():
#             break  # stop reading if a star is encountered
#         lines.append(line)

# # Use StringIO (Python 3) directly to read the data into numpy
# data = np.loadtxt(StringIO("".join(lines)), delimiter=",")

# # You can now use `data` for plotting or other analysis
# # For example, plot the data if it's 2D (e.g., two columns)
# plt.plot(data[:, 0], data[:, 1])
# plt.xlabel('X-axis Label')
# plt.ylabel('Y-axis Label')
# plt.title('Plot of Object 1 Data')
# plt.show()

# #import matplotlib.pyplot as plt
# import numpy as np
# import pandas as pd

# # Save to a temporary string buffer
# from io import StringIO

# # Read and filter lines before the *
# lines = []
# with open("./build/data.csv", "r") as f:
#     for line in f:
#         if '*' in line:
#             break  # stop reading if a star is encountered
#         lines.append(line)



# data = np.loadtxt(StringIO.StringIO("".join(lines)), delimiter=",")

# Read the CSV file
# data1 = np.genfromtxt('./build/data.csv', delimiter=',', skip_header=1)

# # Display the data
# print(data1)

# data_object1 = data1[1:9,:]
# print(data_object1)

# x = data1[:, 0]
# y = data1[:, 1]

# print(x)
# print(y)


# plt.scatter(x, y)



# plt.plot([1, 2, 3, 4])

# plt.ylabel('test')

# plt.show()

# data = {'a': np.arange(50),
#         'c': np.random.randint(0, 50, 50),
#         'd': np.random.randn(50)}
# data['b'] = data['a'] + 10 * np.random.randn(50)
# data['d'] = np.abs(data['d']) * 100

# plt.scatter('a', 'b', c='c', s='d', data=data)
# plt.xlabel('entry a')
# plt.ylabel('entry b')
# plt.show()

# names = ['group_a', 'group_b', 'group_c']
# values = [1, 10, 100]

# plt.figure(figsize=(9, 3))

# plt.subplot(131)
# plt.bar(names, values)
# plt.subplot(132)
# plt.scatter(names, values)
# plt.subplot(133)
# plt.plot(names, values)
# plt.suptitle('Categorical Plotting')
# plt.show()

# names = ['group_a', 'group_b', 'group_c']
# values = [1, 10, 100]

# plt.figure(figsize=(9, 3))

# plt.subplot(131)
# plt.bar(names, values)
# plt.subplot(132)
# plt.scatter(names, values)
# plt.subplot(133)
# plt.plot(names, values, linewidth=4.0)
# plt.suptitle('Categorical Plotting')
# plt.show()

# fig = plt.figure()
# ax = fig.add_subplot(projection='3d')

# ax.set_xlabel('X Label')
# ax.set_ylabel('Y Label')
# ax.set_zlabel('Z Label')

# plt.show()