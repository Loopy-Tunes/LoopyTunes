#ifndef KEYPADDRIVER_H
#define KEYPADDRIVER_H

#include "../Parameters/BinaryParameter.h"

/*****************************************************************************//**
 *  Class name: KeypadDriver
 *  Function: Driver for the keypad input, controls the movement between scenes
 ********************************************************************************/

class KeypadDriver
{
public:

    void init(dsy_gpio_pin t, dsy_gpio_pin b, dsy_gpio_pin l, dsy_gpio_pin r)
    {
        top.init(t, 1000, [this] { topPressed(); });
        bottom.init(b, 1000, [this] { bottomPressed(); });
        right.init(l, 1000, [this] { rightPressed(); });
        left.init(r, 1000, [this] { leftPressed(); });
    }

    void topPressed()
    {
        index.col++;
    }
    
    void bottomPressed()
    {
        index.col--;
    }

    void rightPressed()
    {
        index.row++;
    }

    void leftPressed()
    {
        index.row--;
    }

private:

    struct Index
    {
        int row;
        int col;
    } index;

    BinaryParameter top;
    BinaryParameter bottom;
    BinaryParameter right;
    BinaryParameter left;
};

#endif