/******************************************************//**
 *  Class name: Processor
 *  Function: Top level class for all audio processing
 *********************************************************/

#include "Mixer.h"

class Processor
{
public:

    void prepare();
    void processBlock(float* input, float* output);

    void setIsPlaying();

private:

    Mixer mixer;

    // playhead (time since record was pressed)
    // isPlaying

};