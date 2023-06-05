#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>   
#include <math.h>

// Generates a random number in the range of desired bit size for our 
// 2 prime numbers
long long random_nums(){ 

    long long upper_limit = (long long)pow(2,2048) - 1;  
    long long lower_limit = (long long)pow(2,2047) + 1;
    printf("%lld \n",upper_limit); 
    printf("%lld \n",lower_limit);
    return lower_limit + (rand() % (upper_limit - lower_limit + 1));
}

int main() { 

    long long my_num = random_nums();
    printf("%lld \n",my_num);
    return my_num;
}