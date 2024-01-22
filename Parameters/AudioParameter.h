#include "../Utils/Helpers.h"
#include <cstdint>

/**************************************************************************//**
 *  Class name: AudioParameter
 *  Function: Parameter object for DSP classes
 *****************************************************************************/

template <class type>
class AudioParameter
{
public:

    void init();
    
    void tick();
    void process();

    type getValue();
    
private:

    // pointer to top level daisy seed instance

    type curVal, min, max;
    uint8_t channelID;
    CurveType curve;
    bool isSelected;

};