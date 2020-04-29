# ShaAlgorithm2020

| Project Details   |     |
| --- | --- |
| **Course** | BSc (Hons) in Software Development  |
| **Module** |  Theory of Algorithms |
| **College** | [Galway-Mayo Institute of Technology](http://www.gmit.ie/) Galway |
| **Student** | Shane Moran |
| **Module & Project Supervisor** | Ian McLoughlin |
| **Project Title** | MD5 hash digest algorithm |


## Problem statement
You must write a program in the [C programming language](http://www.open-std.org/jtc1/sc22/wg14/)that calculates
the MD5 hash digest of an input. The algorithm is specified in the Request
For Comments 1321 document supplied by the Internet Engineering Task
Force [here](https://tools.ietf.org/html/rfc1321). The only pre-requisite is that your program performs the algorithm
— you are free to decide what input the algorithm should be performed on.
I suggest you allow the user to input some free text or a filename via the
command line.

## Architecture

The MD5 message-digest algorithm is a widely used hash function producing a 128-bit hash value. Although MD5 was initially designed to be used as a cryptographic hash function, it has been found to suffer from extensive vulnerabilities. It can still be used as a checksum to verify data integrity, but only against unintentional corruption. It remains suitable for other non-cryptographic purposes, for example for determining the partition for a particular key in a partitioned database. MD5 was designed by Ronald Rivest in 1991 to replace an earlier hash function MD4, and was specified in 1992 as [RFC 1321](https://tools.ietf.org/html/rfc1321). One basic requirement of any cryptographic hash function is that it should be computationally infeasible to find two distinct messages that hash to the same value. MD5 fails this requirement catastrophically; such collisions can be found in seconds on an ordinary home computer. The weaknesses of MD5 have been exploited in the field, most infamously by the Flame malware in 2012. The CMU Software Engineering Institute considers MD5 essentially "cryptographically broken and unsuitable for further use".

![MD5](https://upload.wikimedia.org/wikipedia/commons/thumb/c/c8/CPT-Hashing-File-Transmission.svg/350px-CPT-Hashing-File-Transmission.svg.png)![MD5two](https://1.bp.blogspot.com/-HUmboHR6vI8/XZCFccNH9iI/AAAAAAAAC_Q/bnzNNMwAjjInclBSxE81b8Zy-C9CL0iOACLcBGAsYHQ/s1600/MD5--Hashing.png)


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


### Commands

##### Test
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





**References & Resources**

[1] https://cloud.google.com/

[2] https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html

[3] http://cacr.uwaterloo.ca/hac/

[4] https://www.bell-labs.com/usr/dmr/www/chist.html

[5] http://9p.io/cm/cs/cbook/index.html

[6]  https://www.jetbrains.com/clion/

[7] https://tools.ietf.org/html/rfc1321

[8] http://www.open-std.org/jtc1/sc22/wg14/

[9] https://git-scm.com/

[10] https://www.gmit.ie/general/quality-assurance-framework

[11] https://en.wikipedia.org/wiki/MD5

[12] https://stackoverflow.com/questions/9642732/parsing-command-line-arguments-in-c

[13] https://stackoverflow.com/questions/9642732/parsing-command-line-arguments-in-c

[14] https://youtu.be/SjyR74lbZOc

[15] https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
