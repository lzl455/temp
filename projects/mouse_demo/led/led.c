/*******************************************************************************
* Copyright (c) 2013, SHENZHEN Co.,LTD.
* All rights reserved.
*
* �ļ�����: led.c
*
* ����˵��:
* �޸�˵��:
*******************************************************************************/
#include <string.h>
#include "om_driver.h"

#include "main.h"
#include "lvd.h"
#include "led.h"

#include "flash.h"
#include "flash_process.h"
#include "usb_cfg_info.h"
#include "matrix_key.h"

//-----------------------------------------------------------------------------;
// ����������
//


//-----------------------------------------------------------------------------;
// ����������
//
bool                            bdevice_led_status;
bool                            bled_bright_en;
bool                            bback_led_status;
bool                            bargb_valid;

uint8_t                         gtemp_i;
uint8_t                         gtemp_j;
uint8_t                         gtemp_x;

uint8_t                         device_conn_index=0;
uint8_t                         device_hint_count;

uint8_t                         led_hint_mode;
uint8_t                         led_mode_bak;

uint8_t                         logo_hint_time_count;
uint8_t                         rgb_enable;

uint8_t                         pwm_value;
uint8_t                         pwm_count;

uint8_t                         nhjb_led_index;

uint16_t                        flash_on_time;
uint16_t                        flash_off_time;
uint32_t                        led_delay_count;


uint16_t                        led_ctrl_reg;
uint16_t                        led_status_reg;
uint8_t                         led_use_flag;

uint8_t                         led_cur_mode;
uint8_t                         led_pre_mode;
enum speed_level                led_speed_lev;
unsigned char                   led_rgb_index;
unsigned char                   pwm_value;
enum led_level                  led_light_lev;
enum led_level                  led_light_lev_bak;

uint8_t                         pwm_time_count;
uint16_t                        delay_time_count;
uint8_t                         rgb_index;
uint8_t                         led_process_index;
uint8_t                         hint_time_count;

__ALIGNED(4) uint8_t            pwm_rgb_tbl[iLED_MAX][3];

uint8_t                         pwm_duty_array_0[0x10];
uint8_t                         pwm_duty_array_1[0x10];
uint8_t                         pwm_duty_array_2[0x10];
uint8_t                         pwm_duty_array_3[0x10];

extern bool                     b24g_nromal;
extern void delayus(unsigned int time);
//=============================================================================;
// ������                                                                       ;
//=============================================================================;

/*******************************************************************************
* ��������: ledc_init()
* ��������:
* ��������� ��
* ��������� ��
* ˵    ��:
*******************************************************************************/
void ledc_init(void)
{
    ledc_config_t config = {
        .reset_cycles         = 100,
        .long_pulse_cycles    = 44,
        .short_pulse_cycles   = 14,
    };
    drv_ledc_init(OM_LEDC, &config);
    bargb_valid = true;
}

void pwm_init(void)
{
    bargb_valid = true;

    DRV_RCC_CLOCK_ENABLE(RCC_CLK_PWM, 1U);
    OM_PWM->PWMCON = 0x00000001;
    OM_PWM->PWMCR0 = 0x00000001;
    OM_PWM->PWMCR1 = 0x00000000;
    OM_PWM->PWMDIV = 0x00000003;

    if(iLED_LEV_4 == led_light_lev)
        OM_PWM->PWMPRD = iPWM_MAX;
    if(iLED_LEV_3 == led_light_lev)
        OM_PWM->PWMPRD = iPWM_MAX*2;
    else if(iLED_LEV_2 == led_light_lev)
        OM_PWM->PWMPRD = iPWM_MAX*4;
    else if(iLED_LEV_1 == led_light_lev)
        OM_PWM->PWMPRD = iPWM_MAX*8;
}

/******************************************************************************
* ��������: led_status_hint
* ��������:
* �������:
* �������:
* ˵    ��:
******************************************************************************/
void led_status_hint(void)
{
    mLED_VDD_DIS;
	if(hint_led_status&bled_hint_mode)
    {
        switch (hint_led_status&0x0F)
        {
        case bled_bt0:
            mLED_NUM_LOW; 
            break;
        case bled_bt1:
            mLED_CAPS_LOW;
            break;
        case bled_bt2:
            mLED_NUM_LOW; 
            mLED_CAPS_LOW;
            break;
        case bled_24g:
            mLED_LOW_LOW; 
            break;
        case bled_bt0|bled_bt1|bled_bt2|bled_24g:
            mLED_NUM_LOW;
            mLED_CAPS_LOW;
            mLED_LOW_LOW;
            break;
        default:
            mLED_NUM_HIGH;
            mLED_CAPS_HIGH;
            mLED_LOW_HIGH;
            break;
        }
        if(0==(hint_led_status&(bled_bt0|bled_bt1|bled_bt2|bled_24g)))
            return;
    }
    else
    {
        if(kb_led_status&bnum_lock)
        {
            mLED_NUM_LOW;
        }
        else
        {
            mLED_NUM_HIGH;
        }
        if(kb_led_status&bcaps_lock)
        {
            mLED_CAPS_LOW;
        }
        else
        {
            mLED_CAPS_HIGH;
        }

        if(hint_led_status&bled_low)
        {
            mLED_LOW_LOW;
        }
        else
        {
            mLED_LOW_HIGH;
        }
    }
    mLED_VDD_EN;
}

