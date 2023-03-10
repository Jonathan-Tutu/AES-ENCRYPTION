#ifndef CIPHER_H
#define CIPHER_H
#include <stdio.h>
#include <string.h>

#include "Matrix.h"

void keySchedule(byte[4][4], byte[4][44]);

void Cipher(byte[4][4], byte[4][4], byte[4][44]);
void InvCipher(byte[4][4], byte[4][4], byte[4][44]);

void AddRoundKey(byte[4][4], byte[4][44], int);

void SubBytes(byte[4][4]);
void InvSubBytes(byte[4][4]);

void ShiftRows(byte[4][4]);
void InvShiftRows(byte in[4][4]);

void MixColumns(byte[4][4]);
void InvMixColumn(byte[4][4]);

byte xTime_2(byte, byte);
byte xTime_8(byte,byte,byte,byte);
byte xTime_4(byte, byte);

void printOutput(char[30], byte[4][4], int);
void printRoundKey(char[30], byte[4][44], int, int);

#endif // CIPHER_H
