#ifndef STEPPEDSLIDER_H
#define STEPPEDSLIDER_H

/********************************************************//**
 *  Class name: SteppedSlider
 *  Function: Slider for representing stepped parameters
 ***********************************************************/

class SteppedSlider
{
public:

    void init(int ID);
    void tick();

    void setIsSelected(bool s) { isSelected = s; }

    void paint();
    void repaint();

private:

    // pointer to driver
    
    int paramID;
    // pointer to parameter
    float prevVal;
    bool isSelected;
};

#endif