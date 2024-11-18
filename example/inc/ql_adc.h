
/*============================================================================
  Copyright (c) 2017 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
 =============================================================================*/

#ifndef _QL_ADC_H_
#define _QL_ADC_H_

typedef enum {
    QADC_NONE = 0,
    ADC0 = 1,
    ADC1 = 2,
    CBC  = 3,
    ADC2 = 4,
    QADC_END
}Enum_QADC;

/**
 * @brief 
 * This function retrieves the ADC voltage value with the specified 
 * ADC channel.
 * Support input vol value:
 * - ADC0 : 0.3V-VBAT_BB(3.8V)
 * - ADC1 : 0.3V-VBAT_BB
 * - ADC2 : 0.1V-1.7V
 * 
 * @param [in] qadc, adc channel definitions, one value of Enum_QADC. 
 * @return 
 *
 * - adc value(mv) on success
 * - on failure, the return value is -1;
 */
int ql_adc_show(Enum_QADC qadc);

#endif
