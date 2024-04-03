#include <string>

namespace ParameterIDs
{
    namespace Tracks
    {
        static const std::string Track1 = "1";
        static const std::string Track2 = "2";
        static const std::string Track3 = "3";
        static const std::string Track4 = "4";
    }

    namespace PitchShifter
    {
        static const std::string effect = "PitchShifter";

        static const std::string bypass = effect + "Bypass";
        static const std::string amount = effect + "Amount";
        static const std::string semitones = effect+ "Semitones";
        static const std::string random = effect + "Random";
    }

    namespace Waveshaper
    {
        static const std::string effect = "Waveshaper";

        static const std::string bypass = effect + "Bypass";
        static const std::string amount = effect + "Amount";
        static const std::string funcControl = effect + "FuncControl";
        static const std::string waveshape = effect + "Waveshape";
    }

    namespace Filter
    {
        static const std::string effect = "Filter";

        static const std::string bypass = effect + "Bypass";
        static const std::string amount = effect + "Amount";
        static const std::string frequency = effect + "Frequency";
        static const std::string resonance = effect + "Resonance";
        static const std::string mode = effect + "Mode";
    }

    namespace Delay
    {
        static const std::string effect = "Delay";

        static const std::string bypass = effect + "Bypass";
        static const std::string amount = effect + "Amount";
        static const std::string size = effect + "Size";
        static const std::string feedback = effect + "Feedback";
    }

    namespace Reverb
    {
        static const std::string effect = "Reverb";

        static const std::string bypass = effect + "Bypass";
        static const std::string amount = effect + "Amount";
        static const std::string mode = effect + "Mode";
        static const std::string size = effect + "size";
        static const std::string damp = effect + "Damp";
        static const std::string width = effect + "Width";
    }
};