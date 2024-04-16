#ifndef KEYPADDRIVER_H
#define KEYPADDRIVER_H

#include "../Parameters/BinaryParameter.h"

/*****************************************************************************//**
 *  Class name: KeypadDriver
 *  Function: Driver for the keypad input, controls the movement between views
 ********************************************************************************/

class KeypadDriver
{
public:
    KeypadDriver() { index.row = index.col = 0; }

    void init(dsy_gpio_pin t, dsy_gpio_pin b, dsy_gpio_pin l, dsy_gpio_pin r)
    {
        top.init(t, 1000, [this] { topPressed(); });
        bottom.init(b, 1000, [this] { bottomPressed(); });
        left.init(l, 1000, [this] { leftPressed(); });
        right.init(r, 1000, [this] { rightPressed(); });
    }

    void tick()
    {
        top.tick();
        bottom.tick();
        left.tick();
        right.tick();
    }

    struct Index
    {
        int row;
        int col;
    };

    Index getIndex() const
    {
        return index;
    }

    bool isTopPressed() { return top.isPressed();}
    bool isBottomPressed() { return bottom.isPressed();}
    bool isRightPressed() { return right.isPressed();}
    bool isLeftPressed() { return left.isPressed();}

    

private:
    void topPressed()
    {
        index.col--; // Move up through the effects
        wrapIndex();
    }

    void bottomPressed()
    {
        index.col++; // Move down through the effects
        wrapIndex();
    }

    void leftPressed()
    {
        index.row++;
        wrapIndex();
    }

    void rightPressed()
    {
        index.row--;
        wrapIndex();
    }

    void wrapIndex()
    {
        // Wrap index.row for number of tracks
        if(index.row < 0) index.row += 4;
        else if(index.row >= 4) index.row -= 4;

        // Wrap index.col for the number of effects 
        if(index.col < 0) index.col += 5;
        else if(index.col >= 5) index.col -= 5;
    }

    Index index;
    BinaryParameter top;
    BinaryParameter bottom;
    BinaryParameter left;
    BinaryParameter right;
};

#endif 