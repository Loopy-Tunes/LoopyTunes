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

        const int amount = effect + 1;
        const int semitones = effect + 2;
        const int random = effect + 3;
    }

    namespace Waveshaper
    {
        const int effect = 20;

        const int amount = effect + 1;
        const int funcControl = effect + 2;
        const int waveshape = effect + 3;
    }

    namespace Filter
    {
        const int effect = 30;

        const int mode = effect + 1;
        const int frequency = effect + 2;
        const int resonance = effect + 3;
    }

    namespace Delay
    {
        const int effect = 40;

        const int amount = effect + 1;
        const int size = effect + 2;
        const int feedback = effect + 3;
    }

    namespace Reverb
    {
        const int effect = 50;

        const int amount = effect + 1;
        const int mode = effect + 2;
        const int size = effect + 3;
        const int damp = effect + 4;
        const int width = effect + 5;
    }
}

#endif