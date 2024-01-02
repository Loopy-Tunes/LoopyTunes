/**************************************************************************//**
 *  Class name: Subscriber
 *  Function: Base class for DSP parameters to receive UI widget values
 *****************************************************************************/

class Subscriber
{
public:

    void subscribe();
    
    void setValue();
    void getValue();
    
private:

    // string ID

    volatile float value;
    volatile bool valueHasChanged;

};