#include "SMS4_head.h"
void SMS4_DecryptBlock(unsigned char *plainBlock,unsigned long *roundKey,unsigned char *cipherBlock)
{unsigned long temp[36];
 ByteToInt(plainBlock,temp);
 int i;
 for(i=0;i<32;i++)
 { temp[i+4]=temp[i+1]^temp[i+2]^temp[i+3]^roundKey[35-i];
   SBOX(temp+i+4);
   temp[i+4]=temp[i+4]^((temp[i+4]<<2)|(temp[i+4]>>30))^((temp[i+4]<<10)|(temp[i+4]>>22))^
	         ((temp[i+4]<<18)|(temp[i+4]>>14))^((temp[i+4]<<24)|(temp[i+4]>>8));
   temp[i+4]=temp[i]^temp[i+4];
}
 IntToByte(cipherBlock,temp);
}