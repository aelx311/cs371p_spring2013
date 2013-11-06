// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <map>
#include "Collatz.h"

// ------------
// collatz_read
// ------------

bool collatz_read (std::istream& r, int& i, int& j) {
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}

// ------------
// collatz_eval
// ------------
int collatz_eval (int i, int j) {
    using namespace std;
    assert(i > 0);
    assert(i < 1000000);
    assert(j > 0);
    assert(j < 1000000);
    // <your code>
    int count = 0;
    if(i > j){
        i = i ^ j;
        j = i ^ j;
        i = i ^ j;
    }
    count = j - i;
    map<int, int> lengthMap;
    unsigned int maxLength = 1;
	while(count >= 0){
		unsigned int startNum = i;
		unsigned int length = 1;
		std::map<int, int>::iterator itr = lengthMap.find(i);
        while(startNum != 1){
            if(itr != lengthMap.end()){
                startNum += itr->second;
            }
            else{
                if(startNum % 2 == 0){
                    startNum = (startNum >> 1);
                    length += 1;
                }
                else{
                    startNum = (startNum + (startNum >> 1) + 1);
                    length += 2;
                }
            }
		}
        lengthMap[i] = length;
        // find maximum length
		if(length > maxLength)
			maxLength = length;
		i++;
		count--;
	}
    unsigned int v = maxLength;
    assert(v > 0);
    return v;
}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {
    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
