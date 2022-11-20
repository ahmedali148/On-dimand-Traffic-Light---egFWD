/*
 * On_Demand_Trafic_Light.c
 *
 * Created: 29/10/2022 11:45:56 م
 * Author : Ahmed Ali
 */ 

#include "TEST/TEST.h"
#include "APP/APP.h"

int main(void)
{
 if((TEST_Modules() == TEST_OK))
 {		
	while (1)
	{		
		APP_start();
	}
 }
}
