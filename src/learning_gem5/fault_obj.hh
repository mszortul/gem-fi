
#ifndef __LEARNING_GEM5_FAULT_OBJ_HH__
#define __LEARNING_GEM5_FAULT_OBJ_HH__

#include "cpu/simple/timing.hh"
#include "params/FaultObj.hh"
#include "sim/sim_object.hh"

class FaultObj : public SimObject
{
  private:
    void processEvent();

    EventFunctionWrapper event;

    /// Latency between times we fire the event.
    Tick latency;

    /// Number of times to fire before we stop firing
    int timesLeft;

    TimingSimpleCPU* fcpu;

  public:
    FaultObj(FaultObjParams *p);

    TimingSimpleCPU* cpu_ptr;

    void startup();
};

#endif
