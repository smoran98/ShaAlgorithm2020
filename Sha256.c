// Ian McLoughlin
// Adapted from  https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
// The Secure Hash Algorithm 256-bit version.

#include <stdio.h>
#include <stdint.h>

// Section 4.2.2
const uint32_t K[] = {
  0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
  0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
  0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
  0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
  0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
  0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
  0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
  0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
  0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
  0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
  0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
  0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
  0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
  0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
  0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
  0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};



uint32_t Ch(uint32_t x, uint32_t y, uint32_t z) {
  // Section 4.1.2
  return (x & y) ^ (~x & z);
}

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z) {
  // Section 4.1.2
  return (x & y) ^ (x & z) ^ (y & z);
}

uint32_t SHR(uint32_t x, int n) {
  // Section 3.2
  return x >> n;
}

uint32_t ROTR(uint32_t x, int n) {
  // Section 3.2
  return (x >> n) | (x << (32 - n));
}

uint32_t Sig0(uint32_t x) {
  // Section 4.1.2
  return ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22);
}

uint32_t Sig1(uint32_t x) {
  // Section 4.1.2
  return ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25);
}

uint32_t sig0(uint32_t x) {
  // Section 4.1.2
  return ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3);
}

uint32_t sig1(uint32_t x) {
  // Section 4.1.2
  return ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10);
}

union block {
  uint64_t sixfour[8];
  uint32_t threetwo[16];
  uint8_t eight[64];
};

enum flag {READ, PAD0, PAD1, FINISH};

uint64_t nozerobytes(uint64_t nobits) {

  uint64_t result = 512ULL - (nobits % 512ULL);
  
  if (result < 65)
    result += 512;

  result -= 72;

  return (result / 8ULL);
}


int nextblock(union block *M, FILE *infile, uint64_t *nobits, enum flag *status) {
  
  uint8_t i;

  for (*nobits = 0, i = 0; fread(&M.eight[i], 1, 1, infile) == 1; *nobits += 8) {
    printf("%02" PRIx8, M.eight[i]);
  }
  
  printf("%02" PRIx8, 0x80); // Bits: 1000 0000

  for (uint64_t i = nozerobytes(*nobits); i > 0; i--)
    printf("%02" PRIx8, 0x00);


  printf("%016" PRIx64 "\n", *nobits);

}


void nexthash(union block *M, uint32_t *H) {


}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Error: expected single filename as argument.\n");
    return 1;
  }

  FILE *infile = fopen(argv[1], "rb");
  if (!infile) {
    printf("Error: couldn't open file %s.\n", argv[1]);
    return 1;
  }

  // Section 5.3.3
  uint32_t H[] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19  
  };
  
  // The current padded message block.
  union block M;
  uint64_t nobits = 0;
  enum flag status = READ;

  // Read through all of the padded message blocks.
  while (nextblock(&M, infile, nobits, status)) {
    // Calculate the next hash value.
    nexthash(&M, &H);
  }

  for (int i = 0; i < 8; i++)
    printf("%02" PRIX32, H[i]);
  printf("\n");
  fclose(infile);

  return 0;
}

