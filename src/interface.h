#pragma once

#include <iostream>
#include <string>
#include <algorithm>            // used solely for whitespace trimming on input
#include <random>
#include <chrono>

#include "splaytree.h"
#include "HashTable.h"

using namespace std;

int getRandomInt() {
  random_device rd;             // obtain a random number from hardware
  mt19937 gen(rd());            // seed the generator
  uniform_int_distribution<> distr(25, 63); // define the range

  return distr(gen);
}

// input parsing adapted from Kyle Chesney's project 1 submission
// separates a single line of input into a vector of strings, expected input format is: command_1 "some name" command_2
//
vector<string> parseInputLine(string raw_input) {
  vector<string> cmd_vec(3);
  // thankfully - unlike Java - C++ initializes empty strings by default
  string cmd;
  string name;
  string final_cmd;

  // remove cmd from input string
  // adapted from: https://stackoverflow.com/a/14266139/7418735
  // figured it's ok to use SO for things that have nothing to do with the algorithm
  int cmd_end = raw_input.find(" ");
  cmd = raw_input.substr(0, cmd_end);

  // remove cmd from raw input
  // edge case, single command
  if (cmd_end == -1) {
    raw_input = "";
  } else {
    raw_input = raw_input.substr(cmd_end + 1);
  }

  // capture name in quotes
  size_t quote_loc = raw_input.find("\"");
  if (quote_loc != string::npos) {
    // remove up to first quote
    raw_input = raw_input.substr(quote_loc + 1);

    // get next quote location
    quote_loc = raw_input.find("\"");

    // capture portion in quotes
    name = raw_input.substr(0, quote_loc);

    // discard name, final quote, and space
    raw_input = raw_input.substr(quote_loc + 1);
  }

  cmd_end = raw_input.find("\n");
  final_cmd = raw_input.substr(0, cmd_end);

  // trim spaces from final cmd that may be present
  // https://stackoverflow.com/a/83481/7418735
  string::iterator end_pos = remove(final_cmd.begin(), final_cmd.end(), ' ');
  final_cmd.erase(end_pos, final_cmd.end());

  // cmd_vec = { cmd, name, final_cmd}; // lol not allowed
  cmd_vec[0] = cmd;
  cmd_vec[1] = name;
  cmd_vec[2] = final_cmd;

  return cmd_vec;
}

// function expected to be called in main
// runs an infinite loop accepting input until an exit phrase is passed ("exit")
void acceptInput(
  HashTable ht,
  SplayTree st
) {
  // flush input to keep first cmd from being an empty string
  // adapted from: https://stackoverflow.com/a/257098/7418735
  cin.clear();
  cin.ignore(1,'\n');

  string cmd;
  string raw_input;
  vector<string> cmd_vec(3);

  // phrase used to end this loop
  static const string exit_cond = "exit";

  while (1) {
    getline(cin, raw_input);
    cmd_vec = parseInputLine(raw_input);

    if (cmd_vec[0].compare("exit") == 0) { break; }

    // remove first 2 chars
    // TODO: detect if first 2 chars are present before doing this
    unsigned int id = stoi( cmd_vec[0].substr(2, cmd_vec[0].size() - 1) );

    // Hash Table//////////////////////////////////////////////////////////////////
    auto start = chrono::high_resolution_clock::now();

    ht.findKey(id);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    // stdout is captured by a middleware hosting the frontend
    cout << duration.count() << endl;

    // Splay Tree /////////////////////////////////////////////////////////////
    start = chrono::high_resolution_clock::now();

    // capture root for replacement
    string found = "";
    st.n = st.searchName(st.n, id, found);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cout << duration.count() << endl;
  }

  cout << "goodbye!" << endl;
}
