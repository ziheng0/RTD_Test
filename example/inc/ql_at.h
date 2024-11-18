/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Quectel Co., Ltd. 2016
*
*****************************************************************************/
#ifndef __QL_AT_H__
#define __QL_AT_H__

//#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE  1
#define FALSE 0

#define BUF_LEN     1024

#define MAX_URC_EVENT_HANDLER_ARRAY_SIZE    10

//typedef unsigned int size_t;
typedef int URC_EVENT_HANDLE;
typedef void (*ql_urc_event_handle_func_t)(const char* urc_content);

typedef struct
{
    char*      urc_event;
    ql_urc_event_handle_func_t    pfun;
} st_urc_handle_node;


/**
 * @brief result codes.
 *
 * @note All error codes are negative integers. They allow functions with signed
 *  integers to return non-negative values when successful or standard error codes on failure.
 * @deprecated the result code LE_NOT_POSSIBLE is scheduled to be removed.
 */
typedef enum
{
    E_QL_OK                 = 0,    ///< Successful.
    E_QL_NOT_FOUND          = -1,   ///< Referenced item does not exist or could not be found.
    E_QL_NOT_POSSIBLE       = -2,   ///< @deprecated It is not possible to perform the requested action.
    E_QL_OUT_OF_RANGE       = -3,   ///< An index or other value is out of range.
    E_QL_NO_MEMORY          = -4,   ///< Insufficient memory is available.
    E_QL_NOT_PERMITTED      = -5,   ///< Current user does not have permission to perform requested action.
    E_QL_FAULT              = -6,   ///< Unspecified internal error.
    E_QL_COMM_ERROR         = -7,   ///< Communications error.
    E_QL_TIMEOUT            = -8,   ///< A time-out occurred.
    E_QL_OVERFLOW           = -9,   ///< An overflow occurred or would have occurred.
    E_QL_UNDERFLOW          = -10,  ///< An underflow occurred or would have occurred.
    E_QL_WOULD_BLOCK        = -11,  ///< Would have blocked if non-blocking behaviour was not requested.
    E_QL_DEADLOCK           = -12,  ///< Would have caused a deadlock.
    E_QL_FORMAT_ERROR       = -13,  ///< Format error.
    E_QL_DUPLICATE          = -14,  ///< Duplicate entry found or operation already performed.
    E_QL_BAD_PARAMETER      = -15,  ///< Parameter is invalid.
    E_QL_CLOSED             = -16,  ///< The resource is closed.
    E_QL_BUSY               = -17,  ///< The resource is busy.
    E_QL_UNSUPPORTED        = -18,  ///< The underlying resource does not support this operation.
    E_QL_IO_ERROR           = -19,  ///< An IO operation failed.
    E_QL_NOT_IMPLEMENTED    = -20,  ///< Unimplemented functionality.
    E_QL_UNAVAILABLE        = -21,  ///< A transient or temporary loss of a service or resource.
    E_QL_TERMINATED         = -22,  ///< The process, operation, data stream, session, etc. has stopped.
}E_QL_RESULT;

extern const char strDelimit[];

extern st_urc_handle_node g_urc_handler[];

/**
 * @brief QL_AT_PortInit
 * Specify the AT port name used for sending/receiving AT cmd.
 * 
 * @param device_path 
 * @return int 
 */
extern int QL_AT_PortInit(char *device_path);   

/**
 * @brief QL_AT_PortDeinit
 * @param void
 */
extern void QL_AT_PortDeinit(void);


/**
 * @brief register the URC event call back.
 * 
 * @param urc_event 
 * @param pfun 
 * @return URC_EVENT_HANDLE 
 */
extern URC_EVENT_HANDLE register_urc_callback_func(const char* urc_event, ql_urc_event_handle_func_t pfun);


/**
 * @brief unregister the URC event call back.
 * @param h_handle 
 * @value
 * @retval
 */
extern void unregister_urc_callback_func(URC_EVENT_HANDLE h_handle);


#ifdef __cplusplus
}
#endif

#endif //__QL_AT_H__
