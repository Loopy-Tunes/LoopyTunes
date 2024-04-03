#ifndef PARAMETERIDS_H
#define PARAMETERIDS_H
#pragma once

namespace ParameterIDs
{
    namespace Tracks
    {
        const int Track1 = 100;
        const int Track2 = 200;
        const int Track3 = 300;
        const int Track4 = 400;
    }

    namespace PitchShifter
    {
        const int effect = 10;

        const int bypass = effect + 1;
        const int amount = effect + 2;
        const int semitones = effect + 3;
        const int random = effect + 4;
    }

    namespace Waveshaper
    {
        const int effect = 20;

        const int bypass = effect + 1;
        const int amount = effect + 2;
        const int funcControl = effect + 3;
        const int waveshape = effect + 4;
    }

    namespace Filter
    {
        const int effect = 30;

        const int bypass = effect + 1;
        const int frequency = effect + 2;
        const int amount = effect + 3;
        const int resonance = effect + 4;
        const int mode = effect + 5;
    }

    namespace Delay
    {
        const int effect = 40;

        const int bypass = effect + 1;
        const int amount = effect + 2;
        const int size = effect + 3;
        const int feedback = effect + 4;
    }

    namespace Reverb
    {
        const int effect = 50;

        const int bypass = effect + 1;
        const int amount = effect + 2;
        const int mode = effect + 3;
        const int size = effect + 4;
        const int damp = effect + 5;
        const int width = effect + 6;
    }
}

#endif