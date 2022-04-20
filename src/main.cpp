#include "utils.h"
#include "interface.h"
#include <iostream>
#include <chrono>               // timing

#include "splaytree.h"
#include "HashTable.h"

using namespace std;

int main(int argc, char *argv[]) {

    auto start = chrono::high_resolution_clock::now();

    int row_limit = -1;
    if (argc > 1) {
        row_limit = stoi(argv[1]);
    }

    SplayTree st;
    HashTable ht;

    readFile("../data/actors_with_titles.csv",
             ht,
             st,
             row_limit);
    // Get ending timepoint
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    // report time taken to proces csv file and build structures
    cout << duration.count() << endl;

    // Time taken by function: 236,089,942 microseconds
    // That's about 4 minutes

    // smaller file with only essential columns:
    //
    // personal laptop:
    // CPU: 2.9 GHz 4 core, i5-5300U
    // RAM: 8 GB, 1600 MT/s DDR3
    // Time taken by function: 201,785,903 microseconds (4 min)
    //
    // tower:
    // CPU: 3.4 GHz 6 core, Ryzen 5 2600
    // RAM: 16 GB, 3200 MT/s DDR4; configured for 1600 MT/s; 2 identical sticks in DIMM_A2 & DIMM_B2: https://www.crucial.com/memory/ddr4/bl8g32c16u4b
    // Time taken by function: 11,406,715 microseconds
    // 11.5 seconds... lol
    //
    // work laptop:
    // CPU: 2GHz 4 core i5
    // RAM: 32 GB 3733 MHz, DDR4
    // work laptop over NFS share:
    // Time taken by function: 108,544,996 microseconds
    // work laptop with local files:
    // Time taken by function: 90,085,543 microseconds
    // Time taken by function: 82,263,808 microseconds
    //
    // Limiting factor appears to be CPU clock speed

    acceptInput(ht, st);


    return 0;
}
