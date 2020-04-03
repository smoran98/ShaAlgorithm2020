// Theory of Algorithms Projects
// Created by Shane Moran on 03/04/2020.
// All Online Resources & References can be found in the README.MD

#include <stdio.h>
#include <stdint.h>

// constants
const uint32_t K[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5};
uint32_t y[23];

// func's
uint32_t F(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) | (~x & z);
}

uint32_t G(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) | (y & ~z);
}

uint32_t H(uint32_t x, uint32_t y, uint32_t z)
{
    return (x ^ y ^ z);
}

uint32_t I(uint32_t x, uint32_t y, uint32_t z)
{
    return (y ^ (x | ~z));
}


void heading()
{
    printf("\n G00338607 - Shane Moran");
    printf("\n MD5 Hash Digest Algorithm");
}


int main() {
    // Output string & heading
    heading();
    
    printf("\n");
    printf("Hello, World!");
    printf("\n");
    printf("K[2]         = %08x\n", K[2]);

    uint32_t x = K[0];
    uint32_t y = K[1];
    uint32_t z = K[2];

    printf("x  K[0] = %08x\n", K[0]);
    printf("y  K[1] = %08x\n", K[1]);
    printf("z  K[2] = %08x\n", K[2]);

    printf("F(x,y,z) = %08x\n", F(K[0], K[1], K[2]));
    printf("G(x,y,z) = %08x\n", G(K[0], K[1], K[2]));
    printf("H(x,y,z) = %08x\n", H(K[0], K[1], K[2]));
    printf("I(x,y,z) = %08x\n", I(K[0], K[1], K[2]));

    return 0;
}
