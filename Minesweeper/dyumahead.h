#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define tate 6       //�c�̍L��
#define yoko 6       //���̍L��
#define bombnumber  5//���e�̐�

#define bomb -1 //�������(���̐����Ȃ瑽�����v�����B)

int BAN[10][tate + 2][yoko + 2];
int endflag=3;
int number;
