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
    pin(int pin, unsigned int Dir) : zero(0) {
        pinSelect = 1 << pin;
        if (Dir == 0) {
            GlobalCoreDirection &= ~(pinSelect);
            _Dir = 0;
        } else {
            GlobalCoreDirection |= pinSelect;
            _Dir = 1;
        }
    }
    /*
     * toggle, set and clear
     *
     * All below functions take uint8_t input and return nothing
     */


    /**
     *
     * @return toggled to state on direction correct -1 on wrong
     */
    int togglePin() {
        if ((GlobalCoreDirection & pinSelect) != zero) {
            GlobalCoreOutput ^= pinSelect;
            return GlobalCoreOutput >> pinNumber;
        } else {
            return -1;
        }
    }


    /**
     *
     * @return 1 on direction correct -1 on wrong
     */
    int setPin() {
        if ((GlobalCoreDirection & pinSelect) != zero) {
            GlobalCoreOutput |= pinSelect;
            return 1;
        } else {
            return -1;
        }
    }


    /**
     *
     * @return 0 on direction correct -1 on wrong
     */
    int clearPin() {
        if ((GlobalCoreDirection & pinSelect) != zero) {
            GlobalCoreOutput &= ~(pinSelect);
            return 0;
        } else {
            return -1;
        }
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
    int readPin() {
        if ((GlobalCoreDirection && pinSelect) == zero) {
            return (GlobalCoreRead && (pinSelect)) >> pinNumber;
        } else {
            return -1;
        }
    }

    //these functions are slower than using the direct assembly mapped function
    int waitForChange() {
        if ((GlobalCoreDirection && pinSelect) == zero) {
            waitpne(readPin() << pinNumber, pinSelect);
            return readPin();
        } else {
            return -1;
        }
    }

    int waitEqual(unsigned int value) {
        if ((GlobalCoreDirection && pinSelect) == zero) {
            waitpeq(value << pinNumber, pinSelect);
            return readPin();
        } else {
            return -1;
        }
    }

    int waitNotEqual(unsigned int value) {
        if ((GlobalCoreDirection && pinSelect) == zero) {
            waitpne(value << pinNumber, pinSelect);
            return readPin();
        } else {
            return -1;
        }
    }

private:
    unsigned int zero;
    int pinSelect;
    uint_fast8_t pinNumber;
    bool _Dir;

public:
    uint_fast8_t getPinNumber() const {
        //simple getter
        return pinNumber;
    }

    bool getDirection() {
        //simple getter, with verification
        return _Dir = GlobalCoreDirection >> pinNumber;
    }

    //for use when direction is out
    bool getValue() {
        //simple getter
        return _Dir = GlobalCoreOutput >> pinNumber;
    }

    bool flipDirection() {
        //xor pin
        GlobalCoreDirection ^= pinSelect;
        return getDirection();
    }
/*
    bool operator==(const pin &rhs) const {
        return _Dir == rhs._Dir;
    }

    bool operator!=(const pin &rhs) const {
        return !(rhs == *this);
    }
*/
};


#endif //PINCONTROL_PIN_H
