#include <stdio.h>
#include "Cipher.h"

int main()
{
    byte input[4][4]  = {
        {0x00, 0x11, 0x22, 0x33},
        {0x44, 0x55, 0x66, 0x77},
        {0x88, 0x99, 0xaa, 0xbb},
        {0xcc, 0xdd , 0xee, 0xff}
    };

    byte Response[4][4] = {
        {0x00, 0x10, 0x20, 0x30},
        {0x40, 0x50, 0x60, 0x70},
        {0x80, 0x90, 0xa0, 0xb0},
        {0xc0, 0xd0 , 0xe0, 0xf0}
    };

    byte CipherKey[4][4] = {
        {0x00, 0x01, 0x02, 0x03},
        {0x04, 0x05, 0x06, 0x07},
        {0x08, 0x09, 0x0a, 0x0b},
        {0x0c, 0x0d ,0x0e, 0x0f}
    };

    AddRoundKey(input, CipherKey);
    printf("%d", memcmp(&input, &Response, 16));
    printf("\n");
    SubBytes(input);
    printf("\n");
    for(int i = 0; i < 4; i++)
    {
       for(int j = 0; j < 4; j++)
       {
           printf("%02x", input[i][j]);
       }
    }

    ShiftRows(input);
    printf("\n");
    for(int i = 0; i < 4; i++)
    {
       for(int j = 0; j < 4; j++)
       {
           printf("%02x", input[i][j]);
       }
    }
}
