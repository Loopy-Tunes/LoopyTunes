#ifndef KEYPADDRIVER_H
#define KEYPADDRIVER_H

#include "Parameters/BinaryParameter.h"

/*****************************************************************************//**
 *  Class name: KeypadDriver
 *  Function: Driver for the keypad input, controls the movement between scenes
 ********************************************************************************/

class KeypadDriver
{
public:

    // init

    // init top
    // init bottom
    // init left
    // init right

private:

    BinaryParameter top;
    BinaryParameter bottom;
    BinaryParameter left;
    BinaryParameter right;
};

#endif