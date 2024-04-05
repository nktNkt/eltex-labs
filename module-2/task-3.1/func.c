#include <stdio.h>
#include <string.h>

int inputToBin(unsigned char mask[]) {
	//[3][2][1][0]
	int buf = 0;	//двоичное представление

	//цифровое представление
	char t;
	if (strlen(mask) == 3 && (mask[0] - '0' >= 0) && (mask[0] - '0' <= 7)) {
		for (int i = 0; i < 3; i++) {
			t = mask[i] - '0';
			if ((t < 0) || (t > 7)) return -1;
			for (int j = 2; j >= 0; j--) {
				buf = buf << 1;
				if (((1 << j) & t) > 0) buf++;
			}
		}
		return buf;
	}

	//буквенное представление ([ugoa]=[rwx])
	int n = 0, t_mask = 0;
	for (; n <= 3; n++) {
		if (mask[n] == 'a') {
			t_mask = 7; n++;
			break;
		}
		if (mask[n] == 'u') t_mask |= 1 << 2;
		if (mask[n] == 'g') t_mask |= 1 << 1;
		if (mask[n] == 'o') t_mask |= 1;
		if (mask[n] == '=') break;
	}
	if (mask[n] != '=' || t_mask == 0) return -1;

	for (; n <= 9 && mask[n]; n++) {
		if (mask[n] == 'r') {
			if (t_mask & 4) buf |= (1 << 8);
			if (t_mask & 2) buf |= (1 << 5);
			if (t_mask & 1) buf |= (1 << 2);
		}
		if (mask[n] == 'w') {
			if (t_mask & 4) buf |= (1 << 7);
			if (t_mask & 2) buf |= (1 << 4);
			if (t_mask & 1) buf |= (1 << 1);
		}
		if (mask[n] == 'x') {
			if (t_mask & 4) buf |= (1 << 6);
			if (t_mask & 2) buf |= (1 << 3);
			if (t_mask & 1) buf |= 1;
		}
	}
	return buf;
}

void binPrint(int num) {
        for (int i = 8; i >= 0; i--) {
                printf("%d", (num >> i) & 1);
        }
        printf("\n");
}

void symPrint(int num) {
        char mask[10] = "rwxrwxrwx";
        for (int i = 8; i >= 0; i--) {
                if (!((num >> i) & 1)) mask[8-i] = '-';
        }
        printf("%s\n", mask);
}

int fileedit(int original, char newmask[]) {
        int nm = inputToBin(newmask);
        return (0100000 | nm);
}
