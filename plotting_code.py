import numpy as np
import matplotlib.pyplot as plt
from io import StringIO

# Read and filter lines before the first star, skipping empty lines
lines = []
with open("./build/data.csv", "r") as f:
    for line in f:
        if '*' in line:  # Stop reading if a star is encountered
            break
        if line.strip():  # Only add non-empty lines
            lines.append(line)

# Join the lines and pass to StringIO to simulate a file-like object
data_string = "".join(lines)

# Remove any trailing empty lines (or lines that contain only commas)
data_string = "\n".join([line for line in data_string.splitlines() if line.strip(',')])

# Now, we will use np.genfromtxt to read the data and handle malformed rows
try:
    data = np.genfromtxt(StringIO(data_string), delimiter=",", skip_header=0, filling_values=np.nan)
    
    # Check if the data loaded successfully and has multiple columns
    if data.size > 0 and data.shape[1] > 1:  # Ensure there are multiple columns
        print(f"Data loaded successfully with shape {data.shape}.")
        
        # Plot each column (state vector component) over time
        time_steps = np.arange(data.shape[0])  # Time steps based on number of rows
        
        # Plot only every 200th state vector for labeling
        for i in range(0, data.shape[1], 200):  # Every 200th state vector for labeling
            plt.plot(time_steps, data[:, i], label=f'State Vector {i+1}')  # Label selected state vectors
        
        # Label the axes and title
        plt.xlabel('Time Step')
        plt.ylabel('State Vector Value')
        plt.title('State Vectors Over Time')
        plt.legend()

        # Save the plot to a file (for example, in PNG format)
        plt.savefig('state_vectors_plot.png')  # You can specify a different path or format
        print("Plot saved as 'state_vectors_plot.png'.")

        # Optionally, display the plot
        plt.show()

    else:
        print("Data doesn't have the expected number of columns.")
except ValueError as e:
    print("Error in loading data:", e)
    print("Check if there are malformed rows or excessive columns.")




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