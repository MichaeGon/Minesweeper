#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define tate 6       //c‚ÌL‚³
#define yoko 6       //‰¡‚ÌL‚³
#define bombnumber  5//”š’e‚Ì”

#define bomb -1 //‚¢‚¶‚é‚È(•‰‚Ì®”‚È‚ç‘½•ª‘åä•v‚©‚àB)

int BAN[10][tate + 2][yoko + 2];
int endflag=3;
int number;
