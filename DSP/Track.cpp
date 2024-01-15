#include "Track.h"

void Track::prepare()
{

}

void Track::init(float *memL, float *memR, size_t buffSize)
{
    buffer.left = memL;
    buffer.right = memR;
    buffer.size = buffSize;

    buffer.init();
}

void Track::processBlock(StereoBuffer input, StereoBuffer output, size_t size)
{
    
}