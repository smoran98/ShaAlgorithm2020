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

/* Constants for MD5Transform routine.*/
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

// func's
#define F(x,y,z) (((x) & (y)) | ((~x) & (z)))

#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))

#define H(x, y, z) ((x) ^ (y) ^ (z))

#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

// transformations
// rounds 1-4
#define FF(a, b, c, d, x, s, ac) {\
 (a) += F ((b), (c), (d)) + (x) + (UINT4)(ac);\
 (a) = ROTATE_LEFT ((a), (s));\
 (a) += (b);\
  }
#define GG(a, b, c, d, x, s, ac) {\
 (a) += G ((b), (c), (d)) + (x) + (UINT4)(ac);\
 (a) = ROTATE_LEFT ((a), (s));\
 (a) += (b);\
  }
#define HH(a, b, c, d, x, s, ac) {\
 (a) += H ((b), (c), (d)) + (x) + (UINT4)(ac);\
 (a) = ROTATE_LEFT ((a), (s));\
 (a) += (b);\
  }
#define II(a, b, c, d, x, s, ac) {\
 (a) += I ((b), (c), (d)) + (x) + (UINT4)(ac);\
 (a) = ROTATE_LEFT ((a), (s));\
 (a) += (b);\
  }


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

typedef unsigned long int UINT4;

// padding
static unsigned char PADDING[64] = {
        0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


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
    //*nobits += (8ULL * ((uint64_t) nobytesread));
    if (nobytesread == 56) {
        // We can put all padding in this block.
        M->eight[nobytesread] = 0x80;
        for (i = nobytesread + 1; i < 56; i++)
            M->eight[i] = 0;
        M->sixfour[7] = *nobits;
        *status = FINISH;

        return 1;

    }
    // Otherwise we have read between 56 (incl) and 64 (excl) bytes.
    M->eight[nobytesread] = 0x80;
    for (int i = nobytesread + 1; i < 64; i++)
        M->eight[i] = 0x00;
    *status = PAD0;

    return 1;
}

