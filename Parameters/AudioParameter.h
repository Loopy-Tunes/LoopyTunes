#include "daisy_seed.h"
#include "../Utils/Helpers.h"
#include <cstdint>

/**************************************************************************//**
 *  Class name: AudioParameter
 *  Function: Parameter object for DSP classes
 *****************************************************************************/

using namespace daisy;

template <class type>
class AudioParameter
{
public:

    void init(DaisySeed& seed, type mi, type ma, CurveType c, ChannelIDs ID)
    {
        hw = seed;
        input = 0;

        curVal = 0;
        min = mi;
        max = ma;

        curve = c;
        channelID = ID;

        if(channelID != ChannelIDs::Encoder)
            isSelected = true;
    }
    
    void tick()
    {
        input = hw->adc.GetFloat(channelID);
        process();
    }

    void process()
    {
        switch (curve)
        {
        case LINEAR:
            curVal = (input * (max - min)) + min;
            break;
        case EXP:
            curVal = ((input * input) * (max - min)) + min;
            break;
        }
    }

    type getValue() { return curVal; }
    
private:

    DaisySeed* hw;
    float input;

    type curVal, min, max;
    uint8_t channelID;
    CurveType curve;
    bool isSelected;

};