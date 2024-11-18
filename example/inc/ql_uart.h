/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Quectel Co., Ltd. 2016
*
*****************************************************************************/
#ifndef __QL_UART_H__
#define __QL_UART_H__

typedef enum {
    FC_NONE = 0,  // None Flow Control
    FC_RTSCTS,    // Hardware Flow Control (rtscts)
    FC_XONXOFF    // Software Flow Control (xon/xoff)
}Enum_FlowCtrl;

typedef enum {
    PB_NONE = 0,  //none parity check
    PB_ODD,       //odd parity check
    PB_EVEN       //even parity check
}Enum_ParityBit;

typedef enum {
    DB_CS5 = 5,
    DB_CS6 = 6,
    DB_CS7 = 7,
    DB_CS8 = 8
}Enum_DataBit;

typedef enum {
    SB_1 = 1,
    SB_2 = 2
}Enum_StopBit;

typedef enum {
	B_300 		= 300,
	B_600 		= 600,
	B_1200 		= 1200,
	B_2400 		= 2400,
	B_4800 		= 4800,
	B_9600 		= 9600,
	B_19200 	= 19200,
	B_38400 	= 38400,
	B_57600 	= 57600,
	B_115200 	= 115200,
	B_230400 	= 230400,
	B_460800 	= 460800,
	B_921600	= 921600,
	B_3000000	= 3000000,
	B_4000000	= 4000000,
}Enum_BaudRate;

typedef struct {
    Enum_BaudRate       baudrate; 
    Enum_DataBit       	databit;
    Enum_StopBit       	stopbit;
    Enum_ParityBit      parity;
    Enum_FlowCtrl       flowctrl;
}ST_UARTDCB;

/**
 * @brief Ql_UART_Open
 * 
 * @param port 
 * @param baudrate 
 * @param flowctrl 
 * @return int 
 * @par eg:
 * int fd = Ql_UART_Open("/dev/ttyUSB0", B_115200, FC_NONE);
 */
int Ql_UART_Open(const char* port, Enum_BaudRate baudrate, Enum_FlowCtrl flowctrl);

/**
 * @brief Ql_UART_Read
 * @param fd 
 * @param buf 
 * @param buf_len 
 * @return 
 * @par eg:
 * @code 
 * char buf[100];
 * int ret = Ql_UART_Read(fd, buf, sizeof(buf));
 * @endcode
 * 
 */
int Ql_UART_Read(int fd, char* buf, unsigned int buf_len);

/**
 * @brief Ql_UART_Write
 * @param fd 
 * @param buf 
 * @param buf_len 
 * @return 
 */
int Ql_UART_Write(int fd, const char* buf, unsigned int buf_len);

/**
 * @brief Ql_UART_SetDCB
 * @param fd 
 * @param dcb 
 * @return 
 */
int Ql_UART_SetDCB(int fd, ST_UARTDCB *dcb);

/**
 * @brief Ql_UART_GetDCB
 * @param fd 
 * @param dcb 
 * @return 
 */
int Ql_UART_GetDCB(int fd, ST_UARTDCB *dcb);

/**
 * @brief Ql_UART_IoCtl
 * 
 * @param fd 
 * @param cmd 
 * @param pValue 
 * @return int 
 */
int Ql_UART_IoCtl(int fd, unsigned int cmd, void* pValue);

/**
 * @brief Ql_UART_Close
 * 
 * @param fd 
 * @return int 
 */
int Ql_UART_Close(int fd);

#endif //__QL_UART_H__
