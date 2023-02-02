#include "Cipher.h"

void InvCipher(byte in[4][4], byte out[4][4], byte RoundKey[4][44])
{
    byte state[4][4] = {};

    //Copy the input into the state variable
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

    //Copy the state into the out variable
    memcpy_s(out, sizeof(state), state, 16*sizeof (byte));
}

void Cipher(byte in[4][4], byte out[4][4], byte RoundKey[4][44])
{
    byte state[4][4] = {};

    //Copy the input into the state variable
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

    //Copy the state into the out variable
    memcpy_s(out, sizeof(state), state, 16*sizeof (byte));
}

void AddRoundKey(byte in[4][4],  byte RoundKey[4][44], int val)
{
    //Iterate through the input matrix
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //XOR operation between the input and the RoundKey
            // "+val" allow us to shift on the roundkey
            in[j][i] ^= RoundKey[j][i+val];
        }
    }
}

void SubBytes(byte in[4][4])
{
    //Iterate through the input matrix
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //Determine row and col used with the sbox table
            int row = in[j][i] >> 4; //Shift row to extract 4 less significant bit which represent the row
            int col = in[j][i] & 0x0f; //Calculation with Mask to extract 4 less significant bit which represent the col
            in[j][i] = sbox[row][col];
        }
    }
}

//Same function as SubBytes just to have a better understanding
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

       //Shift row 1 by 1 to the left
       temp = in[1][0];
       in[1][0] = in[1][1];
       in[1][1] =  in[1][2];
       in[1][2] = in[1][3];
       in[1][3] = temp;

        //Shift row 2 by 1 to the left (First time)
        temp = in[2][0];
        in[2][0] = in[2][1];
        in[2][1] = in[2][2];
        in[2][2] = in[2][3];
        in[2][3] = temp;

        //Shift row 2 by 1 to the left (Second time)
        temp = in[2][0];
        in[2][0] = in[2][1];
        in[2][1] = in[2][2];
        in[2][2] = in[2][3];
        in[2][3] = temp;

        //Shift row 3 by 1 to the right because it is equivalent to shift 3 times the row to the left
        temp = in[3][3];
        in[3][3] = in[3][2];
        in[3][2] = in[3][1];
        in[3][1] = in[3][0];
        in[3][0] = temp;
}

void InvShiftRows(byte in[4][4]) {
    byte temp;

    //Inverse row 1 by 1 to the left
    temp = in[1][3];
    in[1][3] = in[1][2];
    in[1][2] = in[1][1];
    in[1][1] = in[1][0];
    in[1][0] = temp;

    //Inverse row 2 by 1 to the left
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

    //Inverse row 3 by 1 to the left
    temp = in[3][0];
    in[3][0] = in[3][1];
    in[3][1] = in[3][2];
    in[3][2] = in[3][3];
    in[3][3] = temp;
}

void MixColumns(byte in[4][4])
{
     //Iterate through the column of the input matrix
     for(int i = 0; i < 4; i++)
     {
         //We store each line in a different variable to make the link with the equation written in class
         byte S0 = in[0][i];
         byte S1 = in[1][i];
         byte S2 = in[2][i];
         byte S3 = in[3][i];

         //We calculate the new values ​​of each row using the result of xTime_2 function and XOR operation
         in[0][i] = xTime_2(S0, S1) ^ S1 ^ S2 ^ S3;
         in[1][i] = xTime_2(S1, S2) ^ S0 ^ S2 ^ S3;
         in[2][i]= xTime_2(S2, S3) ^ S0 ^ S1 ^ S3;
         in[3][i] = xTime_2(S3, S0) ^ S0 ^ S2 ^ S1;
    }
}

void InvMixColumn(byte in[4][4])
{
    //Iterate through the column of the input matrix
    for(int i = 0; i < 4; i++)
    {
        //We store each line in a different variable to make the link with the equation written in class
        byte S0 = in[0][i];
        byte S1 = in[1][i];
        byte S2 = in[2][i];
        byte S3 = in[3][i];

        //We calculate the new values ​​of each row using the result of xTime_2, xTime_4, xTime_8 function and XOR operation
        in[0][i] = xTime_8(S0, S1, S2, S3) ^ xTime_4(S0, S2) ^ xTime_2(S0, S1) ^S1 ^ S2 ^ S3;
        in[1][i] = xTime_8(S0, S1, S2, S3) ^ xTime_4(S1, S3) ^ xTime_2(S1, S2) ^S0 ^ S2 ^ S3;
        in[2][i] = xTime_8(S0, S1, S2, S3) ^ xTime_4(S2, S0) ^ xTime_2(S2, S3) ^S1 ^ S0 ^ S3;
        in[3][i] = xTime_8(S0, S1, S2, S3) ^ xTime_4(S3, S1) ^ xTime_2(S3, S0) ^S1 ^ S2 ^ S0;
   }
}

