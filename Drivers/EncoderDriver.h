#ifndef ENCODERDRIVER_H
#define ENCODERDRIVER_H

#include "../Parameters/SteppedParameter.h"

/*****************************************************************************//**
 *  Class name: EncoderDriver
 *  Function: Driver for the encoder input, controls the value of FX parameters
 * 
 *  Based off of Encoder class from libDaisy (Stephen Hensley, 2019)
 *  https://github.com/electro-smith/libDaisy/blob/master/src/hid/encoder.h
 ********************************************************************************/

class EncoderDriver
{
public:

    /***********************************************************************//**
    * @brief Initialises the driver
    * @param button The pin used for the centre push button
    * @param a The pin used for channel A of the encoder
    * @param b The pin used for channel B of the encoder
    * @param navCb The function used for navigation
    ***************************************************************************/
    void init(dsy_gpio_pin button, dsy_gpio_pin a, dsy_gpio_pin b, std::function<void()> navCb)
    {
        parameters.reserve(70);

        prevUpdate = 0;
        isUpdated = false;

        isNavigation = true;
        navCallback = navCb;

        currentParam = 0;
        valueA = 0xFF;
        valueB = 0xFF;

        btn.Init(button);
        
        channelA.pin = a;
        channelB.pin = b;
        channelA.mode = DSY_GPIO_MODE_INPUT;
        channelB.mode = DSY_GPIO_MODE_INPUT;
        channelA.pull = DSY_GPIO_PULLUP;
        channelB.pull = DSY_GPIO_PULLUP;
        dsy_gpio_init(&channelA);
        dsy_gpio_init(&channelB);

        // FOR TESTING
        currentParam = 3;
    }

    /***********************************************************************//**
    * @brief Polls the inputs to see if a change has occured
    ***************************************************************************/
    void tick()
    {
        u_int32_t now = System::GetNow();
        if(now - prevUpdate >= 1) // adjust to change update rate, 1 = 1000Hz, 2 = 2000Hz etc.
        {
            prevUpdate = now;

            // Shift Button states to debounce
            valueA = (valueA << 1) | dsy_gpio_read(&channelA);
            valueB = (valueB << 1) | dsy_gpio_read(&channelB);

            if(!isNavigation)
            {
                if((valueA & 0x03) == 0x02 && (valueB & 0x03) == 0x00)
                    parameters[currentParam]->decrement();
                else if((valueB & 0x03) == 0x02 && (valueA & 0x03) == 0x00)
                    parameters[currentParam]->increment();
            }
        }

        btn.Debounce();
        if(btn.Pressed())
            buttonCallback();
    }

    /***********************************************************************//**
    * @brief The callback function executed when the centre button 
    ***************************************************************************/
    void buttonCallback()
    {
        if(isNavigation)
            navCallback();
    }

    /***********************************************************************//**
    * @brief Gets the state of the encoder's centre button
    * @return If the button is pressed or not
    ***************************************************************************/
    bool getButtonState() { return btn.Pressed(); }

    /********************************************************************************//**
    * @brief Gets the bypass callback for a given index from the bypassCallbacks vector
    ************************************************************************************/
    std::function<void()> getBypassCallback(size_t index) { return bypassCallbacks.at(index); }

    /***********************************************************************//**
    * @brief Sets the current parameter the encoder is assigned to
    * @param newID The ID of the parameter the encoder is to be assigned to
    ***************************************************************************/
    void setCurrentParam(int newID)
    { 
        for(unsigned int i = 0 ; i < parameters.size() ; i++)
        {
            if(parameters[i]->getID() == newID)
            {
                currentParam = i;
                break;
            }
        }
    }

    /***********************************************************************//**
    * @brief Adds a parameter to the parameter vector
    * @param newParam A pointer to the parameter to be added to the vector
    ***************************************************************************/
    void addParameter(SteppedParameter* newParam)
    {
        parameters.push_back(newParam);
    }

    /***********************************************************************//**
    * @brief Adds a bypass callback to the bypassCallbacks vector
    * @param newCallback The callback function to be added
    ***************************************************************************/
    void addBypassCallback(std::function<void()> newCallback)
    {
        bypassCallbacks.push_back(newCallback);
    }

    /***********************************************************************//**
    * @brief Gets a pointer to the parameter with the given index
    * @param paramID The ID of the parameter to be fetched
    ***************************************************************************/
    SteppedParameter* getParameter(int paramID)
    {
        for(unsigned int i = 0 ; i < parameters.size() ; i++)
        {
            if(parameters[i]->getID() == paramID)
                return parameters[i];
            else
                return nullptr;
        }
    }

private:

    bool isUpdated;
    uint32_t prevUpdate;

    bool isNavigation;
    std::function<void()> navCallback;

    int currentParam;
    std::vector<SteppedParameter*> parameters;
    std::vector<std::function<void()>> bypassCallbacks;

    Switch btn;
    dsy_gpio channelA;
    dsy_gpio channelB;

    uint8_t valueA;
    uint8_t valueB;
};

#endif