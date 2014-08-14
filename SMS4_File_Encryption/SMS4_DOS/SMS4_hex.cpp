#include "SMS4_head.h"
int SMS4_hex(char *plainFile, char *keyFile,char *cipherFile)
{   int in_temp;
    time_t ts,te;
	ts=time(NULL);
    FILE *plain,*cipher,*key;
    int i;unsigned long roundKey[36];
    unsigned char plainBlock[16],cipherBlock[16],baseKey[16];
    if((plain = fopen(plainFile,"rb")) == NULL){
        return ERROR;
    }   
	if((key = fopen(keyFile,"rb")) == NULL){
        return ERROR;
    }   
    if((cipher = fopen(cipherFile,"wb")) == NULL){
        return ERROR;
    }
	for (i=0;i<16;i++) {fscanf(plain,"%x",&in_temp);*(plainBlock+i)=in_temp;}   
	for (i=0;i<16;i++) {fscanf(key,"%x",&in_temp);*(baseKey+i)=in_temp;} 
	KeyGenerate(baseKey,roundKey);
	for (i=0;i<500000;i++) {
		  SMS4_EncryptBlock(plainBlock,roundKey,cipherBlock);
		  SMS4_EncryptBlock(cipherBlock,roundKey,plainBlock);
	}
	for (i=0;i<16;i++) printf("%x",plainBlock[i]);
    fclose(plain);
	fclose(cipher);
	fclose(key);
	te=time(NULL);
	printf("\n%d\n",te-ts);
return 1;
}