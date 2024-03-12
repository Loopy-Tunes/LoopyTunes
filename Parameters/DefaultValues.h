#ifndef DEFAULTVALUES_H
#define DEFAULTVALUES_H

#include <functional>

static const struct PitchShifterDefaults
{
	float bypass = 1;
	float amount = 0.5;
	int semitones = 12;
	float rand = 0;
} pitchShifterDefs;

static const struct WaveshaperDefaults
{
	int bypass = 1;
    float input = 0.5;
    int waveshape = 0;
    float amount = 0.5;
} waveshaperDefs;

static const struct ReverbDefaults
{
	int bypass = 1;
	float amount = 0.5;
	float mode = 1;
	float size = 0.5;
	float damp = 0.5;
	float width = 0.5;
} reverbDefs;

static const struct DelayDefaults
{
	int bypass = 1;
	float amount = 0.5;
	size_t size = 5000;
	float feedback = 0.5;
} delayDefs;

#endif