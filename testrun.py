from ctypes import CDLL

# Load the shared library
lib = CDLL('./libhello.so')

# Call the function
lib.hello()