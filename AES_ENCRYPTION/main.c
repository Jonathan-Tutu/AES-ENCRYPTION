#include <stdio.h>
#include "Cipher.h"

int main()
{
    byte RoundKey[4][44] = {};
    byte outputCipher[4][4] = {};
    byte outputInvCipher[4][4] = {};

    //CipherKey
    byte CipherKey[4][4] = {
         {0x00,0x04,0x08,0x0c},
         {0x01,0x05,0x09,0x0d},
         {0x02,0x06,0x0a,0x0e},
         {0x03,0x07,0x0b,0x0f},
     };

    //Input values
    byte input[4][4] = {
        {0x00,0x44,0x88,0xcc},
        {0x11,0x55,0x99,0xdd},
        {0x22,0x66,0xaa,0xee},
        {0x33,0x77,0xbb,0xff},
    };

    //Generate roundkey
    keySchedule(CipherKey, RoundKey, 4);

    //Encryption of input
    Cipher(input, outputCipher, RoundKey);

    //Decryption of the output of input
    InvCipher(outputCipher, outputInvCipher, RoundKey);
}

