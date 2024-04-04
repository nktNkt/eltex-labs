#include "commands.h"

float com_plus(int a, int b) {
	return (float)(a + b);
}

float com_minus(int a, int b) {
	return (float)(a - b);
}

float com_multiply(int a, int b) {
	return (float)(a * b);
}

float com_divide(int a, int b) {
	return a / (float)b;
}

float com_mod(int a, int b) {
	return (float)(a % b);
}

float (*com_select(int choice)) (int, int) {
	switch (choice) {
	case 0: return com_plus;
	case 1: return com_minus;
	case 2: return com_multiply;
	case 3: return com_divide;
	case 4: return com_mod;
	}
}