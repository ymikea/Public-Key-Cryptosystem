#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <unistd.h>
#include <stdint.h>
#include<stdbool.h>
#include<time.h>
#include "Miller_Expon.h"

bool Decry,Encry,Gen;


int main(int argc, char *argv[]){
    FILE *fp_key, *fp_plain, *fp_cipher;
    char *keyTxt_buff = NULL;
    uint64_t plainTxt;
    int opt;
   while((opt = getopt(argc, argv, "dk:ek:in:out:genkey:")) != -1)  {  
        switch(opt)  
        {   
            case 'd':
                Decry = true;
                break; 
            case 'e':
                Encry = true;
                break;
            case 'k': 
                fp_key = fopen(optarg, "r"); 
                break;
            case 'i': 
            case 'n':  
                fp_plain = fopen(optarg, "rb"); 
                break;  
             case 'o':
             case 'u':
             case 't': 
                fp_cipher = fopen(optarg, "w+b"); 
                break;
             case 'g':  
                Gen = true;
                break;  
            
        }  
    }
 

uint64_t q,d = 0,e1 = 2,e2;
uint64_t kk = 0,p;
struct timespec begin,end;
if (Gen){
    clock_gettime(CLOCK_MONOTONIC,&begin);
    printf("Generating Keys Please Hold......\n");
    srand(time(0));
    while(1){
        q = Randoms(pow(2,31)+1,pow(2,33)-1,1);
        p = (q << 1)+1;
            if (fastExponent(q,1,12)==5 && MillerRabin(p,10)){
                break;
            }
    }

    d = Randoms(1,p-2,1); 
    e2 = fastExponent(2,d,p);
    clock_gettime(CLOCK_MONOTONIC,&end);
    double elapsed = end.tv_sec - begin.tv_sec;
    printf("Keys Succesfully Generated in %0.2f seconds!\n",elapsed);
    // printf("q: %u p: %llu d: %u\n",q, p,d);
    fp_cipher = fopen("privateKey.txt", "w+b"); 
    fprintf(fp_cipher , "%llu %u %llu", p,2,d);
    fp_cipher = fopen("publicKey.txt", "w+b"); 
    fprintf(fp_cipher , "%llu %u %llu", p,2,e2);
return 0;
}



if(Encry){
        size_t leng;
    while (( getline(&keyTxt_buff, &leng, fp_key)) != -1){
        char* token = strtok(keyTxt_buff, " ");
        p = strtol(token, NULL, 10);
        token = strtok(NULL, " ");
        e1 = strtol(token, NULL, 10);
        token = strtok(NULL, " ");
        e2 = strtol(token, NULL, 10);
    }


    int amount;
    while ((amount = fread(&plainTxt, 1, 4, fp_plain))> 0){
     if(amount < 4){
            uint64_t a = (4-amount)*2;
            plainTxt = plainTxt << a*4;
            plainTxt = plainTxt + a/2;
        }
        uint64_t m = plainTxt;
        kk = Randoms(1,p-1,1);
        uint64_t  c1 = fastExponent(e1,kk,p); 
        //uint64_t c2 = ModularArithmetic(fastExponent(e1,kk,p), m, p);
        uint64_t  c2 = fastExponent(fastExponent(e2,kk,p) * fastExponent(m,1,p),1,p);
        // printf("c1: %llx c2: %llx\n",c1,c2);
        fprintf(fp_cipher , "%lld %lld\n", c1,c2);
        memset(&plainTxt, 0, sizeof(plainTxt));
    } 
}
 
if(Decry){
        size_t leng;
    while (( getline(&keyTxt_buff, &leng, fp_key)) != -1){
        char* token = strtok(keyTxt_buff, " ");
        p = strtol(token, NULL, 10);
        token = strtok(NULL, " ");
        e1 = strtol(token, NULL, 10);
        token = strtok(NULL, " ");
        d = strtol(token, NULL, 10);
    }
    // printf("p: %llx d: %llx e1: %llu\n",p,d,e1);
    char *plainTxt_bu = NULL;
    size_t len;    
      while (getline(&plainTxt_bu, &len, fp_plain) != -1){
        char* token = strtok(plainTxt_bu, " ");
            uint64_t c1 = strtol(token, NULL, 10);
            token = strtok(NULL, " ");
            uint64_t c2 = strtol(token, NULL, 10);
            //  printf("c1: %llx c2 : %llx\n",c1, c2);
            // uint64_t c3 = fastExponent((fastExponent(c1,p-1-d,p) * fastExponent(c2,1,p)),1,p);
           uint64_t c3 = ModularArithmetic(fastExponent(c1, p-d-1, p), c2, p);

                uint8_t *k = (uint8_t *)&c3;
                int length  = sizeof(uint32_t);
                if ((k[0] < 0x04) && (k[0] > 0x00)) {
                    int c = k[0]*8;
                    length = 4-k[0];
                    k[0] = 0x00;
                    c3 = c3 >> c;
                }
            // printf("%llx ", c3);
            fwrite(&c3 ,length ,1 , fp_cipher );
      }
}


    return 0;
}




























//   while (( getdelim(&plainTxt_bu, &len, 21, fp_plain)) != -1){
    //   while ((fread(plainTxt_buff, 1, 19, fp_plain))> 0){
         
        //   printf("%s",plainTxt_bu);
        //   printf("%s",plainTxt_buff);

 //Decrytion
    // uint64_t c3 = fastExponent((fastExponent(c1,p-1-d,p) * fastExponent(c2,1,p)),1,p);
    // char Hex_Res[17];
    // sprintf(Hex_Res,"%16llx",c3);
    // fwrite(Hex_Res , sizeof(Hex_Res)-1 ,1 , fp_cipher );
    // printf("c3: %llu\n",c3);
    // printf("%llu ",c3);
    // printf("%s ",Hex_Res);

    // fread(keyTxt_buff, 16, 1, fp_key);
    // uint32_t e1 = Randoms(1,p-1,1);
    // uint32_t e1 = 2;
    // printf("p: %llu e1: %u d: %u\n",p,e1,d);      
    // (e1,e2,p) are public keys 
    // d is private key
    // uint32_t e2 = fastExponent(e1,d,p);
    // printf("kk: %llu e2: %u\n",kk,e2);


// uint32_t m;
// fread(&plainTxt_buff,16, 1, fp_plain);
//  uint8_t *k = (uint8_t *)&plainTxt_buff;

// // Encryption
// for (int i = 0; i < 16; i++){
//     uint64_t kk = Randoms(1,p-1,1);
//     // printf("%hhu",k[i]);
//     m = k[i];
//     uint64_t c1 = fastExponent(e1,kk,p); 
//     uint64_t c2 = fastExponent(fastExponent(e2,kk,p) * fastExponent(m,1,p),1,p);
//     printf("k: %llu c1: %llu c2: %llu\n",kk,c1,c2);

//     //Decrytion
//     uint64_t c3 = fastExponent((fastExponent(c1,p-1-d,p) * fastExponent(c2,1,p)),1,p);
//     printf("c3: %llu\n",c3);
// }
