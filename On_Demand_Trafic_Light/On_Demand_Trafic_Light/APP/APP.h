/*
 * APP.h
 *
 * Created: 12/11/2022 04:29:41 ص
 *  Author: M
 */ 


#ifndef APP_H_
#define APP_H_


typedef enum
{
	APP_OK, APP_ERROR
}APP_State_t;

APP_State_t APP_start(void);
void Pedestrian_Mode(void);


#endif /* APP_H_ */