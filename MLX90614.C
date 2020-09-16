#include "MLX90614.h"
#include "IIC.h"
#include "lib.h"
u16 mah[5];
u8 ReadTemp(short* Tempdat) 		
{
	u8 ACK=0,templ=0,temph=0,err=0;	 
	IIC_Start();  				 
	IIC_Send_Byte(0xb4);	//���ʹӵ�ַ	 
	ACK|=IIC_Wait_Ack();	   
  IIC_Send_Byte(0x07);   		//��������
	ACK|=IIC_Wait_Ack(); 	 										  		   
	IIC_Start();  	 	   		//��������
	IIC_Send_Byte(0xb4+1);	//���ӵ�ַ 
	ACK|=IIC_Wait_Ack();	   
	templ=IIC_Read_Byte(1);		//��ȡһ���ֽ�,�������ٶ�,����NAK 	
	temph=IIC_Read_Byte(1);		//��ȡһ���ֽ�,�������ٶ�,����NAK 	
	err=IIC_Read_Byte(0);		  //��ȡһ���ֽ�,�������ٶ�,����NAK 
	IIC_Stop();					//����һ��ֹͣ���� 
	*Tempdat=(temph<<8)|templ;
	return ACK|err;				//���ض�����ֵ
} 

void CALTEMP(u32 TEMP) 
{ 
  u32 T; 
  u32 a,b; 
  u8 A4,A5,A6,A7,A8; 
  T=TEMP*2; 
  if(T>=27315) 
  { 
    T=T-27315; 
    a=T/100; 
    b=T-a*100; 
    if(a>=100) 
    { 
       A4=a/100; 
       a=a%100; 
       A5=a/10; 
       a=a%10; 
       A6=a; 
    } 
    else if(a>=10) 
	  { 
       A4=0; 
       A5=a/10; 
       a=a%10; 
       A6=a; 
    } 
	  else 
	  { 
       A4=0; 
       A5=0; 
       A6=a; 
    } 
    if(b>=10) 
    { 
			 A7=b/10; 
       b=b%10; 
       A8=b; 
		} 
    else 
	  { 
       A7=0; 
       A8=b; 
		} 
	} 
  else 
	{ 
    T=27315-T; 
    a=T/100; 
	  b=T-a*100; 
		A4=9; 
    if(a>=10) 
	  { 
       A5=a/10; 
       a=a%10; 
       A6=a; 
    } 
    else 
	  { 
       A5=0; 
       A6=a; 
    } 
    if(b>=10) 
	  { 
       A7=b/10; 
       b=b%10; 
       A8=b; 
    } 
    else 
    { 
       A7=0; 
       A8=b; 
    } 
  } 
  mah[4]=A8; 
  mah[3]=A7; 
  mah[2]=A6; 
  mah[1]=A5; 
  mah[0]=A4; 
} 

short _READ_Tempdata(void)
{
	 short Tempdat;
   ReadTemp(&Tempdat);
	 CALTEMP(Tempdat);
	 Tempdat=mah[1]*10+mah[2];
	 return Tempdat;
}	