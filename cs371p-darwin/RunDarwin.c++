// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunCollatz.c++ -o RunCollatz.c++.app
    % valgrind RunDarwin.c++.app > RunDarwin.out

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
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    // ----------
    // darwin 8x8
    // ----------

    try {
    	cout << "*** Darwin 8x8 ***" << endl;
		/*
		8x8 Darwin
		Food,   facing east,  at (0, 0)
		Hopper, facing north, at (3, 3)
		Hopper, facing east,  at (3, 4)
		Hopper, facing south, at (4, 4)
		Hopper, facing west,  at (4, 3)
		Food,   facing north, at (7, 7)
		Simulate 5 moves.
		Print every grid.
		*/
		Game game(8, 8);
		game.addCreature(Creature(Food(), EAST), 'f', 0, 0);
		game.addCreature(Creature(Hopper(), NORTH), 'h', 3, 3);
		game.addCreature(Creature(Hopper(), EAST), 'h', 3, 4);
		game.addCreature(Creature(Hopper(), SOUTH), 'h', 4, 4);
		game.addCreature(Creature(Hopper(), WEST), 'h', 4, 3);
		game.addCreature(Creature(Food(), NORTH), 'f', 7, 7);
		game.simulate(5, cout, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
		Game game(7, 9);
		game.addCreature(Creature(Trap(), SOUTH), 't', 0, 0);
		game.addCreature(Creature(Hopper(), EAST), 'h', 3, 2);
		game.addCreature(Creature(Rover(), NORTH), 'r', 5, 4);
		game.addCreature(Creature(Trap(), WEST), 't', 6, 8);
		game.simulate(5, cout, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Print every 100th grid.
        */
		int n = 72;
		int m = 72;
		Game game(n, m);
		int mod = n*m;
		for(int f = 0; f < 10; ++f) {
			int pos = rand() % mod;
			int dir = rand() % 4;
			game.addCreature(Creature(Food(), Direction(dir)), 'f', (pos/n), (pos%n));
		}

		for(int h = 0; h < 10; ++h) {
			int pos = rand() % mod;
			int dir = rand() % 4;
			game.addCreature(Creature(Hopper(), Direction(dir)), 'h', (pos/n), (pos%n));
		}

		for(int r = 0; r < 10; ++r) {
			int pos = rand() % mod;
			int dir = rand() % 4;
			game.addCreature(Creature(Rover(),Direction(dir)), 'r', (pos/n), (pos%n));
		}

		for(int t = 0; t < 10; ++t) {
			int pos = rand() % mod;
			int dir = rand() % 4;
			game.addCreature(Creature(Trap(),Direction(dir)), 't', (pos/n), (pos%n));
		}
		game.simulate(1000, cout, 100);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // with best
    // ------------

   try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        10 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */
		int n = 72;
		int m = 72;
		Game game(n, m);
		int mod = n*m;
		for(int f = 0; f < 10; ++f) {
			int pos = rand() % mod;
			int dir = rand() % 4;
			game.addCreature(Creature(Food(), Direction(dir)), 'f', (pos/n), (pos%n));
		}

		for(int h = 0; h < 10; ++h) {
			int pos = rand() % mod;
			int dir = rand() % 4;
			game.addCreature(Creature(Hopper(), Direction(dir)), 'h', (pos/n), (pos%n));
		}

		for(int r = 0; r < 10; ++r) {
			int pos = rand() % mod;
			int dir = rand() % 4;
			game.addCreature(Creature(Rover(),Direction(dir)), 'r', (pos/n), (pos%n));
		}

		for(int t = 0; t < 10; ++t) {
			int pos = rand() % mod;
			int dir = rand() % 4;
			game.addCreature(Creature(Trap(),Direction(dir)), 't', (pos/n), (pos%n));
		}

		for(int t = 0; t < 10; ++t) {
			int pos = rand() % mod;
			int dir = rand() % 4;
			game.addCreature(Creature(Best(),Direction(dir)), 'b', (pos/n), (pos%n));
		}
		game.simulate(1000, cout, 100);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 2x1
    // ----------

    try {
        cout << "*** Darwin 2x1 ***" << endl;
		Game game(2,1);
		game.addCreature(Creature(Food(), SOUTH), 'f', 0, 0);
		game.addCreature(Creature(Trap(), SOUTH), 't', 1, 0);
		game.simulate(1, cout, 1);
		}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 10x1
    // ------------

    try {
        cout << "*** Darwin 10x1 ***" << endl;
        srand(0);
		Game game(10,1);
		
		for(int i = 0; i < 10; i+=2) {
			game.addCreature(Creature(Trap(), SOUTH), 't', i, 0);
		}
		for(int i = 1; i < 10; i+=2) {
			game.addCreature(Creature(Rover(), SOUTH), 'r', i, 0);
		}
		game.simulate(1, cout, 1);
		}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 3x3
    // ----------

    try {
        cout << "*** Darwin 3x3 ***" << endl;
        srand(0);
		Game game(3,3);
		game.addCreature(Creature(Rover(), NORTH), 'r', 1, 1);
		game.addCreature(Creature(Food(), SOUTH), 'f', 0, 0);
		game.addCreature(Creature(Food(), SOUTH), 'f', 0, 1);
		game.addCreature(Creature(Food(), SOUTH), 'f', 0, 2);
		game.addCreature(Creature(Food(), SOUTH), 'f', 1, 0);
		game.addCreature(Creature(Food(), SOUTH), 'f', 1, 2);
		game.addCreature(Creature(Food(), SOUTH), 'f', 2, 0);
		game.addCreature(Creature(Food(), SOUTH), 'f', 2, 1);
		game.addCreature(Creature(Food(), SOUTH), 'f', 2, 2);
		game.simulate(5, cout, 1);
		}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 10x10
    // ------------

    try {
        cout << "*** Darwin 10x10 ***" << endl;
        srand(0);
		Game game(10,10);
		game.addCreature(Creature(Rover(), SOUTH), 'r', 5, 5);
		game.addCreature(Creature(Hopper(), NORTH), 'h', 9, 0);
		game.addCreature(Creature(Hopper(), NORTH), 'h', 9, 9);
		game.addCreature(Creature(Hopper(), SOUTH), 'h', 0, 9);
		game.addCreature(Creature(Hopper(), NORTH), 'h', 0, 0);
		game.simulate(35, cout, 7);
		}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 120x1
    // ------------

    try {
        cout << "*** Darwin 120x1 ***" << endl;
        srand(0);
		Game game(120,1);
		game.addCreature(Creature(Hopper(), NORTH), 'h', 119, 0);
		game.addCreature(Creature(Trap(), NORTH), 't', 0, 0);
		game.simulate(122, cout, 122);
		}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ------------
    // darwin 50x50
    // ------------

    try {
        cout << "*** Darwin 50x50 ***" << endl;
        srand(0);
		Game game(50,50);
		for(int i = 15; i < 30; ++i) { 
			game.addCreature(Creature(Hopper(), NORTH), 'h', i, 18);
		}
		for(int i = 15; i < 30; ++i) { 
			game.addCreature(Creature(Hopper(), NORTH), 'h', i, 19);
		}
		for(int i = 15; i < 30; ++i) { 
			game.addCreature(Creature(Hopper(), NORTH), 'h', i, 20);
		}
		for(int i = 21; i < 25; ++i) { 
			game.addCreature(Creature(Hopper(), NORTH), 'h', 21, i);
		}
		for(int i = 21; i < 25; ++i) { 
			game.addCreature(Creature(Hopper(), NORTH), 'h', 22, i);
		}
		for(int i = 15; i < 30; ++i) { 
			game.addCreature(Creature(Hopper(), NORTH), 'h', i, 25);
		}
		for(int i = 15; i < 30; ++i) { 
			game.addCreature(Creature(Hopper(), NORTH), 'h', i, 26);
		}
		for(int i = 15; i < 30; ++i) { 
			game.addCreature(Creature(Hopper(), NORTH), 'h', i, 27);
		}


		for(int i = 22; i < 30; ++i) { 
			game.addCreature(Creature(Hopper(), NORTH), 'h', i, 31);
		}
		for(int i = 22; i < 30; ++i) { 
			game.addCreature(Creature(Hopper(), NORTH), 'h', i, 32);
		}
		for(int i = 22; i < 30; ++i) { 
			game.addCreature(Creature(Hopper(), NORTH), 'h', i, 33);
		}

		for(int i = 31; i < 34; ++i) { 
			game.addCreature(Creature(Hopper(), NORTH), 'h', 19, i);
		}
		for(int i = 31; i < 34; ++i) { 
			game.addCreature(Creature(Hopper(), NORTH), 'h', 20, i);
		}

		for(int i = 0; i < 49; ++i) { 
			game.addCreature(Creature(Rover(), SOUTH), 'r', i, 0);
		}
		game.simulate(100, cout, 50);
		}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
