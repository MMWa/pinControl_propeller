//
// Created by wahba on 12/03/2017.
//

#ifndef PINCONTROL_MULTIPINCONTROL_H
#define PINCONTROL_MULTIPINCONTROL_H

#ifndef _PROPELLER_H_
#include <propeller.h>
#endif

#define GlobalCoreDirection _DIRA
#define GlobalCoreOutput _OUTA
#define GlobalCoreRead _INA

/*
 * Simple class to Manage Multiple pin control
 */

class pinGroup {
public:
    pinGroup(int pins[], int length) {
        //make sure pin mask is empty
        localOutMask = 0;
        maskSize = length;
        for (int i = 0; i < length; i++) {
            //b'10000...' then shifted by the pin number to desired position
            //then set in by equal OR
            localOutMask |= 1 << pins[i];
        }
        //set the _DIRA to localOutMask
        GlobalCoreDirection |= localOutMask;
    }

    /*
     * Do operations on all pins in constructor Mask
     * toggle, set and clear
     */
    void toggleAll(){
        GlobalCoreOutput ^= localOutMask;
    }

    void setAll(){
        GlobalCoreOutput |= localOutMask;
    }

    void clearAll(){
        GlobalCoreOutput &= ~localOutMask;
    }



private:
    uint_fast8_t maskSize;

    unsigned int localOutMask,localInMask;

};


#endif //PINCONTROL_MULTIPINCONTROL_H
