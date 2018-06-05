# bbone
Linear_ops functions are now all working. 

Testing ARM Neon code and Vector operations.

This repo contains some practice C code I wrote (in one file) to learn C so that I could interact with the NEON. The rest of the code is header files containing the definitions or various linear algebra data structures and the definitions of various functions that can be performe don them.

The purpose of the repo is not only to save the code, but also to quickly transfer code between the Beagle Bone and my machine so that it can be compiled and tested (since it requires the ARM NEON headers and the processor itself to function).

Furthermore, I include "neon wrappers": function wrappers that allow interaction and usage between the C structs previously defined in the project and the special data types that the NEON uses to manage memory and perform operations. 

Some "tester" files will use these data types, and wrappers to test if wrapping the data dn operations into NEON operations is faster than simply using the C structs, and if so, in what cases.

ToDo:
Still have to fix some syntax errors in the headers and tester functions. 
Implement a test of efficency (time/memory usage). 
