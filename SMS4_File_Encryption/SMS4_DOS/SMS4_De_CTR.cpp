#include "SMS4_head.h"

int SMS4_De_CTR(char *plainFile, unsigned char *baseKey,char *cipherFile,unsigned char *Counter,long int *Lenth)
{
    FILE *plain,*cipher;
	long int fileLen,times=0;
    int i,count,in_temp;unsigned long roundKey[36];
    unsigned char plainBlock[16],cipherBlock[16],O_Counter[16],t_Counter[16];
     if((plain = fopen(plainFile,"wb")) == NULL){
        return ERROR;
    }   
    if((cipher = fopen(cipherFile,"rb")) == NULL){
        return ERROR;
    }

    KeyGenerate(baseKey,roundKey);
    for (i=0;i<16;i++) t_Counter[i]=Counter[i];
	fseek(cipher,0,SEEK_END);    
    fileLen = ftell(cipher);    
    rewind(cipher); 

	while(1)
	{    
        fread(cipherBlock,sizeof(char),16,cipher);
        SMS4_EncryptBlock(t_Counter,roundKey,O_Counter);
		for (i=0;i<16;i++) {plainBlock[i]=cipherBlock[i]^O_Counter[i];}
		Plus(t_Counter);
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
	{   
        fwrite(plainBlock,sizeof(char),16 - plainBlock[15],plain);      
	}
     else 
	 {   
		 fwrite(plainBlock,sizeof(char),16,plain);		
	}
    fclose(plain);
	fclose(cipher);

	*Lenth=fileLen;
return 1;
}