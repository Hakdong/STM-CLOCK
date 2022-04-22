/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define C	262
#define D	294
#define E	330
#define F	349
#define G	392
#define A	440
#define B	494
#define C1	523
#define D1	587
#define E1	659
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim8;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_RTC_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM5_Init(void);
static void MX_TIM8_Init(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#ifdef __GNUC__
  /* With GCC, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#define UP_KEY_MIN 0
#define UP_KEY_MAX 10

#define DOWN_KEY_MIN 800
#define DOWN_KEY_MAX 900

#define LEFT_KEY_MIN 1900
#define LEFT_KEY_MAX 2000

#define RIGHT_KEY_MIN 2950
#define RIGHT_KEY_MAX 3050

#define LONG_CLICK_MIN 1500  //1.5sec
#define LONG_CLICK_MAX 5000  //5sec

#define DOUBLE_CLICK_MIN 40
#define DOUBLE_CLICK_MAX 120
/*
 * led.c
 *
 *  Created on: Jan 3, 2022
 *      Author: 1
 */

#include "main.h"
#include "pitches.h"
I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart3;

uint16_t melody1[] = {
NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,
NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
NOTE_G5,NOTE_G5,NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,
NOTE_C5,NOTE_C5,NOTE_C5,
NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
NOTE_G5,NOTE_G5,NOTE_G5,
NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
NOTE_G5,NOTE_G5,NOTE_G5,
NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
NOTE_G5,NOTE_G5,NOTE_G5,NOTE_A5,NOTE_G5,
NOTE_C6,NOTE_G5,NOTE_C6,NOTE_G5,
NOTE_E5,NOTE_D5,NOTE_C5
};
uint16_t noteDurations1[]={
4,8,8,4,4,
4,8,8,4,4,
8,8,4,8,8,4,
4,4,2,
4,4,4,4,
4,4,2,
4,4,4,4,
4,4,2,
4,4,4,4,
8,8,8,8,2,
4,4,4,4,
4,4,2
};


uint8_t start = 0;
uint8_t seq = 0;
uint8_t stop = 0;
uint16_t melody2[] = {
NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,
NOTE_DS6,NOTE_B5,NOTE_B5,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_B5,
NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,
NOTE_B5,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_G5,NOTE_D5,NOTE_D5,0,
NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,
NOTE_DS6,NOTE_B5,NOTE_B5,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_B5,
NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,
NOTE_B5,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_G5,NOTE_D5,NOTE_D5,0,
NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_FS5,
NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_FS5,
NOTE_E5,NOTE_E5
};
uint16_t noteDurations2[]={
4,4,2,4,4,2,
4,4,4,4,4,4,4,2,
4,4,2,4,4,2,
4,4,4,4,4,4,2,16,
4,4,2,4,4,2,
4,4,4,4,4,4,4,2,
4,4,2,4,4,2,
4,4,4,4,4,4,2,16,
8,8,8,8,8,8,8,8,
8,8,8,8,8,8,8,8,
1,1
};
uint16_t melody3[] = {
NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,
NOTE_DS6,NOTE_B5,NOTE_B5,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_B5,
NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,
NOTE_B5,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_G5,NOTE_D5,NOTE_D5,0,
NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,
NOTE_DS6,NOTE_B5,NOTE_B5,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_B5,
NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,NOTE_B5,
NOTE_B5,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_G5,NOTE_D5,NOTE_D5,0,
NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_FS5,
NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_FS5,
NOTE_E5,NOTE_E5
};

uint16_t noteDurations3[]={
4,4,2,4,4,2,
4,4,4,4,4,4,4,2,
4,4,2,4,4,2,
4,4,4,4,4,4,2,16,
4,4,2,4,4,2,
4,4,4,4,4,4,4,2,
4,4,2,4,4,2,
4,4,4,4,4,4,2,16,
8,8,8,8,8,8,8,8,
8,8,8,8,8,8,8,8,
1,1


};

#define LCD_ADDR (0x27 << 1)

#define PIN_RS    (1 << 0)
#define PIN_EN    (1 << 2)
#define BACKLIGHT (1 << 3)

#define LCD_DELAY_MS 5

void I2C_Scan() {
	 char info[] = "Scanning I2C bus...\r\n";
    HAL_UART_Transmit(&huart3, (uint8_t*)info, strlen(info), HAL_MAX_DELAY);

    HAL_StatusTypeDef res;
    for(uint16_t i = 0; i < 128; i++) {
        res = HAL_I2C_IsDeviceReady(&hi2c1, i << 1, 1, 10);
        if(res == HAL_OK) {
            char msg[64];
            snprintf(msg, sizeof(msg), "0x%02X", i);
            HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
        } else {
            HAL_UART_Transmit(&huart3, (uint8_t*)".", 1, HAL_MAX_DELAY);
        }
    }

    HAL_UART_Transmit(&huart3, (uint8_t*)"\r\n", 2, HAL_MAX_DELAY);
}

HAL_StatusTypeDef LCD_SendInternal(uint8_t lcd_addr, uint8_t data, uint8_t flags) {
    HAL_StatusTypeDef res;
    for(;;) {
        res = HAL_I2C_IsDeviceReady(&hi2c1, lcd_addr, 1, HAL_MAX_DELAY);
        if(res == HAL_OK)
            break;
    }

    uint8_t up = data & 0xF0;
    uint8_t lo = (data << 4) & 0xF0;

    uint8_t data_arr[4];
    data_arr[0] = up|flags|BACKLIGHT|PIN_EN;
    data_arr[1] = up|flags|BACKLIGHT;
    data_arr[2] = lo|flags|BACKLIGHT|PIN_EN;
    data_arr[3] = lo|flags|BACKLIGHT;

    res = HAL_I2C_Master_Transmit(&hi2c1, lcd_addr, data_arr, sizeof(data_arr), HAL_MAX_DELAY);
    HAL_Delay(LCD_DELAY_MS);
    return res;
}

void LCD_SendCommand(uint8_t lcd_addr, uint8_t cmd) {
    LCD_SendInternal(lcd_addr, cmd, 0);
}

void LCD_SendData(uint8_t lcd_addr, uint8_t data) {
    LCD_SendInternal(lcd_addr, data, PIN_RS);
}

void LCD_Init(uint8_t lcd_addr) {
    // 4-bit mode, 2 lines, 5x7 format
    LCD_SendCommand(lcd_addr, 0b00110000);
    // display & cursor home (keep this!)
    LCD_SendCommand(lcd_addr, 0b00000010);
    // display on, right shift, underline off, blink off
    LCD_SendCommand(lcd_addr, 0b00001100);
    // clear display (optional here)
    LCD_SendCommand(lcd_addr, 0b00000001);
}

void LCD_SendString(uint8_t lcd_addr, char *str) {
    while(*str) {
        LCD_SendData(lcd_addr, (uint8_t)(*str));
        str++;
    }
}
void LCD_print(int line_num,char *str)
{
	if(line_num == 0)
	{
	    LCD_SendCommand(LCD_ADDR, 0b10000000);
	    LCD_SendString(LCD_ADDR, str);
	}
	else
	{
	    LCD_SendCommand(LCD_ADDR, 0b11000000);
	    LCD_SendString(LCD_ADDR, str);
	}
}
void init() {
    I2C_Scan();
    LCD_Init(LCD_ADDR);


}

void loop() {
    HAL_Delay(100);
}



uint32_t FirstSector = 0, NbOfSectors = 0;
uint32_t Address = 0, SECTORError = 0;
__IO uint32_t data32 = 0 , MemoryProgramStatus = 0;
static FLASH_EraseInitTypeDef EraseInitStruct;

static uint32_t GetSector(uint32_t Address);
static uint32_t GetSectorSize(uint32_t Sector);

typedef struct {
  char ampm[3];
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
}TimeTypeDef;
uint8_t Key_value = 0,tim_set = 0;
TimeTypeDef ctime = {"AM",0,0,0};
TimeTypeDef stime = {"AM",0,0,0};
TimeTypeDef atime = {"AM",12,0,0};
uint32_t long_key_count;
char rcv_byte;

uint32_t ADC_value;
uint32_t last_time,current_time,time_interval, last_time_interval;

typedef struct{
  int32_t time;
  GPIO_PinState level;
}ClickInfoDef;

ClickInfoDef click[3];


enum CLOCK_BUTTON{
	NO_KEY,
	UP_KEY,
	DOWN_KEY,
	RIGHT_KEY,
	LEFT_KEY,
	SEL_KEY,
	LONG_KEY,
	DOUBLE_KEY
};

char time_str[30];
char stime_str[30];
char atime_str[30];
uint8_t setting_Location=0;
uint8_t alarm_Location=0;
uint8_t Cursor = 0b11000000;
uint8_t Music_Select=0;
uint8_t Mel;
uint8_t Length;
uint32_t address_melody=0x08108000;
uint32_t address_length=0x08110000;
uint8_t rx_data = 0;
void Memory(uint32_t Start,uint32_t end,TimeTypeDef clock)//Memory set
{
	  HAL_FLASH_Unlock();
	  FirstSector = GetSector(Start);
	  /* Get the number of sector to erase from 1st sector*/
	  NbOfSectors = GetSector(end) - FirstSector + 1;
	  /* Fill EraseInit structure*/
	  EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	  EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	  EraseInitStruct.Sector        = FirstSector;
	  EraseInitStruct.NbSectors     = NbOfSectors;

	  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
	     you have to make sure that these data are rewritten before they are accessed during code
	     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
	     DCRST and ICRST bits in the FLASH_CR register. */
	 if(HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	  {
	    /*
	      Error occurred while sector erase.
	      User can add here some code to deal with this error.
	      SECTORError will contain the faulty sector and then to know the code error on this sector,
	      user can call function 'HAL_FLASH_GetError()'
	    */
	    /* Infinite loop */
	    while (1)
	    {
	    }
	  }

	    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Start, clock.hours);
	    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Start+4, clock.minutes);
	    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Start+8, clock.seconds);
	 	 HAL_FLASH_Lock();
}

