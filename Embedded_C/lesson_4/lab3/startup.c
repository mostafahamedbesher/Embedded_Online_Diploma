//startup.c
//Eng:Mostafa Besher

#include <stdint.h>
//prototypes
extern int main(void);
void Default_handler();
void Reset_handler();
void NMI_handler()__attribute__((weak,alias("Default_handler")));;
void HARD_FAULT_handler()__attribute__((weak,alias("Default_handler")));;
void MM_handler()__attribute__((weak,alias("Default_handler")));;
void BUS_handler()__attribute__((weak,alias("Default_handler")));;
void USAGE_FAULT_handler()__attribute__((weak,alias("Default_handler")));;

//declaration of symbols
extern uint32_t _E_text;
extern uint32_t _S_data;
extern uint32_t _E_data;
extern uint32_t _S_bss;
extern uint32_t _E_bss;


static unsigned long stack_top[256];
//.vectors section 
void (* const vectors[])() __attribute__((section(".vectors"))) = 
{
	(void (*) ())((unsigned long)&stack_top + sizeof(stack_top)),
	&Reset_handler,
	&NMI_handler,
	&HARD_FAULT_handler,
	&MM_handler,
	&BUS_handler,
	&USAGE_FAULT_handler
};


void Reset_handler()
{
	int i = 0;
	//copy .data from flash to sram
	uint32_t Data_size = (unsigned char *)&_E_data - (unsigned char *)&_S_data;
	unsigned char *p_src = (unsigned char *)&_E_text;	//starting address of .data in flash
	unsigned char *p_dst = (unsigned char *)&_S_data;	//starting address of .data in sram
	
	for(i = 0; i < Data_size; i++)
	{
		*((unsigned char *)p_dst++) = *((unsigned char *)p_src++);
	}
	
	//initialize .bss with zero
	uint32_t bss_size = (unsigned char *)&_E_bss - (unsigned char *)&_S_bss;
	p_dst = (unsigned char *)&_S_bss;
	
	for(i = 0; i < bss_size; i++)
	{
		*((unsigned char *)p_dst++) = (unsigned char)0;
	}
	
	//jump to main
	main();
}

void Default_handler()
{
	Reset_handler();
}
