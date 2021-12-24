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
			//M1
			cmd->motor_1_speed = MotorSpeedGet_HextoDec(&src[1]);
			if(cmd->motor_1_speed > 1000)
			{
				cmd->motor_1_speed = 1000;
			}
			else if(cmd->motor_1_speed < -1000)
			{
				cmd->motor_1_speed = -1000;
			}
			
			//M2
			cmd->motor_2_speed = MotorSpeedGet_HextoDec(&src[5]);
			if(cmd->motor_2_speed > 1000)
			{
				cmd->motor_2_speed = 1000;
			}
			else if(cmd->motor_2_speed < -1000)
			{
				cmd->motor_2_speed = -1000;
			}
			
			//M3
			cmd->motor_3_speed = MotorSpeedGet_HextoDec(&src[9]);
			if(cmd->motor_3_speed > 1000)
			{
				cmd->motor_2_speed = 1000;
			}
			else if(cmd->motor_3_speed < -1000)
			{
				cmd->motor_3_speed = -1000;
			}
			
			//M4
			cmd->motor_4_speed = MotorSpeedGet_HextoDec(&src[13]);
			if(cmd->motor_4_speed > 1000)
			{
				cmd->motor_4_speed = 1000;
			}
			else if(cmd->motor_4_speed < -1000)
			{
				cmd->motor_4_speed = -1000;
			}
			
			//S1
			cmd->servo_1 = MotorSpeedGet_HextoDec(&src[17]);
			if(cmd->servo_1 > 180)
			{
				cmd->servo_1 = 180;
			}
			else if(cmd->servo_1 < 0)
			{
				cmd->servo_1 = 0;
			}
			
			//S2
			cmd->servo_2 = MotorSpeedGet_HextoDec(&src[21]);
			if(cmd->servo_2 > 180)
			{
				cmd->servo_2 = 180;
			}
			else if(cmd->servo_2 < 0)
			{
				cmd->servo_2 = 0;
			}
			
			//S3
			cmd->servo_3 = MotorSpeedGet_HextoDec(&src[25]);
			if(cmd->servo_3 > 180)
			{
				cmd->servo_3 = 180;
			}
			else if(cmd->servo_3 < 0)
			{
				cmd->servo_3 = 0;
			}
			
			//S4
			cmd->servo_4 = MotorSpeedGet_HextoDec(&src[29]);
			if(cmd->servo_4 > 180)
			{
				cmd->servo_4 = 180;
			}
			else if(cmd->servo_4 < 0)
			{
				cmd->servo_4 = 0;
			}
			
			
			break;
			
		}
		case 1:
		{
			cmd->motor_1_speed = MotorSpeedGet_HextoDec(&src[5]);
			if(cmd->motor_1_speed > 1000)
			{
				cmd->motor_1_speed = 1000;
			}
			else if(cmd->motor_1_speed < -1000)
			{
				cmd->motor_1_speed = -1000;
			}
			
			cmd->motor_2_speed = MotorSpeedGet_HextoDec(&src[1]);
			if(cmd->motor_2_speed > 1000)
			{
				cmd->motor_2_speed = 1000;
			}
			else if(cmd->motor_2_speed < -1000)
			{
				cmd->motor_2_speed = -1000;
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
			//adjust motor 1 speed
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
			
			//adjust motor 2 speed
			if(cmd->motor_2_speed > 0)
			{
				HAL_GPIO_WritePin(MOTOR_DIR_2_GPIO_Port,MOTOR_DIR_2_Pin,GPIO_PIN_RESET);
				TIM1->CCR2 = cmd->motor_2_speed;
			}
			else
			{
				HAL_GPIO_WritePin(MOTOR_DIR_2_GPIO_Port,MOTOR_DIR_2_Pin,GPIO_PIN_SET);
				TIM1->CCR2 = 0 - cmd->motor_2_speed;
			}
			
			//adjust motor 3 speed
			if(cmd->motor_3_speed > 0)
			{
				HAL_GPIO_WritePin(MOTOR_DIR_3_GPIO_Port,MOTOR_DIR_3_Pin,GPIO_PIN_RESET);
				TIM1->CCR3 = cmd->motor_3_speed;
			}
			else
			{
				HAL_GPIO_WritePin(MOTOR_DIR_3_GPIO_Port,MOTOR_DIR_3_Pin,GPIO_PIN_SET);
				TIM1->CCR3 = 0 - cmd->motor_3_speed;
			}
			
			//adjust motor 4 speed
			if(cmd->motor_4_speed > 0)
			{
				HAL_GPIO_WritePin(MOTOR_DIR_4_GPIO_Port,MOTOR_DIR_4_Pin,GPIO_PIN_RESET);
				TIM1->CCR4 = cmd->motor_4_speed;
			}
			else
			{
				HAL_GPIO_WritePin(MOTOR_DIR_4_GPIO_Port,MOTOR_DIR_4_Pin,GPIO_PIN_SET);
				TIM1->CCR4 = 0 - cmd->motor_4_speed;
			}
			
			//adjust S1~S4 angle
				
			TIM8->CCR1 = (int)((double)cmd->servo_1*2000/180+500);
			TIM8->CCR2 = (int)((double)cmd->servo_2*2000/180+500);
			TIM8->CCR3 = (int)((double)cmd->servo_3*2000/180+500);
			TIM8->CCR4 = (int)((double)cmd->servo_4*2000/180+500);
			
			break;
		}
		case 1:
		{
			//adjust motor 1 speed
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
			//adjust motor 2 speed
			if(cmd->motor_2_speed > 0)
			{
				HAL_GPIO_WritePin(MOTOR_DIR_2_GPIO_Port,MOTOR_DIR_2_Pin,GPIO_PIN_RESET);
				TIM1->CCR2 = cmd->motor_2_speed;
			}
			else
			{
				HAL_GPIO_WritePin(MOTOR_DIR_2_GPIO_Port,MOTOR_DIR_2_Pin,GPIO_PIN_SET);
				TIM1->CCR2 = 0 - cmd->motor_2_speed;
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