void Memory1(uint32_t Start,uint32_t end,uint16_t Melody[])//Memory set
{
	  HAL_FLASH_Unlock();
	  FirstSector = GetSector(Start);
	  /* Get the number of sector to erase from 1st sector*/
	  NbOfSectors =  1;
	  /* Fill EraseInit structure*/
	  EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	  EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	  EraseInitStruct.Sector        = FirstSector;
	  EraseInitStruct.NbSectors     = NbOfSectors;

	  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
	     you have to make sure that these data are rewritten before they are accessed during code
	     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
	     DCRST and ICRST bits in the FLASH_CR register. */
	 if(HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	  {
	    /*
	      Error occurred while sector erase.
	      User can add here some code to deal with this error.
	      SECTORError will contain the faulty sector and then to know the code error on this sector,
	      user can call function 'HAL_FLASH_GetError()'
	    */
	    /* Infinite loop */
	    while (1)
	    {
	    }
	  }
	 for(int i = 0 ; Melody[i] != 0 ; i++)
	 {
	    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Start, Melody[i]);
	    Start += 4;
	 }
	 	 HAL_FLASH_Lock();
}

void Music_set()
{

	if(Key_value == UP_KEY)
	{
		Music_Select++;
		if(Music_Select >= 3) Music_Select = 2;
	}
	else if (Key_value == DOWN_KEY)
	{
		Music_Select--;
		if(Music_Select < 0) Music_Select = 0;
	}
	LCD_print(0,"Alarm Music Sel ");
	if(Music_Select==0)
	{
		LCD_print(1,"Three bears      ");
		if(Key_value == LONG_KEY)
		{
			printf("Mel1\r\n");
			Memory1(ADDR_FLASH_SECTOR_14,ADDR_FLASH_SECTOR_15,melody1);
			Memory1(ADDR_FLASH_SECTOR_15,ADDR_FLASH_SECTOR_16,noteDurations1);
		}
	}
	if(Music_Select==1)
	{
		LCD_print(1,"Squid Game BGM    ");
		if(Key_value == LONG_KEY)
		{
			printf("Mel2\r\n");
			Memory1(ADDR_FLASH_SECTOR_14,ADDR_FLASH_SECTOR_15,melody2);
			Memory1(ADDR_FLASH_SECTOR_15,ADDR_FLASH_SECTOR_16,noteDurations2);
		}
	}
	if(Music_Select==2)
	{
		LCD_print(1,"Kill Bill ost      ");
		if(Key_value == LONG_KEY)
		{
			printf("Mel3\r\n");
			Memory1(ADDR_FLASH_SECTOR_14,ADDR_FLASH_SECTOR_15,melody3);
			Memory1(ADDR_FLASH_SECTOR_16,ADDR_FLASH_SECTOR_17,noteDurations3);
		}
	}


}

