/*
 * Led.h
 *
 *  Created on: 26 апр. 2022 г.
 *      Author: hard_
 */

//PG13
//PG14
#ifndef  STM_H
#define STM_H

#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"

#endif

#ifndef LED_H_
#define LED_H_

void init_gpio();
void Led3_on();
void Led4_on();
void Led3_off();
void Led4_off();
void Blink_Led3();
void Blink_Led4();

#endif /* LED_H_ */
