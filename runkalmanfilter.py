# import the module
from ctypes import cdll
# load the library
lib = cdll.LoadLibrary('./kf.so')

# create a KalmanFilter class
class KalmanFilter(object):

    # constructor
    def __init__(self):

        #attribute
        self.obj = lib.KF_new()

    # define method
    def myFunction(self):
        lib.KF_myFunction(self.obj)

# create a KF class object
kf = KalmanFilter()

# object method calling
f.myFunction()