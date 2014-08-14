#include "SMS4_head.h"
void ByteToInt(unsigned char *plainBlock,unsigned long  *temp)
{ int j;
  for (j=0;j<4;j++)
   {   
	   temp[j]=plainBlock[j*4+0]*0x1000000+plainBlock[j*4+1]*0x10000+plainBlock[j*4+2]*0x100+plainBlock[j*4+3];
   }
}