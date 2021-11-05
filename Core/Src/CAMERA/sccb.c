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

#define SCCB_READ_SDA    HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)     //����SDA
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

//SCCB��ʼ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĸߵ���,ΪSCCB��ʼ�ź�
//�ڼ���״̬��,SDA��SCL��Ϊ�͵�ƽ
void SCCB_Start(void)
{
	
    SCCB_SDA(1);     //�����߸ߵ�ƽ	   
    SCCB_SCL(1);	    //��ʱ���߸ߵ�ʱ���������ɸ�����
    HAL_Delay(1);  
	
    SCCB_SDA(0);
    HAL_Delay(1);  
	
    SCCB_SCL(0);	    //�����߻ָ��͵�ƽ��������������Ҫ	  
}

//SCCBֹͣ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĵ͵���,ΪSCCBֹͣ�ź�
//����״����,SDA,SCL��Ϊ�ߵ�ƽ
void SCCB_Stop(void)
{
    SCCB_SDA(0);
    HAL_Delay(1);
	
    SCCB_SCL(1);	
    HAL_Delay(1); 
	
    SCCB_SDA(1);	
    HAL_Delay(1);  
}

//����NA�ź�
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
	for(j=0;j<8;j++) //ѭ��8�η�������
	{
		if(dat&0x80)SCCB_SDA(1);	
		else SCCB_SDA(0);
		dat<<=1;
		HAL_Delay(1);  
		SCCB_SCL(1);	
		HAL_Delay(1);  
		SCCB_SCL(0);		   
	}			 
	SCCB_SDA_IN();		//����SDAΪ���� 
    HAL_Delay(1);  
	SCCB_SCL(1);			//���յھ�λ,���ж��Ƿ��ͳɹ�
    HAL_Delay(1);  
	if(SCCB_READ_SDA)res=1;  //SDA=1����ʧ�ܣ�����1
	else res=0;         //SDA=0���ͳɹ�������0
	SCCB_SCL(0);		 
	SCCB_SDA_OUT();		//����SDAΪ���    
	return res;  
}	 
//SCCB ��ȡһ���ֽ�
//��SCL��������,��������
//����ֵ:����������
uint8_t SCCB_RD_Byte(void)
{
	uint8_t temp=0,j;    
	SCCB_SDA_IN();		//����SDAΪ����  
	for(j=8;j>0;j--) 	//ѭ��8�ν�������
	{		     	  
		HAL_Delay(1);  
		SCCB_SCL(1);
		temp=temp<<1;
		if(SCCB_READ_SDA)temp++;   
		HAL_Delay(1);  
		SCCB_SCL(0);
	}	
	SCCB_SDA_OUT();		//����SDAΪ���    
	return temp;
}

#ifdef OV2640_DevE
//The reg of OV2640 is 8-bit
//0: OK, 1:ERROR 
uint8_t SCCB_WR_Reg(uint16_t reg, uint8_t data)
{
	uint8_t res=0;
	SCCB_Start(); 					//����SCCB����
	if(SCCB_WR_Byte(OV2640_ADDR))res=1;	//д����ID
	HAL_Delay(1);
	
   	if(SCCB_WR_Byte(reg))res=1;		//д�Ĵ���8λ��ַ		  
   	HAL_Delay(1);
	
	if(SCCB_WR_Byte(data))res=1; 	//д����	 
  	SCCB_Stop();
	HAL_Delay(1);

  	return	res;
}

uint8_t SCCB_RD_Reg(uint16_t reg)
{
	uint8_t val=0;
	SCCB_Start(); 				//����SCCB����
	SCCB_WR_Byte(OV2640_ADDR);	//д����ID
	HAL_Delay(1);
	
  	SCCB_WR_Byte(reg);			//д�Ĵ�����8λ��ַ
	HAL_Delay(1);
	
 	SCCB_Stop();
	HAL_Delay(1);
	
 	//Read after writing the addr
	SCCB_Start();
	SCCB_WR_Byte(OV2640_ADDR|0X01);//���Ͷ�����
    HAL_Delay(1);
	
   	val=SCCB_RD_Byte();		 	//��ȡ����
  	SCCB_No_Ack();
  	SCCB_Stop();
  	return val;
}
#endif
