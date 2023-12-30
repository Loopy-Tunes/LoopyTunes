/**************************************************************************//**
 *  Class name: AudioParameter
 *  Function: Parameter object for DSP classes
 *****************************************************************************/

#include "../Architecture/Subscriber.h"

class AudioParameter : public Subscriber
{
public:

    void initialise();
    
    void setValue();
    void publishValue();
    
private:

    // string ID

};