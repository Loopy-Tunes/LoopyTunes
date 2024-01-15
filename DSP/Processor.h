/******************************************************//**
 *  Class name: Processor
 *  Function: Top level class for all audio processing
 *********************************************************/

#include "Mixer.h"

class Processor
{
public:

    void prepare();
    void processBlock(StereoBuffer input, StereoBuffer output, size_t size);

private:

    Mixer mixer;

};