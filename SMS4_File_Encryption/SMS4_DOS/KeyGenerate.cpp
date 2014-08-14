#include "SMS4_head.h"
void KeyGenerate(unsigned char *baseKey,unsigned long *roundKey)
{
 ByteToInt(baseKey,roundKey);
 int i;
 roundKey[0]^=0xa3b1bac6;
 roundKey[1]^=0x56aa3350;
 roundKey[2]^=0x677d9197;
 roundKey[3]^=0xb27022dc;
 unsigned long CK[32] =
{0x00070e15,0x1c232a31,0x383f464d,0x545b6269,
0x70777e85,0x8c939aa1,0xa8afb6bd,0xc4cbd2d9,
0xe0e7eef5,0xfc030a11,0x181f262d,0x343b4249,
0x50575e65,0x6c737a81,0x888f969d,0xa4abb2b9,
0xc0c7ced5,0xdce3eaf1,0xf8ff060d,0x141b2229,
0x30373e45,0x4c535a61,0x686f767d,0x848b9299,
0xa0a7aeb5,0xbcc3cad1,0xd8dfe6ed,0xf4fb0209,
0x10171e25,0x2c333a41,0x484f565d,0x646b7279};
 for(i=0;i<32;i++)
 { 
   roundKey[i+4]=roundKey[i+1]^roundKey[i+2]^roundKey[i+3]^CK[i];
   SBOX(roundKey+i+4);
   roundKey[i+4]=roundKey[i+4]^((roundKey[i+4]<<13)|(roundKey[i+4]>>19))^((roundKey[i+4]<<23)|(roundKey[i+4]>>9));
   roundKey[i+4]=roundKey[i]^roundKey[i+4];
}
}