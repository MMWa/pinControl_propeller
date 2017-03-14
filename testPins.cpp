#include "simpletools.h"
#include "pinClasses/pin.h"
#include "pinClasses/pinGroup.h"


int main() {
    //Direction output is anything other that zero
    pin pin1(23, 2), pin2(21, 0), pin3(17, 0), pin4(19, 1);
    int pinsarr[] = {17, 15, 25};
    pinGroup group1(pinsarr, 3);
    while (1) {

        pin1.togglePin();
        pin4.setPin();
        sleep(1);

        pin4.togglePin();

        sleep(1);

        pin2.flipDirection();

        sleep(1);


        pin2.flipDirection();

        sleep(1);

        group1.toggleAll();

    }
    return 0;
}