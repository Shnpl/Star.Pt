#ifndef __SCCB_H__
#define __SCCB_H__
#include "main.h"

void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);

uint8_t SCCB_WR_Byte(uint8_t dat);
uint8_t SCCB_RD_Byte(void);
uint8_t SCCB_WR_Reg(uint16_t reg, uint8_t data);
uint8_t SCCB_RD_Reg(uint16_t reg);

#endif
