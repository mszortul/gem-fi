
#include "debug/Fault_.hh"
#include "cpu/simple_thread.hh"
#include "cpu/simple/base.hh"
#include "learning_gem5/fault_obj.hh"

#include <stdlib.h>
#include <time.h>

FaultObj::FaultObj(FaultObjParams *params) :
    SimObject(params), event([this]{processEvent();}, name()),
    latency(params->lat), timesLeft(params->times_left), fcpu(params->cpu_obj)
{
    DPRINTF(Fault_, "Created the fault object\n");
}

void
FaultObj::startup()
{
    schedule(event, latency);
}

void
FaultObj::processEvent()
{
    int rand_reg = 0;
    timesLeft--;
    int cur_thread_no = fcpu->get_cur_thread();
    ThreadContext* cur_tc = fcpu->getContext(cur_thread_no);

/*
    uint64_t reg5 = cur_tc->readIntReg(2); //SimpleThread::readIntReg(5);
    if (0) {
        DPRINTF(Fault_, "Injecting fault: %d \nNum int regs: %d \nReg 2: %d \n\n", timesLeft, cur_thread_no, reg5);
    }
*/

    // TODO: write member function in simple_thread that returns TheISA::NumIntRegs

    int reg_idx;
    if (rand_reg){
        //int num_int_reg = TheISA::NumIntRegs;
        //int reg_idx = rand() % num_int_reg;
    } else {
        reg_idx = 2;
    }


    uint64_t reg_orig = cur_tc->readIntReg(reg_idx);
    int bit_pos = rand() % 16; // inject one of first 16 bits
    int target_bit = (reg_orig >> bit_pos) % 2;
    uint64_t mask = 1;
    if (target_bit) {
        // bit is 1
        mask = ~(mask << bit_pos);
    } else {
        mask = (mask << bit_pos);
    }
    uint64_t reg_faulty = reg_orig | mask;

    cur_tc->setIntReg(reg_idx, reg_faulty);
    DPRINTF(Fault_, "Left: %d \t FI to reg %d: %#x to %#x (bit pos=%d)\n", timesLeft, reg_idx, reg_orig, reg_faulty, bit_pos);

    if (0) {
        DPRINTF(Fault_, "That's all folks.\n");
    } else {
        schedule(event, curTick() + latency);
    }

}

FaultObj*
FaultObjParams::create()
{
    return new FaultObj(this);
}