byte xTime_2(byte byte1, byte byte2)
{
    //Calculate the XOR operation of the two input bytes variable
    byte calcul = byte1 ^ byte2;
    byte mask = 0x80;
    //Calculate the value of the most significant bit
    byte pf = calcul&mask;

    //If the most significant bit is equal to 0
    if(pf == 0)
    {
          //We shift the bits to the left
          calcul  = calcul << 1;
    }
    //If the most significant bit is equal to 128
    else if(pf == 128)
    {
        //We shift the bits to the left and XOR calculation with 0x1b
         calcul  = calcul << 1;
         calcul ^= 0x1b;
    }

    //return the result
    return calcul;
}

byte xTime_8(byte byte1, byte byte2,byte byte3,byte byte4)
{
    //Calculate the XOR operation of the three input bytes variable
    byte calcul = byte1 ^ byte2 ^ byte3 ^ byte4;
    byte mask = 0x80;

    //We make the operation 3 times
    for(int i = 0; i < 3; i++)
    {
        //Calculate the value of the most significant bit
        byte pf = calcul&mask;

        //If the most significant bit is equal to 0
        if(pf == 0)
        {
              //We shift the bits to the left
              calcul  = calcul << 1;
        }
        //If the most significant bit is equal to 128
        else if(pf == 128)
        {
            //We shift the bits to the left and XOR calculation with 0x1b
             calcul  = calcul << 1;
             calcul ^= 0x1b;
        }
    }

    //return the result
    return calcul;
}

byte xTime_4(byte byte1, byte byte2)
{
    //Calculate the XOR operation of the two input bytes variable
    byte calcul = byte1 ^ byte2;
    byte mask = 0x80;

    //We make the operation 2 times
    for(int i = 0; i < 2; i++)
    {
        //Calculate the value of the most significant bit
        byte pf = calcul&mask;

        //If the most significant bit is equal to 0
        if(pf == 0)
        {
              //We shift the bits to the left
              calcul  = calcul << 1;
        }
        //If the most significant bit is equal to 128
        else if(pf == 128)
        {
             //We shift the bits to the left and XOR calculation with 0x1b
             calcul  = calcul << 1;
             calcul ^= 0x1b;
        }
    }

    //return the result
    return calcul;
}

void keySchedule(byte CypherKey[4][4], byte RoundKey[4][44])
{
     short Nk = 4; //Number of row of the key
     int Nb = 4; //Number of columns in the block
     int Nr = 10; //Number of rounds
     int rcon_index = 0; //Rcon array index

    //Transfer the encryption key (CypherKey) to the RoundKey variable
for (int i = 0; i < Nk; i++)
{
    for (int j = 0; j < Nk; j++)
    {
        RoundKey[j][i] = CypherKey[j][i];
    }
}

//Start of the loop that will generate all RoundKeys
for(int i = Nk ; i < Nb * (Nr+1);  i++)
{
    //If the current turn is a multiple of Nk
    if(i % Nk  == 0)
    {
        //Get the last column
        byte temp[4];
        for(int j = 0 ; j < Nk; j++)
        {
               temp[j] = RoundKey[j][i-1];
        }

        //Rotate byte of the last column
        byte tempo = temp[0];
        temp[0] = temp[1];
        temp[1] = temp[2];
        temp[2] = temp[3];
        temp[3] = tempo;

        //SubBytes function for a 1 dimension array
        for(int k = 0; k < Nk ; k++)
        {
            int row = temp[k] >> 4;
            int col = temp[k] & 0x0f;
            temp[k] = sbox[row][col];
         }

        //Calculation of first col 'main one' for each row
        for(int rows = 0; rows < Nk; rows++)
        {
            RoundKey[rows][i] =  RoundKey[rows][i-4] ^ rcon[rows][rcon_index] ^ temp[rows];
        }
            //increase the rcon_index
            rcon_index++;
        }
        else
        {
            //For each row calculate the column value
            for(int rows=0; rows < Nk; rows++)
            {
                RoundKey[rows][i] = RoundKey[rows][i-1] ^ RoundKey[rows][i-4];
            }
        }
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





