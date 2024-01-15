#include "Processor.h"

void Processor::prepare()
{

}

void Processor::processBlock(float inputL, float inputR, float outputL, float outputR, size_t size)
{
    mixer.processBlock(inputL, inputR, outputL, outputR, size);
}