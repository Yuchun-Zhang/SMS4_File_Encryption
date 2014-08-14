#include "SMS4_head.h"
int SMS4_En_CBC(char *plainFile,unsigned  char *baseKey,char *cipherFile,unsigned char *IVector,long int *Lenth)
{
    FILE *plain,*cipher;
	long int fileLen;
    int i,count,in_temp;
	unsigned long roundKey[36];
    unsigned char plainBlock[16],cipherBlock[16];
     if((plain = fopen(plainFile,"rb")) == NULL){
        return ERROR;
    }   
    if((cipher = fopen(cipherFile,"wb")) == NULL){
        return ERROR;
    }

	fseek(plain,0,SEEK_END);    
    fileLen = ftell(plain);    
    rewind(plain);  


    KeyGenerate(baseKey,roundKey);
    for (i=0;i<16;i++) cipherBlock[i]=IVector[i];
	while(!feof(plain)){
        if((count = fread(plainBlock,sizeof(char),16,plain)) == 16){
            for (i=0;i<16;i++) plainBlock[i]^=cipherBlock[i];
            SMS4_EncryptBlock(plainBlock,roundKey,cipherBlock);
            fwrite(cipherBlock,sizeof(char),16,cipher);   
        }
    }
    if(count){
        Fill(plainBlock + count,'\0',16 - count);
		plainBlock[15] = 16 - count; 
        for (i=0;i<16;i++) plainBlock[i]^=cipherBlock[i];
		SMS4_EncryptBlock(plainBlock,roundKey,cipherBlock);
        fwrite(cipherBlock,sizeof(char),16,cipher);
    }
    fclose(plain);
	fclose(cipher);
	*Lenth=fileLen;
return 1;
}