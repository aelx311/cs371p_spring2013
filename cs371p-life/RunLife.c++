// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2013
// Glenn P. Downing
// -------------------------

/*
 To run the program:
 % make RunLife
 % make run
 
 To configure Doxygen:
 doxygen -g
 That creates the file Doxyfile.
 Make the following edits:
 EXTRACT_ALL            = YES
 EXTRACT_PRIVATE        = YES
 EXTRACT_STATIC         = YES
 GENERATE_LATEX         = NO
 
 To document the program:
 doxygen Doxyfile
 */

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <fstream>
#include "Life.h"
#include "ConwayCell.h"
#include "FredkinCell.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    
    // ------------------
    // Conway Cell 109x69
    // ------------------
    
    try {
        cout << "*** Life<ConwayCell> 109x69 ***" << endl;
        ifstream readFile("RunLifeConway.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<ConwayCell> game(rows, cols, ConwayCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        round_to_print.push_back(6);
        round_to_print.push_back(7);
        round_to_print.push_back(8);
        round_to_print.push_back(9);
        round_to_print.push_back(283);
        round_to_print.push_back(2500);
        while(!readFile.eof() && counter < rows*cols) {
        	readFile >> in;
            if(in == '*') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(2500, "CONWAYCELL", round_to_print);
        readFile.close();
        
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Conway Cell 5x5
    // ------------------
    try {
        cout << "*** Life<ConwayCell> 5x5 ***" << endl;
        ifstream readFile("RunLifeConway5x5.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<ConwayCell> game(rows, cols,ConwayCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        round_to_print.push_back(6);
        round_to_print.push_back(7);
        round_to_print.push_back(8);
        round_to_print.push_back(9);
        round_to_print.push_back(10);
        while(!readFile.eof() && counter < rows*cols) {
        	readFile >> in;
            if(in == '*') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(10, "CONWAYCELL", round_to_print);
        readFile.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Conway Cell 10x10
    // ------------------
    try {
        cout << "*** Life<ConwayCell> 10x10 ***" << endl;
        ifstream readFile("RunLifeConway10x10.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<ConwayCell> game(rows, cols, ConwayCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        round_to_print.push_back(6);
        round_to_print.push_back(7);
        round_to_print.push_back(8);
        round_to_print.push_back(9);
        round_to_print.push_back(10);
        while(!readFile.eof() && counter < rows*cols) {
        	readFile >> in;
            if(in == '*') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(10, "CONWAYCELL", round_to_print);
        readFile.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Conway Cell 20x20
    // ------------------
    try {
        cout << "*** Life<ConwayCell> 20x20 ***" << endl;
        ifstream readFile("RunLifeConway20x20.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<ConwayCell> game(rows, cols, ConwayCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        round_to_print.push_back(6);
        round_to_print.push_back(7);
        round_to_print.push_back(8);
        round_to_print.push_back(9);
        round_to_print.push_back(10);
        while(!readFile.eof() && counter < rows*cols) {
        	readFile >> in;
            if(in == '*') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(20, "CONWAYCELL", round_to_print);
        readFile.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Conway Cell 50x50
    // ------------------
    try {
        cout << "*** Life<ConwayCell> 50x50 ***" << endl;
        ifstream readFile("RunLifeConway50x50.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<ConwayCell> game(rows, cols, ConwayCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        round_to_print.push_back(6);
        round_to_print.push_back(7);
        round_to_print.push_back(8);
        round_to_print.push_back(9);
        while(!readFile.eof() && counter < rows*cols) {
        	readFile >> in;
            if(in == '*') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(50, "CONWAYCELL", round_to_print);
        readFile.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Conway Cell 1x20
    // ------------------
    try {
        cout << "*** Life<ConwayCell> 1x20 ***" << endl;
        ifstream readFile("RunLifeConway1x20.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<ConwayCell> game(rows, cols, ConwayCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        round_to_print.push_back(6);
        round_to_print.push_back(7);
        round_to_print.push_back(8);
        round_to_print.push_back(9);
        round_to_print.push_back(10);
        while(!readFile.eof() && counter < rows*cols) {
        	readFile >> in;
            if(in == '*') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(50, "CONWAYCELL", round_to_print);
        readFile.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Conway Cell 20x1
    // ------------------
    try {
        cout << "*** Life<ConwayCell> 20x1 ***" << endl;
        ifstream readFile("RunLifeConway20x1.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<ConwayCell> game(rows, cols, ConwayCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        round_to_print.push_back(6);
        round_to_print.push_back(7);
        round_to_print.push_back(8);
        round_to_print.push_back(9);
        round_to_print.push_back(10);
        while(!readFile.eof() && counter < rows*cols) {
        	readFile >> in;
            if(in == '*') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(50, "CONWAYCELL", round_to_print);
        readFile.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ------------------
    // Fredkin Cell 20x20
    // ------------------
    try {
        cout << "*** Life<FredkinCell> 20x20 ***" << endl;
        ifstream readFile("RunLifeFredkin.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<FredkinCell> game(rows, cols, FredkinCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        while(!readFile.eof() && counter < rows*cols) {
            readFile >> in;
            if(in == '0' || in == '1') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(5, "FREDKINCELL", round_to_print);
        readFile.close();
        
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    
    // ------------------
    // Fredkin Cell 5x5
    // ------------------
    try {
        cout << "*** Life<FredkinCell> 5x5 ***" << endl;
        ifstream readFile("RunLifeFredkin5x5.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<FredkinCell> game(rows, cols, FredkinCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        while(!readFile.eof() && counter < rows*cols) {
            readFile >> in;
            if(in == '0' || in == '1') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(5, "FREDKINCELL", round_to_print);
        readFile.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Fredkin Cell 10x10
    // ------------------
    try {
        cout << "*** Life<FredkinCell> 10x10 ***" << endl;
        ifstream readFile("RunLifeFredkin10x10.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<FredkinCell> game(rows, cols, FredkinCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        while(!readFile.eof() && counter < rows*cols) {
            readFile >> in;
            if(in == '0' || in == '1') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(5, "FREDKINCELL", round_to_print);
        readFile.close();
        
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Fredkin Cell 20x20
    // ------------------
    try {
        cout << "*** Life<FredkinCell> 20x20 ***" << endl;
        ifstream readFile("RunLifeFredkin20x20.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<FredkinCell> game(rows, cols, FredkinCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        while(!readFile.eof() && counter < rows*cols) {
            readFile >> in;
            if(in == '0' || in == '1') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(5, "FREDKINCELL", round_to_print);
        readFile.close();
        
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Fredkin Cell 1x20
    // ------------------
    try {
        cout << "*** Life<FredkinCell> 1x20 ***" << endl;
        ifstream readFile("RunLifeFredkin1x20.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<FredkinCell> game(rows, cols, FredkinCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        while(!readFile.eof() && counter < rows*cols) {
            readFile >> in;
            if(in == '0' || in == '1') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(5, "FREDKINCELL", round_to_print);
        readFile.close();
        
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Fredkin Cell 20x1
    // ------------------
    try {
        cout << "*** Life<FredkinCell> 20x1 ***" << endl;
        ifstream readFile("RunLifeFredkin20x1.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<FredkinCell> game(rows, cols, FredkinCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        while(!readFile.eof() && counter < rows*cols) {
            readFile >> in;
            if(in == '0' || in == '1') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(5, "FREDKINCELL", round_to_print);
        readFile.close();
        
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Fredkin Cell 50x50
    // ------------------
    try {
        cout << "*** Life<FredkinCell> 50x50 ***" << endl;
        ifstream readFile("RunLifeFredkin50x50.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<FredkinCell> game(rows, cols, FredkinCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        while(!readFile.eof() && counter < rows*cols) {
            readFile >> in;
            if(in == '0' || in == '1') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(5, "FREDKINCELL", round_to_print);
        readFile.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ----------
    // Cell 20x20
    // ----------
    
    try {
        cout << "*** Life<Cell> 20x20 ***" << endl;
        ifstream readFile("RunLifeCell.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<Cell> game(rows, cols, new FredkinCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        while(!readFile.eof() && counter < rows*cols) {
            readFile >> in;
            if(in == '0' || in == '1') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(5,"CELL", round_to_print);
        readFile.close();
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ----------
    // Cell 10x10
    // ----------
    
    try {
        cout << "*** Life<Cell> 10x10 ***" << endl;
        ifstream readFile("RunLifeCell10x10.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<Cell> game(rows, cols, new FredkinCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        while(!readFile.eof() && counter < rows*cols) {
            readFile >> in;
            if(in == '0' || in == '1') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(5,"CELL", round_to_print);
        readFile.close();
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ----------
    // Cell 20x20
    // ----------
    
    try {
        cout << "*** Life<Cell> 20x20 ***" << endl;
        ifstream readFile("RunLifeCell20x20.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<Cell> game(rows, cols, new FredkinCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        while(!readFile.eof() && counter < rows*cols) {
            readFile >> in;
            if(in == '0' || in == '1') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(5,"CELL", round_to_print);
        readFile.close();
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ----------
    // Cell 50x50
    // ----------
    
    try {
        cout << "*** Life<Cell> 50x50 ***" << endl;
        ifstream readFile("RunLifeCell50x50.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<Cell> game(rows, cols, new FredkinCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        while(!readFile.eof() && counter < rows*cols) {
            readFile >> in;
            if(in == '0' || in == '1') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(5,"CELL", round_to_print);
        readFile.close();
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ----------
    // Cell 5x5
    // ----------
    
    try {
        cout << "*** Life<Cell> 5x5 ***" << endl;
        ifstream readFile("RunLifeCell5x5.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<Cell> game(rows, cols, new FredkinCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        while(!readFile.eof() && counter < rows*cols) {
            readFile >> in;
            if(in == '0' || in == '1') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(5,"CELL", round_to_print);
        readFile.close();
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ----------
    // Cell 1x20
    // ----------
    
    try {
        cout << "*** Life<Cell> 1x20 ***" << endl;
        ifstream readFile("RunLifeCell1x20.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<Cell> game(rows, cols, new FredkinCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        while(!readFile.eof() && counter < rows*cols) {
            readFile >> in;
            if(in == '0' || in == '1') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(5,"CELL", round_to_print);
        readFile.close();
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ----------
    // Cell 20x1
    // ----------
    
    try {
        cout << "*** Life<Cell> 20x1 ***" << endl;
        ifstream readFile("RunLifeCell20x1.in");
        char in;
        int rows;
        int cols;
        int counter = 0;
        readFile >> rows;
        readFile >> cols;
        Life<Cell> game(rows, cols, new FredkinCell(0,0,0));
        vector<int> round_to_print;
        round_to_print.push_back(0);
        round_to_print.push_back(1);
        round_to_print.push_back(2);
        round_to_print.push_back(3);
        round_to_print.push_back(4);
        round_to_print.push_back(5);
        while(!readFile.eof() && counter < rows*cols) {
            readFile >> in;
            if(in == '0' || in == '1') {
                game.make_alive(counter/cols, counter%cols);
            }
            counter++;
        }
        game.run(5,"CELL", round_to_print);
        readFile.close();
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    return 0;}
