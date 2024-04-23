#include "PitchShift.h"

void PitchShift::init(EncoderDriver* driver, int trackID)
{
    for(size_t i = 0 ; i < BLOCKLENGTH ; i++)
    {
        buffer[L][i] = 0.0f;
        buffer[R][i] = 0.0f;
    }
    
    shifter.Init(48000);
    shifter.SetFun(0.f);

    amount.param.init(0, 1, 0.05, ParameterIDs::PitchShifter::amount, trackID, [this] (float a) { setAmount(a); });
    semitones.param.init(-12, 12, 1, ParameterIDs::PitchShifter::semitones, trackID, [this] (float s) { shifter.SetTransposition(s); });

    driver->addBypassCallback([this] { setBypass(); });
    driver->addParameter(&amount.param);
    driver->addParameter(&semitones.param);

    setDefaultValues();
}

void PitchShift::setDefaultValues()
{
    isBypass = true;
    setAmount(pitchShifterDefs.amount);
    shifter.SetTransposition(pitchShifterDefs.semitones);
    shifter.SetFun(pitchShifterDefs.rand);

    shifter.SetDelSize(2400);
}

void PitchShift::processBlock(float* input[2], size_t size)
{
    if(isBypass)
        return;

    for(size_t i = 0 ; i < size ; i++)
    {
        buffer[L][i] = shifter.Process(input[L][i]);
        buffer[R][i] = shifter.Process(input[R][i]);

        input[L][i] = (input[L][i] * (1.f - amount.value)) + (buffer[L][i] * amount.value);
        input[R][i] = (input[R][i] * (1.f - amount.value)) + (buffer[R][i] * amount.value);
    }
}