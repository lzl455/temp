/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: led.c
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#include <string.h>
#include "om_driver.h"

#include "main.h"
#include "led.h"
#include "led_logo_tbl.h"

//-----------------------------------------------------------------------------;
// 常量定义区
//

//-----------------------------------------------------------------------------;
// 变量定义区
//


//-----------------------------------------------------------------------------;
// 表格定义区
//

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

const uint8_t heartbeat_table[80] = {
    0, 30, 120, 210, 230, 180, 80, 20,   // 第一跳急升急降
    30, 60, 120, 200, 255, 255, 240, 200, 140, 80, 30, 5, // 第二跳缓升缓降
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void effect_breatch(void)
{
    uint8_t i;
    if(led_speed_lev>delay_time_count)
    {
        delay_time_count++;
        return;
    }
    delay_time_count = 0;

    i = pwm_time_count;
    if(!bback_led_status)
    {
        if(pwm_time_count >= iPWM_MAX-1)
            pwm_value = 0;
        else
            pwm_value = (iPWM_MAX-1 - i);
    }
    else
    {
        if(pwm_time_count >= iPWM_MAX-1)
            pwm_value = iPWM_MAX-1;
        else
            pwm_value = i;
    }

    if(pwm_time_count == iPWM_MAX-1)   // 最亮和最暗的时间加长
    {
        pwm_time_count = 0;
        bback_led_status = !bback_led_status;
    }

    OM_PWM->PWMDC0 = pwm_value;
    pwm_time_count++;
}

void effect_heartbeat(void)
{
    static uint8_t heartbeat_index;
    if(led_speed_lev+1>delay_time_count)
    {
		delay_time_count++;
        return;
	}
    delay_time_count = 0;
    heartbeat_index++;
    if(heartbeat_index>=80)
        heartbeat_index = 0;
    OM_PWM->PWMDC0 = heartbeat_table[heartbeat_index];
}

