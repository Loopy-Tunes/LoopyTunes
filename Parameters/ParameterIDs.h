#include <string>

typedef const std::string ID;

namespace ParameterIDs
{
    namespace Tracks
    {
        ID Track1 = "1";
        ID Track2 = "2";
        ID Track3 = "3";
        ID Track4 = "4";
    };

    namespace PitchShifter
    {
        ID effect = "PitchShifter";

        ID bypass = effect + "Bypass";
        ID amount = effect + "Amount";
        ID semitones = effect+ "Semitones";
        ID random = effect + "Random";
    };

    namespace Waveshaper
    {
        ID effect = "Waveshaper";

        ID bypass = effect + "Bypass";
        ID amount = effect + "Amount";
        ID inputGain = effect + "InputGain";
        ID waveshape = effect + "Waveshape";
    };

    namespace Delay
    {
        ID effect = "Delay";

        ID bypass = effect + "Bypass";
        ID amount = effect + "Amount";
        ID size = effect + "Size";
        ID feedback = effect + "Feedback";
    };

    namespace Reverb
    {
        ID effect = "Reverb";

        ID bypass = effect + "Bypass";
        ID amount = effect + "Amount";
        ID mode = effect + "Mode";
        ID size = effect + "size";
        ID damp = effect + "Damp";
        ID width = effect + "Width";
    };
};