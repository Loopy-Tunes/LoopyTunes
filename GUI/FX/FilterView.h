#ifndef FILTERVIEW_H
#define FILTERVIEW_H

/*************************************************//**
 *  Class name: FilterView
 *  Function: FX level GUI class for the filter
 ****************************************************/

class FilterView
{
public:

    void init(int ID);
    void tick();

    void paint();
    void clear();

    void updateParameters();

private:

    // lcd driver pointer
    // keypad driver

    // parameter controls

    bool isOpen;
    int effectID;
};

#endif