#include "SMS4_head.h"

void main()
{printf("*******************************************************\n");
 printf("*                  WELCOME TO SMS4                    *\n");
 printf("*   * * * * *    * * * * *   * * * * *   *     *      *\n");
 printf("*   *            *   *   *   *           *     *      *\n");
 printf("*   * * * * *    *   *   *   * * * * *   *     *      *\n");
 printf("*           *    *   *   *           *   * * * * *    *\n");
 printf("*   * * * * *    *   *   *   * * * * *         *      *\n");
 printf("*                         ECB_CBC_CFB_OFB_CRT 5 Modes *\n");
 printf("*                    By:Season   Frozenseason@163.com *\n");
 printf("*******************************************************\n");
 long int Lenth=0;
 clock_t ts,te;
 int slt,slt2,i;
 char enc[50],dec[50];
 unsigned char baseKey[16]={'1','2','3','4','5','6','7','8','9','0','a','b','c','d','e','f'},
               IVector[16]={'1','2','3','4','5','6','7','8','9','0','a','b','c','d','e','f'};
 FILE *rpt;
 rpt=fopen("report.txt","a");
 while(1) 
 {printf("\n\nSelect What U Want:\n1-Encryption\n2-Decryption\n3-Modify Key\n4-Modify Initial Vector\\Counter\n5-Exit\n");
  scanf("%d",&slt);
  if (slt==1)
  {printf("\nInput the File and Location to Encrypt:\n");
   printf("(For Example: D:\\\\love\\\\love.mp3)\n");
      scanf("%s",enc);
   printf("\nInput the File and Location of the ciphertext:\n");
   printf("(For Example: D:\\\\love\\\\cipherfile.xxx)\n");
      scanf("%s",dec);
loop1:   printf("\nPlease Select Mode:\n1-ECB(Normal) Mode\n2-CBC Mode\n3-CFB Mode(128-bit)\n4-OFB Mode(128-bit)\n5-CTR Mode(128-bit)\n");
      scanf("%d",&slt2);
      if (slt2==1)
       {ts=clock();
        SMS4_Encrypt(enc,baseKey,dec,&Lenth);
	    te=clock();
        printf("Encryption------ECB(Normal) Mode\n");
        printf("Cost Time: %g s\n",(te-ts)/1000.0);
        printf("The File is %g Kb\n",Lenth/1024.0);
        if ((te-ts)/1000.0==0) printf("Speed: N/A Kb/s"); else  printf("Speed: %g Kb/s",(Lenth/1024.0+1)/((te-ts)/1000.0));
	    fprintf(rpt,"Encryption------ECB(Normal) Mode\n");
        fprintf(rpt,"Cost Time: %g s\n",(te-ts)/1000.0);
        fprintf(rpt,"The File is %g Kb\n",Lenth/1024.0);
        if ((te-ts)/1000.0==0) fprintf(rpt,"Speed: N/A Kb/s"); else  fprintf(rpt,"Speed: %g Kb/s\n",(Lenth/1024.0+1)/((te-ts)/1000.0));
	   }
      else if (slt2==2)
        {
         ts=clock();
         SMS4_En_CBC(enc,baseKey,dec,IVector,&Lenth);
		 te=clock();
		 printf("Encryption------CBC Mode\n");
         printf("Cost Time: %g s\n",(te-ts)/1000.0);
         printf("The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) printf("Speed: N/A Kb/s"); else  printf("Speed: %g Kb/s",(Lenth/1024.0+1)/((te-ts)/1000.0));
		 fprintf(rpt,"Encryption------CBC Mode\n");
         fprintf(rpt,"Cost Time: %g s\n",(te-ts)/1000.0);
         fprintf(rpt,"The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) fprintf(rpt,"Speed: N/A Kb/s"); else  fprintf(rpt,"Speed: %g Kb/s\n",(Lenth/1024.0+1)/((te-ts)/1000.0));
	    }
      else if (slt2==3)
        {
         ts=clock();
         SMS4_En_CFB(enc,baseKey,dec,IVector,&Lenth);
	     te=clock();
		 printf("Encryption------CFB Mode(128-bit)\n");
         printf("Cost Time: %g s\n",(te-ts)/1000.0);
         printf("The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) printf("Speed: N/A Kb/s"); else  printf("Speed: %g Kb/s",(Lenth/1024.0+1)/((te-ts)/1000.0));
		 fprintf(rpt,"Encryption------CFB Mode(112-bit)\n");
         fprintf(rpt,"Cost Time: %g s\n",(te-ts)/1000.0);
         fprintf(rpt,"The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) fprintf(rpt,"Speed: N/A Kb/s"); else  fprintf(rpt,"Speed: %g Kb/s\n",(Lenth/1024.0+1)/((te-ts)/1000.0));
	    }
	  else if (slt2==4)
        {
         ts=clock();
         SMS4_En_OFB(enc,baseKey,dec,IVector,&Lenth);
	     te=clock();
		 printf("Encryption------OFB Mode(128-bit)\n");
         printf("Cost Time: %g s\n",(te-ts)/1000.0);
         printf("The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) printf("Speed: N/A Kb/s"); else  printf("Speed: %g Kb/s",(Lenth/1024.0+1)/((te-ts)/1000.0));
		 fprintf(rpt,"Encryption------OFB Mode(128-bit)\n");
         fprintf(rpt,"Cost Time: %g s\n",(te-ts)/1000.0);
         fprintf(rpt,"The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) fprintf(rpt,"Speed: N/A Kb/s"); else  fprintf(rpt,"Speed: %g Kb/s\n",(Lenth/1024.0+1)/((te-ts)/1000.0));
	    }
	  else if (slt2==5)
        {
         ts=clock();
         SMS4_En_CTR(enc,baseKey,dec,IVector,&Lenth);
	     te=clock();
		 printf("Encryption------CTR Mode(128-bit)\n");
         printf("Cost Time: %g s\n",(te-ts)/1000.0);
         printf("The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) printf("Speed: N/A Kb/s"); else  printf("Speed: %g Kb/s",(Lenth/1024.0+1)/((te-ts)/1000.0));		 
		 fprintf(rpt,"Encryption------CTR Mode(128-bit)\n");
         fprintf(rpt,"Cost Time: %g s\n",(te-ts)/1000.0);
         fprintf(rpt,"The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) fprintf(rpt,"Speed: N/A Kb/s"); else  fprintf(rpt,"Speed: %g Kb/s\n",(Lenth/1024.0+1)/((te-ts)/1000.0));
	    }
      else goto loop1;
  }
  else 
  if(slt==2)
  {printf("\nInput the File and Location to Decrypt:\n");
   printf("(For Example: D:\\\\love\\\\cipherfile.xxx)\n"); 
      scanf("%s",dec);
   printf("\nInput the File and Location of the plaintext:\n");
   printf("(For Example: D:\\\\love\\\\LOVE.mp3)\n");
       scanf("%s",enc);
  loop2:   printf("\nPlease Select Mode:\n1-ECB(Normal) Mode\n2-CBC Mode\n3-CFB Mode(128-bit)\n4-OFB Mode(128-bit)\n5-CTR Mode(128-bit)\n");
      scanf("%d",&slt2);
      if (slt2==1)
        {ts=clock();
         SMS4_Decrypt(enc,baseKey,dec,&Lenth);
		 te=clock();
         printf("Decryption------ECB(Normal) Mode\n");
         printf("Cost Time: %g s\n",(te-ts)/1000.0);
         printf("The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) printf("Speed: N/A Kb/s"); else  printf("Speed: %g Kb/s",(Lenth/1024.0+1)/((te-ts)/1000.0));
	     fprintf(rpt,"Decryption------ECB(Normal) Mode\n");
         fprintf(rpt,"Cost Time: %g s\n",(te-ts)/1000.0);
         fprintf(rpt,"The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) fprintf(rpt,"Speed: N/A Kb/s"); else  fprintf(rpt,"Speed: %g Kb/s\n",(Lenth/1024.0+1)/((te-ts)/1000.0));
        }   
      else if (slt2==2)
        {
         ts=clock();
         SMS4_De_CBC(enc,baseKey,dec,IVector,&Lenth);
		 te=clock();
		 printf("Decryption------CBC Mode\n");
         printf("Cost Time: %g s\n",(te-ts)/1000.0);
         printf("The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) printf("Speed: N/A Kb/s"); else  printf("Speed: %g Kb/s",(Lenth/1024.0+1)/((te-ts)/1000.0));
	  	 fprintf(rpt,"Decryption------CBC Mode\n");
         fprintf(rpt,"Cost Time: %g s\n",(te-ts)/1000.0);
         fprintf(rpt,"The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) fprintf(rpt,"Speed: N/A Kb/s"); else  fprintf(rpt,"Speed: %g Kb/s\n",(Lenth/1024.0+1)/((te-ts)/1000.0));}
     else if (slt2==3)
        {
         ts=clock();
         SMS4_De_CFB(enc,baseKey,dec,IVector,&Lenth);
	     te=clock();
		 printf("Decryption------CFB Mode(128-bit)\n");
         printf("Cost Time: %g s\n",(te-ts)/1000.0);
         printf("The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) printf("Speed: N/A Kb/s"); else  printf("Speed: %g Kb/s",(Lenth/1024.0+1)/((te-ts)/1000.0));
		 fprintf(rpt,"Decryption------CFB Mode(112-bit)\n");
         fprintf(rpt,"Cost Time: %g s\n",(te-ts)/1000.0);
         fprintf(rpt,"The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) fprintf(rpt,"Speed: N/A Kb/s"); else  fprintf(rpt,"Speed: %g Kb/s\n",(Lenth/1024.0+1)/((te-ts)/1000.0));	  }
     else if (slt2==4)
        {
         ts=clock();
         SMS4_De_OFB(enc,baseKey,dec,IVector,&Lenth);
	 	 te=clock();
		 printf("Decryption------OFB Mode(128-bit)\n");
         printf("Cost Time: %g s\n",(te-ts)/1000.0);
         printf("The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) printf("Speed: N/A Kb/s"); else  printf("Speed: %g Kb/s",(Lenth/1024.0+1)/((te-ts)/1000.0));
		 fprintf(rpt,"Decryption------OFB Mode(128-bit)\n");
         fprintf(rpt,"Cost Time: %g s\n",(te-ts)/1000.0);
         fprintf(rpt,"The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) fprintf(rpt,"Speed: N/A Kb/s"); else  fprintf(rpt,"Speed: %g Kb/s\n",(Lenth/1024.0+1)/((te-ts)/1000.0));	 }
	 else if (slt2==5)
        {
         ts=clock();
         SMS4_De_CTR(enc,baseKey,dec,IVector,&Lenth);
	     te=clock();
		 printf("Decryption------CTR Mode(128-bit)\n");
         printf("Cost Time: %g s\n",(te-ts)/1000.0);
         printf("The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) printf("Speed: N/A Kb/s"); else  printf("Speed: %g Kb/s",(Lenth/1024.0+1)/((te-ts)/1000.0));
		 fprintf(rpt,"Decryption------CTR Mode(128-bit)\n");
         fprintf(rpt,"Cost Time: %g s\n",(te-ts)/1000.0);
         fprintf(rpt,"The File is %g Kb\n",Lenth/1024.0);
         if ((te-ts)/1000.0==0) fprintf(rpt,"Speed: N/A Kb/s"); else  fprintf(rpt,"Speed: %g Kb/s\n",(Lenth/1024.0+1)/((te-ts)/1000.0));
	    } 
	 else goto loop2;
  }
  else if (slt==3) 
  { printf("Input A New Key(16characters)  Default:1234567890abcdef\n");
    printf("The Current Key is\n");
    for (i=0;i<16;i++) printf("%c",baseKey[i]);
	printf("\n");	getchar();
    for (i=0;i<16;i++) scanf("%c",&baseKey[i]);
    printf("Modified Successful!\n");
	printf("The Current Key is\n");
    for (i=0;i<16;i++) printf("%c",baseKey[i]);
	printf("\n");
 }
  else if (slt==4) 
  { printf("Input A New Initial Vector\\Counter(16characters)  Default:1234567890abcdef\n");
    printf("The Current IV\\C is\n");
    for (i=0;i<16;i++) printf("%c",IVector[i]);
	printf("\n");getchar();
    for (i=0;i<16;i++) scanf("%c",&IVector[i]);
    printf("Modified Successful!\n");
	printf("The Current IV\\C is\n");
    for (i=0;i<16;i++) printf("%c",IVector[i]);
	printf("\n");
 }
  else if (slt==5) {      
	  test_Encrypt(baseKey);}
}
 printf("\n");
 printf("     ((`\'-\"``\"\"-\'`)) \n");
 printf("      )   -    -  ( \n");
 printf("     /   (o _ o)   \\ \n");
 printf("     \\    ( 0 )    / \n");
 printf("      _'-.._'='_..-'_ \n");
 printf("    /`;#'#'#.-.#'#'#;`\\ \n");
 printf("    \\_))    '#'    ((_/ \n");
 printf("     #.  ¡î ¡î ¡î   # \n");
 printf("     '#.    3Q! .  #' \n");          
 printf("     / '#.      .#' \\ \n");
 printf("     _\\  \\'#. .#'/  /_\n"); 
 printf("     ((___) '#' (___) \n");
 system("pause");
          
}