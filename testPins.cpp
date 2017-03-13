#include "simpletools.h"
#include "pinClasses/pin.h"
#include "pinClasses/pinGroup.h"


int main() {
    //Direction output is anything other that zero
    pin pin1(23, 2), pin2(21, 0), pin3(17, 0), pin4(19, 1);
    int pinsarr[] = {17,15,25};
    pinGroup group1(pinsarr,3);
    while (1) {
        if (pin3 == pin4) {
            pin1.togglePin();
            pin4.setPin();
        } else {
            pin4.togglePin();
        }
        sleep(1);

        if (pin2 != pin3){
            pin2.flipDirection();
        }
        sleep(1);

        if (pin2 == pin4){
            pin2.flipDirection();
        }
        sleep(1);

        group1.toggleAll();

    }
    return 0;
}