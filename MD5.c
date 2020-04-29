// Theory of Algorithms Projects
// Created by Shane Moran on 03/04/2020.
// All Online Resources & References can be found in the README.MD

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

// 64-byte block of memory, accessed via different types
union block{
    uint64_t sixfour[8];
    uint32_t threetwo[16];
    uint8_t eight[64];
};

// Keep track of where we are in padding the message.
enum flag {READ, PAD0, FINISH} ;

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
int nextblock(union block *M, FILE *infile, uint64_t *nobits, enum flag *status) {

    // var's
    int i;
    size_t nobytesread;

    // Try to read 64 bytes from the file.
    nobytesread = fread(M->eight, 1, 64, infile);
    *nobits += nobytesread * 8;

    if (*status == FINISH)
        return 0;

    // We need an all-padding block without the 1 bit.
    if (*status == PAD0) {
        for (i = 0; i < 56; i++)
            M ->eight[i] = 0x00;
        M->sixfour[7] = *nobits;
        *status = FINISH;

        return 1;
    }

    if (nobytesread == 64)
        return 1;

    if (nobytesread < 56) {
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
static void nexthash(union block *M, uint32_t *Hash)
{
    // var's
    uint32_t H[4];

    Hash[0] = H[0];
    Hash[1] = H[1];
    Hash[2] = H[2];
    Hash[3] = H[3];

    // R1
    FF(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[0], S11, K[0]);
    FF(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[1], S12, K[1]);
    FF(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[2], S13, K[2]);
    FF(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[3], S14, K[3]);
    FF(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[4], S11, K[4]);
    FF(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[5], S12, K[5]);
    FF(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[6], S13, K[6]);
    FF(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[7], S14, K[7]);
    FF(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[8], S11, K[8]);
    FF(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[9], S12, K[9]);
    FF(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[10], S13, K[10]);
    FF(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[11], S14, K[11]);
    FF(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[12], S11, K[12]);
    FF(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[13], S12, K[13]);
    FF(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[14], S13, K[14]);
    FF(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[15], S14, K[15]);

    // R2
    GG(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[1], S21, K[16]);
    GG(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[6], S22, K[17]);
    GG(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[11], S23, K[18]);
    GG(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[0], S24, K[19]);
    GG(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[5], S21, K[20]);
    GG(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[10], S22, K[21]);
    GG(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[15], S23, K[22]);
    GG(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[4], S24, K[23]);
    GG(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[9], S21, K[24]);
    GG(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[14], S22, K[25]);
    GG(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[3], S23, K[26]);
    GG(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[8], S24, K[27]);
    GG(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[13], S21, K[28]);
    GG(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[2], S22, K[29]);
    GG(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[7], S23, K[30]);
    GG(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[12], S24, K[31]);

    // R3
    HH(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[5], S31, K[32]);
    HH(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[8], S32, K[33]);
    HH(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[11], S33, K[34]);
    HH(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[14], S34, K[35]);
    HH(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[1], S31, K[36]);
    HH(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[4], S32, K[37]);
    HH(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[7], S33, K[38]);
    HH(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[10], S34, K[39]);
    HH(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[13], S31, K[40]);
    HH(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[0], S32, K[41]);
    HH(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[3], S33, K[42]);
    HH(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[6], S34, K[43]);
    HH(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[9], S31, K[44]);
    HH(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[12], S32, K[45]);
    HH(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[15], S33, K[46]);
    HH(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[2], S34, K[47]);

    // R4
    II(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[0], S41, K[48]);
    II(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[7], S42, K[49]);
    II(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[14], S43, K[50]);
    II(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[5], S44, K[51]);
    II(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[12], S41, K[52]);
    II(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[3], S42, K[53]);
    II(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[10], S43, K[54]);
    II(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[1], S44, K[55]);
    II(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[8], S41, K[56]);
    II(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[15], S42, K[57]);
    II(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[6], S43, K[58]);
    II(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[13], S44, K[59]);
    II(Hash[0], Hash[1], Hash[2], Hash[3], M->threetwo[4], S41, K[60]);
    II(Hash[3], Hash[0], Hash[1], Hash[2], M->threetwo[11], S42, K[61]);
    II(Hash[2], Hash[3], Hash[0], Hash[1], M->threetwo[2], S43, K[62]);
    II(Hash[1], Hash[2], Hash[3], Hash[0], M->threetwo[9], S44, K[63]);


    Hash[0] += H[0];
    Hash[1] += H[1];
    Hash[2] += H[2];
    Hash[3] += H[3];


}


// display
void heading()
{
    printf("\n G00338607 - Shane Moran");
    printf("\n MD5 Hash Digest Algorithm");
}

void help(){
    printf("Help:\n");
    printf("-t           --test           tests MD5\n");
    printf("-h           --help           commands\n");
    printf("-r           --run           runs programs (***file required***)\n");
}
void test(){

    printf("test complete, i guess\n");

}


int main(int argc, char *argv[]) {
    // Output string & heading
    heading();

    printf("\n");


    int c;

    while (1)
    {
        static struct option long_options[] =
                {
                        {"test",    no_argument,      0,  't'},
                        {"help",     no_argument,       0, 'h'},
                        {"run",  no_argument,       0, 'r'},
                        {0, 0, 0, 0}
                };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "thr:",
                         long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
            case 0:

                if (long_options[option_index].flag != 0)
                    break;
                printf ("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;

            case 't':
                test();
                break;

            case 'h':
                help();
                break;

            case 'r':
                if (argc != 3)
                {
                    printf("Error: expected single filename as argument.\n");
                    return 1;
                }


                // We assume argv[1] is a filename to open
                FILE *infile = fopen(argv[2], "rb");
                if (!infile)
                {
                    printf("Error: couldn't open file %s.\n", argv[2]);
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

                printf("File: %s\n Hash Output: ", argv[2]);

                for (int i = 0; i < 4; i++)

                    printf("%02x%02x%02x%02x",(H[i] >> 0 ) & 0xFF, (H[i] >> 8 ) & 0xFF, (H[i] >> 16) & 0xFF, (H[i] >> 24) & 0xFF);

                printf("\n");

                fclose(infile);
                break;

            case '?':
                /* getopt_long already printed an error message. */
                break;

            default:
                abort ();
        }
    }

    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
    }

    exit (0);
}