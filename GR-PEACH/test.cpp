#ifndef INCLUDED_IR_H
#define INCLUDED_IR_H

#include "mbed.h"

DigitalOut irout(P4_0);

class IR{
private:
    
    Timer timer;
    
    void wait_ms(int i){
        timer.reset();
        timer.start();
        while(timer.read_ms() < i){ }
        timer.stop();
        return;
    }
    
    void send1bit(char i){
        if(i>1) i=1;
        if(i==0) irout = 0;
        else irout = 1;
    }
    
    void send1data(char i){
        char data = i;
        for(int t=0; t<4; t++){
            send1bit((data>>(3-t)) & 1);
            wait_ms(5);
        }
    }
    
    
public:
    
    IR(){
        
    }
    
    void sendIR(char *data, int length){
        char parity = (char)(length);
        
        //パリティ生成
        for(int i=0; i<length; i++){
            parity += data[i];
        }
        parity &= 15;
        parity = 15 - parity;
        
        //ヘッダ
        send1data(15);
        send1data(15);
        send1data(0);
        
        //データ
        send1data((char)(length));
        for(int i=0; i<length; i++){
            send1data(data[i]);
        }
        
        //フッタ
        send1data(parity);
        send1data(0);
        send1data(0);
    }
    
    
    ~IR(){
        
    }
    
};


#endif





    IR ir;
    char data[3] = {5, 15, 5};
    
    blueled = 1;
    ir.sendIR(data, 3);