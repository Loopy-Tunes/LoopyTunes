void SteppedSlider::init(int ID)
{
    // set driver pointer
    
    paramID = ID;
    // fetch param from driver

    prevValue = 0;
    isSelected = false;
}

void SteppedSlider::tick()
{

}

void SteppedSlider::paint()
{
    // paint slider
}

void SteppedSlider::repaint()
{
    // update slider if value has changed

    // fetch curVal from slider pointer
}