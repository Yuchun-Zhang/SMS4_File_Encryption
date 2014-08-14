#include "SMS4_head.h"
int SMS4_Decrypt(char *plainFile, unsigned char *baseKey,char *cipherFile,long int *Lenth)
{
    FILE *plain,*cipher;long int fileLen,times=0;
    int i,count,in_temp;unsigned long roundKey[36];
    unsigned char plainBlock[16],cipherBlock[16];
     if((plain = fopen(plainFile,"wb")) == NULL){
        return ERROR;
    }   
    if((cipher = fopen(cipherFile,"rb")) == NULL){
        return ERROR;
    }
    KeyGenerate(baseKey,roundKey);	
    
	fseek(cipher,0,SEEK_END);    
    fileLen = ftell(cipher);    
    rewind(cipher);              
	while(1)
	{
        fread(cipherBlock,sizeof(char),16,cipher);
        SMS4_DecryptBlock(cipherBlock,roundKey,plainBlock);                       
        times += 16;
        if(times < fileLen){
            fwrite(plainBlock,sizeof(char),16,plain);
        }
        else  break;   
    }
    if(plainBlock[15] < 16)
        for(count = 16 - plainBlock[15]; count < 15; count++)
            if(plainBlock[count] != '\0')   break;   
    if(count == 15)
        fwrite(plainBlock,sizeof(char),16 - plainBlock[15],plain);
     else fwrite(plainBlock,sizeof(char),16,plain);
    fclose(plain);
	fclose(cipher);
	*Lenth=fileLen;
return 1;
}