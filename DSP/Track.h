/**********************************************************//**
 *  Class name: Track
 *  Function: Processes audio buffer and FX for each track
 *************************************************************/

class Track
{
public:

    void prepare();
    void processBlock(float* input, float* output);

    void setIsRecording();
    void setIsPlaying();

private:

    // playhead
    // isRecording
    // isplaying

    // track buffer

};