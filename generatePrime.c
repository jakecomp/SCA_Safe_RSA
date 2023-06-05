#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>   
#include <math.h>  
#include <time.h>

#define NUM_BITS 63

// Generates a random number in the range of desired bit size for our 
// 2 prime numbers
long long random_nums(){ 

    long long upper_limit = (long long)pow(2,NUM_BITS) - 1;  
    long long lower_limit = (long long)pow(2,NUM_BITS - 1) + 1;
    srand(time(NULL)); 

    printf("Upper Limit is: %lld \n", upper_limit); 
    printf("Lower limit is: %lld \n", lower_limit);  
    printf("Difference: %lld \n",upper_limit - lower_limit);
    printf("#################################### \n");
    return lower_limit + (rand() % (upper_limit - lower_limit + 1));
}

int main() { 

    long long first_rand = random_nums(); 
    long long second_rand = random_nums(); 
    
    while(first_rand == second_rand){ 
        second_rand = random_nums();
    } 

    printf("First random number is: %lld \n", first_rand); 
    printf("Second random number is: %lld \n", second_rand);
    return 1;
}