Because of the recursive function thats needed in the second option of the assignment
, this program needs extra stack space to run properly.

Please run a command like "ulimit -s unlimited" or "ulimit -s 100000" on the terminal before using the makefile.
I didn't add these commands to the makefile for safety reasons, responsibility
to provide the required stack space belongs to the instructor.

By my experiments, 50mb or more stack space is enough for the second option to run properly.