/*******************************************************************************
* ��������: device_led_on()             
* ��������:
* ��������� ��
* ��������� ��
* ˵    ��:
*******************************************************************************/
void device_led_on(void)
{
    bdevice_led_status = true;

    hint_led_status &= 0xF0;
    if(iDEVICE_TYPE_BT0 == device_type)
        hint_led_status |= bled_bt0;
    else if(iDEVICE_TYPE_BT1 == device_type)
        hint_led_status |= bled_bt1;
    else if(iDEVICE_TYPE_BT2 == device_type)
        hint_led_status |= bled_bt2;
    else if(iDEVICE_TYPE_24G == device_type)
        hint_led_status |= bled_24g;
}

/*******************************************************************************
* ��������: device_led_off()
* ��������:
* ��������� ��
* ��������� ��
* ˵    ��:
*******************************************************************************/
void device_led_off(void)
{
    bdevice_led_status = false;

    hint_led_status &= 0xF0;
}

void logo_off(void)
{
    bargb_valid = false;
    OM_PWM->PWMCON = 0x00000000;
}

void clr_rgb(void)
{
    memset(pwm_rgb_tbl, 0x00, iLED_MAX*3);
}

void rgb_pwm0_w(void)
{
    if(rgb_enable&iPWM_R)
         pwm_rgb_tbl[gtemp_j][iR_INDEX] = pwm_duty_array_0[gtemp_x];
     else
         pwm_rgb_tbl[gtemp_j][iR_INDEX] = 0;
    if(rgb_enable&iPWM_G)
         pwm_rgb_tbl[gtemp_j][iG_INDEX] = pwm_duty_array_0[gtemp_x];
     else
         pwm_rgb_tbl[gtemp_j][iG_INDEX] = 0;
    if(rgb_enable&iPWM_B)
         pwm_rgb_tbl[gtemp_j][iB_INDEX] = pwm_duty_array_0[gtemp_x];
     else
         pwm_rgb_tbl[gtemp_j][iB_INDEX] = 0;          
}

void rgb_w_max(void)
{
    if(rgb_enable&iPWM_R)
        pwm_rgb_tbl[gtemp_j][iR_INDEX] = iPWM_MAX;
    else
        pwm_rgb_tbl[gtemp_j][iR_INDEX] = 0;
    if(rgb_enable&iPWM_G)
        pwm_rgb_tbl[gtemp_j][iG_INDEX] = iPWM_MAX;
    else
        pwm_rgb_tbl[gtemp_j][iG_INDEX] = 0;
    if(rgb_enable&iPWM_B)
        pwm_rgb_tbl[gtemp_j][iB_INDEX] = iPWM_MAX;
    else
        pwm_rgb_tbl[gtemp_j][iB_INDEX] = 0;
}

extern void key_into_fcc_test(void);

