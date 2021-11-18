#include "PID.h"
#include "encoder.h"
#include "user_motor_init.h"
#include "command.h"
Status Delta_PID(Delta_PID_TypeDef* Object)
{
	static int cnt = 0;
	if(cnt < 100)
	{
		++cnt;
	}
	else
	{
		cnt = 0;
		
		float T = 0.01;
		float a_0 = Object->Kp + Object->Ki*T+Object->Kd/T;
		float a_1 = Object->Kp + 2* Object->Kd/T;
		float a_2 = Object->Kd/T;
		Object->err = Object->target_speed - M1_speed;  
		//Object->proportion = Object->err-Object->err_last;                            
		//Object->integral = Object->err;
		//Object->derivative = (Object->err - 2*Object->err_last + Object->err_last_2);
		//Object->delta = Object->Kp * Object->proportion + 
		//				Object->Ki * Object->integral + 
		//				Object->Kd * Object->derivative; //计算得到PID增量
		Object->delta = a_0 * Object->err -a_1 *Object->err_last +a_2*Object->err_last_2;
		Object->PWM = Object->PWM + Object->delta; //计算最终的PID输出
		if(Object->PWM > 1000)
		{
			Object->PWM = 1000;
		}
		if(Object->PWM < 0)
		{
			Object->PWM = 0;
		}
		direct_command_0x01(0,Object->PWM);
		
		Object->err_last_2 = Object->err_last; //更新上上次偏差
		Object->err_last = Object->err; //更新上次偏差
	}
	return 0;
}