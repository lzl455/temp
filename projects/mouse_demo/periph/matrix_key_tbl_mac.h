/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: _MATRIX_KEY_TBL_
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#ifndef _MATRIX_KEY_MAC_TBL_
#define _MATRIX_KEY_MAC_TBL_

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 正常矩阵表
//

// WIN键值表
unsigned char           const   matrixkey_mac_tbl[] =
{
// C2
    iSTD_F,             iKEY_TYPE_STD|iKEY_PRESS,
    iKEY_DEFAULT,       iKEY_TYPE_SPECIAL, 
    iLED_BRIGHT_SUB,    iKEY_TYPE_SPECIAL,
    iSTD_Z,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_1,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_C,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_3,             iKEY_TYPE_STD|iKEY_PRESS,
// C3
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_SHIFT,
    iSTD_U,             iKEY_TYPE_STD|iKEY_PRESS,
    iLED_BRIGHT_ADD,    iKEY_TYPE_SPECIAL,
    iMMK_BRIGHT_SUM_L,  iKEY_TYPE_MMK|iMMK_BRIGHT_SUM_H,
    iMMK_NEXT_TRACK_L,  iKEY_TYPE_MMK | iMMK_NEXT_TRACK_H,
    iSTD_ENTER,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID,
    iSTD_NULL,          iKEY_TYPE_INVALID,       
// C4
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_CTRL,    
    iSTD_K,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_P,             iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_PLAY_PAUSE_L,  iKEY_TYPE_MMK | iMMK_PLAY_PAUSE_H,
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_SHIFT,       
    iMMK_PREV_TRACK_L,  iKEY_TYPE_MMK | iMMK_PREV_TRACK_H,            
    iSTD_ESCAPE,        iKEY_TYPE_STD|iKEY_PRESS,       
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_ALT,      
// C5
    iSTD_SPACE,         iKEY_TYPE_STD|iKEY_PRESS,    
    iSTD_I,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID, 
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_GUI,  
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_CTRL,
    iSTD_X,             iKEY_TYPE_STD|iKEY_PRESS, 
    iSTD_2,             iKEY_TYPE_STD|iKEY_PRESS, 
    iSTD_CAPITAL,       iKEY_TYPE_STD|iKEY_PRESS, 
// C6
    iSTD_A,             iKEY_TYPE_STD|iKEY_PRESS,
    iLED_OFF,           iKEY_TYPE_SPECIAL,
    iSTD_O,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID, 
    iSTD_NULL,          iKEY_TYPE_INVALID, 
    iSTD_NULL,          iKEY_TYPE_INVALID, 
    iSTD_NULL,          iKEY_TYPE_INVALID, 
    iSTD_NULL,          iKEY_TYPE_INVALID, 
// C7
    iSTD_TAB,           iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_WAVE,          iKEY_TYPE_STD|iKEY_PRESS,
    iLED_MODE_CYC_ADD,  iKEY_TYPE_SPECIAL,         
    iSTD_Y,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_END,           iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_7,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SEMICOLON,     iKEY_TYPE_STD|iKEY_PRESS,    
    iMMK_MUTE_L,        iKEY_TYPE_MMK | iMMK_MUTE_H,          
// C8
    iSTD_S,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SUBTRACT,      iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_MEDIA_SELECT_L,iKEY_TYPE_MMK|iMMK_MEDIA_SELECT_H,
    iSTD_4,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SQUARE_BRACKET_LEFT, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_8,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_INSERT,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_N,             iKEY_TYPE_STD|iKEY_PRESS,
// C9
    iSTD_D,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_ADD,           iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_WWW_HOME_L,    iKEY_TYPE_MMK|iMMK_WWW_HOME_H,
    iSTD_NULL,          iKEY_TYPE_INVALID, 
    iSTD_SQUARE_BRACKET_RIGHT, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_9,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_QUOTATION_SIGN,iKEY_TYPE_STD|iKEY_PRESS,    
    iMODE_KEY_FN,       iKEY_TYPE_SPECIAL,
// C10
    iSTD_W,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_BACKSPACE,     iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_MY_COMPUTER_L, iKEY_TYPE_MMK|iMMK_MY_COMPUTER_H,
    iSTD_SNAPSHOT,      iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_HOME,          iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_DELETE,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_H,             iKEY_TYPE_STD|iKEY_PRESS,    
    iSTD_FULLSTOP,      iKEY_TYPE_STD|iKEY_PRESS,
// C11
    iSTD_E,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_L,             iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_CALCULATOR_L,  iKEY_TYPE_MMK|iMMK_CALCULATOR_H,
    iSTD_SCROLL,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_CANCEL,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_PAGEUP,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID,         
    iSTD_SLASH,         iKEY_TYPE_STD|iKEY_PRESS,
// C12
    iSTD_Q,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_J,             iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_MY_COMPUTER_L, iKEY_TYPE_MMK|iMMK_MY_COMPUTER_H,       
    iSTD_NULL,          iKEY_TYPE_INVALID,   
    iSTD_BACKSLASH,     iKEY_TYPE_STD|iKEY_PRESS, 
    iSTD_0,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_PAGEDOWN,      iKEY_TYPE_STD|iKEY_PRESS,    
    iSTD_COMMA,         iKEY_TYPE_STD|iKEY_PRESS,           
// C13
    iSTD_B,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID, 
    iSTD_NULL,          iKEY_TYPE_INVALID,  
    iSTD_NUMLOCK,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD7,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD4,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD1,       iKEY_TYPE_STD|iKEY_PRESS, 
    iSTD_NULL,          iKEY_TYPE_INVALID, 
// C14
    iSTD_V,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_5,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID, 
    iSTD_NUMPAD_DIVIDE, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD8,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD5,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD2,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD0,       iKEY_TYPE_STD|iKEY_PRESS,
// C15
    iSTD_R,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_6,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID, 
    iSTD_NUMPAD_MULTIPLY,iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD9,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD6,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD3,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NUMPAD_FULLSTOP,iKEY_TYPE_STD|iKEY_PRESS,
// C16
    iSTD_T,             iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_BRIGHT_ADD_L,  iKEY_TYPE_MMK|iMMK_BRIGHT_ADD_H,
    iSTD_NULL,          iKEY_TYPE_INVALID, 
    iSTD_NUMPAD_SUBTRACT,iKEY_TYPE_STD|iKEY_PRESS, 
    iSTD_NUMPAD_ADD,    iKEY_TYPE_STD|iKEY_PRESS, 
    iSTD_NULL,          iKEY_TYPE_INVALID, 
    iSTD_NUMPAD_ENTER,  iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_INVALID, 
// C17
    iSTD_NULL,          iKEY_TYPE_INVALID, 
    iSTD_G,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_UP,            iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_LEFT,          iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_DOWN,          iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_M,             iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,          iKEY_TYPE_STD|iKEY_PRESS|iLEFT_ALT,
    iSTD_RIGHT,         iKEY_TYPE_STD|iKEY_PRESS
};
//-----------------------------------------------------------------------------;

#endif
