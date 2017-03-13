//
// Created by wahba on 13/03/2017.
//

#ifndef PINCONTROL_PIN_H
#define PINCONTROL_PIN_H

#ifndef _PROPELLER_H_

#include <propeller.h>

#endif

#define GlobalCoreDirection _DIRA
#define GlobalCoreOutput _OUTA
#define GlobalCoreRead _INA

class pin {
public:
    pin(int pin, unsigned int Dir){
        if (Dir==0){
            GlobalCoreDirection &= ~(1 << pin);
            _Dir = 0;
        } else{
            GlobalCoreDirection |= 1 << pin;
            _Dir = 1;
        }

    }

    /*
     * toggle, set and clear
     *
     * All below functions take uint8_t input and return nothing
     */

    void togglePin() {
        GlobalCoreOutput ^= 1 << pinNumber;
    }

    void setPin() {
        GlobalCoreOutput |= 1 << pinNumber;
    }

    void clearPin() {
        GlobalCoreOutput &= ~(1 << pinNumber);
    }

    /**
     * @brief       This function value pin value.
     *              Checks if pin is an input, if not it returns -1.
     *
     * @param pin   uint8 indicating which pin to read
     * @return      returns _INA ANDED with a one at pin position
     *              then that value is shifted by "pin" times
     *              result is int 1 or 0  or -1 if not input.
     */
    int readPin(uint_fast8_t pin) {
        if ((GlobalCoreDirection && 1 << pin) != 1 << pin) { return -1; }
        return (GlobalCoreRead && (1 << pin)) >> pin;
    }

private:
    uint_fast8_t pinNumber;
    bool _Dir;

public:
    uint_fast8_t getPinNumber() const {
        //simple getter
        return pinNumber;
    }

    bool getDirection() const {
        //simple getter
        return _Dir;
    }

    void flipDirection(){
        //xor pin
        GlobalCoreDirection ^= 1 << pinNumber;
    }

    bool operator==(const pin &rhs) const {
        return _Dir == rhs._Dir;
    }

    bool operator!=(const pin &rhs) const {
        return !(rhs == *this);
    }
};


#endif //PINCONTROL_PIN_H
