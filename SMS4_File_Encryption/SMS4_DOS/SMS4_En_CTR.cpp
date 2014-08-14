#include "SMS4_head.h"
int SMS4_En_CTR(char *plainFile,unsigned char *baseKey,char *cipherFile,unsigned char *Counter,long int *Lenth)
{
    FILE *plain,*cipher;
	long int fileLen;
    int i,count,in_temp;
	unsigned long roundKey[36];
    unsigned char plainBlock[16],cipherBlock[16],t_Counter[16],O_Counter[16];
    if((plain = fopen(plainFile,"rb")) == NULL){  return ERROR; }   
    if((cipher = fopen(cipherFile,"wb")) == NULL){ return ERROR; }

	fseek(plain,0,SEEK_END);    
    fileLen = ftell(plain);    
    rewind(plain);  
    for (i=0;i<16;i++) t_Counter[i]=Counter[i];
    KeyGenerate(baseKey,roundKey);
	while(!feof(plain))
	{
        if((count = fread(plainBlock,sizeof(char),16,plain)) == 16)
		{
                
			SMS4_EncryptBlock(t_Counter,roundKey,O_Counter);			   
			for (i=0;i<16;i++){cipherBlock[i]=plainBlock[i]^O_Counter[i];}	
			Plus(t_Counter);
            fwrite(cipherBlock,sizeof(char),16,cipher);     
        }
    }
    if(count)
	{
        Fill(plainBlock + count,'\0',16 - count);
        plainBlock[15] = 16 - count;
		SMS4_EncryptBlock(t_Counter,roundKey,O_Counter);	
		for (i=0;i<16;i++){cipherBlock[i]=plainBlock[i]^O_Counter[i];}
        fwrite(cipherBlock,sizeof(char),16,cipher);  
	}
    fclose(plain);
	fclose(cipher);
	*Lenth=fileLen;
return 1;
}