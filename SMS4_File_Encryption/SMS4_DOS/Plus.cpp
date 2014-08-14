#include "SMS4_head.h"
void Plus(unsigned char *Counter)
{unsigned long temp[4];
 ByteToInt(Counter,temp);
 if (temp[0]==0xffffffff) 
    {temp[0]=0x00000000;
     if (temp[1]==0xffffffff)
	 {temp[1]=0x00000000;
	  if (temp[2]==0xffffffff)
	  {temp[2]=0x00000000;
	   if (temp[3]==0xffffffff)
	     temp[3]=0x00000000;
	   else temp[3]++;
	  }
	  else temp[2]++;
	 }
	 else temp[1]++;
    }
  else temp[0]++;
   
   
 IntToByte(Counter,temp);
}