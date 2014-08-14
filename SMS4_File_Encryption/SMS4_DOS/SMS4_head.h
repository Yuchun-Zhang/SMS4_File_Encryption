#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ERROR -2
extern void SMS4_EncryptBlock(unsigned char *,unsigned long*,unsigned char *);
extern void SMS4_DecryptBlock(unsigned char *,unsigned long*,unsigned char *);

extern int SMS4_Encrypt(char *, unsigned char *,char *,long int*);
extern int SMS4_Decrypt(char *, unsigned char *,char *,long int*);

extern int test_Encrypt( unsigned char *);

extern int SMS4_En_CBC(char *, unsigned char *,char *,unsigned char *,long int*);
extern int SMS4_De_CBC(char *, unsigned char *,char *,unsigned char *,long int*);

extern int SMS4_En_CFB(char *, unsigned char *,char *,unsigned char *,long int*);
extern int SMS4_De_CFB(char *, unsigned char *,char *,unsigned char *,long int*);

extern int SMS4_En_OFB(char *, unsigned char *,char *,unsigned char *,long int*);
extern int SMS4_De_OFB(char *, unsigned char *,char *,unsigned char *,long int*);

extern int SMS4_En_CTR(char *, unsigned char *,char *,unsigned char *,long int*);
extern int SMS4_De_CTR(char *, unsigned char *,char *,unsigned char *,long int*);

extern void ByteToInt(unsigned char *,unsigned long *);
extern void IntToByte (unsigned char *,unsigned long *);
extern void KeyGenerate(unsigned char *,unsigned long *);
extern void SBOX(unsigned long *temp);
extern void Fill(unsigned char *,char ,int );
extern int SMS4_hex(char *,char *,char *);
extern void Plus(unsigned char *);
