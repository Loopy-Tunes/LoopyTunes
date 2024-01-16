#include "Processor.h"

void Processor::init(float* m, float* t1, float* t2, float* t3, float* t4, size_t s)
{
    mixer.init(m, t1, t2, t3, t4, s);
}

void Processor::prepare()
{

}

void Processor::processBlock(size_t size)
{
    
}