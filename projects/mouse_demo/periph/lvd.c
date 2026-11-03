/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* �ļ�����: led.c
*
* ����˵��:
* �޸�˵��:
POFCON bit(7~4):�͵�ѹ����ֵ����λ��
				0000:0.8v			0001:0.9v			0010:1.0v
				0011:1.1v			0100:1.2v			0101:1.4v
				0110:1.7v			0111:1.8v			1000:1.9v
				1001:2.0v			1010:2.1v			1011:2.2v
				1100:2.4v			1101:2.7v
POFCON bit(3):POFʹ��λ��1Ϊʹ�ܣ�0Ϊ��ʹ�ܡ�
POFCON bit(2~1):LVD�������á�00��ӦP00��01��ӦP05��10��ӦP07��11��ӦP13��
POFCON bit(0):�͵�ѹָʾ��־λ����������ֵʱΪ�͵�ƽ������Ϊ�ߵ�ƽ��
*******************************************************************************/
#include "om_driver.h"
#include "main.h"
#include "led.h"
#include "lvd.h"
#include "time_delay.h"
#include "flash_process.h"

//-----------------------------------------------------------------------------;
// ����������
//
#define	mPOF_ENABLE     		OM_POF->POFCON |= 0x08
#define	mPOF_DISABLE     		OM_POF->POFCON &= ~0x08

#define	mPOF_WARM_READ     		(OM_POF->POFCON & 0x01)

//-----------------------------------------------------------------------------;
// ����������
//
uint8_t                         bat_status;
uint8_t                         lvd_value;          // lvd���ֵ
uint8_t                         bat_value;          // �ٷֱ�ֵ

bool                            bkey_bat_update;
bool                            bbat_update;
bool                            bbat_check_scan;
bool                            bcharging_bak;

uint8_t                         lvd_scan_count;
uint16_t                        bat_power_delay;
uint16_t                        led_hint_time_count;
uint16_t                        power_off_time_count;
unsigned char                   charge_ok_delay_count;

uint32_t                        lvd_hint_time_count;
uint32_t                        charge_time_count;
uint16_t                        threshold;

//=============================================================================;
// ��������                                                                      ;
//=============================================================================;

//----------------------------------------------
// ﮵�أ�����2M������1M
//
unsigned char           const    bat_li_value_tbl[] =
{
    0,
    5,
    10,
    20,
    40,
    60,
    80,
    100,
};

unsigned char           const    bat_li_value_a3_tbl[] =
{
    0,                  // 0
    5,                  // 1
    10,                 // 2
    15,                 // 3
    20,                 // 4
    30,                 // 5
    40,                 // 6
    50,                 // 7
    60,                 // 8
    70,                 // 9
    80,                 // 10
    90,                 // 11
    100,                // 12
    100,
    100,
    100,
};

#define mPOF_SET                 {OM_POF->POFCON &= ~0x1F0;\
                                    OM_POF->POFCON |= threshold;}

//=============================================================================;
// ������                                                                      ;
//=============================================================================;

/******************************************************************************
* ��������: bat_voltage_check
* ��������: ����ؽ���
* �������:
* �������:
* ˵    ��:
******************************************************************************/
__RAM_CODE void lvd_check(void)
{
    unsigned char i;

    for(i=0; i<7; i++)
    {
        mPOF_SET;
        mPOF_ENABLE;
        delayus(5);
        if(0 != mPOF_WARM_READ)
            break;
        if(0 == threshold)
            break;
        threshold -= 0x10;
    }
}

/******************************************************************************
* ��������: bat_voltage_check
* ��������: ����ؽ���
* �������:
* �������:
* ˵    ��:
******************************************************************************/
__RAM_CODE unsigned char bat_voltage_check(void)
{
    unsigned char i;

    // POF_LVD_PIN_P23   POF_LVD_PIN_P33   POF_LVD_PIN_VBUS   POF_LVD_PIN_VDD
	OM_POF->POFCON &= ~0x0E;
	OM_POF->POFCON |= (POF_LVD_PIN_P33 << 1);

    threshold = POF_THRESHOLD_1_225V;
    mPOF_SET;
	mPOF_ENABLE;
    delayus(8);
    if(0 != mPOF_WARM_READ)
    {                                           
        threshold = POF_THRESHOLD_1_400V;
        mPOF_SET;
        mPOF_ENABLE;
        delayus(8);
        if(0 != mPOF_WARM_READ)
        {                                       
            threshold = POF_THRESHOLD_1_550V;
            lvd_check();
        }
        else
        {                                       
            threshold = POF_THRESHOLD_1_400V;
            lvd_check();
        }
    }
    else
    {                                           
        threshold = POF_THRESHOLD_1_050V;
        mPOF_SET;
        mPOF_ENABLE;
        delayus(8);                             
        if(0 != mPOF_WARM_READ)
        {                                       
            threshold = POF_THRESHOLD_1_225V;
            lvd_check();
        }
        else
        {                                       
            threshold = POF_THRESHOLD_1_050V;
            lvd_check();
        }
    }
    mPOF_DISABLE;

    i = ((threshold>>4)+1);
    return i;
}

/******************************************************************************
* ��������: bat_init
* ��������: ����ؽ���
* �������:
* �������:
* ˵    ��:
******************************************************************************/
void bat_init(void)
{
    bat_status |= blvd_power_on;
    charge_time_count = 0;
}

