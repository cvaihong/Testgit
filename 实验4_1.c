#include "reg52.h"
bit read_flag = 0;	// 读取的标志位
unsigned char ch;		// 存放读取到的字符
// 串口通信的初始化
void init_serialcom( void ) 
   { 
     SCON = 0x50 ;  //SCON: serail mode 1, 8-bit UART, enable ucvr 
	   TMOD |= 0x20 ; //TMOD: timer 1, mode 2, 8-bit reload 
	   PCON |= 0x80 ; //SMOD=1; 
	   TH1 = 0xFA ;   //Baud:9600 fosc=11.0592MHz 
	   IE |= 0x90 ;   //Enable Serial Interrupt 
	   TR1 = 1 ;     // timer 1 run 
	   TI=1; 
	}
// 发送字符
void send_char_com( unsigned char ch) { 
	SBUF = ch; 
	while (TI== 0); 
	TI= 0 ; 
}
// 串口监听字符
void serial () interrupt 4 using 3 { 
	if (RI) {  
		RI = 0 ; 
		ch=SBUF; 
		read_flag= 1 ;	
		}
}

void main(){
	init_serialcom();					
	while(1){
	if(read_flag==1){				// 判断是否读取到数据
				send_char_com(ch);	// 将读取到的数据发送出去
				read_flag=0;				// 将读取标志清零
		}
	}
}
