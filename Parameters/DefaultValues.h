#ifndef DEFAULTVALUES_H
#define DEFAULTVALUES_H

#include <functional>

static const struct PitchShifterDefaults
{
	bool bypass = true;
	float amount = 0.5;
	float semitones = 12;
	float rand = 0;
} pitchShifterDefs;

static const struct WaveshaperDefaults
{
	bool bypass = true;
    float amount = 0.5;
	float funcControl = 0;
    float mode = 0;
} waveshaperDefs;

static const struct FilterDefaults
{
	bool bypass = true;
	float mode = 0;
	float frequency = 0.5;
} filterDefs;

static const struct ReverbDefaults
{
	bool bypass = true;
	float amount = 0.5;
	float mode = 0;
	float size = 0.5;
	float damp = 0.5;
	float width = 0.5;
} reverbDefs;

static const struct DelayDefaults
{
	bool bypass = true;
	float amount = 0.5;
	size_t size = 5000;
	float feedback = 0.5;
} delayDefs;

#endif