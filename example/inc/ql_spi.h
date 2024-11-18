/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Quectel Co., Ltd. 2016
*
*****************************************************************************/
#ifndef __QL_SPI_H__
#define __QL_SPI_H__

typedef enum
{
	SPIMODE0  =   SPI_MODE_0,
	SPIMODE1  =   SPI_MODE_1,
	SPIMODE2  =   SPI_MODE_2,
	SPIMODE3  =   SPI_MODE_3,
}SPI_MODE;

/**
 * @brief SPI default support frequency
 * 
 */
typedef enum
{
	S_960K  	=   960000,
	S_4_8M 		=   4800000,
	S_9_6M  	=   9600000,
	S_16M  		=   16000000,
	S_19_2M 	=   19200000,
	S_25M  		=   25000000,
	S_50M  		=   50000000,
}SPI_SPEED;


/**
 * @brief 
 * spi init
 * @param dev_name:need to insmod spidev.ko or quec_spi_chn.ko, The corresponding device can be found in the "/dev/" directory. 
 * @param mode:the default is mode0 
 * - CPOL:when spi work in idles,the level of sclk, 1:HIGH,0:LOW
 * - CHPA:sample on the first few edges of sclk     0:the first edge 1:the second edge
 * @param bits:bits of word, Supports 4 to 32 bits per word of transfer 
 * @param speed:the max spi speed 
 * @return 
 * - spi_fd when successfully
 * - -1 when failed
 */
int Ql_SPI_Init(char *dev_name,SPI_MODE mode,uint8_t bits,SPI_SPEED speed);


/**
 * @brief 
 * write and read spi data
 * @param fd:spi file description 
 * @param write_buf: the pointer to write data 
 * @param read_buf: the pointer to read data 
 * @param len:the length of data 
 * @return 
 * - 0 when successfully
 * - negative value when failed
 */
int Ql_SPI_Write_Read(int fd,uint8_t* write_buf,uint8_t* read_buf,uint32_t len);


/**
 * @brief 
 * close spi device fd
 * @param fd 
 * @return 
 */
int Ql_SPI_DeInit(int fd);

#endif
