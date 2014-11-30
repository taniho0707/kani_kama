#include "mbed.h"
#include "ir.h"

DigitalOut blueled(LED_BLUE);

int main(){
    IR ir;
    char data[3] = {5, 15, 4};
    
    blueled = 1;
    ir.sendIR(data, 3);
    
    while(true){
        blueled = 0;
    }
}

