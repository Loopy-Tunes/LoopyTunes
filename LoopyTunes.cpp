#include "DSP/Mixer.h"
#include "Architecture/ConnectionMatrix.h"

using namespace daisy;
using namespace daisysp;

/*
TO DO:
- AudioParameter value smoothing / ramping
- Parameter update queue
- Parameter denormalisation (for display)
- Come up with much better mixing system
- Decibel conversion
- Output EQ profiles for different output sources
- Delay ms/room size -> samples calculation
- Find out ms delay of certain room sizes for delay
- Calculate correct max delay
- LPF on track inputs
- Block counter for handling parameter updates
- Reverse mode
- Keypad driver
- Encoder driver
- CPU load testing (after distortion or symposium)
*/

// Hardware
DaisySeed hw;

// Global
int sample;

// System - Flash
ConnectionMatrix connectionMatrix;

// DSP - SDRAM
Mixer mixer;

// UI - QSPI

namespace Buffers
{
	float DSY_SDRAM_BSS mix[2][SAMPLERATE * DURATION];
	float DSY_SDRAM_BSS track1[2][SAMPLERATE * DURATION];
	float DSY_SDRAM_BSS track2[2][SAMPLERATE * DURATION];
	float DSY_SDRAM_BSS track3[2][SAMPLERATE * DURATION];
	float DSY_SDRAM_BSS track4[2][SAMPLERATE * DURATION];

	float* mixPtr[2] = {mix[L], mix[R]};
	float* track1Ptr[2] = {track1[L], track1[R]};
	float* track2Ptr[2] = {track2[L], track2[R]};
	float* track3Ptr[2] = {track3[L], track3[R]};
	float* track4Ptr[2] = {track4[L], track4[R]};

	DelayLine<float, MAXDELAY> DSY_SDRAM_BSS delayLine[2];
	DelayLine<float, MAXDELAY>* delayLinePtr[2] = {&delayLine[L], &delayLine[R]};
};

void init()
{
	// initialise Daisy Seed
	hw.Init();
	hw.SetAudioBlockSize(BLOCKLENGTH); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	
	// initialise global variables
	sample = 0;

	// initialise DSP
	mixer.init(&hw, Buffers::mixPtr, Buffers::track1Ptr, Buffers::track2Ptr, Buffers::track3Ptr, Buffers::track4Ptr, Buffers::delayLinePtr);
}

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	//mixer.tick();

	mixer.processInputBlock(in[L], in[R], size);
	mixer.processOutputBlock(out[L], out[R], size);
}

int main(void)
{
	init();

	hw.StartLog();
	hw.StartAudio(AudioCallback);

	// handle ADC init
	AdcChannelConfig configs[ADCINPUTS];
	configs[ChannelIDs::AMP1].InitSingle(seed::A0);
	configs[ChannelIDs::TEMP1].InitSingle(seed::A1);
	configs[ChannelIDs::TEMP2].InitSingle(seed::A2);
	configs[ChannelIDs::TEMP3].InitSingle(seed::A3);
	configs[ChannelIDs::TEMP4].InitSingle(seed::A4);
	hw.adc.Init(configs, ADCINPUTS);
	hw.adc.Start();

	while(1) 
	{
		mixer.tick();
		//hw.PrintLine("temp 1 pot = %f", hw.adc.GetFloat(ChannelIDs::TEMP1));
		//hw.PrintLine("temp 2 pot = %f", hw.adc.GetFloat(ChannelIDs::TEMP2));
		//hw.PrintLine("temp 3 pot = %f", hw.adc.GetFloat(ChannelIDs::TEMP3));
		//hw.PrintLine("temp 4 pot = %f", hw.adc.GetFloat(ChannelIDs::TEMP4));

		System::Delay(50);
	}
}
