#ifndef _COMMANDS_H_
#define _COMMANDS_H_

float com_plus(int a, int b);
float com_minus(int a, int b);
float com_multiply(int a, int b);
float com_divide(int a, int b);
float com_mod(int a, int b);

float (*com_select(int choice)) (int, int);

#endif