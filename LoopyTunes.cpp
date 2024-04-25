#include "DSP/Mixer.h"
#include "GUI/MixerView.h"

using namespace daisy;
using namespace daisysp;

/*
TO DO:
- test reverb dry/wet
- Doxygen docs
- bypass UI class
- fix bit reducer
- test seamless looping algorithm
- fix bit reducer
*/

// Hardware
DaisySeed hw;

// Global
size_t sample;

// DSP
Mixer mixer;

// UI
MixerView mixerView;
EncoderDriver encoder;
UiDriver lcd;
KeypadDriver keypad;

// buffers
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
	float DSY_SDRAM_BSS mix[2][BLOCKLENGTH];
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

void navCallback()
{

}

void init()
{
	// initialise Daisy Seed
	hw.Init(true); // true = boost enabled
	hw.SetAudioBlockSize(BLOCKLENGTH); 
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);

	// initialise DSP
	mixer.init(&hw, Buffers::track1Ptr, Buffers::track2Ptr, Buffers::track3Ptr, Buffers::track4Ptr);
	mixer.initMixChannels(Buffers::mixPtr, Buffers::t1mPtr, Buffers::t2mPtr, Buffers::t3mPtr, Buffers::t4mPtr);
	mixer.initFX(&encoder, Buffers::t1delayPtr, Buffers::t2delayPtr, Buffers::t3delayPtr, Buffers::t4delayPtr);

	// initialise hardware controls
	encoder.init(seed::D4, seed::D13, seed::D14, navCallback);
	lcd.Init();
	lcd.Fill(COLOR_BLACK);
	lcd.Update();
	// keypad driver

	// initialise GUI
	mixerView.init(&hw, &encoder, &lcd, &keypad);

	System::Delay(100);
}

inline void tick(size_t size)
{
	if(sample >= MACROBLOCK)
	{
		keypad.tick();
		encoder.tick();
		mixer.tick();
		mixerView.tick();
		lcd.Update();
		sample = 0;
	}
	else
	{
		sample += size;
	}
}

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	tick(size);

	mixer.processInputBlock(in[L], in[R], size);
	mixer.processOutputBlock(out[L], out[R], size);
}

int main(void)
{	
	init();
	hw.StartAudio(AudioCallback);

	// init global variabls
	sample = 0;

	// handle ADC init
	AdcChannelConfig configs[ADCINPUTS];
	configs[ChannelIDs::AMP1].InitSingle(seed::A0);
	configs[ChannelIDs::AMP2].InitSingle(seed::A1);
	configs[ChannelIDs::AMP3].InitSingle(seed::A2);
	configs[ChannelIDs::AMP4].InitSingle(seed::A3);
	configs[ChannelIDs::MASTER].InitSingle(seed::A11);
	hw.adc.Init(configs, ADCINPUTS);
	hw.adc.Start();

	//lcd.Fill(COLOR_BLACK);
    //lcd.Update();

	while(1) 
	{
		
	}
}
