#include "daisysp.h"
#include "DSP/Mixer.h"
#include "Architecture/ConnectionMatrix.h"

using namespace daisy;
using namespace daisysp;

/*
TO DO:
- Refactor play/record to have similar parameter class to analog ins
- AudioParameter value smoothing
- Update AudioParameter value only if changed
- Parameter update queue
- Value normalisation
- Tick parameters less often
- Move buffers to track level
- Reduce floating point precision
*/

// Hardware
DaisySeed hw;

// GPIO
Switch record;
Switch play;

// ADC inputs
AdcChannelConfig amp1;

// Global
float sampleRate;
bool isRecord;
bool isPlay;

// System - Flash
ConnectionMatrix connectionMatrix;

// DSP - SDRAM
Mixer mixer;

// UI - QSPI

void init()
{
	// initialise Daisy Seed
	hw.Init();
	hw.SetAudioBlockSize(BLOCKLENGTH); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	sampleRate = hw.AudioSampleRate();

	// initialise GPIO
	record.Init(daisy::seed::D0, 30);
	play.Init(daisy::seed::D1, 30);

	isRecord = false;
	isPlay = false;

	// initialise DSP
	mixer.init(&hw, mixPtr, track1Ptr, track2Ptr, track3Ptr, track4Ptr, sampleRate * DURATION);
}

void initADC()
{
	amp1.InitSingle(daisy::seed::A0);
	hw.adc.Init(&amp1, 1);
	hw.adc.Start();
}

void pollInputs()
{
	isRecord = record.Pressed();
	isPlay = play.Pressed();

	if(isRecord) 
	{  
		mixer.setIsRecording();
		hw.PrintLine("Record set");
	}
	record.Debounce();

	if(isPlay) 
	{ 
		mixer.setIsPlaying(); 
		hw.PrintLine("Play set");
	}
	play.Debounce();
}

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	mixer.processInputBlock(in[L], in[R], size);
	mixer.processOutputBlock(out[L], out[R], size);
}

int main(void)
{
	init();
	initADC();

	hw.StartLog();
	hw.StartAudio(AudioCallback);

	while(1) 
	{
		pollInputs();
		mixer.tick();
	}
}
