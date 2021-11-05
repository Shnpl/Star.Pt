#ifndef __USMART_STR_H__
#define __USMART_STR_H__	 
#include "main.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com 
//版本：V3.3
//版权所有，盗版必究。
//Copyright(C) 正点原子 2011-2021
//All rights reserved
//********************************************************************************
//升级说明
//V1.4
//增加了对参数为string类型的函数的支持.适用范围大大提高.
//优化了内存占用,静态内存占用为79个字节@10个参数.动态适应数字及字符串长度
//V2.0 
//1,修改了list指令,打印函数的完整表达式.
//2,增加了id指令,打印每个函数的入口地址.
//3,修改了参数匹配,支持函数参数的调用(输入入口地址).
//4,增加了函数名长度宏定义.	
//V2.1 20110707		 
//1,增加dec,hex两个指令,用于设置参数显示进制,及执行进制转换.
//注:当dec,hex不带参数的时候,即设定显示参数进制.当后跟参数的时候,即执行进制转换.
//如:"dec 0XFF" 则会将0XFF转为255,由串口返回.
//如:"hex 100" 	则会将100转为0X64,由串口返回
//2,新增usmart_get_cmdname函数,用于获取指令名字.
//V2.2 20110726	
//1,修正了void类型参数的参数统计错误.
//2,修改数据显示格式默认为16进制.
//V2.3 20110815
//1,去掉了函数名后必须跟"("的限制.
//2,修正了字符串参数中不能有"("的bug.
//3,修改了函数默认显示参数格式的修改方式. 
//V2.4 20110905
//1,修改了usmart_get_cmdname函数,增加最大参数长度限制.避免了输入错误参数时的死机现象.
//2,增加USMART_ENTIM2_SCAN宏定义,用于配置是否使用TIM2定时执行scan函数.
//V2.5 20110930
//1,修改usmart_init函数为void usmart_init(uint8_t sysclk),可以根据系统频率自动设定扫描时间.(固定100ms)
//2,去掉了usmart_init函数中的uart_init函数,串口初始化必须在外部初始化,方便用户自行管理.
//V2.6 20111009
//1,增加了read_addr和write_addr两个函数.可以利用这两个函数读写内部任意地址(必须是有效地址).更加方便调试.
//2,read_addr和write_addr两个函数可以通过设置USMART_USE_WRFUNS为来使能和关闭.
//3,修改了usmart_strcmp,使其规范化.			  
//V2.7 20111024
//1,修正了返回值16进制显示时不换行的bug.
//2,增加了函数是否有返回值的判断,如果没有返回值,则不会显示.有返回值时才显示其返回值.
//V2.8 20111116
//1,修正了list等不带参数的指令发送后可能导致死机的bug.
//V2.9 20120917
//1,修改了形如：void*xxx(void)类型函数不能识别的bug。
//V3.0 20130425
//1,新增了字符串参数对转义符的支持。
//V3.1 20131120
//1,增加runtime系统指令,可以用于统计函数执行时间.
//用法:
//发送:runtime 1 ,则开启函数执行时间统计功能
//发送:runtime 0 ,则关闭函数执行时间统计功能
///runtime统计功能,必须设置:USMART_ENTIMX_SCAN 为1,才可以使用!!
//V3.2 20140828
//1,修改usmart_get_aparm函数,加入+/-符号的支持
//2,修改usmart_str2num函数,支持负数转换
//V3.3 20160506
//修正usmart_exe函数在USMART_ENTIMX_SCAN为0的时候，报错的bug
/////////////////////////////////////////////////////////////////////////////////////
  
uint8_t usmart_get_parmpos(uint8_t num);						//得到某个参数在参数列里面的起始位置
uint8_t usmart_strcmp(uint8_t*str1,uint8_t *str2);					//对比两个字符串是否相等
uint32_t usmart_pow(uint8_t m,uint8_t n);							//M^N次方
uint8_t usmart_str2num(uint8_t*str,uint32_t *res);					//字符串转为数字
uint8_t usmart_get_cmdname(uint8_t*str,uint8_t*cmdname,uint8_t *nlen,uint8_t maxlen);//从str中得到指令名,并返回指令长度
uint8_t usmart_get_fname(uint8_t*str,uint8_t*fname,uint8_t *pnum,uint8_t *rval);		//从str中得到函数名
uint8_t usmart_get_aparm(uint8_t *str,uint8_t *fparm,uint8_t *ptype); 	//从str中得到一个函数参数
uint8_t usmart_get_fparam(uint8_t*str,uint8_t *parn);  			//得到str中所有的函数参数.
#endif











