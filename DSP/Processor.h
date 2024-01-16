/******************************************************//**
 *  Class name: Processor
 *  Function: Top level class for all audio processing
 *********************************************************/

#include "Mixer.h"

class Processor
{
public:

    void init(float* m, float* t1, float* t2, float* t3, float* t4, size_t s);
    
    void prepare();
    void processBlock(size_t size);

private:

    Mixer mixer;

};