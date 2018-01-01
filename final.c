#include "final.h"

int saga_git = 0;
int sola_git = 0;
int gidis_hizi = 0;
int ekran[64][48];
short blue=0x001F;
short green=0x07E0;
short red = 0xF800;
short pink = 0xF81F;
short black = 0x0000;
short screen[320][240];
int block[6][6];
int dif=41;
int len_of_block=80;
int len_of_two_block = 60;

int main(){
	//srand((unsigned) time(&t));
	srand(time(NULL));   // should only be called once
	int r = rand()%260;
	int i,j;
	// full screen is blue firstly
	for(i=0;i<48;i++)
	{
		for(j=0;j<64;j++)
		{
			draw_one_box(j,i,blue);
		}
	}
	// fill the screen array
	for(i=0;i<320;i++)
	{
		for(j=0;j<240;j++)
		{
			screen[i][j]=blue;
		}
	}
	// create random blocks and draw them
	for(i=0;i<6;i++)
	{
		block[i][1]=i*dif+35;
		block[i][0]=r;
		draw_one_block(block[i][0],block[i][1],black);
		if(block[i][0]<=0)
		{
			r= rand()%(block[i][0]+len_of_block+len_of_two_block);
		}
		else
		{
			r= block[i][0]-len_of_two_block + rand()%(len_of_block+2*len_of_two_block);
		}
	}
	// put blocks color to screen array
	int k,l;
	for(k=0;k<6;k++)
	{
		for(l=0;l<6;l++)
		{
			for(j=0;j<80;j++)
			{
				screen[block[k][0]+j][block[k][1]+l]=black;
			}
		}
	}
	//configure_pinmux(); // Configure Pin Muxing
	//I2C0_Init(); // Initialize I2C0 Controller
	//disable_A9_interrupts (); // disable interrupts in the A9 processor
	//set_A9_IRQ_stack(); // initialize the stack pointer for IRQ mode
	//config_GIC(); // configure the general interrupt controller
	//config_KEYs (); // configure buttons for interrupt
	//config_interval_timer (); // configure Altera interval timer to generate interrupts
	//enable_A9_interrupts(); // enable interrupts in the A9 processor
    //
	//ADXL345_REG_READ(ADXL345_REG_DEVID, &devid);
	//
	//if (devid == 0xE5) // Correct Device ID
	//{
	//	ADXL345_Init(); // Initialize accelerometer chip
	// 	while(1){
	//		//for(i=0;i<100000000;i++);
	//		//*LEDS = number_of_tick;
	//		*HEX0_3= (sevensegment[(number_of_tick/1000)%10]<<24)|(sevensegment[(number_of_tick/100)%10]<<16)|(sevensegment[(number_of_tick/10)%10]<<8)|sevensegment[number_of_tick%10];
	//		if (ADXL345_IsDataReady()==1)
	//		{
	//			ADXL345_XYZ_Read(value);
	//			int a = (value[0]*4)/10;
	//			if(a<-10)
	//			{
	//				*LEDS = 2;
	//			}
	//			else if(a>10)
	//			{
	//				*LEDS = 1;
	//			}
	//			else
	//			{
	//				*LEDS = 0;
	//			}
	//			//printf("%d,%d,%d\n",value[0],value[1],value[2]);
	//			//set_sevensegment(HEX0_3,HEX4_5,value,sevensegment);
	//		}
	//	}
	//} else {
	//	printf("wrong device");
	//}
	//draw_one_box(0,0,pink);
	//change_box(0,0,0,47);

	//volatile short * pixel_buffer = (short *) 0x08000000; // Pixel buffer
	//volatile char * character_buffer = (char *) 0x09000000; // Character buffer
	//int x1=0;
	//int y1=0;
	//int x2=319;
	//int y2=239;
	//int pixel_ptr, row, col;
	///* Draw a box with corners (x1, y1) and (x2, y2). Assume that the box coordinates are valid */
	//for (row = y1; row <= y2; row++)
	//{
	//	for (col = x1; col <= x2; ++col)
	//	{
	//		pixel_ptr = 0xC8000000 | (row << 10) | (col << 1);
	//		*(short *)pixel_ptr = black; // set pixel color
	//	}
	//}
	//int **offset;
	//char *text_ptr;
	//text_ptr = (char *) malloc(15);
	//text_ptr = "FNASJFHASJKDFRA";
	//
	///* Display a null-terminated text string at coordinates x, y. Assume that the text fits on one line */
	//offset = (75 << 7) + 75;
	//while ( *(text_ptr)!='\0' )
	//{
	//	*(0xC9000000 + offset) = *(text_ptr); // write to the character buffer
	//	++text_ptr;
	//	++offset;
	//}

	return 0;
}

