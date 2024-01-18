#include "daisy_seed.h"
#include "daisysp.h"
#include "DSP/Mixer.h"
#include "Architecture/ConnectionMatrix.h"

using namespace daisy;
using namespace daisysp;

// Hardware
DaisySeed hw;

// GPIO


// System - Flash
ConnectionMatrix connectionMatrix;

// DSP - SDRAM
Mixer DSY_SDRAM_BSS mixer;

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
void initialise()
{
	// initialise DSP
	mixer.init(mixPtr, track1Ptr, track2Ptr, track3Ptr, track4Ptr, SAMPLERATE * DURATION);

}

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	mixer.processInput(in[0], in[1], size);

	// process output
	for(size_t i = 0 ; i < size ; i++)
	{
		mixer.tick();

		out[L][i] = mixer.processOutputLeft();
		out[R][i] = mixer.processOutputRight();
	}
}

int main(void)
{
	hw.Init();
	hw.SetAudioBlockSize(BLOCKLENGTH); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);

	initialise();

	hw.StartLog();
	hw.StartAudio(AudioCallback);

	GPIO record;
	GPIO play;
	GPIO led;

	bool isRecord = false;
	bool isPlay = false;

	// initialise GPIO
	record.Init(hw.GetPin(21), GPIO::Mode::INPUT, GPIO::Pull::PULLDOWN);
	play.Init(daisy::seed::D17, GPIO::Mode::INPUT, GPIO::Pull::PULLDOWN);
	led.Init(daisy::seed::D18, GPIO::Mode::OUTPUT);

	while(1) 
	{
		//hw.ProcessDi

		isRecord = record.Read();
		isPlay = play.Read();
		System::Delay(50);

		led.Write(isRecord);
		hw.SetLed(isPlay);

		if(isRecord)
			mixer.setIsRecording();

		if(isPlay)
			mixer.setIsPlaying();

		hw.PrintLine("Record State: %s", isRecord ? "true" : "false");
		hw.PrintLine("Play State: %s", isPlay ? "true" : "false");
	}
}