void time_setting()
{

		if(Key_value == RIGHT_KEY)
		{
			setting_Location++;
			if(setting_Location >= 4) setting_Location = 3;
		}
		else if (Key_value == LEFT_KEY)
		{
			setting_Location--;
			if(setting_Location < 0) setting_Location = 0;
		}
		if(setting_Location == 0)
		{
			if(Key_value == UP_KEY || Key_value == DOWN_KEY)
			{
		    	if(strchr(stime.ampm,'A')!= 0) strcpy(stime.ampm,"PM");
		    	else if(strchr(stime.ampm,'P')!= 0) strcpy(stime.ampm,"AM");
			}
		}
		if(setting_Location == 1)
		{
			Cursor = 0b11000100;
			if(Key_value == UP_KEY) stime.hours++;
			else if(Key_value == DOWN_KEY) stime.hours--;
			if(stime.hours >= 11) stime.hours = 11;
			if(stime.hours<0) stime.hours = 0;
		}
		if(setting_Location == 2)
		{
			Cursor = 0b11000111;
			if(Key_value == UP_KEY) stime.minutes++;
			else if(Key_value == DOWN_KEY) stime.minutes--;
			if(stime.minutes >= 59)	stime.minutes = 59;
			if(stime.minutes<0) stime.minutes = 0;
		}
		if(setting_Location == 3)
		{
			Cursor = 0b11001010;
			if(Key_value == UP_KEY) stime.seconds++;
			else if(Key_value == DOWN_KEY) stime.seconds--;
			if(stime.seconds >= 59)	stime.seconds = 59;
			if(stime.seconds<0) stime.seconds = 0;

		}
		sprintf(stime_str,"%s %02d:%02d:%02d        ",stime.ampm,stime.hours,stime.minutes,stime.seconds);
		LCD_print(0,"Time Setting    ");
		LCD_print(1,stime_str);


		LCD_SendCommand(LCD_ADDR, 0b00001101);
		LCD_SendCommand(LCD_ADDR, Cursor);
		HAL_Delay(200);

}
void alarm_setting()
{
	if(Key_value == RIGHT_KEY)
	{
		alarm_Location++;
		if(alarm_Location >= 4) alarm_Location = 3;

	}
	else if (Key_value == LEFT_KEY)
	{
		alarm_Location--;
		if(alarm_Location < 0) alarm_Location = 0;
	}
	if(alarm_Location == 0)
	{
		if(Key_value == UP_KEY || Key_value == DOWN_KEY)
		{
	    	if(strchr(stime.ampm,'A')!= 0) strcpy(stime.ampm,"PM");
	    	else if(strchr(stime.ampm,'P')!= 0) strcpy(stime.ampm,"AM");
		}
	}
	if(alarm_Location == 1)
	{
		Cursor = 0b11000100;
		if(Key_value == UP_KEY) atime.hours++;
		else if(Key_value == DOWN_KEY) atime.hours--;
		if(atime.hours >= 11) atime.hours = 11;
		if(atime.hours<0) atime.hours = 0;
	}
	if(alarm_Location == 2)
	{
		Cursor = 0b11000111;
		if(Key_value == UP_KEY) atime.minutes++;
		else if(Key_value == DOWN_KEY) atime.minutes--;
		if(atime.minutes >= 59) atime.minutes = 59;
		if(atime.minutes<0) atime.minutes = 0;
	}
	if(alarm_Location == 3)
	{
		Cursor = 0b11001010;
		if(Key_value == UP_KEY) atime.seconds++;
		else if(Key_value == DOWN_KEY) atime.seconds--;
		if(atime.seconds >= 59)	atime.seconds = 59;
		if(atime.seconds<0) atime.seconds = 0;
	}
	sprintf(atime_str,"%s %02d:%02d:%02d AL     ",atime.ampm,atime.hours,atime.minutes,atime.seconds);
	LCD_print(0,"Alarm Setting    ");
	LCD_print(1,atime_str);

    LCD_SendCommand(LCD_ADDR, 0b00001101);
    LCD_SendCommand(LCD_ADDR, Cursor);
    HAL_Delay(200);
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_RTC_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim3);
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim5);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
  HAL_UART_Receive_IT(&huart3, &rx_data, 1);
  ctime.hours = *(uint32_t *)0x08100000;
  ctime.minutes =*(uint32_t *)0x08100004;
  ctime.seconds =*(uint32_t *)0x08100008;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  init();

  while (1)
  {

	  if(Key_value == SEL_KEY)
	  {
			while(1)
			{

				time_setting();

				if(Key_value == SEL_KEY)
				{
					Memory(ADDR_FLASH_SECTOR_13,ADDR_FLASH_SECTOR_14,stime);
					ctime.hours = stime.hours;
					ctime.minutes = stime.minutes;
					ctime.seconds = stime.seconds;
					stime.hours =0;
					stime.minutes =0;
					stime.seconds =0;
					break;
				}

			}
	  }
	  else if(Key_value == LONG_KEY)
	  {
		  while(1)
		 {
			alarm_setting();

			if(Key_value == SEL_KEY)
			{
				printf("%02d\r\n",atime.hours);
				printf("%02d\r\n",atime.minutes);
				printf("%02d\r\n",atime.seconds);
				break;
			}
		 }


	  }
	  else if(Key_value == DOUBLE_KEY)
	  {
		  while(1)
		  {
			  Music_set();

			if(Key_value == SEL_KEY)
				break;
		  }
	  }



	  sprintf(time_str,"%s %02d:%02d:%02d       ",ctime.ampm,ctime.hours,ctime.minutes,ctime.seconds);
	  if((ctime.seconds % 10) ==0) Memory(ADDR_FLASH_SECTOR_12,ADDR_FLASH_SECTOR_13,ctime);
	  LCD_print(0,"Current Time      ");
	  LCD_print(1,time_str);

	  if(ctime.hours == atime.hours && ctime.minutes == atime.minutes && ctime.seconds == atime.seconds)
	  {
			start = 1;
			seq = 0;
			while(1)
			{
				if(Key_value == SEL_KEY){
					HAL_TIM_Base_Stop_IT(&htim5);
					HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
					break;
				}
				LCD_print(0,"It is your Time      ");
				uint16_t  Mel = *(uint32_t *)address_melody;
				uint16_t  Length =*(uint32_t *)address_length;

				if(stop == 1){
					TIM5->ARR = 2000;
					stop = 0;
				}
				else{
					if(Mel > 0xFFFFF){
						 Mel = *(uint32_t *)address_melody;
						 Length =*(uint32_t *)address_length;
					}
					else{
						TIM8->ARR = Mel;
						TIM8->CCR3 = Mel / 2;
						TIM5->ARR = Length * 2000;
						stop = 1;

						  address_melody += 4;
						  address_length += 4;
					}
				}
			}
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* USART3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* TIM4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM4_IRQn);
  /* TIM5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM5_IRQn);
  /* EXTI15_10_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
  /* TIM3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* TIM2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING;
  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 10000;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 10000;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 900;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 9999;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 17999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 1599;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 2249;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 179;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 199;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */
  HAL_TIM_MspPostInit(&htim8);

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_MDC_Pin RMII_RXD0_Pin RMII_RXD1_Pin */
  GPIO_InitStruct.Pin = RMII_MDC_Pin|RMII_RXD0_Pin|RMII_RXD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_REF_CLK_Pin RMII_MDIO_Pin RMII_CRS_DV_Pin */
  GPIO_InitStruct.Pin = RMII_REF_CLK_Pin|RMII_MDIO_Pin|RMII_CRS_DV_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : RMII_TXD1_Pin */
  GPIO_InitStruct.Pin = RMII_TXD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(RMII_TXD1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_SOF_Pin USB_ID_Pin USB_DM_Pin USB_DP_Pin */
  GPIO_InitStruct.Pin = USB_SOF_Pin|USB_ID_Pin|USB_DM_Pin|USB_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_VBUS_Pin */
  GPIO_InitStruct.Pin = USB_VBUS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_VBUS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_TX_EN_Pin RMII_TXD0_Pin */
  GPIO_InitStruct.Pin = RMII_TX_EN_Pin|RMII_TXD0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	  if(htim->Instance==TIM2)
	  {
	      ctime.seconds++;

	      if(ctime.seconds>=60)
	      {
	    	ctime.minutes++;
	    	ctime.seconds = 0;
	      }
	      if(ctime.minutes>=60)
	      {
	    	ctime.hours++;
	        ctime.minutes = 0;
	      }
	      if(ctime.hours>=12)
	      {
	    	ctime.hours = 0;
	    	if(strchr(stime.ampm,'A')!= 0) strcpy(stime.ampm,"PM");
	    	else if(strchr(stime.ampm,'P')!= 0) strcpy(stime.ampm,"AM");
	      }


	  }

  else if(htim->Instance==TIM3)
  {
	  ADC_value = HAL_ADC_GetValue(&hadc1);
	  HAL_ADC_Start(&hadc1);

	//printf("%d\r\n",ADC_value);
	    if(ADC_value<=UP_KEY_MAX)
	    {
	    	printf("UP\r\n");
	    	return Key_value= UP_KEY;
	    }
	    if(ADC_value>= DOWN_KEY_MIN && ADC_value<=DOWN_KEY_MAX)
	    {
	    	printf("DOWN\r\n");
	    	return Key_value= DOWN_KEY;
	    }
	    if(ADC_value>= LEFT_KEY_MIN && ADC_value<=LEFT_KEY_MAX)
	    {
	    	printf("LEFT\r\n");
	    	return Key_value= LEFT_KEY;
	    }
	    if(ADC_value>= RIGHT_KEY_MIN && ADC_value<=RIGHT_KEY_MAX)
	    {
	    	printf("RIGHT\r\n");
	    	return Key_value= RIGHT_KEY;
	    }
	    else
	    {
	    	 return Key_value = NO_KEY;
	    }
  }
  else if (htim->Instance==TIM8)
  {


  }


}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART3){
		uint8_t ch;

		ch = rx_data;
		if(ch == 'a')	return Key_value= UP_KEY;
		else if(ch == 'b')	return Key_value= DOWN_KEY;
		else if(ch == 'e')	return Key_value= SEL_KEY;
		else if(ch == 'c')	return Key_value= LEFT_KEY;
		else if(ch == 'd')	return Key_value= RIGHT_KEY;
		else if(ch == 'e')	return Key_value= LONG_KEY;
		else if(ch == 'f')	return Key_value= DOUBLE_KEY;

		HAL_UART_Receive_IT(&huart3, &rx_data, 1);
	}
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  GPIO_PinState pin;
  int i;

  if(GPIO_Pin == GPIO_PIN_13)
  {
	current_time = HAL_GetTick();
    time_interval = current_time - last_time;
    last_time = current_time;

    pin = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13);

	//printf("<%d,%d>\r\n",pin,time_interval);

    if(time_interval<=2) // noise
    {
    	//printf("Noise %d,%d\r\n",pin,time_interval);
    }
    else
    {

      click[2].time = click[1].time;
      click[2].level = click[1].level;

      click[1].time = click[0].time;
      click[1].level = click[0].level;

      click[0].time = time_interval;
      click[0].level = pin;
#if 0
      printf("===============\r\n");

      for(i=0;i<3;i++)
      {
    	  printf("[%d,%d]\r\n",click[i].level,click[i].time);
      }
      printf("===============\r\n");
#endif
      if( click[2].level ==GPIO_PIN_RESET && click[1].level == GPIO_PIN_SET &&  click[0].level ==GPIO_PIN_RESET)
      {
    	  for(i=0;i<3;i++)
    	  {
    		  if(click[i].time>= DOUBLE_CLICK_MIN && click[i].time <= DOUBLE_CLICK_MAX)
    		  {
    			  continue;
    		  }
    		  else
    			  break;
    	  }
    	  if(i==3)
    	  {
      		printf("Double Click\r\n");
      		Key_value= DOUBLE_KEY;
    	  }
      }

	  if(click[0].level == GPIO_PIN_RESET && click[0].time >=LONG_CLICK_MIN) // long click
	  {
		printf("Long Key\r\n");
		Key_value= LONG_KEY;
	  }
	  else if(click[0].level == GPIO_PIN_RESET && click[0].time < LONG_CLICK_MIN && click[0].time > DOUBLE_CLICK_MAX)
	  {
		 printf("Select Key, %d\r\n",click[0].time);
		 Key_value= SEL_KEY;
	  }

    }
  }
}
static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;

  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0;
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1;
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2;
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3;
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4;
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_SECTOR_5;
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_SECTOR_6;
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_SECTOR_7;
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_SECTOR_8;
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_SECTOR_9;
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_SECTOR_10;
  }
  else if((Address < ADDR_FLASH_SECTOR_12) && (Address >= ADDR_FLASH_SECTOR_11))
  {
    sector = FLASH_SECTOR_11;
  }
  else if((Address < ADDR_FLASH_SECTOR_13) && (Address >= ADDR_FLASH_SECTOR_12))
  {
    sector = FLASH_SECTOR_12;
  }
  else if((Address < ADDR_FLASH_SECTOR_14) && (Address >= ADDR_FLASH_SECTOR_13))
  {
    sector = FLASH_SECTOR_13;
  }
  else if((Address < ADDR_FLASH_SECTOR_15) && (Address >= ADDR_FLASH_SECTOR_14))
  {
    sector = FLASH_SECTOR_14;
  }
  else if((Address < ADDR_FLASH_SECTOR_16) && (Address >= ADDR_FLASH_SECTOR_15))
  {
    sector = FLASH_SECTOR_15;
  }
  else if((Address < ADDR_FLASH_SECTOR_17) && (Address >= ADDR_FLASH_SECTOR_16))
  {
    sector = FLASH_SECTOR_16;
  }
  else if((Address < ADDR_FLASH_SECTOR_18) && (Address >= ADDR_FLASH_SECTOR_17))
  {
    sector = FLASH_SECTOR_17;
  }
  else if((Address < ADDR_FLASH_SECTOR_19) && (Address >= ADDR_FLASH_SECTOR_18))
  {
    sector = FLASH_SECTOR_18;
  }
  else if((Address < ADDR_FLASH_SECTOR_20) && (Address >= ADDR_FLASH_SECTOR_19))
  {
    sector = FLASH_SECTOR_19;
  }
  else if((Address < ADDR_FLASH_SECTOR_21) && (Address >= ADDR_FLASH_SECTOR_20))
  {
    sector = FLASH_SECTOR_20;
  }
  else if((Address < ADDR_FLASH_SECTOR_22) && (Address >= ADDR_FLASH_SECTOR_21))
  {
    sector = FLASH_SECTOR_21;
  }
  else if((Address < ADDR_FLASH_SECTOR_23) && (Address >= ADDR_FLASH_SECTOR_22))
  {
    sector = FLASH_SECTOR_22;
  }
  else /* (Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_23) */
  {
    sector = FLASH_SECTOR_23;
  }
  return sector;
}

/**
  * @brief  Gets sector Size
  * @param  None
  * @retval The size of a given sector
  */
static uint32_t GetSectorSize(uint32_t Sector)
{
  uint32_t sectorsize = 0x00;
  if((Sector == FLASH_SECTOR_0) || (Sector == FLASH_SECTOR_1) || (Sector == FLASH_SECTOR_2) ||\
     (Sector == FLASH_SECTOR_3) || (Sector == FLASH_SECTOR_12) || (Sector == FLASH_SECTOR_13) ||\
     (Sector == FLASH_SECTOR_14) || (Sector == FLASH_SECTOR_15))
  {
    sectorsize = 16 * 1024;
  }
  else if((Sector == FLASH_SECTOR_4) || (Sector == FLASH_SECTOR_16))
  {
    sectorsize = 64 * 1024;
  }
  else
  {
    sectorsize = 128 * 1024;
  }
  return sectorsize;
}

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