/******************************************************************************
* ��������: bat_level_cal
* ��������:
* �������:
* �������:
* ˵    ��:
******************************************************************************/
__RAM_CODE uint8_t bat_level_cal(uint8_t bat_level)
{
    if((iOM6239_A3_0 == OM_RF->LINE)||(iOM6239_A3_1 == OM_RF->LINE))
    {
        if(iLVD_0_VALUE_A3>=bat_level)
            bat_level = 0;
        else if(iLVD_100_VALUE_A3<=bat_level)
            bat_level = 100;
        else
            bat_level = bat_li_value_a3_tbl[(bat_level-iLVD_0_VALUE_A3)&0x0F];
    }
    else
    {
        if(iLVD_0_VALUE>=bat_level)
            bat_level = 0;
        else if(iLVD_100_VALUE<=bat_level)
            bat_level = 100;
        else
            bat_level = bat_li_value_tbl[(bat_level-iLVD_0_VALUE)&0x07];
    }

    return bat_level;
}

/******************************************************************************
* ��������: bat_check
* ��������:
* �������:
* �������:
* ˵    ��:
******************************************************************************/
__RAM_CODE void bat_check(void)
{
    uint8_t bat_dat, bat_temp;

    bat_status &= ~(bcharge_ok|bcharging);
    if(0 != USB_5V_PIN)
        bat_status |= bcharging;
    if(0 != CHR_OK_PIN)
        bat_status |= bcharge_ok;

    bat_dat = bat_voltage_check();

    if(0 != (bat_status&blvd_power_on))
    {
        if(0x1F == (bat_status&0x1F))
        {                                       
            if(1000>sys_tick_count)
                return;
            bat_status &= 0xE0;
            bat_status |= bat_dat;
            bsave_status = true;
            bbat_update = true;
        }
        bat_status &= ~blvd_power_on;

        lvd_value = (bat_status&0x1F);
        bat_value = bat_level_cal(lvd_value);
        return;
    }

    if(0 != (bat_status&bcharging))
    {                                           
        if(bat_dat > lvd_value)
        {
            bat_power_delay++;
            if(0 != (bat_status&bcharge_ok))
            {                                   
                if((iOM6239_A3_0 == OM_RF->LINE)||(iOM6239_A3_1 == OM_RF->LINE))
                    lvd_value = iLVD_100_VALUE_A3;
                else
                    lvd_value = iLVD_100_VALUE;

                if(100 != bat_value)
                {
                    bat_status &= 0xE0;
                    bat_status |= lvd_value;
                    bat_value = 100;
                    bsave_status = true;
                    bbat_update = true;
                }
            }
            else if((5*64) < bat_power_delay)
            {
                bat_power_delay=0;

                uint8_t lvd_value_temp;
                if((iOM6239_A3_0 == OM_RF->LINE)||(iOM6239_A3_1 == OM_RF->LINE))
                    lvd_value_temp = iLVD_90_VALUE_A3;
                else
                    lvd_value_temp = iLVD_90_VALUE;

                if(lvd_value_temp>lvd_value)
                {
                    lvd_value++;

                    bat_status &= 0xE0;
                    bat_status |= lvd_value;
                    bat_value = bat_level_cal(lvd_value);
                    bsave_status = true;
                    bbat_update = true;
                }
            }
        }
    }
    else
    {
        if(bat_dat < lvd_value)
        {
            bat_power_delay++;
            if((5*64) < bat_power_delay)
            {
                bat_power_delay=0;

                uint8_t lvd_value_temp;
                if((iOM6239_A3_0 == OM_RF->LINE)||(iOM6239_A3_1 == OM_RF->LINE))
                    lvd_value_temp = iLVD_0_VALUE_A3;
                else
                    lvd_value_temp = iLVD_0_VALUE;

                if(lvd_value_temp < lvd_value)
                {
                    lvd_value--;

                    bat_status &= 0xE0;
                    bat_status |= lvd_value;
                    bat_value = bat_level_cal(lvd_value);
                    bsave_status = true;
                    bbat_update = true;
                }
            }
        }
    }
}

/******************************************************************************
* ��������: led_hint_process
* ��������:
* �������:
* �������:
* ˵    ��:
******************************************************************************/
void led_hint_process(void)
{
    uint8_t i;

    rtc_cur_value = drv_rtc_read(OM_RTC);
    bat_check();
    if(0 != (bat_status&blvd_power_on))
        return;

    if(0 == (bat_status&bcharging))
    {
        if(iLOW_POWER >= bat_value)
        {
            if(0!=(hint_led_status&bled_low))
            {
                if(mMS_TO_TICK(500) < (rtc_cur_value - lvd_hint_time_count))
                {
                    hint_led_status &= ~bled_low;
                    lvd_hint_time_count = rtc_cur_value;
                }
            }
            else
            {
                if(mMS_TO_TICK(1500) < (rtc_cur_value - lvd_hint_time_count))
                {
                    hint_led_status |= bled_low;
                    lvd_hint_time_count = rtc_cur_value;
                }
            }

            if(0<bat_value)
			    return;

		    power_off_time_count++;				
            if(600 > power_off_time_count)		
			    return;

            logo_off();
            OM_PMU->SW_RSVD1 |= PMU_SW_RSVD1_POWER_OFF;
            mouse_periph_wakeup_enable(WAKEUP_SLEEP_LEVEL2);
            drv_pmu_set_low_power_mode(PMU_LPM_DEEP_SLEEP);
        }
        else
        {
            lvd_hint_time_count = 0;
            power_off_time_count = 0;
            hint_led_status &= ~bled_low;
        }
    }
    else
    {
        lvd_hint_time_count = 0;
        if(0 != (bat_status&bcharge_ok))
		{									
            if(0!=charge_ok_delay_count)
            {
                charge_ok_delay_count--;
                return;
            }

            power_off_time_count = 0;
            hint_led_status &= ~bled_low;
        }
        else
        {									
            hint_led_status |= bled_low;
            charge_ok_delay_count = 200;
        }
    }
}