/******************************************************************************
* ��������: logo_process
* ��������:
* �������:
* �������:
* ˵    ��:
******************************************************************************/
void device_led_process(void)
{
    if(0 != hint_time_count)
    {
        hint_led_status |= bled_hint_mode;
        if(0 != (hint_time_count&0x08))
        {
            bdevice_led_status = true;
            hint_led_status |= (bled_hint_mode|bled_24g|bled_bt2|bled_bt1|bled_bt0);
        }
        else
        {
            device_led_off();
        }

        hint_time_count--;
        if(2>hint_time_count)
        {
            hint_time_count = 0;
            hint_led_status = 0x00;
        }

        return;
    }

    rtc_cur_value = drv_rtc_read(OM_RTC);
    if(iDEVICE_TYPE_USB != device_type)
    {
        if(ble_24g_ctrl & bom6239_conning)
        {
            hint_led_status |= bled_hint_mode;
            if(0 == device_conn_index)
            {
                device_conn_index++;
                led_delay_count = rtc_cur_value;
            }
            else if(1 == device_conn_index)
            {
                if(ble_24g_ctrl&bom6239_conn_ok)
                {
                    device_conn_index++;
                    led_delay_count = rtc_cur_value;
                    device_hint_count = 0;
                }

                key_into_fcc_test();
                if(false == bdevice_led_status)
                {
                    device_led_off();
                    if(mMS_TO_TICK(250) < (rtc_cur_value - led_delay_count))
                    {
                        bdevice_led_status = true;
                        led_delay_count = rtc_cur_value;
                    }
                }
                else
                {
                    device_led_on();
                    if(mMS_TO_TICK(250) < (rtc_cur_value - led_delay_count))
                    {
                        bdevice_led_status = false;
                        led_delay_count = rtc_cur_value;
                    }
                }
            }
            else if(2 == device_conn_index)
            {
                device_conn_index = 0;
                ble_24g_ctrl &= ~bom6239_conning;
            }
            return;
        }
        else if(ble_24g_ctrl&bom6239_sync_ing)
        {
            if(true == b24g_nromal)
                return;

            hint_led_status |= bled_hint_mode;
            if(0 == device_conn_index)
            {
                device_conn_index++;
                led_delay_count = rtc_cur_value;
            }
            else if(1 == device_conn_index)
            {
                if(ble_24g_ctrl&bom6239_sync_ok)
                {
                    device_conn_index++;
                    led_delay_count = rtc_cur_value;
                    device_hint_count = 0;
                }

                if(false == bdevice_led_status)
                {
                    device_led_off();
                    if(mMS_TO_TICK(1000) < (rtc_cur_value - led_delay_count))
                    {
                        bdevice_led_status = true;
                        led_delay_count = rtc_cur_value;
                    }
                }
                else
                {
                    device_led_on();
                    if(mMS_TO_TICK(1000) < (rtc_cur_value - led_delay_count))
                    {
                        bdevice_led_status = false;
                        led_delay_count = rtc_cur_value;
                    }
                }
            }
            else if(2 == device_conn_index)
            {
                device_conn_index = 0;
                ble_24g_ctrl &= ~bom6239_sync_ing;
            }
            return;
        }
        hint_led_status &= ~bled_hint_mode;
        device_conn_index = 0;
    }
    else
    {
        hint_led_status &= ~bled_hint_mode;
        if(0 != (usb_ctrl_flag&busb_suspend_resume))
            return;
    }
}

/******************************************************************************
* ��������: logo_process
* ��������:
* �������:
* �������:
* ˵    ��:
******************************************************************************/
void logo_process(void)
{
    uint8_t i;

    if(true==bsave_status)
    {
        bsave_status = false;
        flash_save_status();
    }
    if(true==bsave_cfg_dpi)
    {
        bsave_cfg_dpi = false;
        flash_save_cfg_dpi();
    }
    if(iDEVICE_TYPE_24G == device_type)
    {
        if(true==bflash_ctrl)
            return;
    }

    if(iDEVICE_TYPE_USB == device_type)
    {
        if(0 != (usb_ctrl_flag&busb_suspend_resume))
        {
            logo_off();
            return;
        }
    }
    else
    {
        if(ble_24g_ctrl&bom6239_sync_ing)
        {
            logo_off();
            return;
        }
    }

    if((false == bled_bright_en) || (iLED_LEV_MIN==led_light_lev))
    {
        logo_off();
        return;
    }

    if((bat_status & bcharging)==0)
    {
        if(iLOW_POWER>=bat_value)
        {
            logo_off();
            return;
        }
    }

    if(false==bargb_valid)
    {
        pwm_init();
        OM_PWM->PWMCON = 0x00000001;
        delayus(2000);
    }

    if(led_light_lev != led_light_lev_bak)
    {
        led_light_lev_bak = led_light_lev;
        pwm_init();
        delayus(100);
    }

    if(led_pre_mode != led_cur_mode)
    {
        led_pre_mode = led_cur_mode;

        switch(led_cur_mode)
        {
            case iMODE_LED_OFF:
                OM_PWM->PWMCON = 0x00000000;
                break;
            case iMODE_LED_ON:
                OM_PWM->PWMCON = 0x00000001;
                break;
            case iMODE_LED_BREATH:
                OM_PWM->PWMCON = 0x00000001;
                pwm_time_count = 0;
                break;
            case iMODE_LED_HB:
                break;
        }
    }
    else
    {
        switch(led_cur_mode)
        {
            case iMODE_LED_OFF:
                OM_PWM->PWMCON = 0x00000000;
                break;
            case iMODE_LED_ON:
                OM_PWM->PWMDC0 = iPWM_MAX-1;
                break;
            case iMODE_LED_BREATH:
                effect_breatch();
                break;
            case iMODE_LED_HB:
                effect_heartbeat();
                break;
        }
    }
}
