#include "PitchShift.h"

void PitchShift::init(EncoderDriver* driver, std::string trackID)
{
    for(size_t i = 0 ; i < BLOCKLENGTH ; i++)
    {
        buffer[L][i] = 0.0f;
        buffer[R][i] = 0.0f;
    }
    
    shifter.Init(48000);

    bypass.param.init(0, 1, 1, ParameterIDs::PitchShifter::bypass, trackID, [this] (float b) { setBypass(b); });
    amount.param.init(0, 1, 0.05, ParameterIDs::PitchShifter::amount, trackID, [this] (float a) { setAmount(a); });
    semitones.param.init(-12, 12, 1, ParameterIDs::PitchShifter::semitones, trackID, [this] (float s) { shifter.SetTransposition(s); });
    rand.param.init(0, 1, 0.05, ParameterIDs::PitchShifter::random, trackID, [this] (float r) { shifter.SetFun(r); });

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
    
}

void PitchShift::process(float* input[2], size_t size)
{
    if(bypass.value == 1)
        return;

    for(size_t i = 0 ; i < size ; i++)
    {
        buffer[L][i] = shifter.Process(input[L][i]);
        buffer[R][i] = shifter.Process(input[R][i]);

        input[L][i] = (input[L][i] * (1.f - amount.value)) + (buffer[L][i] * amount.value);
        input[R][i] = (input[R][i] * (1.f - amount.value)) + (buffer[R][i] * amount.value);
    }
}