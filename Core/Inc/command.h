#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "main.h"
#include "general.h"
uint8_t direct_command_0x01(int32_t motor_spd1,int32_t motor_spd2);
Status Get_Current_Spd(uint8_t target);
Status Change_M1_Spd(int8_t target1000);
Status Change_M1_PID(int8_t Kp1000,int8_t Ki1000,int8_t Kd1000);
Status PrintPID(void);
#endif
