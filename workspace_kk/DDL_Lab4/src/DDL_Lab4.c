/*
===============================================================================
 Name        : DDL_Lab4.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif

#include <cr_section_macros.h>


/*
 * */
void GPIOInit(void);

void TIMER32Init(void);

void PIOINT2_IRQHandler(void);

void TIMER32_0_IRQHandler(void);


int main(void) {

	GPIOInit();
	TIMER3Init();


	while(1);
    return 0 ;
}

void GPIOInit(void){

}

void TIMER32Init(void){

}

void PIOINT2_IRQHandler(void){

}


void PIOINT2_IRQHandler(void){


}

