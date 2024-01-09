/******************************************************//**
 *  Class name: Processor
 *  Function: Top level class for all audio processing
 *********************************************************/

#include "Mixer.h"

class Processor
{
public:

    void prepare();
    void processBlock(float* inputL, float* inputR);

    void setIsPlaying(bool val) { isPlaying = val; }

private:

    Mixer mixer;

    // playhead (time since record was pressed)
    bool isPlaying;

};