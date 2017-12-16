# tiger-compiler
built on VS 2015 from source tiger code to executable program
the essence of this program is translate the tiger code to assembly language based on x86. 
in the origin code we assume that program read the file "8queens.tig" then generate the out.c.
out.c including the assemly code can be compiled and linked by any C compiler to get a executable program.

in other words, out.c provide an running environment for assembly code just like a virtual machine. 
in this way, we can add multiple function for tiger based on the powerful library of C and generate PE file in a easy way.
