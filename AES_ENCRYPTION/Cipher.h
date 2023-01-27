#ifndef CIPHER_H
#define CIPHER_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef uint8_t byte;

void Cipher(byte[4][4], byte[4][4], byte[4][4]);
void AddRoundKey(byte[4][4], byte[44][4], int);
void SubBytes(byte[4][4]);
void ShiftRows(byte[4][4]);
void MixColumns(byte[4][4]);
void keySchedule(byte[4][4], byte[40][4], short);
byte xTime(byte, byte);

#endif // CIPHER_H
