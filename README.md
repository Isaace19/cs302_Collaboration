COSC302 Project 2 - Sorting Algorithms
Project Members: Isaac Abella, Colton Coughlin, John Cordwell III
Member github ids: Isaace19, jcordwel3, Tempstarwolf

<https://github.com/Isaace19/cs302_Collaboration>

Project 2 Compile command - Same as Makefile:
CXXFLAGS= -g -Wall -std=gnu++11
PROGRAMS= volsort
SOURCES= main.cpp stl.cpp qsort.cpp quick.cpp merge.cpp list.cpp

Random Number Generation (numgen) compilation
g++ -Wall -std=c++11 -o numgen numgen.cpp

Sorting Algorithms -- Time Measured:

/user/bin/time -v ./volsort -m [sorting algorithm] -n < 10, 100, 1000, 10k, 1mil, 10mil...
This command gives detailed run processes as well as a wall clock time of how long
it takes to run the program in (h:mm:ss)

=== SORTING TIME TABLE ===

| Mode  | Size     | Elapsed Time H:MM:ss|
|-------|----------|---------------------|
| STL   | 10       | 0:00.00    seconds  |
| STL   | 100      | 0:00.00    seconds  |
| STL   | 1000     | 0:00.00    seconds  |
| STL   | 10000    | 0:00.01    seconds  |
| STL   | 100000   | 0:00.13    seconds  |
| STL   | 1000000  | 0:01.87    seconds  |
| STL   | 10000000 | 0:24.50    minutes  |
| QSORT | 10       | 0:00.00    seconds  |
| QSORT | 100      | 0:00.00    seconds  |
| QSORT | 1000     | 0:00.00    seconds  |
| QSORT | 10000    | 0:00.01    seconds  |
| QSORT | 100000   | 0:00.11    seconds  |
| QSORT | 1000000  | 0:01.83    minutes  |
| QSORT | 10000000 | 0:21.66    minutes  |
| MERGE | 10       | 0:00.00    seconds  |
| MERGE | 100      | 0:00.00    seconds  |
| MERGE | 1000     | 0:00.00    seconds  |
| MERGE | 10000    | 0:00.01    seconds  |
| MERGE | 100000   | 0:00.12    seconds  |
| MERGE | 1000000  | 0:02.02    minutes  |
| MERGE | 10000000 | 0:26.07    minutes  |
| QUICK | 10       | 0:00.00    seconds  |
| QUICK | 100      | 0:00.00    seconds  |
| QUICK | 1000     | 0:00.00    seconds  |
| QUICK | 10000    | 0.00:01    seconds  |
| QUICK | 100000   | 0:00:17    seconds  |
| QUICK | 1000000  | 0:08.29    minutes  |
| QUICK | 10000000 | 0:34.54    minutes  |

------------------------------------------

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

=== MEMORY CONSUMPTION TABLE ===

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

Questions:

1) Discuss the relative performance of each sorting method and try to explain the differences

   - STL:
   - Qsort:
   - Merge:
   - Quick:
  
All of these sorting algorithms can handle 10 - 10k elements with about the same expected time of 0:00.01
seconds to compile. The main difference is when the sorting algorithms take on 1 million and 10 million
sorting objects.

We can see that the std::sort and std::qsort both handle larger amounts of data at around the same time of
~23 minutes. And we can see that our more sophistocated implementations of merge sort and quicksort take longer
at about ~26 minutes for merge and ~34 minutes for quicksort.

Merge.cpp is about expected because it's worst case scenario is the same as it's average case at around
O(nlogn) sorts, meaning that in it's worst case it will perform the max amount of comparisons.

The reason that quick.cpp in particular takes the longest to sort through all the data is because it's sorting
at it's worst case scenario of O(N^2) time. This is because our pivot choice was bad as we chose the first
element to be our pivot. This means for 10 million objects, there is just an empty section of the sorting
algorithm as we got through data.

2) What do these results reveal about the relationship between theoretical complexity discussed in class
and actual performance?

We can see that our actual performance for quick and merge sort more accurately showcase the worst-case scenario instead of the best case/average case scenarios. This is because the implementations that we chose were simple, but not the best implementations. This can be seen by our merge sort splitting algorithm and divide and conquer, and our choice of first element pivot instead of a median-of-three pivot.

3) In your opinion, which sorting mode is the best? Justify your conclusion by examining the trade-offs for the chosen mode.

As a group, we've come to the conclusion that merge sort would be the best overall algorithm because of the relatively easily implementation compared to performance vs. STL implementations. It's worst case scenario is the same as std::sort's O(nlogn), and is better than std::qsort's O(N^2) worst-case scenario

Group Member Contributions:

Colton Coughlin: Assisted on all sorting implementations. Focused on Quick and Merge Sorts as well as initial
linked list implementations at the start of the project.

Isaac Abella: Managed Github commits, std::sort and std::qsort implementations, as well as fixing memory leaks
and conducting the testing of the sorting algorithms given varying input sizes.

John Cordwell III: Worked on Merge and Quicksorts and segmentation faults with both versions of sorting.
