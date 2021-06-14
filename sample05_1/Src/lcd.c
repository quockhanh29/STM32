/*
 * lcd.c
 *
 *  Created on: 2019/12/17
 *      Author: SM11
 */

#include "stm32l1xx_hal.h"
#include"lcd.h"

extern LCD_HandleTypeDef hlcd;

const uint8_t ramPattern[10][2] = {
		{0x5, 0xf},
		{0x4, 0x2},
		{0xf, 0x5},
		{0xe, 0x7},
		{0xe, 0xa},
		{0xa, 0xf},
		{0xb, 0xf},
		{0x4, 0x6},
		{0xf, 0xf},
		{0xe, 0xf}
};

void LCD_WriteChar(uint8_t pos, char c){

	uint8_t ram0, ram2;

	if(pos < 1 || pos > 6){
		return;
	}
	if( c < '0' || c > '9'){
		return;
	}

	ram0 = ramPattern[c -'0'][0];
	ram2 = ramPattern[c - '0'][1];

	switch (pos){
	case 1:
		HAL_LCD_Write(&hlcd, 0, ~0x30000003, (ram0 & 0x3) | ((ram0 & 0xc) << 26));
		HAL_LCD_Write(&hlcd, 2, ~0x30000003, (ram2 & 0x3) | ((ram2 & 0xc) << 26));
		break;
	case 2:
		HAL_LCD_Write(&hlcd, 0, ~0x0c000084, ((ram0 & 0x1) << 2 ) |((ram0 & 2) << 6)| ((ram0 & 0xc) << 24));
		HAL_LCD_Write(&hlcd, 2, ~0x0c000084, ((ram2 & 0x1) << 2 ) |((ram2 & 2) << 6)| ((ram2 & 0xc) << 24));
		break;
	case 3:
		HAL_LCD_Write(&hlcd, 0, ~0x03000300, ((ram0 & 0x3) << 8 ) | ((ram0 & 0xc) << 22));
		HAL_LCD_Write(&hlcd, 2, ~0x03000300, ((ram2 & 0x3) << 8 ) | ((ram2 & 0xc) << 22));
		break;
	case 4:
		HAL_LCD_Write(&hlcd, 0, ~0x00300c00, ((ram0 & 0x3) << 10 ) | ((ram0 & 0xc) << 18));
		HAL_LCD_Write(&hlcd, 2, ~0x00300c00, ((ram2 & 0x3) << 10 ) | ((ram2 & 0xc) << 18));
		break;
	case 5:
		HAL_LCD_Write(&hlcd, 0, ~0x000c3000, ((ram0 & 0x3) << 12 ) | ((ram0 & 0xc) << 16));
		HAL_LCD_Write(&hlcd, 2, ~0x000c3000, ((ram2 & 0x3) << 12 ) | ((ram2 & 0xc) << 16));
		break;
	case 6:
		HAL_LCD_Write(&hlcd, 0, ~0x0003c000, ((ram0 & 0x3) << 14 ) | ((ram0 & 0x4) << 15) | ((ram0 & 0x8) << 13));
		HAL_LCD_Write(&hlcd, 2, ~0x0003c000, ((ram2 & 0x3) << 14 ) | ((ram2 & 0x4) << 15) | ((ram2 & 0x8) << 13));
		break;

	}
	HAL_LCD_UpdateDisplayRequest(&hlcd);
}

