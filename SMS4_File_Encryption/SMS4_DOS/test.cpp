#include "SMS4_head.h"
int test_Encrypt( unsigned char *baseKey)
{
    FILE *plain,*cipher;long int fileLen;
    int i,count,in_temp;unsigned long roundKey[36];
	unsigned char plainBlock[16]={'1','2','3','4','5','6','7','8','9','0','a','b','c','d','e','f'};
	unsigned char	cipherBlock[16];
	KeyGenerate(baseKey,roundKey);
	for (i=0;i<36;i++) printf("%u  ",roundKey[i]);
		printf("\n");
    SMS4_EncryptBlock(plainBlock,roundKey,cipherBlock);
	for (i=0;i<16;i++) printf("%u  ",plainBlock[i]);
	printf("\n");
	for (i=0;i<16;i++) printf("%u  ",cipherBlock[i]);
	getchar();
	SMS4_DecryptBlock(cipherBlock,roundKey,plainBlock);
	getchar();
	SMS4_EncryptBlock(plainBlock,roundKey,cipherBlock);
return 1;
}