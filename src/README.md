# Compilation

The CLI API can be compiled with the following command:

``` sh
g++ -std=c++11 main.cpp
```

This CLI app is intended to be used to shuttle queries and results between the data structures and the frontend, but the CLI app can be used independently.

Launch the program with:

```bash
./a.out [$NUMBER_OF_ROWS_TO_READ]
```

`$NUMBER_OF_ROWS_TO_READ` is an optional parameter, it is recommended as by default the program reads the entirety of `../data/actors_with_titles.csv` which is over 11 million rows, this can take over 5 minutes! `$NUMBER_OF_ROWS_TO_READ` = 100,000 should take around 2 seconds.

Once the program is done reading the data and populating the data structures, the time taken (in microseconds) to populate will be printed to stdout.  
After the data structures are built, you can enter the ID of any actor you wish to search for (ID < `$NUMBER_OF_ROWS_TO_READ`) and the time to locate this ID (in nanoseconds) will be printed to stdout in the order Hash Table, Splay Tree.

Here is an example CLI session with annotations:

```bash
$ ./a.out 100000 # starting the program, limiting to 100,000 rows read
3290818          # time taken (us) to populate both structures
1                # user input, searching for ID 1
866              # time taken (ns) to find ID 1 in the Hash Table
9119696          # time taken (ns) to find ID 1 in the Splay Tree
1                # user input, searching for ID 1 again
500              # time taken (ns) to find ID 1 in the Hash Table
385              # time taken (ns) to find ID 1 in the Splay Tree
100000           # user input, searching for ID 100,000
1148             # time taken (ns) to find ID 100,000 in the Hash Table
545377           # time taken (ns) to find ID 100,000 in the Splay Tree
exit             # user input, exiting the program, terminating the loop accepting user input
goodbye!         # exit message
```

