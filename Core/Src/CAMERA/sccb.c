#include "sccb.h"
#include "camera.h"
#include "ov2640.h"
//SCCB_SCL:PB10
//SCCB_SDA:PB11
//I or O
#define SCCB_SDA_IN()  {GPIOB->MODER&=~(3<<(11*2));GPIOB->MODER|=0<<11*2;}	//PB11 Input mode
#define SCCB_SDA_OUT() {GPIOB->MODER&=~(3<<(11*2));GPIOB->MODER|=1<<11*2;}    //PB11 Output mode
//IO
#define SCCB_SCL(n)  (n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET)) //SCL
#define SCCB_SDA(n)  (n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET)) //SDA

#define SCCB_READ_SDA    HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)     //输入SDA
/*
#define SCCB_SCL_Pin GPIO_PIN_10
#define SCCB_SCL_GPIO_Port GPIOB
#define SCCB_SDA_Pin GPIO_PIN_11
#define SCCB_SDA_GPIO_Port GPIOB
*/
void SCCB_Init(void)
{
	//GPIO of SCCB(I2C) has been initialized in gpio.c
}

//SCCB起始信号
//当时钟为高的时候,数据线的高到低,为SCCB起始信号
//在激活状态下,SDA和SCL均为低电平
void SCCB_Start(void)
{
	
    SCCB_SDA(1);     //数据线高电平	   
    SCCB_SCL(1);	    //在时钟线高的时候数据线由高至低
    HAL_Delay(1);  
	
    SCCB_SDA(0);
    HAL_Delay(1);  
	
    SCCB_SCL(0);	    //数据线恢复低电平，单操作函数必要	  
}

//SCCB停止信号
//当时钟为高的时候,数据线的低到高,为SCCB停止信号
//空闲状况下,SDA,SCL均为高电平
void SCCB_Stop(void)
{
    SCCB_SDA(0);
    HAL_Delay(1);
	
    SCCB_SCL(1);	
    HAL_Delay(1); 
	
    SCCB_SDA(1);	
    HAL_Delay(1);  
}

//产生NA信号
void SCCB_No_Ack(void)
{
    HAL_Delay(1);  
	SCCB_SDA(1);	
	SCCB_SCL(1);	
    HAL_Delay(1);  
	SCCB_SCL(0);	
    HAL_Delay(1);  
	SCCB_SDA(0);	
    HAL_Delay(1);  
}
uint8_t SCCB_WR_Byte(uint8_t dat)
{
	uint8_t j,res;	 
	for(j=0;j<8;j++) //循环8次发送数据
	{
		if(dat&0x80)SCCB_SDA(1);	
		else SCCB_SDA(0);
		dat<<=1;
		HAL_Delay(1);  
		SCCB_SCL(1);	
		HAL_Delay(1);  
		SCCB_SCL(0);		   
	}			 
	SCCB_SDA_IN();		//设置SDA为输入 
    HAL_Delay(1);  
	SCCB_SCL(1);			//接收第九位,以判断是否发送成功
    HAL_Delay(1);  
	if(SCCB_READ_SDA)res=1;  //SDA=1发送失败，返回1
	else res=0;         //SDA=0发送成功，返回0
	SCCB_SCL(0);		 
	SCCB_SDA_OUT();		//设置SDA为输出    
	return res;  
}	 
//SCCB 读取一个字节
//在SCL的上升沿,数据锁存
//返回值:读到的数据
uint8_t SCCB_RD_Byte(void)
{
	uint8_t temp=0,j;    
	SCCB_SDA_IN();		//设置SDA为输入  
	for(j=8;j>0;j--) 	//循环8次接收数据
	{		     	  
		HAL_Delay(1);  
		SCCB_SCL(1);
		temp=temp<<1;
		if(SCCB_READ_SDA)temp++;   
		HAL_Delay(1);  
		SCCB_SCL(0);
	}	
	SCCB_SDA_OUT();		//设置SDA为输出    
	return temp;
}

#ifdef OV2640_DevE
//The reg of OV2640 is 8-bit
//0: OK, 1:ERROR 
uint8_t SCCB_WR_Reg(uint16_t reg, uint8_t data)
{
	uint8_t res=0;
	SCCB_Start(); 					//启动SCCB传输
	if(SCCB_WR_Byte(OV2640_ADDR))res=1;	//写器件ID
	HAL_Delay(1);
	
   	if(SCCB_WR_Byte(reg))res=1;		//写寄存器8位地址		  
   	HAL_Delay(1);
	
	if(SCCB_WR_Byte(data))res=1; 	//写数据	 
  	SCCB_Stop();
	HAL_Delay(1);

  	return	res;
}

uint8_t SCCB_RD_Reg(uint16_t reg)
{
	uint8_t val=0;
	SCCB_Start(); 				//启动SCCB传输
	SCCB_WR_Byte(OV2640_ADDR);	//写器件ID
	HAL_Delay(1);
	
  	SCCB_WR_Byte(reg);			//写寄存器低8位地址
	HAL_Delay(1);
	
 	SCCB_Stop();
	HAL_Delay(1);
	
 	//Read after writing the addr
	SCCB_Start();
	SCCB_WR_Byte(OV2640_ADDR|0X01);//发送读命令
    HAL_Delay(1);
	
   	val=SCCB_RD_Byte();		 	//读取数据
  	SCCB_No_Ack();
  	SCCB_Stop();
  	return val;
}
#endif
