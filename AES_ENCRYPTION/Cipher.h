#ifndef CIPHER_H
#define CIPHER_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef uint8_t byte;

void Cipher(byte[4][4], byte[4][4], byte[4][4]);
void AddRoundKey(byte[4][4], byte[4][4]);
void SubBytes(byte[4][4]);
void ShiftRows(byte[4][4]);
void MixColumns();

#endif // CIPHER_H
