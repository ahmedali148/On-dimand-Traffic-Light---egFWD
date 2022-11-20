/*
 * TEST.h
 *
 * Created: 19/11/2022 08:15:04 م
 *  Author: M
 */ 


#ifndef TEST_H_
#define TEST_H_

typedef enum
{
	TEST_OK, TEST_ERROR
}TEST_State_t;

TEST_State_t TEST_Modules(void);

#endif /* TEST_H_ */