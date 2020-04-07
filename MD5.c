// Theory of Algorithms Projects
// Created by Shane Moran on 03/04/2020.
// All Online Resources & References can be found in the README.MD

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

// 64-byte block of memory, accessed via different types
union block{
    uint64_t sixfour[8];
    uint32_t threetwo[16];
    uint8_t eight[64];
};

// Keep track of where we are in padding the message.
enum PADFLAG {READ, PAD0, FINISH} ;

// func's
#define F(x,y,z) (((x) & (y)) | ((~x) & (z)))

#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))

#define H(x, y, z) ((x) ^ (y) ^ (z))

#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))


// sin func table
const uint32_t K[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                      0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                      0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
                      0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                      0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
                      0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                      0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                      0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                      0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
                      0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                      0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
                      0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                      0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
                      0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                      0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
                      0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};


// Section 5.1.1 - message input from infile.
int nextblock(union block *M, FILE *infile, uint64_t *nobits, enum PADFLAG *status) {

    // var's
    int i;
    size_t nobytesread;

            // We need an all-padding block without the 1 bit.
            if (*status == PAD0) {
                for (i = 0; i < 56; i++)
                    M ->eight[i] = 0x00;
                M->sixfour[7] = *nobits;
                *status = FINISH;

                return 1;
            }

            // Try to read 64 bytes from the file.
            nobytesread = fread(M->eight, 1, 64, infile);
            *nobits += (8ULL * ((uint64_t) nobytesread));

            if (nobytesread < 56) {
                // We can put all padding in this block.
                M->eight[nobytesread] = 0x80;
                for (i = nobytesread + 1; i < 56; i++)
                    M->eight[i] = 0x00;
                M->sixfour[7] = *nobits;
                *status = FINISH;
            } else if (nobytesread < 64) {
                // Otherwise we have read between 56 (incl) and 64 (excl) bytes.
                M->eight[nobytesread] = 0x80;
                for (int i = nobytesread + 1; i < 64; i++)
                    M->eight[i] = 0x00;
                *status = PAD0;
            }

    return 1;

}

// Section 6.2.2
int nexthash(union block *M, uint32_t *H)
{
    // var's
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

        for (s = 16; s < 64; s++)
        {
            W[s] = M->threetwo[t * 16 + s];
        }

        AA = A;
        BB = B;
        CC = C;
        DD = D;

        return 1;
    }
    return 0;
}


// display
void heading()
{
    printf("\n G00338607 - Shane Moran");
    printf("\n MD5 Hash Digest Algorithm");
}


int main(int argc, char *argv[]) {
    // Output string & heading
    heading();

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