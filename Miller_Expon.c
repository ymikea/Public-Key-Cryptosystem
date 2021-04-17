#include<stdio.h>
#include<math.h>
#include<inttypes.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include <unistd.h>

#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define BLUE   "\x1B[34m"
#define RESET "\x1B[0m"

uint64_t Random_A = 0;
bool debug = false;


uint64_t Randoms(uint64_t lower, uint64_t upper,  uint64_t count) { 
    uint64_t i,num; 
    for (i = 0; i < count; i++) { 
        num = (rand() % 
           (upper - lower + 1)) + lower; 
    } 
     return (num <=0 ) ? Randoms(lower,upper,count) : num;
} 


uint64_t ModularArithmetic(uint64_t a, uint64_t b, uint64_t n) { 
    uint64_t ModRes = 0; 
    while (b > 0){ 
        if (b & 1) 
            ModRes = (ModRes+a) % n; 
        a = (a*2)  % n; 
        b = b >> 1; 
    } 
    return ModRes; 
}


uint64_t fastExponent(uint64_t a, uint64_t b ,uint64_t n){
    uint64_t ModRes = 1;
    while(b > 0){
        if(b & 1){
            ModRes = ModularArithmetic(ModRes,a,n);
        }
        a = ModularArithmetic(a,a,n);
        b = b >> 1;
    }
    if(debug)printf(YELLOW"a^b mod n: "GREEN"%lld.\n",ModRes);
    return ModRes;

}



     
uint64_t ModulerExpo(uint64_t a, uint64_t b ,uint64_t n){
    uint64_t c = 0;
    uint64_t d = 1, temp = b;
    uint64_t b_r[100] = {0};
    uint64_t y;
     for(y=0;temp>0;y++){    
        b_r[y]=temp%2;    
        temp = temp >> 1;    
    }
    uint64_t k = y;
    // for(y = y-1; y >= 0; y--){
    //     printf("%lld",b_r[y]);
    // }

    for(int i = k; i >=0; i--){
        c = c * 2;
        d = ModularArithmetic(d,d,n);
        // d = (d*d) % n;
        if(b_r[i] == 1){
            c++; 
            // d = (d*a) % n;
             d = ModularArithmetic(d,a,n);
        }
        
    }
    return d;
}


bool witness(uint64_t a, uint64_t n){
    uint64_t t = 0;
    uint64_t x[10];
    uint64_t u = n-1;
    while(u % 2 == 0){
        u = u/2;
        t++;
    }

    x[0] = ModulerExpo(a,u, n);
    for(int i = 1; i <= t; i++){
        x[i] = ModulerExpo(x[i-1],2, n);
        if(x[i] == 1 && x[i-1] != 1 && x[i-1] != n-1){
            return true;
        }
    }
    if(x[t] != 1) return true;
    else return false;
}

bool MillerRabin(uint64_t n, uint64_t s ){
    uint64_t a;
    if (n < 2) {
        if(debug)printf(YELLOW "%llu " RESET "is " RED "Composite.\n",n);
        return false;
    }
    if (n != 2 && n % 2==0) {
        if(debug)printf(YELLOW "%llu " RESET "is " RED "Composite.\n",n);
        return false;
    }
    srand(time(0));
    for(int j = 0; j < s; j++){
        if(!Random_A){
            a = Randoms(1, n-1,1);
        }else{
            a = Random_A;
        }
         if(witness(a,n)){
            if(debug)printf(YELLOW "%llu " RESET "is " RED "Composite.\n",n);
            return false;
         }
    }
    if(debug)printf(YELLOW "%llu " RESET "is " GREEN "Prime.\n",n);
    return true;
}