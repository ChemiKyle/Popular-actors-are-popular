#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>              // stringstream
#include <fstream>              // ifstream

#include "splaytree.h"
#include "HashTable.h"

using namespace std;

// parse csv and use as input on both data structures
// adapted from Kyle Chesney's Lab 7 for COP 3503
void readFile(string file_name,
              HashTable& ht,
              SplayTree& st,
              int row_limit = -1) {
  ifstream file (file_name);
  string line, cell, tmp;
  vector<string> header, row;

  getline(file, line);
  stringstream s_line(line);

  // capture the head of the csv file
  // not actually used for anything in this project
  while (getline(s_line, cell, ',')) {
    header.push_back((string) cell);
  }

  unsigned int rows_processed = 1;

  // iterate over every data row
  while (getline(file, line)) {
    // allow each line to be parsed by getline
    stringstream s_line(line);
    row.clear();


    // nconst, primary_name, titles
    while (getline(s_line, cell, ',')) {
      row.push_back((string) cell);
    }

    string id = row[0];
    string name = row[1];
    string titles = row[2];

    // remove first 2 chars of ID
    // TODO: detect if first 2 chars are present before doing this
    unsigned int uid = stoi( cmd_vec[0].substr(2, cmd_vec[0].size() - 1) );

    // insert into data structures
    // TODO: record time taken to build each structure independently
    st.n = st.insertNAMEID(st.n, name, uid, titles);
    ht.insert(uid, name, titles);

    // print debugging
    if (0) {
      cout <<
        "id: " << id << endl <<
        "name: " << name << endl <<
        "titles: " << titles << endl;
    }

    rows_processed++;

    // debug, limit rows to save time during testing and use
    if (row_limit > -1 && rows_processed >= row_limit) {
      break;
    }
  }
}
