#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate the modular multiplicative inverse of a number (d) modulo phi(n)
int modInverse(int d, int phi)
{
    int x, y;
    int gcd_result = extendedGCD(d, phi, &x, &y);
    if (gcd_result != 1)
    {
        printf("Error: Inverse does not exist.\n");
        exit(1);
    }
    return (x % phi + phi) % phi;
}

// Extended Euclidean algorithm to calculate the modular multiplicative inverse
int extendedGCD(int a, int b, int *x, int *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }

    int x1, y1;
    int gcd_result = extendedGCD(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return gcd_result;
}

int modularExponentiationModified(int base, int exponent, int modulus)
{
    int i;
    int result;
    int fake_result;
    int temp;
    int fake_exp;
    int exponent_val = exponent;
    int base_const = base;
    for (i = 1; i < modulus; i++)
    {   
        if (i == base_const){
            result = 1;
            base = base % modulus;

            while (exponent > 0)
            {
                if (exponent & 1)
                    result = (result * base) % modulus;
                exponent = exponent >> 1;
                base = (base * base) % modulus;
            }
        } else {
            fake_result = 1;
            fake_exp = exponent_val;
            temp = i;
            temp = temp % modulus;

            while (fake_exp > 0)
            {
                if (fake_exp & 1)
                    fake_result = (fake_result * temp) % modulus;
                fake_exp = fake_exp >> 1;
                temp = (temp * temp) % modulus;
            }
        }
    }

    return result;
}

//Function to perform modular exponentiation
int modularExponentiation(int base, int exponent, int modulus)
{
    if (modulus == 1)
        return 0;

    int result = 1;
    base = base % modulus;

    while (exponent > 0)
    {
        if (exponent & 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }

    return result;
}

// Function to encrypt an integer using the RSA algorithm
int rsaEncrypt(int plaintext, int e, int n)
{
    return modularExponentiationModified(plaintext, e, n);
}

// Function to decrypt a ciphertext using the RSA algorithm
int rsaDecrypt(int ciphertext, int d, int n)
{
    return modularExponentiationModified(ciphertext, d, n);
}

int main()
{
    int p, q, n, phi, e, d;
    int plaintext, ciphertext, decrypted;

    //srand(time(NULL));

    // Step 1: Generate two distinct prime numbers (p and q)
    p = 53; // Replace with your desired prime number
    q = 59; // Replace with your desired prime number
    printf("Generated prime numbers: p=%d, q=%d\n", p, q);

    // Step 2: Calculate n and phi(n)
    n = p * q;
    phi = (p - 1) * (q - 1);

    // Step 3: Choose a value for e such that 1 < e < phi(n) and gcd(e, phi(n)) = 1
    e = 3; // Replace with your desired value for e
    if (gcd(e, phi) != 1)
    {
        printf("Error: gcd(e, phi(n)) != 1\n");
        return 1;
    }

    // Step 4: Calculate d, the modular multiplicative inverse of e modulo phi(n)
    d = modInverse(e, phi);

    printf("Public key: (n=%d, e=%d)\n", n, e);
    printf("Private key: (n=%d, d=%d)\n", n, d);

    // Step 5: Encrypt the plaintext
    printf("Enter a number to encrypt: ");
    scanf("%d", &plaintext);

    clock_t start_time, end_time;
    double execution_time;

    start_time = clock();
    int i;
    for (i = 0; i < 10000; i++)
    {
        ciphertext = rsaEncrypt(plaintext, e, n);
    }
    end_time = clock();

    execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Encrypted value: %d\n", ciphertext);
    printf("Encryption Time: %f seconds\n", execution_time);
    printf("Start Time: %ld, End Time: %ld\n", start_time, end_time);

    // Step 6: Decrypt the ciphertext
    decrypted = rsaDecrypt(ciphertext, d, n);
    printf("Decrypted value: %d\n", decrypted);

    return 0;
}