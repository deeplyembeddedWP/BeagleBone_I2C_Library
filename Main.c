/*
 * Main.c
 *
 *  Created on: Sep 6, 2017
 *  Author: Vinay Divakar
 */

/* Lib Includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Header Files */
#include "I2C.h"


/* Definitions*/
#define SSD1306_OLED_ADDR 0x3C
#define SSD1306_CNTRL_CMD 0x00

/* Externs - I2C.c */
extern I2C_DeviceT I2C_DEV_2;

/* Debug Definitions */
#define I2C_DBG_INIT
//#define I2C_DBG_SINGLE_WRITE
#define I2C_DBG_MULTIPLE_WRITES
//#define I2C_DBG_DUAL_WRITE

#ifdef I2C_DBG_MULTIPLE_WRITES
unsigned char Test_buff[]={0xFF, 0xA0, 0xAA, 0xF0, 0x0F};
#define TEST_BUFF_SIZE     sizeof(Test_buff)
#endif

int main()
{
#ifdef I2C_DBG_INIT
	if(init_i2c_dev2(SSD1306_OLED_ADDR) == 0)
	{
		printf("(Main)i2c-2: Bus Connected to SSD1306\r\n");
	}
	else
	{
		printf("(Main)i2c-2: OOPS! Something Went Wrong\r\n");
		exit(1);
	}
#endif
while(1)
{
#ifdef I2C_DBG_SINGLE_WRITE
	if(i2c_write(I2C_DEV_2.fd_i2c,0x55) == I2C_ONE_BYTE)
	{
		printf("(Main)i2c-2: Single Write Test Passed\r\n");
	}
	else
	{
		printf("(Main)i2c-2: Single Write Test Failed\r\n");
		//exit(1);
	}
#endif

#ifdef I2C_DBG_DUAL_WRITE
	if(i2c_write_register(I2C_DEV_2.fd_i2c, SSD1306_CNTRL_CMD, 0xA0 ) == I2C_TWO_BYTES)
	{
		printf("(Main)i2c-2: Dual Write Test Passed\r\n");
	}
	else
	{
		printf("(Main)i2c-2: Dual Write Test Failed\r\n");
		//exit(1);
	}
#endif

#ifdef I2C_DBG_MULTIPLE_WRITES
	if(i2c_multiple_writes(I2C_DEV_2.fd_i2c, TEST_BUFF_SIZE, Test_buff) == TEST_BUFF_SIZE)
	{
		printf("(Main)i2c-2: Multiple Write Test Passed\r\n");
	}
	else
	{
		printf("(Main)i2c-2: Multiple Write Test Failed\r\n");
		//exit(1);
	}
#endif
  /*1 sec delay between transactions */
  usleep(1000000);
}
 return 0;
}

