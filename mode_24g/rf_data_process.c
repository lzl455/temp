/*******************************************************************************
* Copyright (c) 2013, SHENZHEN HUNTERSUN Co.,LTD.
* All rights reserved.
*
* �ļ�����: rf_data_process.c
* �ļ�����: rf���ݴ���
*
* ��    ��: V1.0.0
* ��    ��:
* ��    ��:
* ����˵��:
* ʹ��˵��:
*******************************************************************************/
#include "main_24g.h"
#include "usb_cfg_info.h"

//-----------------------------------------------------------------------------;
//����������
//

//----------------------------------------------------------------------------
//����������
//
//unsigned char               key_data_1;
//unsigned char               mouse_x_1;
//unsigned char               mouse_y_1;
//unsigned char               mouse_xy_1;

//unsigned char               key_data_2;
//unsigned char               mouse_x_2;
//unsigned char               mouse_y_2;
//unsigned char               mouse_xy_2;

//unsigned char               mouse_x_3;
//unsigned char               mouse_y_3;
//unsigned char               mouse_xy_3;
//unsigned char               mouse_z;

//----------------------------------------------------------------------------
//��������
//

//============================================================================;
// ������                                                                     ;
//============================================================================;

/******************************************************************************
* ��������: clr_mouse_data()
* ��������:
* �������: ��
* �������: ��
* ˵    ��:
******************************************************************************/
void clr_mouse_data(void)
{
    mouse_x_1 = 0;
    mouse_y_1 = 0;
    mouse_xy_1 = 0;

    mouse_x_2 = 0;
    mouse_y_2 = 0;
    mouse_xy_2 = 0;
}

/******************************************************************************
* ��������:  �����лص�����()
   
------------------------------------------------------------------------------
|              2ms               |                2ms               |  // ����
               |  TX0          |                    |  TX1        |    // ����
|                 iqr          |                       iqr        |    // iqrʱ���
               tx0 idle          |                tx1 idle          |  // �����ݷ���
------------------------------------------------------------------------------

******************************************************************************/

//----------------------------------------------------------------------------
void rf_tx1_idle_callback(void)
{
    lvd_scan_count++;
    if(4==(lvd_scan_count&0x07))
        device_led_process();                     // 16ms
    if(0==(lvd_scan_count&0x01))
        logo_process();
}

void rf_tx1_irq_callback(void)
{
    lvd_scan_count++;
    if(4==(lvd_scan_count&0x07))
        device_led_process();
    if(0==(lvd_scan_count&0x01))
        logo_process();
}

/******************************************************************************
* ��������: rf_sync_ok_process()
* ��������:
* �������: ��
* �������: ��
* ˵    ��: ��
******************************************************************************/
void rf_sync_ok_process(void)
{
    mMCU_MODE_NORMAL;
    clr_mouse_data();

    if(adv_cfg_value&iPOWER_LOW)
        report_24g = iREPORT_125;
    else
        report_24g = ((report_dpi[key_mode]>>4)&0x03);
    m_tx_count = 0;
    drv_encoder_control(OM_ENCODER, ENCODER_CONTROL_START, NULL);

    if(true == b24g_nromal)
        ble_24g_ctrl &= ~bom6239_sync_ing;
}

/******************************************************************************
* ��������: rf_device_info
* ��������: RF��һ�����ڴ�����ɺ�������ߵĴ���
* �������:
* �������:
* ˵    ��: ��
******************************************************************************/
__RAM_CODE void rf_normal_mode_sleep(void)
{                       
    OM_CRITICAL_BEGIN();
    drv_pmu_set_low_power_mode(PMU_LPM_IDLE);
    OM_CRITICAL_END();
}

/******************************************************************************
* ��������: rf_conn_data_process()
* ��������:
* �������: ��
* �������: ��
* ˵    ��: ��
******************************************************************************/
void rf_conn_data_process(void)
{
    if(0==(ble_24g_ctrl&bom6239_conn_ok))
    {
        if(mMS_TO_TICK(60*1000) > (drv_rtc_read(OM_RTC) - connect_time_count))
            return;                             // ����פ��15s

        ble_24g_ctrl &= ~bom6239_conning;
        rf_ctrl_reg |= (brf_sync_time|brf_sync_status);
        rf_mode_convert(iRF_MODE_SYNC);
    }
    else
    {
        rf_ctrl_reg |= (bsearch_dongle|brf_sync_time|brf_sync_status);
        sync_word = iSEARCH_SYNC_WORD;
        rf_mode_convert(iRF_MODE_SYNC);
    }
}
