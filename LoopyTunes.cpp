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

// UI - QSPI


// Global

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	
	for (size_t i = 0; i < size; i++)
	{
		out[0][i] = in[0][i];
		out[1][i] = in[1][i];
	}
	
/*
	for(size_t i = 0 ; i < size ; i++)
	{
		processor.processBlock(in[0][i], in[1][i], out[0][i], out[1][i], size);
	}
	*/
}

int main(void)
{
	hw.Init();
	hw.SetAudioBlockSize(4); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	hw.StartAudio(AudioCallback);
	while(1) {}
}