void change_box(int x1,int y1, int x2,int y2)
{
	int pixel_ptr;
	pixel_ptr = 0xC8000000 | (y2*5 << 10) | (x2*5 << 1);
	draw_one_box(x2,y2,black);
	draw_one_box(x1,y1,*(short *)pixel_ptr) ;
}

void draw_one_block(int x,int y,short color)
{
	int pixel_ptr, row, col;
	for (row = x; row <= x+5; row++)
	{
		for (col = y; col <= y+79; ++col)
		{
			pixel_ptr = 0xC8000000 | (row << 10) | (col << 1);
			*(short *)pixel_ptr = color; // set pixel color
		}
	}
}

void draw_one_box(int x1,int y1,short color)
{
	int pixel_ptr, row, col;
	for (row = y1*5; row <= y1*5+5; row++)
	{
		for (col = x1*5; col <= x1*5+5; ++col)
		{
			pixel_ptr = 0xC8000000 | (row << 10) | (col << 1);
			*(short *)pixel_ptr = color; // set pixel color
		}
	}
}

void pushbutton_ISR( void )
{
	volatile int * KEY_ptr = (int *) 0xFF200050;
	int press;
	press = *(KEY_ptr + 3); // read the pushbutton interrupt register
	*(KEY_ptr + 3) = press; // clear the interrupt
	if (press & 0x1) // KEY0
		*LEDS = 1;
	else if (press & 0x2) // KEY1
		*LEDS = 2;
	else if (press & 0x4) // KEY2
		*LEDS = 4;
	else // press & 0x8, which is KEY3
		*LEDS = 8;
	return;
}

extern unsigned int number_of_tick;
void timer_increment_count(void){
	volatile int * interval_timer_ptr = (int *) 0xFF202000;
	*interval_timer_ptr = 0; // restart timer
	number_of_tick++;
	return;
}

