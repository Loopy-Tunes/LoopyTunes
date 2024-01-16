#include "daisy_seed.h"
#include "daisysp.h"
#include "DSP/Processor.h"
#include "Architecture/ConnectionMatrix.h"

using namespace daisy;
using namespace daisysp;

// Hardware
DaisySeed hw;

// System - Flash
ConnectionMatrix connectionMatrix;

// DSP - SDRAM
Processor DSY_SDRAM_BSS processor;

// Buffers
float DSY_SDRAM_BSS mix[2][SAMPLERATE * DURATION];

float DSY_SDRAM_BSS track1[2][SAMPLERATE * DURATION];
float DSY_SDRAM_BSS track2[2][SAMPLERATE * DURATION];
float DSY_SDRAM_BSS track3[2][SAMPLERATE * DURATION];
float DSY_SDRAM_BSS track4[2][SAMPLERATE * DURATION];

// UI - QSPI

// functions
void initialise()
{
	// initialise track buffer pointers and buffer sizes

}

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	/*
	for (size_t i = 0; i < size; i++)
	{
		out[0][i] = in[0][i];
		out[1][i] = in[1][i];
	}
	*/

	processor.processBlock(size);
	
}

int main(void)
{
	hw.Init();
	hw.SetAudioBlockSize(BLOCKLENGTH); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	hw.StartAudio(AudioCallback);
	while(1) {}
}
