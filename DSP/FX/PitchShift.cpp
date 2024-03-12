#include "PitchShift.h"

void PitchShift::init(DaisySeed* seed)
{
    for(size_t i = 0 ; i < BLOCKLENGTH ; i++)
    {
        buffer[L][i] = 0.0f;
        buffer[R][i] = 0.0f;
    }
    
    shifter.Init(48000);

    //bypass.param.init(daisy::seed::D5, 1000, [this]{ setBypass(); }); // CHECK THIS
    amount.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP2, [this] (float a) { amount.value = a; });
    semitones.init(seed, -12, 12, LINEAR, ChannelIDs::AMP3, [this] (int s) { shifter.SetTransposition(s); });
    rand.init(seed, 0, 1, LINEAR, ChannelIDs::AMP4, [this] (float r) { shifter.SetFun(r); });

    setDefaultValues();
}

void PitchShift::setDefaultValues()
{
    bypass.value = pitchShifterDefs.bypass;
    amount.value = pitchShifterDefs.amount;
    shifter.SetTransposition(pitchShifterDefs.semitones);
    shifter.SetFun(pitchShifterDefs.rand);

    shifter.SetDelSize(2400);
}

void PitchShift::tick()
{
    //bypass.tick();
    amount.param.tick();
    semitones.tick();
    rand.tick();
}

void PitchShift::process(float* input[2], size_t size)
{
    //if(bypass.value)
        //return;

    for(size_t i = 0 ; i < size ; i++)
    {
        buffer[L][i] = shifter.Process(input[L][i]);
        buffer[R][i] = shifter.Process(input[R][i]);

        input[L][i] = (input[L][i] * (1.f - amount.value)) + (buffer[L][i] * amount.value);
        input[R][i] = (input[R][i] * (1.f - amount.value)) + (buffer[R][i] * amount.value);
    }
}