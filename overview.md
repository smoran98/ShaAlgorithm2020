# ShaAlgorithm2020

| Project Details   |     |
| --- | --- |
| **Course** | BSc (Hons) in Software Development  |
| **Module** |  Theory of Algorithms |
| **College** | [Galway-Mayo Institute of Technology](http://www.gmit.ie/) Galway |
| **Student** | Shane Moran |
| **Module & Project Supervisor** | Ian McLoughlin |
| **Project Title** | MD5 hash digest algorithm |


# Introduction

## Problem statement
You must write a program in the [C programming language](http://www.open-std.org/jtc1/sc22/wg14/)that calculates
the MD5 hash digest of an input. The algorithm is specified in the Request
For Comments 1321 document supplied by the Internet Engineering Task
Force [here](https://tools.ietf.org/html/rfc1321). The only pre-requisite is that your program performs the algorithm
— you are free to decide what input the algorithm should be performed on.
I suggest you allow the user to input some free text or a filename via the
command line.

# Algorithm
## Architecture
Whether it was watching one the videos or listening along in one of our lectures, it definetly simplified things when it came to actually tackling the MD5 message-digest algorithm which is a widely used hash function producing a 128-bit hash value. Although MD5 was initially designed to be used as a cryptographic hash function, it has been found to suffer from extensive vulnerabilities. It can still be used as a checksum to verify data integrity, but only against unintentional corruption. It remains suitable for other non-cryptographic purposes, for example for determining the partition for a particular key in a partitioned database. MD5 was designed by Ronald Rivest in 1991 to replace an earlier hash function MD4, and was specified in 1992 as [RFC 1321](https://tools.ietf.org/html/rfc1321). One basic requirement of any cryptographic hash function is that it should be computationally infeasible to find two distinct messages that hash to the same value. MD5 fails this requirement catastrophically; such collisions can be found in seconds on an ordinary home computer. The weaknesses of MD5 have been exploited in the field, most infamously by the Flame malware in 2012. The CMU Software Engineering Institute considers MD5 essentially "cryptographically broken and unsuitable for further use".

### Pseudocode

The MD5 hash is calculated according to this algorithm. All values are in [little-endian](https://www.youtube.com/watch?v=seZLUbgbB7Y).


```
// Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating

var int s[64], K[64]

var int i

// s specifies the per-round shift amounts

s[ 0..15] := { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22 }

s[16..31] := { 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20 }

s[32..47] := { 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23 }

s[48..63] := { 6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 }


// Use binary integer part of the sines of integers (Radians) as constants:

for i from 0 to 63 do

    K[i] := floor(232 × abs (sin(i + 1)))
    
end for


// (Or just use the following precomputed table):

K[ 0.. 3] := { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee }

K[ 4.. 7] := { 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 }

K[ 8..11] := { 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be }

K[12..15] := { 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 }

K[16..19] := { 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa }

K[20..23] := { 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 }

K[24..27] := { 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed }

K[28..31] := { 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a }

K[32..35] := { 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c }

K[36..39] := { 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 }

K[40..43] := { 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 }

K[44..47] := { 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 }

K[48..51] := { 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 }

K[52..55] := { 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 }

K[56..59] := { 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 }

K[60..63] := { 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 }


// Initialize variables:
var int a0 := 0x67452301   // A

var int b0 := 0xefcdab89   // B

var int c0 := 0x98badcfe   // C

var int d0 := 0x10325476   // D


// Pre-processing: adding a single 1 bit

append "1" bit to message    

// Notice: the input bytes are considered as bits strings,

//  where the first bit is the most significant bit of the byte.


// Pre-processing: padding with zeros

append "0" bit until message length in bits ≡ 448 (mod 512)

append original length in bits mod 264 to message

// Process the message in successive 512-bit chunks:

for each 512-bit chunk of padded message do
    
    break chunk into sixteen 32-bit words M[j], 0 ≤ j ≤ 15
    
    // Initialize hash value for this chunk:
    
    var int A := a0
    
    var int B := b0
    
    var int C := c0
    
    var int D := d0
    
    
    // Main loop:
    
    for i from 0 to 63 do
        
        var int F, g
        
        if 0 ≤ i ≤ 15 then
            
            F := (B and C) or ((not B) and D)
            
            g := i
        
        else if 16 ≤ i ≤ 31 then
            
            F := (D and B) or ((not D) and C)
            
            g := (5×i + 1) mod 16
        
        else if 32 ≤ i ≤ 47 then
            
            F := B xor C xor D
            
            g := (3×i + 5) mod 16
        
        else if 48 ≤ i ≤ 63 then
            
            F := C xor (B or (not D))
            
            g := (7×i) mod 16
        
        // Be wary of the below definitions of a,b,c,d
        
        F := F + A + K[i] + M[g]  // M[g] must be a 32-bits block
        
        A := D
        
        D := C
        
        C := B
        
        B := B + leftrotate(F, s[i])
    
    end for
    
    
    // Add this chunk's hash to result so far:
    
    a0 := a0 + A
    
    b0 := b0 + B
    
    c0 := c0 + C
    
    d0 := d0 + D

end for


var char digest[16] := a0 append b0 append c0 append d0 // (Output is in little-endian)



// leftrotate function definition

leftrotate (x, c)
    
    return (x << c) binary or (x >> (32-c));

```

```
Instead of the formulation from the original RFC 1321 explained, the following can improve efficiency:

( 0 ≤ i ≤ 15): F := D xor (B and (C xor D))
(16 ≤ i ≤ 31): F := C xor (D and (B xor C))

```


![MD5](https://upload.wikimedia.org/wikipedia/commons/thumb/c/c8/CPT-Hashing-File-Transmission.svg/350px-CPT-Hashing-File-Transmission.svg.png)![MD5two](https://1.bp.blogspot.com/-HUmboHR6vI8/XZCFccNH9iI/AAAAAAAAC_Q/bnzNNMwAjjInclBSxE81b8Zy-C9CL0iOACLcBGAsYHQ/s1600/MD5--Hashing.png)


# Run

## How to Run 
The following project's guide on how to run is guided towards windows operating systems, but, we first need to discuss what software is needed. 
##### Software used
[CLion](https://www.jetbrains.com/clion/) is a cross-platform IDE which natively supports C and C++, libc++ and Boost. It offers instant navigation to a symbol's declaration or usages, code generation for constructors/destructors, operators and more. ***Any other C Programming language supported IDE will be fine.***
To run MD5, the following software may be required to installed. Firstly, if you want to clone this repository it is recommended that [Git](https://git-scm.com/) is installed and can be done by following the instructions in the link below or clicking on the link.

To run this program you will need to install a C compiler. I recommend using the [GCC](https://jmeubank.github.io/tdm-gcc/) compiler. Like with git, follow the installation instructions and you'll be fine.


#### Clone Repository
To clone the repository, open a terminal window  To clone the repository enter the following command:
```
git clone OR get from Version Control using CLion and input https://github.com/smoran98/ShaAlgorithm2020
```

Navigate to a directory at which you would like to clone the repository.
```
cd ShaAlgorithm2020  
```

#### Test file
Navigate to the ShaAlgorithm2020 directory via file explorer and create a new text document/file by right clicking in the directory. Name it and edit it with some content in order for it to be hashed, ***make sure it is saved and in the ShaAlgorithm2020directory*** .

##### Compiling and Running
Compile the program which was used to clone the repository and type the following command

```
gcc -o MD5 MD5.c (OR build using CLion)
```

As long you saved a test file ***in the ShaAlgorithm2020 directory***, you should be able to enter the following command:
```
./MD5 --run "file" (OR run using CLion)
```

# Test

### Commands

##### Test

![Declaring func's and printfs](https://github.com/smoran98/ShaAlgorithm2020/blob/master/Tests/Test1.PNG)

![Calling Funtion](https://github.com/smoran98/ShaAlgorithm2020/blob/master/Tests/Test2.PNG)

```
I basically just declared the functions and wrote the printfs. 

Then, I call each of the three functions declared above and break.
```



```
MD5 --test "file"
```

##### Help
```
MD5 --help "file"
```

##### Info
```
MD5 --info "file"
```




***CLion Build and Run***

![CLion run](https://i.imgur.com/K0vnlZT.gif)


# Complexity

MD5 is designed to be cryptographically irreversible. In this case, the most important property is that it is computationally unfeasible to find the reverse of a hash, but it is easy to find the hash of any data. For example, let's think about just operating on numbers (binary files could be interpreted as a very long number).

Let's say we have the number "7", and we want to take the hash of it. Perhaps the first thing we try as our hash function is "multiply by two". As we'll see, this is not a very good hash function, but we'll try it, to illustrate a point. In this case, the hash of the number will be "14". That was pretty easy to calculate. But now, if we look at how hard it is to reverse it, we find that it is also just as easy! Given any hash, we can just divide it by two to get the original number! This is not a good hash, because the whole point of a hash is that it is much harder to calculate the inverse than it is to calculate the hash .
[1](https://stackoverflow.com/questions/6603849/why-is-it-not-possible-to-reverse-a-cryptographic-hash)


An ideal cryptographic hash function has the following main properties:

- Same message always results in the same hash
- Quick to compute the hash value 
- Infeasible to generate a message that yields a given hash value
- Infeasible to find two different messages with the same hash value
- Small changes to a message change a hash value so much that the new hash value appears so much different in comparison to the old hash value, [avalanche effect](https://en.wikipedia.org/wiki/Avalanche_effect)
[2](https://en.wikipedia.org/wiki/Cryptographic_hash_function)

![Avalanche Effect](https://upload.wikimedia.org/wikipedia/commons/thumb/2/2b/Cryptographic_Hash_Function.svg/375px-Cryptographic_Hash_Function.svg.png)


You can't "reverse" password hashes. You can't "dehash" passwords. You can't "reverse" MD5, SHA256, bcrypt, SHA1, or similar hashes, salted or unsalted. You usually can't "decode" passwords, "decrypt" password hashes or "reverse" or "unscramble" password hashes at all. There's no such thing as a "dehashing tool" or a "dehashing program" or a "password reversing program". These terms run completely counter to the fundamental concept of hashing as a one-way function. These terms are inaccurate. They're basically the password-cracking equivalent of showing up on a baking forum and saying "I bought this cake. How can I turn it back into eggs and flour and milk?" 
[3](https://www.techsolvency.com/passwords/dehashing-reversing-decrypting/)

![Reverse Hash](https://miro.medium.com/max/1400/1*gHVavC-9-0BIKOacMcz5Cg.png)


# References

**References & Resources**

[1] https://cloud.google.com/

You can use Google Cloud Platform as a VM to code, not necessary

[2] https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html

Great guide for learning C, from defining constants to calling functions

[3] http://cacr.uwaterloo.ca/hac/

See Chapter 9 - Hash Functions and Data Integrity pdf

[4] https://www.bell-labs.com/usr/dmr/www/chist.html

The Development of the C Language

[5]  https://www.jetbrains.com/clion/

Link to Download CLion

[6] https://tools.ietf.org/html/rfc1321

Used for Constants for MD5Transform routine, transformations for rounds and padding

[7] https://git-scm.com/

Link to Download Git

[8] https://en.wikipedia.org/wiki/MD5

About MD5

[9] https://stackoverflow.com/questions/9642732/parsing-command-line-arguments-in-c

Command Line Arguments

[10] https://youtu.be/SjyR74lbZOc

C Programming and using getopt()

[11] https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html

Example of Parsing Long Options with getopt_long
