#include "SMS4_head.h"
void IntToByte (unsigned char *cipherBlock,unsigned long *temp)
{ int j;
  for (j=0;j<4;j++)
   {cipherBlock[j*4+0]=temp[35-j]>>24;
    cipherBlock[j*4+1]=(temp[35-j]<<8)>>24;
	cipherBlock[j*4+2]=(temp[35-j]<<16)>>24;
	cipherBlock[j*4+3]=(temp[35-j]<<24)>>24;
   }
}