/* setup the interval timer interrupts in the FPGA */
void config_interval_timer(){
	volatile int * interval_timer_ptr = (int *) 0xFF202000; // interal timer base address
/* set the interval timer period for scrolling the HEX displays */
	int counter = 100000000; //15 e ayarladık
	*(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
	*(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;
/* start interval timer, enable its interrupts */
	*(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1
	return;
}

/* Initialize the banked stack pointer register for IRQ mode */
void set_A9_IRQ_stack(){
	int stack, mode;
	stack = 0xFFFFFFFF-7; // top of A9 on-chip memory, aligned to 8 bytes
	/* change processor to IRQ mode with interrupts disabled */
	mode = 0b11010010;
	asm("msr cpsr, %[ps]" : : [ps] "r" (mode));
	/* set banked stack pointer */
	asm("mov sp, %[ps]" : : [ps] "r" (stack));
	/* go back to SVC mode before executing subroutine return! */
	mode = 0b11010011;
	asm("msr cpsr, %[ps]" : : [ps] "r" (mode));
}

/* setup the KEY interrupts in the FPGA */
void config_KEYs()
{
	volatile int * KEY_ptr = (int *) 0xFF200050; // pushbutton KEY address
	*(KEY_ptr + 2) = 0xF; // enable interrupts for all four KEYs
}

/* Configure the Generic Interrupt Controller (GIC) */
void config_GIC(){
/* configure the FPGA interval timer and KEYs interrupts */
	*((int *) 0xFFFED848) = 0x00000101;
	*((int *) 0xFFFED108) = 0x00000300;
// Set Interrupt Priority Mask Register (ICCPMR). Enable interrupts of all priorities
	*((int *) 0xFFFEC104) = 0xFFFF;
// Set CPU Interface Control Register (ICCICR). Enable signaling of interrupts
	*((int *) 0xFFFEC100) = 1; // enable = 1
// Configure the Distributor Control Register (ICDDCR) to send pending interrupts to CPUs
	*((int *) 0xFFFED000) = 1; // enable = 1
	return;
}
/* Set up the pushbutton KEYs port in the FPGA */

/* Turn on interrupts in the ARM processor */
void enable_A9_interrupts(){
	int status = 0b01010011;
	asm("msr cpsr, %[ps]" : : [ps]"r"(status));
	return;
}
void disable_A9_interrupts(void){
int status = 0b11010011;
asm("msr cpsr, %[ps]" : : [ps]"r"(status));
}

/* Define the IRQ exception handler */
void __attribute__ ((interrupt)) __cs3_isr_irq (void)
{
// Read the ICCIAR from the processor interface
	int int_ID = *((int *) 0xFFFEC10C);
	if (int_ID == 72) // check if interrupt is from the Altera timer
		timer_increment_count();
	else if (int_ID == 73) // check if interrupt is from the KEYs
		pushbutton_ISR ();
	else
		while (1); // if unexpected, then stay here
		// Write to the End of Interrupt Register (ICCEOIR)
	*((int *) 0xFFFEC110) = int_ID;
	return;
}
// Define the remaining exception handlers */
void __attribute__((interrupt))__cs3_isr_undef (void)
{
while (1);
}
void __attribute__((interrupt))__cs3_isr_swi (void)
{
while (1);
}
void __attribute__((interrupt))__cs3_isr_pabort (void)
{
while (1);
}
void __attribute__((interrupt))__cs3_isr_dabort (void)
{
while (1);
}
void __attribute__((interrupt))__cs3_isr_fiq (void)
{
while (1);
}

 void configure_pinmux(){
	*SYSMGR_I2C0USEFPGA = 0;
	*SYSMGR_GENERALIO7 = 1;
	*SYSMGR_GENERALIO8 = 1;
 }

 void I2C0_Init(){ //configure I2CO
	// Abort any ongoing transmits and disable I2C0.
	*I2C0_ENABLE = 2;

	// Wait until I2C0 is disabled
	while(((*I2C0_ENABLE_STATUS)&0x1) == 1){}

	// Configure the config reg with the desired setting (act as
	// a master, use 7bit addressing, fast mode (400kb/s)).
	*I2C0_CON = 0x65;

	// Set target address (disable special commands, use 7bit addressing)
	*I2C0_TAR = 0x53;

	// Set SCL high/low counts (Assuming default 100MHZ clock input to I2C0 Controller).
	// The minimum SCL high period is 0.6us, and the minimum SCL low period is 1.3us,
	// However, the combined period must be 2.5us or greater, so add 0.3us to each.
	*I2C0_FS_SCL_HCNT = 60 + 30; // 0.6us + 0.3us
	*I2C0_FS_SCL_LCNT = 130 + 30; // 1.3us + 0.3us

	// Enable the controller
	*I2C0_ENABLE = 1;

	// Wait until controller is powered on
	while(((*I2C0_ENABLE_STATUS)&0x1) == 0){}
 }

 // Read value from internal register at address
 void ADXL345_REG_READ(uint8_t address, uint8_t *value){

	// Send reg address (+0x400 to send START signal)
	*I2C0_DATA_CMD = address + 0x400;

	// Send read signal
	*I2C0_DATA_CMD = 0x100;

	// Read the response (first wait until RX buffer contains data)
	while (*I2C0_RXFLR == 0){}
	*value = *I2C0_DATA_CMD;
 }

 // Write value to internal register at address
 void ADXL345_REG_WRITE(uint8_t address, uint8_t value){

	// Send reg address (+0x400 to send START signal)
	*I2C0_DATA_CMD = address + 0x400;

	// Send value
	*I2C0_DATA_CMD = value;
 }

 // Read multiple consecutive internal registers
 void ADXL345_REG_MULTI_READ(uint8_t address, uint8_t values[], uint8_t len){

	// Send reg address (+0x400 to send START signal)
	*I2C0_DATA_CMD = address + 0x400;

	// Send read signal len times
	int i;
	for (i=0;i<len;i++)
		*I2C0_DATA_CMD = 0x100;

	// Read the bytes
	int nth_byte=0;
	while (len){
		if ((*I2C0_RXFLR) > 0){
			values[nth_byte] = *I2C0_DATA_CMD;
			nth_byte++;
			len--;
		}
	}
 }

 // Initialize the ADXL345 chip
 void ADXL345_Init(){

	// +- 16g range, full resolution
	ADXL345_REG_WRITE(ADXL345_REG_DATA_FORMAT, XL345_RANGE_2G | XL345_FULL_RESOLUTION);

	// Output Data Rate: 100Hz
	ADXL345_REG_WRITE(ADXL345_REG_BW_RATE, XL345_RATE_100);

	// stop measure
	ADXL345_REG_WRITE(ADXL345_REG_POWER_CTL, XL345_STANDBY);

	// start measure
	ADXL345_REG_WRITE(ADXL345_REG_POWER_CTL, XL345_MEASURE);
 }

 // Read acceleration data of all three axes
 void ADXL345_XYZ_Read(int16_t szData16[3]){

	uint8_t szData8[6];
	ADXL345_REG_MULTI_READ(0x32, (uint8_t *)&szData8, sizeof(szData8));

	szData16[0] = (szData8[1] << 8) | szData8[0];
	szData16[1] = (szData8[3] << 8) | szData8[2];
	szData16[2] = (szData8[5] << 8) | szData8[4];
 }

 // Return true if there is new data
 int ADXL345_IsDataReady(){
	int bReady = 0;
	uint8_t data8;
	ADXL345_REG_READ(ADXL345_REG_INT_SOURCE,&data8);
	if (data8 & XL345_DATAREADY)
		bReady = 1;
	return bReady;
 }

//void yaz(volatile unsigned int * hex_address1, volatile unsigned int * hex_address2, uint8_t seg_value[], uint8_t sevensegment[]){
//
//	 *hex_address1 = (sevensegment[seg_value[3]]<<24)|(sevensegment[seg_value[2]]<<16)|(sevensegment[seg_value[1]]<<8)|sevensegment[seg_value[0]];
//	 *hex_address2 = (sevensegment[seg_value[5]]<<8)|sevensegment[seg_value[4]];
// }
//void set_sevensegment(volatile unsigned int * hex_address1, volatile unsigned int * hex_address2, int16_t value[], uint8_t sevensegment[]){
//	 uint8_t seg_value[6];
//	 int led_value[3];
//	 int i=0;
//	 for(i=0;i<3;i++){
//		if(value[i]<0){
//			led_value[i]=-1;
//			value[i]=-value[i]*4;
//		}else{
//			led_value[i]=1;
//			value[i]=value[i]*4;
//		}
//		value[i]=value[i]/10;
//
//		if(value[i]>99){
//			value[i]=99;
//		}
//
//		seg_value[2*(2-i)] = value[i]%10;
//		seg_value[2*(2-i)+1] = value[i]/10;
//	 }
//	 yaz(hex_address1,hex_address2,seg_value,sevensegment);
//	 led(led_value);
//
// }
// void led(int value[]){
//	 *LEDS = 0b00000000;
//	 if(value[0]<0){
//		 *LEDS |= 0b10000000;
//	 }
//	 if(value[1]<0){
//		 *LEDS |= 0b00100000;
//	 }
//	 if(value[2]<0){
//		 *LEDS |= 0b00001000;
//	 }
// }
