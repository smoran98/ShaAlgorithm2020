// Theory of Algorithms Projects
// Created by Shane Moran on 03/04/2020.
// All Online Resources & References can be found in the README.MD

#pragma region IMPORTS
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#pragma endregion

#pragma region PREPROCESSING SETUP
// 64-byte block of memory, accessed via different types
typedef union {
    uint64_t sixfour[8];
    uint32_t threetwo[16];
    uint8_t eight[64];
} BLOCK;
#pragma endregion

#pragma region PARSE STATUS
// Keep track of where we are in padding the message.
typedef enum {READ, PAD0, FINISH} PADFLAG;

// constants
const uint32_t K[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5};

// func's
//uint32_t F(uint32_t x, uint32_t y, uint32_t z)
//{
//    return (x & y) | (~x & z);
//}
#define F(x,y,z) (((x) & (y)) | ((~x) & (z)))

//uint32_t G(uint32_t x, uint32_t y, uint32_t z)
//{
//    return (x & y) | (y & ~z);
//}
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))

//uint32_t H(uint32_t x, uint32_t y, uint32_t z)
//{
//    return (x ^ y ^ z);
//}
#define H(x, y, z) ((x) ^ (y) ^ (z))

//uint32_t I(uint32_t x, uint32_t y, uint32_t z)
//{
//    return (y ^ (x | ~z));
//}
#define I(x, y, z) ((y) ^ ((x) | (~z)))


#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

// basic MD5 func's'
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

// transformations for rounds 1-4
#define FF(a, b, c, d, x, s, ac) { \
 (a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

#define GG(a, b, c, d, x, s, ac) { \
 (a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

#define HH(a, b, c, d, x, s, ac) { \
 (a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

#define II(a, b, c, d, x, s, ac) { \
 (a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

#pragma endregion

uint64_t no_zero_bytes(uint64_t nobytes)
{
    uint64_t no = 512 - (nobytes % 512ULL);

    if (no < 65)
        no += 512;

    no -= 72;

    return (no / 8ULL);
}


// Section 5.1.1 - message input from infile.
int nextblock(BLOCK *M, FILE *infile, uint64_t *nobits, enum PADFLAG *status) {

    int i;
    size_t nobytesread;

    switch(*status){
        case FINISH:
            return 0;
        case PAD0:
            // We need an all-padding block without the 1 bit.
            for (int i = 0; i < 56; i++)
                M->eight[i] = 0x00;
            M->sixfour[7] = htobe64(*nobits);
            *status = FINISH;
            break;
        default:
            // Try to read 64 bytes from the file.
            nobytesread = fread(M->eight, 1, 64, infile);
            *nobits += (8ULL * ((uint64_t) nobytesread));

            if (nobytesread < 56) {
                // We can put all padding in this block.
                M->eight[nobytesread] = 0x80;
                for (i = nobytesread + 1; i < 56; i++)
                    M->eight[i] = 0x00;
                M->sixfour[7] = htobe64(*nobits);
                *status = FINISH;
            } else if (nobytesread < 64) {
                // Otherwise we have read between 56 (incl) and 64 (excl) bytes.
                M->eight[nobytesread] = 0x80;
                for (int i = nobytesread + 1; i < 64; i++)
                    M->eight[i] = 0x00;
                *status = PAD0;
            }
    }

    // Convert to host endianess, word-size-wise.
    for (i = 0; i < 16; i++)
        M->threetwo[i] = be32toh(M->threetwo[i]);

    return 1;

}

// Section 6.2.2
int nexthash(union block *M, uint32_t *H)
{
    uint32_t W[64];
    uint32_t A, AA, B, BB, C, CC, D, DD;
    A = K[0];
    B = K[1];
    C = K[2];
    D = K[3];
    int t;
    int s;

    for (t = 0; t < 16; t++)
    {

    for (s = 16; s < 64; t++)
    {
        W[s] = M->threetwo[t * 16 + s];
    }

        AA = A;
        BB = B;
        CC = C;
        DD = D;
    }
}



void heading()
{
    printf("\n G00338607 - Shane Moran");
    printf("\n MD5 Hash Digest Algorithm");
}


int main(int argc, char *argv[]) {
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