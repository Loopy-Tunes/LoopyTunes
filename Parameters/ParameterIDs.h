#ifndef PARAMETERIDS_H
#define PARAMETERIDS_H
#pragma once

#include <string>

namespace ParameterIDs
{
    namespace Tracks
    {
        const std::string Track1 = "1";
        const std::string Track2 = "2";
        const std::string Track3 = "3";
        const std::string Track4 = "4";
    }

    namespace PitchShifter
    {
        const std::string effect = "PitchShifter";

        const std::string bypass = effect + "Bypass";
        const std::string amount = effect + "Amount";
        const std::string semitones = effect+ "Semitones";
        const std::string random = effect + "Random";
    }

    namespace Waveshaper
    {
        const std::string effect = "Waveshaper";

        const std::string bypass = effect + "Bypass";
        const std::string amount = effect + "Amount";
        const std::string funcControl = effect + "FuncControl";
        const std::string waveshape = effect + "Waveshape";
    }

    namespace Filter
    {
        const std::string effect = "Filter";

        const std::string bypass = effect + "Bypass";
        const std::string frequency = effect + "Frequency";
        const std::string amount = effect + "Amount";
        const std::string resonance = effect + "Resonance";
        const std::string mode = effect + "Mode";
    }

    namespace Delay
    {
        const std::string effect = "Delay";

        const std::string bypass = effect + "Bypass";
        const std::string amount = effect + "Amount";
        const std::string size = effect + "Size";
        const std::string feedback = effect + "Feedback";
    }

    namespace Reverb
    {
        const std::string effect = "Reverb";

        const std::string bypass = effect + "Bypass";
        const std::string amount = effect + "Amount";
        const std::string mode = effect + "Mode";
        const std::string size = effect + "size";
        const std::string damp = effect + "Damp";
        const std::string width = effect + "Width";
    }
}

#endif