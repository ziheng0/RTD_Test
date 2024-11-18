 /*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Quectel Co., Ltd. 2016
*
*****************************************************************************/
#ifndef __QL_DEV_H__
#define __QL_DEV_H__


#define QL_OEM_ABOUT_MAX_COUNT          32
#define QL_OEM_ABOUT_NAME_MAX_SIZE      32
#define QL_OEM_ABOUT_INFO_MAX_SIZE      128

typedef struct {
    char oem_info_name[QL_OEM_ABOUT_NAME_MAX_SIZE + 1];
    char oem_info_vaule[QL_OEM_ABOUT_INFO_MAX_SIZE + 1];  
} ql_oem_about_info_s;


typedef struct {
    char manufacturer[33];
    char product_name[33];
    char firmware_version[65];
    char firmware_date[33];
    char apps_verison[65];
    
    int oem_about_count;
    ql_oem_about_info_s oem_about[QL_OEM_ABOUT_MAX_COUNT];//only support max 32 item info
} ql_module_about_info_s;



/**
 * @brief 
 * Get the IMEI string.
 * 
 * @param imei 
 * input buffer
 * @param imeiLen 
 * input buffer length
 * @return int 
 */
extern int QL_DEV_GetImei(char* imei, size_t imeiLen);

/**
 * @brief 
 * Get the FirmwareVersion string.
 * 
 * @param version 
 * input buffer
 * @param versionLen 
 * input buffer length
 * @return int 
 */
extern int QL_DEV_GetFirmwareVersion(char* version, size_t versionLen);



/**
 * @brief Get the DeviceModel string.
 *
 * @param model     : input buffer 
 * @param modelLen  : input buffer length 
 * @return int 
 */
extern int QL_DEV_GetDeviceModel(char* model, size_t modelLen);

/**
 * @brief Get the MEID string.
 * 
 * @param meid      : input buffer 
 * @param meidLen   : input buffer length 
 * @return int 
 */
extern int QL_DEV_GetMeid(char* meid, size_t meidLen);


/**
 * @brief Get the ESN string.
 * 
 * @param esn       : input buffer 
 * @param esnLen    : input buffer length 
 * @return int 
 */
extern int QL_DEV_GetEsn(char* esn, size_t esnLen);


/**
 * @brief Get OEM About's Info
 * 
 * @param about: save about result, 
 * @param about_count: about buffer num 
 * @return int 
 * actual about count
 */
extern int QL_OEM_About_Get(ql_oem_about_info_s *about, int about_count);

/**
 * @brief Set OEM About's Info
 * 
 * @param about: input about info, 
 * @param about_count: about nums 
 * @return int 
 * actual about count
 * @note: it will cleal all old info
 */
extern int QL_OEM_About_Set(ql_oem_about_info_s *about, int about_count);

/**
 * @brief 
 * 
 * @param about 
 * @return int 
 */
extern int QL_OEM_About_Get_ByName(ql_oem_about_info_s *about);

/**
 * @brief QL_OEM_About_Set_ByName
 * 
 * @param about 
 * @return int 
 */
extern int QL_OEM_About_Set_ByName(ql_oem_about_info_s *about);

/**
 * @brief QL_Module_About_Get
 * 
 * @param about 
 * @return int 
 */
extern int QL_Module_About_Get(ql_module_about_info_s *about);

#endif // __QL_DEV_H__

