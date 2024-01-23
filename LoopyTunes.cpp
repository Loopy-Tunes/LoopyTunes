#include "daisysp.h"
#include "DSP/Mixer.h"
#include "Architecture/ConnectionMatrix.h"

using namespace daisy;
using namespace daisysp;

/*
TO DO:
- Refactor play/record to have similar parameter class to analog ins
- Implement AudioParameter
*/

// Hardware
DaisySeed hw;

// GPIO
Switch record;
Switch play;

// Global
float sampleRate;
bool isRecord;
bool isPlay;

// System - Flash
ConnectionMatrix connectionMatrix;

// DSP - SDRAM
Mixer mixer;

// Buffers
float DSY_SDRAM_BSS mix[2][SAMPLERATE * DURATION];

float DSY_SDRAM_BSS track1[2][SAMPLERATE * DURATION];
float DSY_SDRAM_BSS track2[2][SAMPLERATE * DURATION];
float DSY_SDRAM_BSS track3[2][SAMPLERATE * DURATION];
float DSY_SDRAM_BSS track4[2][SAMPLERATE * DURATION];

// Buffer pointers
float* mixPtr[2] = {mix[L], mix[R]};

float* track1Ptr[2] = {track1[L], track1[R]};
float* track2Ptr[2] = {track2[L], track2[R]};
float* track3Ptr[2] = {track3[L], track3[R]};
float* track4Ptr[2] = {track4[L], track4[R]};

// UI - QSPI

// functions
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
	mixer.init(mixPtr, track1Ptr, track2Ptr, track3Ptr, track4Ptr, sampleRate * DURATION);
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

	hw.StartLog();
	hw.StartAudio(AudioCallback);

	while(1) 
	{
		pollInputs();
	}
}