// Section 6.2.2
int nexthash(union block *M, uint32_t *H)
{
    // var's
    uint32_t a, b, c, d;

    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];

    // R1
    FF(a, b, c, d, M->threetwo[0], S11,  0xd76aa478);
    FF(d, a, b, c, M->threetwo[1], S12,  0xe8c7b756);
    FF(c, d, a, b, M->threetwo[2], S13,  0x242070db);
    FF(b, c, d, a, M->threetwo[3], S14,  0xc1bdceee);
    FF(a, b, c, d, M->threetwo[4], S11,  0xf57c0faf);
    FF(d, a, b, c, M->threetwo[5], S12,  0x4787c62a);
    FF(c, d, a, b, M->threetwo[6], S13,  0xa8304613);
    FF(b, c, d, a, M->threetwo[7], S14,  0xfd469501);
    FF(a, b, c, d, M->threetwo[8], S11,  0x698098d8);
    FF(d, a, b, c, M->threetwo[9], S12,  0x8b44f7af);
    FF(c, d, a, b, M->threetwo[10], S13, 0xffff5bb1);
    FF(b, c, d, a, M->threetwo[11], S14, 0x895cd7be);
    FF(a, b, c, d, M->threetwo[12], S11, 0x6b901122);
    FF(d, a, b, c, M->threetwo[13], S12, 0xfd987193);
    FF(c, d, a, b, M->threetwo[14], S13, 0xa679438e);
    FF(b, c, d, a, M->threetwo[15], S14, 0x49b40821);

    // R2
    GG(a, b, c, d, M->threetwo[1], S21,  0xf61e2562);
    GG(d, a, b, c, M->threetwo[6], S22,  0xc040b340);
    GG(c, d, a, b, M->threetwo[11], S23, 0x265e5a51);
    GG(b, c, d, a, M->threetwo[0], S24,  0xe9b6c7aa);
    GG(a, b, c, d, M->threetwo[5], S21,  0xd62f105d);
    GG(d, a, b, c, M->threetwo[10], S22, 0x2441453);
    GG(c, d, a, b, M->threetwo[15], S23, 0xd8a1e681);
    GG(b, c, d, a, M->threetwo[4], S24,  0xe7d3fbc8);
    GG(a, b, c, d, M->threetwo[9], S21,  0x21e1cde6);
    GG(d, a, b, c, M->threetwo[14], S22, 0xc33707d6);
    GG(c, d, a, b, M->threetwo[3], S23,  0xf4d50d87);
    GG(b, c, d, a, M->threetwo[8], S24,  0x455a14ed);
    GG(a, b, c, d, M->threetwo[13], S21, 0xa9e3e905);
    GG(d, a, b, c, M->threetwo[2], S22,  0xfcefa3f8);
    GG(c, d, a, b, M->threetwo[7], S23,  0x676f02d9);
    GG(b, c, d, a, M->threetwo[12], S24, 0x8d2a4c8a);

    // R3
    HH(a, b, c, d, M->threetwo[5], S31,  0xfffa3942);
    HH(d, a, b, c, M->threetwo[8], S32,  0x8771f681);
    HH(c, d, a, b, M->threetwo[11], S33, 0x6d9d6122);
    HH(b, c, d, a, M->threetwo[14], S34, 0xfde5380c);
    HH(a, b, c, d, M->threetwo[1], S31,  0xa4beea44);
    HH(d, a, b, c, M->threetwo[4], S32,  0x4bdecfa9);
    HH(c, d, a, b, M->threetwo[7], S33,  0xf6bb4b60);
    HH(b, c, d, a, M->threetwo[10], S34, 0xbebfbc70);
    HH(a, b, c, d, M->threetwo[13], S31, 0x289b7ec6);
    HH(d, a, b, c, M->threetwo[0], S32,  0xeaa127fa);
    HH(c, d, a, b, M->threetwo[3], S33,  0xd4ef3085);
    HH(b, c, d, a, M->threetwo[6], S34,  0x4881d05);
    HH(a, b, c, d, M->threetwo[9], S31,  0xd9d4d039);
    HH(d, a, b, c, M->threetwo[12], S32, 0xe6db99e5);
    HH(c, d, a, b, M->threetwo[15], S33, 0x1fa27cf8);
    HH(b, c, d, a, M->threetwo[2], S34,  0xc4ac5665);

    // R4
    II(a, b, c, d, M->threetwo[0], S41, 0xf4292244);
    II(d, a, b, c, M->threetwo[7], S42, 0x432aff97);
    II(c, d, a, b, M->threetwo[14], S43, 0xab9423a7);
    II(b, c, d, a, M->threetwo[5], S44, 0xfc93a039);
    II(a, b, c, d, M->threetwo[12], S41, 0x655b59c3);
    II(d, a, b, c, M->threetwo[3], S42, 0x8f0ccc92);
    II(c, d, a, b, M->threetwo[10], S43, 0xffeff47d);
    II(b, c, d, a, M->threetwo[1], S44, 0x85845dd1);
    II(a, b, c, d, M->threetwo[8], S41, 0x6fa87e4f);
    II(d, a, b, c, M->threetwo[15], S42, 0xfe2ce6e0);
    II(c, d, a, b, M->threetwo[6], S43, 0xa3014314);
    II(b, c, d, a, M->threetwo[13], S44, 0x4e0811a1);
    II(a, b, c, d, M->threetwo[4], S41, 0xf7537e82);
    II(d, a, b, c, M->threetwo[11], S42, 0xbd3af235);
    II(c, d, a, b, M->threetwo[2], S43, 0x2ad7d2bb);
    II(b, c, d, a, M->threetwo[9], S44, 0xeb86d391);

    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
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

    printf("\n");

    if (argc != 2)
    {
        printf("Error: expected single filename as argument.\n");
        return 1;
    }
    FILE *infile = fopen(argv[1], "rb");
    if (!infile)
    {
        printf("Error: couldn't open file %s.\n", argv[1]);
        return 1;
    }
    uint32_t H[] = {
            0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476
    };

    union block M;
    uint64_t nobits = 0;
    enum flag status = READ;
    // Read through all of the padded message blocks.
    while (nextblock(&M, infile, &nobits, &status)){
        // gets nexthash value
        nexthash(&M, H);
    }

    printf("\n Hash value of the file with MD5 algorithm\n");

    // print hash
    for (int i = 0; i < 4; i++)

        printf("%02" PRIx32 "", H[i]);

    printf("\n");

    fclose(infile);

    return 0;
}