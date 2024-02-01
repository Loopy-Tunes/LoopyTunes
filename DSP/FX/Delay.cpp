#include "Delay.h"

using namespace daisysp;

DelayLine<float, MAXDELAY> DSY_SDRAM_BSS buffer;

void Delay::init()
{


}

void Delay::tick()
{
    size.process();
    bounce.process();
    amount.process();
}

void Delay::prepare()
{


}

void Delay::process()
{


}