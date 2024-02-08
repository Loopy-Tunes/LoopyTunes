#include "DSP/Mixer.h"
#include "Architecture/ConnectionMatrix.h"

using namespace daisy;
using namespace daisysp;

/*
TO DO:
- AudioParameter value smoothing / ramping
- Parameter update queue
- Value normalisation
- Tick parameters less often
- Reduce floating point precision
- Come up with much better mixing system
- Decibel conversion
- Output EQ profiles for different output sources
- Interpolate between start and end sample of loop to smooth transition
- Check bit width of pointers, memory range
- Delay ms/room size -> samples calculation
- Find out ms delay of certain room sizes for delay
- Calculate correct max delay
- Sort out problem with buffers not looping
- Fix potentiometers
*/

// Hardware
DaisySeed hw;

// ADC inputs
namespace ADC
{
	AdcChannelConfig amp1;
	AdcChannelConfig temp1;
	AdcChannelConfig temp2;
	AdcChannelConfig temp3;
	AdcChannelConfig temp4;
	AdcChannelConfig configs[ADCINPUTS] = {amp1, temp1, temp2, temp3, temp4};
};

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

	// initialise ADC
	ADC::amp1.InitSingle(daisy::seed::A0);
	ADC::temp1.InitSingle(daisy::seed::A1);
	ADC::temp2.InitSingle(daisy::seed::A2);
	ADC::temp3.InitSingle(daisy::seed::A3);
	ADC::temp4.InitSingle(daisy::seed::A4);

	hw.adc.Init(ADC::configs, ADCINPUTS);
	hw.adc.Start();

	// initialise DSP
	mixer.init(&hw, Buffers::mixPtr, Buffers::track1Ptr, Buffers::track2Ptr, Buffers::track3Ptr, Buffers::track4Ptr, Buffers::delayLinePtr);
}

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	mixer.processInputBlock(in[L], in[R], size);
	mixer.processOutputBlock(out[L], out[R], size);
}

int main(void)
{
	init();

	hw.StartLog();
	hw.StartAudio(AudioCallback);

	while(1) 
	{
		mixer.tick();

		float ampPot = hw.adc.GetFloat(ChannelIDs::Amp1);
		float pot1 = hw.adc.GetFloat(ChannelIDs::TEMP1);
		float pot2 = hw.adc.GetFloat(ChannelIDs::TEMP2);
		float pot3 = hw.adc.GetFloat(ChannelIDs::TEMP3);
		float pot4 = hw.adc.GetFloat(ChannelIDs::TEMP4);

		hw.PrintLine("amp pot = %f", ampPot);
		hw.PrintLine("pot 1 = %f", pot1);
		//hw.PrintLine("pot 2 = %f", pot2);
		//hw.PrintLine("pot 3 = %f", pot3);
		//hw.PrintLine("pot 4 = %f", pot4);
	}
}
