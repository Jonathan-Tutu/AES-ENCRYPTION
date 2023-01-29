#include "Cipher.h"

void InvCipher(byte in[4][4], byte out[4][4], byte RoundKey[4][44])
{

    byte state[4][4] = {};
    memcpy_s(state, sizeof(state), in, 16*sizeof (byte));

    int Nr = 10;
    printf("\n\nINVERSE CIPHER (DECRYPT):\n");

    printOutput(".iinput", state, 0);
    printRoundKey(".ik_sch", RoundKey, 0, 10);
    AddRoundKey(state, RoundKey, 40);

    for(int nbRound = Nr - 1; nbRound > 0; nbRound--)
    {
        printOutput(".istart", state, Nr - nbRound);
        InvShiftRows(state);
        printOutput(".is_row", state, Nr - nbRound);

        InvSubBytes(state);
        printOutput(".is_box", state, Nr - nbRound);

        AddRoundKey(state, RoundKey, 4*nbRound);
        printRoundKey(".ik_sch", RoundKey, Nr - nbRound, nbRound);

        InvMixColumn(state);
        printOutput(".ik_add", state, Nr - nbRound);
    }

    printOutput(".istart", state, 10);
    InvShiftRows(state);
    printOutput(".is_row", state, 10);

    InvSubBytes(state);
    printOutput(".is_box", state, 10);
    printRoundKey(".ik_sch", RoundKey, 10, 0);

    AddRoundKey(state, RoundKey, 0);
    printOutput(".ioutput", state, 10);

    memcpy_s(out, sizeof(state), state, 16*sizeof (byte));
}

void Cipher(byte in[4][4], byte out[4][4], byte RoundKey[4][44])
{
    byte state[4][4] = {};
    memcpy_s(state, sizeof(state), in, 16*sizeof (byte));

    int Nr = 10;
    printf("\nCIPHER (ENCRYPT):\n");

    printOutput(".input", state, 0);
    printRoundKey(".k_sch", RoundKey, 0,0);
    AddRoundKey(state, RoundKey, 0);
    printOutput(".start", state, 0);

    for(int nbRound = 1; nbRound <= Nr-1;  nbRound++)
    {

        printOutput(".start", state, nbRound);
        SubBytes(state);
        printOutput(".s_box", state, nbRound);

        ShiftRows(state);
        printOutput(".s_row", state, nbRound);

        MixColumns(state);
        printOutput(".m_col", state, nbRound);

        AddRoundKey(state, RoundKey, 4*nbRound);
        printRoundKey(".k_sch", RoundKey, nbRound, nbRound);
     }

    SubBytes(state);
    printOutput(".s_box", state, 10);

    ShiftRows(state);
    printOutput(".s_row", state, 10);
    printRoundKey(".k_sch", RoundKey, 10, 10);

    AddRoundKey(state, RoundKey, 40);
    printOutput(".output", state, 10);

    memcpy_s(out, sizeof(state), state, 16*sizeof (byte));
}

void AddRoundKey(byte in[4][4],  byte RoundKey[4][44], int val)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            in[j][i] ^= RoundKey[j][i+val];
        }
    }
}

void SubBytes(byte in[4][4])
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            int row = in[j][i] >> 4;
            int col = in[j][i] & 0x0f;
            in[j][i] = sbox[row][col];
        }
    }
}

void InvSubBytes(byte in[4][4])
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            int row = in[j][i] >> 4;
            int col = in[j][i] & 0x0f;
            in[j][i] = InvSbox[row][col];
        }
    }
}

void ShiftRows(byte in[4][4])
{
       byte temp;

        // Shift row 1 by 1
       temp = in[1][0];
       in[1][0] = in[1][1];
       in[1][1] =  in[1][2];
       in[1][2] = in[1][3];
       in[1][3] = temp;

        // Shift row 2 by 2
       //Colonne //ligne
        temp = in[2][0];
        in[2][0] = in[2][1];
        in[2][1] = in[2][2];
        in[2][2] = in[2][3];
        in[2][3] = temp;

        temp = in[2][0];
        in[2][0] = in[2][1];
        in[2][1] = in[2][2];
        in[2][2] = in[2][3];
        in[2][3] = temp;

        // Shift row 3 by 3
        temp = in[3][3];
        in[3][3] = in[3][2];
        in[3][2] = in[3][1];
        in[3][1] = in[3][0];
        in[3][0] = temp;
}

void InvShiftRows(byte in[4][4]) {
    byte temp;

    //Inverse row 1
    temp = in[1][3];
    in[1][3] = in[1][2];
    in[1][2] = in[1][1];
    in[1][1] = in[1][0];
    in[1][0] = temp;

    //Inverse row 2
    temp = in[2][3];
    in[2][3] = in[2][2];
    in[2][2] = in[2][1];
    in[2][1] = in[2][0];
    in[2][0] = temp;

    temp = in[2][3];
    in[2][3] = in[2][2];
    in[2][2] = in[2][1];
    in[2][1] = in[2][0];
    in[2][0] = temp;

    //Inverse row 3
    temp = in[3][0];
    in[3][0] = in[3][1];
    in[3][1] = in[3][2];
    in[3][2] = in[3][3];
    in[3][3] = temp;
}

