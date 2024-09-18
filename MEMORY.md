COSC302 Project 2 - Sorting Algorithms
Project Members: Isaac Abella, Colton Coughlin, John Cordwell III
Member github ids: Isaace19, jcordwel3, Tempstarwolf


=== Isaac Abella -- Memory Consumption of Sorting Algorithms ===

Random Number Generation (numgen) compilation
g++ -Wall -std=c++11 -o numgen numgen.cpp

Sorting Algorithms -- Time Measured:

/user/bin/time -v ./volsort -m [sorting algorithm] -n < 10, 100, 1000, 10k, 1mil, 10mil...
This command gives detailed run processes as well as a wall clock time of how long
it takes to run the program in (h:mm:ss)

That's an oversimplification, the -v flag gives a lot of cool information, such as
the wall time it takes for a program to run, the CPU time and System time to run the code, as 
well as the total amount of CPU power it took to run that program. 

Importantly, we can view how much memory was used by computer to actually run this program. 
Max. Resident Size is the amount of ram our laptop used to perform the program. 

Although not listed here, there was a bit of Minor reclaiming per program, this is just memory
on hardware that was freed up, but still had to be mapped to our program's address space. This is
essentially overhead bloat from programs.


This will vary from system to system because everyone has different laptops in varying states. 
For reference, I performed these tests locally on a M1 macbook pro with 8gbs of ram.

When navigating our REPO to the sorting dump, you can see a full transcript of the time flag output, 
here is the summary:

| Mode  | Size     | Max. Resident Size |
|-------|----------|--------------------|
| STL   | 10       | 3304 kbyte         |
| STL   | 100      | 3448 kbyte         |
| STL   | 1000     | 3360 kbyte         |
| STL   | 10000    | 4224 kbyte         |
| STL   | 100000   | 10480 kbyte        |
| STL   | 1000000  | 73872 kbyte        |
| STL   | 10000000 | 759144 kbyte       |
| QSORT | 10       | 3284 kbyte         |
| QSORT | 100      | 3440 kbyte         |
| QSORT | 1000     | 3504 kbyte         |
| QSORT | 10000    | 4188 kbyte         |
| QSORT | 100000   | 10984 kyte         |
| QSORT | 1000000  | 81364 kbyte        |
| QSORT | 10000000 | 784216 kbyte       |
| MERGE | 10       | 3280 kbyte         |
| MERGE | 100      | 3376 kbyte         |
| MERGE | 1000     | 3364 kbyte         |
| MERGE | 10000    | 3984 kbyte         |
| MERGE | 100000   | 9532 kbyte         |
| MERGE | 1000000  | 65940 kbyte        |
| MERGE | 10000000 | 628368 kbyte       |
| QUICK | 10       | 3296 kbyte         |
| QUICK | 100      | 3280 kbyte         |
| QUICK | 1000     | 3440 kbyte         |
| QUICK | 10000    | 4044 kbyte         |
| QUICK | 100000   | 9628 kbyte         |
| QUICK | 1000000  | 15765 kbyte        |
| QUICK | 10000000 | 628960 kbyte       |
------------------------------------------
