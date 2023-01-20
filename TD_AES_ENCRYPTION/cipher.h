#ifndef CIPHER_H
#define CIPHER_H


class Cipher
{
public:
    Cipher();
    void AddRoundKey();
    void SubBytes();
    void ShiftRows();
    void MixColumns();
};

#endif // CIPHER_H
