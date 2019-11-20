from m5.params import *
from m5.SimObject import SimObject

class FaultObj(SimObject):
    type = 'FaultObj'
    cxx_header = "learning_gem5/fault_obj.hh"

    cpu_obj = Param.TimingSimpleCPU("current cpu")
    times_left = Param.Int("no of injections")
    lat = Param.Int("interval between injections")
