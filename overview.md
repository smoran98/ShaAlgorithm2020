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
