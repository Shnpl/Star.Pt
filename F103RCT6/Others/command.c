#include "command.h"

int32_t ASCIIHextoDec(uint8_t src);
int32_t MotorSpeedGet_HextoDec(uint8_t *src);
/*RaspberryPi-->STM32:
@[0]: unused
@ 0 : direct_command_mode ,single motor
@[1:4] :M1_Speed;(Hex)


@ 0 : direct_command_mode single motor
@[1:4] :M1_Speed;(Hex)
@[5:8]:M2_Speed;(Hex)
@[9:12]:M3_speed
@[13:16]:M4 speed
@[17:19]:S1
@[20:22]:S2
@[23:25]:S3
@[26:28]:S4
*/

uint8_t PreProcessCommand(uint8_t *src, int32_t length, CommandTypeDef *cmd)
{
	cmd->type = src[0] - '0';

	switch (cmd->type)
	{
		case 0:
		{
			cmd->motor_1_speed = MotorSpeedGet_HextoDec(&src[1]);
			if(cmd->motor_1_speed > 1000)
			{
				cmd->motor_1_speed = 1000;
			}
			else if(cmd->motor_1_speed < -1000)
			{
				cmd->motor_1_speed = -1000;
			}
			break;
		}
		default:
		{
			break;
		}
	}
	return 0;
}

uint8_t ProcessCommand(CommandTypeDef *cmd)
{
	switch (cmd->type)
	{
		case 0:
		{
			if(cmd->motor_1_speed > 0)
			{
				HAL_GPIO_WritePin(MOTOR_DIR_1_GPIO_Port,MOTOR_DIR_1_Pin,GPIO_PIN_RESET);
				TIM1->CCR1 = cmd->motor_1_speed;
			}
			else
			{
				HAL_GPIO_WritePin(MOTOR_DIR_1_GPIO_Port,MOTOR_DIR_1_Pin,GPIO_PIN_SET);
				TIM1->CCR1 = 0 - cmd->motor_1_speed;
			}
			
		}
		default:
		{
			break;
		}
	}
	return 0;
}
int32_t ASCIIHextoDec(uint8_t src)
{
	int32_t ans;
	if (src >= '0' && src <= '9')
	{
		ans = src - '0';
	}
	else if (src >= 'A' && src <= 'F')
	{
		ans = src - 'A' + 10;
	}
	return ans;
}

int32_t MotorSpeedGet_HextoDec(uint8_t *src)
{
	int32_t ans = 0;
	ans = ASCIIHextoDec(src[1]) * 256 +
		  ASCIIHextoDec(src[2]) * 16 +
		  ASCIIHextoDec(src[3]);

	if (src[0] == '-')
	{
		ans = 0-ans;
	}
	return  ans;
}
