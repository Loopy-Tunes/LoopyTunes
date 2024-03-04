#include "DSP/Mixer.h"
#include "Architecture/ConnectionMatrix.h"

using namespace daisy;
using namespace daisysp;

/*
TO DO:
- AudioParameter value smoothing / ramping
- Parameter update queue (is this needed?)
- Parameter denormalisation (for display)
- Decibel conversion
- Output EQ profiles for different output sources (?)
- LPF/HPF filters
- Pitch shift
- Block counter for handling parameter updates
- Encoder driver
- Output Limiter
- Play/record LEDs
- Modularise track methods with ID enum
- Reverb
- Move dekay buffers to delay level
*/

// Hardware
DaisySeed hw;

// Global
//int sample;

// System - Flash
ConnectionMatrix connectionMatrix;

// DSP - SDRAM
static Mixer mixer;

// UI - QSPI

// testing

namespace Buffers
{
	// Sample Buffers
	float DSY_SDRAM_BSS track1[2][SAMPLERATE * DURATION];
	float DSY_SDRAM_BSS track2[2][SAMPLERATE * DURATION];
	float DSY_SDRAM_BSS track3[2][SAMPLERATE * DURATION];
	float DSY_SDRAM_BSS track4[2][SAMPLERATE * DURATION];

	float* track1Ptr[2] = {track1[L], track1[R]};
	float* track2Ptr[2] = {track2[L], track2[R]};
	float* track3Ptr[2] = {track3[L], track3[R]};
	float* track4Ptr[2] = {track4[L], track4[R]};

	// Mix Buffers
	float DSY_SDRAM_BSS mix[2][SAMPLERATE * DURATION];
	float DSY_SDRAM_BSS t1m[2][BLOCKLENGTH];
	float DSY_SDRAM_BSS t2m[2][BLOCKLENGTH];
	float DSY_SDRAM_BSS t3m[2][BLOCKLENGTH];
	float DSY_SDRAM_BSS t4m[2][BLOCKLENGTH];

	float* mixPtr[2] = {mix[L], mix[R]};
	float* t1mPtr[2] = {t1m[L], t1m[R]};
	float* t2mPtr[2] = {t2m[L], t2m[R]};
	float* t3mPtr[2] = {t3m[L], t3m[R]};
	float* t4mPtr[2] = {t4m[L], t4m[R]};

	// Delay Lines
	DelayLine<float, MAXDELAY> DSY_SDRAM_BSS t1delay[2];
	DelayLine<float, MAXDELAY> DSY_SDRAM_BSS t2delay[2];
	DelayLine<float, MAXDELAY> DSY_SDRAM_BSS t3delay[2];
	DelayLine<float, MAXDELAY> DSY_SDRAM_BSS t4delay[2];

	DelayLine<float, MAXDELAY>* t1delayPtr[2] = {&t1delay[L], &t1delay[R]};
	DelayLine<float, MAXDELAY>* t2delayPtr[2] = {&t2delay[L], &t2delay[R]};
	DelayLine<float, MAXDELAY>* t3delayPtr[2] = {&t3delay[L], &t3delay[R]};
	DelayLine<float, MAXDELAY>* t4delayPtr[2] = {&t4delay[L], &t4delay[R]};
};

void init()
{
	// initialise Daisy Seed
	hw.Init();
	hw.SetAudioBlockSize(BLOCKLENGTH); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);

	// initialise global variables
	//sample = 0;

	// initialise DSP
	mixer.init(&hw, Buffers::mixPtr, Buffers::track1Ptr, Buffers::track2Ptr, Buffers::track3Ptr, Buffers::track4Ptr);
	mixer.initMixChannels(Buffers::t1mPtr, Buffers::t2mPtr, Buffers::t3mPtr, Buffers::t4mPtr);
	mixer.initFX(&hw, Buffers::t1delayPtr, Buffers::t2delayPtr, Buffers::t3delayPtr, Buffers::t4delayPtr);
}

void initTrackIO()
{
	TrackIO t1IO {ChannelIDs::AMP1, seed::D19, seed::D20};
	TrackIO t2IO {ChannelIDs::AMP2, seed::D21, seed::D22};
	TrackIO t3IO {ChannelIDs::AMP3, seed::D23, seed::D24};
	TrackIO t4IO {ChannelIDs::AMP4, seed::D6, seed::D5};

	mixer.initTrackIO(&hw, t1IO, t2IO, t3IO, t4IO);
}

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	mixer.processInputBlock(in[L], in[R], size);
	mixer.processOutputBlock(out[L], out[R], size);
}

int main(void)
{
	init();
	initTrackIO();
	hw.StartAudio(AudioCallback);

	// handle ADC init
	AdcChannelConfig configs[ADCINPUTS];
	configs[ChannelIDs::AMP1].InitSingle(seed::A0);
	configs[ChannelIDs::AMP2].InitSingle(seed::A1);
	configs[ChannelIDs::AMP3].InitSingle(seed::A2);
	configs[ChannelIDs::AMP4].InitSingle(seed::A3);
	configs[ChannelIDs::MASTER].InitSingle(seed::A11);
	configs[ChannelIDs::ENCODER].InitSingle(seed::A10);
	hw.adc.Init(configs, ADCINPUTS);
	hw.adc.Start();
	
	hw.StartLog();
	
	while(1) 
	{
		mixer.tick();
	}
}
