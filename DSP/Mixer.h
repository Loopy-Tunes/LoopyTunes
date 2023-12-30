/********************************************//**
 *  Class name: Mixer
 *  Function: Mixes outputs of track classes
 ***********************************************/

class Mixer
{
public:

    void prepare();
    void processBlock(float* input, float* output);

    void setChannel1Gain(float val);
    void setChannel2Gain(float val);
    void setChannel3Gain(float val);
    void setChannel4Gain(float val);

private:

    // Channel 1
    // Channel 2
    // Channel 3
    // Channel 4

};