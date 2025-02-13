# Appendix

Here you may find some helpful code examples that (hopefully) provide some insight for
how to tackle parts of the assignment that might be more unfamiliar. Note that the 
examples may not behave the same on all systems, and are largely intended for consumption 
on Linux. Additionally, the C LSP may highlight some includes as erroneous, however still 
compile correctly. 

This may be fixed by editing your code editor's settings, directing it 
to where it may find these non-standard libraries. It should not be necessary, as the compiler
ought to handle these inclusions with slightly more finesse.


## Appendix a:

 TL;DR: *A child process example.*

 In this example, fork & execve are used to create a child process that runs the "ls" 
 command with one argument given to the "ls" command (i.e., "-1" which lists all of the files 
 in a single column).


## Appendix b:

 TL;DR: *A piping example.*

 Like the code in Appendix A, this creates a child running -- in effect -- the * command "ls -1". This time, however, the output from the command is not
 output to the console but rather is redirected to a file named
 "output.txt". That is, the result of this program would be the same as if
 we had run "ls -1 > output.txt" in bash.
 
 Note the three arguments used for open().
  
 Also note the use of dup2(). This system call is perhaps easier to use
 than dup(). For example, "dup2(fd, 1)" means "force file descriptor 
 corresponding to stream 1 -- stdout -- to now be connected to the file
 to which "fd" refers". Remember -- the output is now stored in a file
 named "output.txt", which means you will *not* see the directory listing
 appearing on the console when the program is running.
  
 Finally note that the end of the program the parent waits for the
 child by explicitly referring to the child's pid (i.e., waitpid()
 instead of the loop involving wait().)


## Appendix c:

 TL;DR: *A strtok* (string parsing) *exmaple.*

 This shows how input from the user can be broken down into individual
 words / tokens.
 
 To understand this code, you must be *completely* convinced that a
 "char *" variables does *not* store a string. Rather, it stores 
 an address to memory location storing a character. If the value stored
 at that memory location changes, but the "char *" value doesn't, then
 it is the new contents at the memory location which appear, not the old.
 
 Important: strtok modifies the char array which is being tokenized.
 If you need to keep the original string, then make a copy of it before
 running strtok.


## Appendix d:

 TL;DR: *A `sys/time.h` library example*. 

 This code shows how to use time functions within a C program by demonstrating
 time formatting as well as some common functions.

---
### Acknowledgements

These apendices were created by M. Zastre in the Summer 2022 offering of CSC 360. Some examples may
have been modified for clarity or brevity at the discretion of the Spring 2025 teaching team. 