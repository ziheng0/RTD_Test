/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Quectel Co., Ltd. 2016
*
*****************************************************************************/

#ifndef __QL_ERROR_H__
#define __QL_ERROR_H__

/**
 * @brief Error code definition.
 * 
 */
enum {
	RES_OK = 0, ///< 0
	RES_BAD_PARAMETER  = -1,     ///< Parameter is invalid.
	RES_IO_NOT_SUPPORT = -2, ///< -2
	RES_IO_ERROR = -3, ///< -3
	RES_NOT_IMPLEMENTED = -4 ///< -4
};

#endif //QL_ERROR_H 
