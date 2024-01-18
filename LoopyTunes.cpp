#include "daisy_seed.h"
#include "daisysp.h"
#include "DSP/Mixer.h"
#include "Architecture/ConnectionMatrix.h"

using namespace daisy;
using namespace daisysp;

// Hardware
DaisySeed hw;

// GPIO
static Switch record;
static Switch play;

// Global
static float sampleRate;

// System - Flash
ConnectionMatrix connectionMatrix;

// DSP - SDRAM
static Mixer mixer;

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

	// initialise GPIO
	record.Init(hw.GetPin(22), sampleRate / 48.f, Switch::Type::TYPE_MOMENTARY, Switch::Polarity::POLARITY_NORMAL, Switch::Pull::PULL_DOWN); 
	play.Init(hw.GetPin(23), sampleRate / 48.f, Switch::Type::TYPE_MOMENTARY, Switch::Polarity::POLARITY_NORMAL, Switch::Pull::PULL_DOWN);
}

void pollInputs()
{
	record.Debounce();
	play.Debounce();

	if(record.Pressed())
		mixer.setIsRecording();

	if(play.Pressed())
		mixer.setIsPlaying();
}

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	pollInputs();

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
	sampleRate = hw.AudioSampleRate();

	initialise();

	hw.StartLog();
	hw.StartAudio(AudioCallback);

	while(1) 
	{
		hw.PrintLine("Record State: %s", record.Pressed() ? "true" : "false");
		hw.PrintLine("Play State: %s", play.Pressed() ? "true" : "false");
	}
}
