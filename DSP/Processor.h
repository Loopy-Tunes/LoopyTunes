/******************************************************//**
 *  Class name: Processor
 *  Function: Top level class for all audio processing
 *********************************************************/

#include "Mixer.h"

class Processor
{
public:

    void prepare();
    void processBlock(float inputL, float inputR, float outputL, float outputR, size_t size);

private:

    Mixer mixer;

};