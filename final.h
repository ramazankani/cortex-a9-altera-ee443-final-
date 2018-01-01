#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEX0_3 ((volatile unsigned int *) 0xFF200020)
#define HEX4_5 ((volatile unsigned int *) 0xFF200030)
#define LEDS ((volatile unsigned int *) 0xFF200000)
#define SYSMGR_GENERALIO7 ((volatile unsigned int *) 0xFFD0849C)
#define SYSMGR_GENERALIO8 ((volatile unsigned int *) 0xFFD084A0)
#define SYSMGR_I2C0USEFPGA ((volatile unsigned int *) 0xFFD08704)
#define I2C0_ENABLE ((volatile unsigned int *) 0xFFC0406C)
#define I2C0_ENABLE_STATUS ((volatile unsigned int *) 0xFFC0409C)
#define I2C0_CON ((volatile unsigned int *) 0xFFC04000)
#define I2C0_TAR ((volatile unsigned int *) 0xFFC04004)
#define I2C0_FS_SCL_HCNT ((volatile unsigned int *) 0xFFC0401C)
#define I2C0_FS_SCL_LCNT ((volatile unsigned int *) 0xFFC04020)
#define I2C0_DATA_CMD ((volatile unsigned int *) 0xFFC04010)
#define I2C0_RXFLR ((volatile unsigned int *) 0xFFC04078)
#define ADXL345_REG_DEVID 0x00
#define ADXL345_REG_DATA_FORMAT 0x31
#define ADXL345_REG_POWER_CTL 0x2D
#define ADXL345_REG_BW_RATE 0x2C
#define ADXL345_REG_INT_SOURCE 0x30
#define XL345_RANGE_2G 0x00
#define XL345_FULL_RESOLUTION 0x08
#define XL345_RATE_100 0x0A
#define XL345_STANDBY 0x00
#define XL345_MEASURE 0x08
#define XL345_DATAREADY 0x80

void configure_pinmux();
void I2C0_Init();
void ADXL345_REG_READ(uint8_t address, uint8_t *value);
void ADXL345_REG_WRITE(uint8_t address, uint8_t value);
void ADXL345_REG_MULTI_READ(uint8_t address, uint8_t values[], uint8_t len);
void ADXL345_Init();
void ADXL345_XYZ_Read(int16_t szData16[3]);
int ADXL345_IsDataReady();
void yaz(volatile unsigned int * hex_address1, volatile unsigned int * hex_address2, uint8_t value[], uint8_t sevensegment[]);
void set_sevensegment(volatile unsigned int * hex_address1, volatile unsigned int * hex_address2, int16_t value[],uint8_t sevensegment[]);
void led(int value[]);

void config_KEYs (void);
void set_A9_IRQ_stack(void);
void config_GIC(void);
void config_interval_timer(void);
void enable_A9_interrupts(void);
void interval_timer_ISR (void);
void disable_A9_interrupts(void);


void draw_one_box(int,int,short);
void change_box(int,int,int,int);

uint8_t sevensegment[10]={63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
unsigned int number_of_tick=0;
int16_t value[3];
uint8_t devid;
