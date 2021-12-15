#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "main.h"

typedef struct
{
	int32_t type;

	int32_t motor_1_speed;
	int32_t motor_2_speed;
	int32_t motor_3_speed;
	int32_t motor_4_speed;

	int32_t servo_1;
	int32_t servo_2;
	int32_t servo_3;
	int32_t servo_4;
} CommandTypeDef;


uint8_t PreProcessCommand(uint8_t *src, int32_t length, CommandTypeDef *cmd);
uint8_t ProcessCommand(CommandTypeDef *cmd);
#endif