void MixColumns(byte in[4][4])
{
     for(int i = 0; i < 4; i++)
     {
         byte S0 = in[0][i];
         byte S1 = in[1][i];
         byte S2 = in[2][i];
         byte S3 = in[3][i];

         in[0][i] = xTime_2(S0, S1) ^ S1 ^ S2 ^ S3;
         in[1][i] = xTime_2(S1, S2) ^ S0 ^ S2 ^ S3;
         in[2][i]= xTime_2(S2, S3) ^ S0 ^ S1 ^ S3;
         in[3][i] = xTime_2(S3, S0) ^ S0 ^ S2 ^ S1;
    }
}

void InvMixColumn(byte in[4][4])
{
    for(int i = 0; i < 4; i++)
    {
        byte S0 = in[0][i];
        byte S1 = in[1][i];
        byte S2 = in[2][i];
        byte S3 = in[3][i];

        in[0][i] = xTime_8(S0, S1, S2, S3) ^ xTime_4(S0, S2) ^ xTime_2(S0, S1) ^S1 ^ S2 ^ S3;
        in[1][i] = xTime_8(S0, S1, S2, S3) ^ xTime_4(S1, S3) ^ xTime_2(S1, S2) ^S0 ^ S2 ^ S3;
        in[2][i] = xTime_8(S0, S1, S2, S3) ^ xTime_4(S2, S0) ^ xTime_2(S2, S3) ^S1 ^ S0 ^ S3;
        in[3][i] = xTime_8(S0, S1, S2, S3) ^ xTime_4(S3, S1) ^ xTime_2(S3, S0) ^S1 ^ S2 ^ S0;
   }
}

byte xTime_2(byte byte1, byte byte2)
{
    byte calcul = byte1 ^ byte2;
    byte mask = 0x80;
    byte pf = calcul&mask; //On vérifie la valeur du bit de poids fort

    if(pf == 0)
    {
          calcul  = calcul << 1;
    }
    else if(pf == 128)
    {
         calcul  = calcul << 1;
         calcul ^= 0x1b;
    }

    return calcul;
}

byte xTime_8(byte byte1, byte byte2,byte byte3,byte byte4)
{
    byte calcul = byte1 ^ byte2 ^ byte3 ^ byte4;
    byte mask = 0x80;

    for(int i = 0; i < 3; i++)
    {
        byte pf = calcul&mask; //On vérifie la valeur du bit de poids fort
        if(pf == 0)
        {
              calcul  = calcul << 1;
        }
        else if(pf == 128)
        {
             calcul  = calcul << 1;
             calcul ^= 0x1b;
        }
    }

    return calcul;
}

byte xTime_4(byte byte1, byte byte2)
{
    byte calcul = byte1 ^ byte2;
    byte mask = 0x80;

    for(int i = 0; i < 2; i++)
    {
        byte pf = calcul&mask; //On vérifie la valeur du bit de poids fort
        if(pf == 0)
        {
              calcul  = calcul << 1;
        }
        else if(pf == 128)
        {
             calcul  = calcul << 1;
             calcul ^= 0x1b;
        }
    }

    return calcul;
}

void keySchedule(byte CypherKey[4][4], byte RoundKey[4][44], short Nk)
{
     int Nb = 4;
     int Nr = 10;
     int rcon_index = 0;

    /* Transfert CypherKey to RoundKey*/
    for (int i = 0; i < Nk; i++)
    {
            for (int j = 0; j < Nk; j++)
            {
                RoundKey[j][i] = CypherKey[j][i];
            }
    }

for(int i = Nk ; i < Nb * (Nr+1);  i++)
{
    if(i % Nk  == 0)
    {
        /* Get Last cols*/
        byte temp[4];
        for(int j = 0 ; j < Nk; j++)
        {
               temp[j] = RoundKey[j][i-1];
        }

        /*Rotate byte of the last Column*/
        byte tempo = temp[0];
        temp[0] = temp[1];
        temp[1] = temp[2];
        temp[2] = temp[3];
        temp[3] = tempo;

        /* SubBytes */
        for(int k = 0; k < Nk ; k++)
        {
            int row = temp[k] >> 4;
            int col = temp[k] & 0x0f;
            temp[k] = sbox[row][col];
         }

        /*Calculation of first col*/
        for(int rows = 0; rows < Nk; rows++)
        {
            RoundKey[rows][i] =  RoundKey[rows][i-4] ^ rcon[rows][rcon_index] ^ temp[rows];
        }
            rcon_index++;
        }
        else
        {
                for(int rows=0; rows < Nk; rows++)
            {
                RoundKey[rows][i] = RoundKey[rows][i-1] ^ RoundKey[rows][i-4];
            }
        }
    }
for(int i = 0; i < 4; i++)
{
    for(int j = 0; j < 44; j++)
    {
        printf("%02x ", RoundKey[i][j]);
    }
    printf("\n");
}
}

void printRoundKey(char message[15], byte RoundKey[4][44], int index_round, int round)
{
    printf("\nround[%d]%s ", index_round , message);
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            printf("%02x",RoundKey[j][i+4*round]);
        }
    }
}

void printOutput(char message[15], byte in[4][4], int round)
{
    printf("\nround[%d]%s ", round , message);
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            printf("%02x", in[j][i]);
        }
    }
}





