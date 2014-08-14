#include "SMS4_head.h"
void Fill(unsigned char *plainBlock,char ch,int n)
{int i;
 for (i=0;i<n-1;i++) *(plainBlock+i)=ch;
}