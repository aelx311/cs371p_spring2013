// ------------------------------------
// projects/Life/TestLife.c++
// Copyright (C) 2013
// Glenn P. Downing
// ------------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -Wall Life.c++ TestLife.c++ -o TestLife -lcppunit -ldl
    % valgrind TestLife >& TestLife.out
*/

// --------
// includes
// --------

#include <algorithm> // count
#include <iostream>  // ios_base
#include <memory>    // Life

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#define private public
#define protected public
#include "Life.h"
#include "ConwayCell.h"
#include "FredkinCell.h"



// -------------
// TestLife
// -------------


using namespace std;
struct TestLife : CppUnit::TestFixture {
    void test_conway_cell_constructor_1(){
        ConwayCell cell(1,1,1);
        CPPUNIT_ASSERT(cell.get_row()==1);
        CPPUNIT_ASSERT(cell.get_col()==1);
        CPPUNIT_ASSERT(cell.get_status()==1);
        CPPUNIT_ASSERT(cell.to_char() == '*');
        CPPUNIT_ASSERT(cell.type() == 'c');
        cell.change_status();
        CPPUNIT_ASSERT(cell.get_status()==0);        
    }

    void test_conway_cell_constructor_2(){
        ConwayCell cell(2,2,0);
        CPPUNIT_ASSERT(cell.get_row()==2);
        CPPUNIT_ASSERT(cell.get_col()==2);
        CPPUNIT_ASSERT(cell.get_status()==0);
        CPPUNIT_ASSERT(cell.to_char() == '.');
        CPPUNIT_ASSERT(cell.type() == 'c');
        cell.change_status();
        CPPUNIT_ASSERT(cell.get_status()==1); 
    }
    
    void test_conway_cell_constructor_3(){
        ConwayCell cell(2,2,5);
        CPPUNIT_ASSERT(cell.get_row()==-1);
        CPPUNIT_ASSERT(cell.get_col()==-1);
        CPPUNIT_ASSERT(cell.get_status()==-1);
        CPPUNIT_ASSERT(cell.to_char() == 'E');
        CPPUNIT_ASSERT(cell.type() == 'c');
        cell.change_status();
        CPPUNIT_ASSERT(cell.get_status()==-1); 
    }

  void test_fredkin_cell_constructor_1(){
        FredkinCell cell(1,1,ALIVE);
        CPPUNIT_ASSERT(cell.get_row() == 1);
        CPPUNIT_ASSERT(cell.get_col() == 1);
        CPPUNIT_ASSERT(cell.get_status() == ALIVE);
        CPPUNIT_ASSERT(cell.to_char() == '0');
        CPPUNIT_ASSERT(cell.type() == FREDKIN_CELL);
        cell.add_age();
        CPPUNIT_ASSERT(cell.age == 1);
        cell.change_status();
        CPPUNIT_ASSERT(cell.get_status() == DEAD);        
    }

    void test_fredkin_cell_constructor_2(){
        FredkinCell cell(9,9,0);
        CPPUNIT_ASSERT(cell.get_row() == 9);
        CPPUNIT_ASSERT(cell.get_col() == 9);
        CPPUNIT_ASSERT(cell.get_status() == 0);
        CPPUNIT_ASSERT(cell.to_char() == '-');
        CPPUNIT_ASSERT(cell.type() == FREDKIN_CELL);
        cell.change_status();
        CPPUNIT_ASSERT(cell.get_status() == ALIVE);
    }

    void test_fredkin_cell_constructor_3(){
        FredkinCell cell(4,3,0);
        CPPUNIT_ASSERT(cell.get_row() == 4);
        CPPUNIT_ASSERT(cell.get_col() == 3);
        CPPUNIT_ASSERT(cell.get_status() == 0);
        CPPUNIT_ASSERT(cell.to_char() == '-');
        CPPUNIT_ASSERT(cell.type() == FREDKIN_CELL);
        cell.change_status();
        CPPUNIT_ASSERT(cell.get_status() == ALIVE);
    }

     void test_life_is_alive_1(){
        Life<ConwayCell> game(1,1, ConwayCell(0,0,0));
        ConwayCell cell(2,2,1);
        CPPUNIT_ASSERT(game.is_alive(cell) == 1);
    }

   void test_life_is_alive_2(){
        Life<ConwayCell> game(1,1, ConwayCell(0,0,0));
        ConwayCell cell(2,2,0);
        CPPUNIT_ASSERT(game.is_alive(cell) == 0);
    }

    void test_life_is_alive_3(){
        Life<ConwayCell> game(1,1, ConwayCell(0,0,0));
        ConwayCell cell(3,3,1);
        CPPUNIT_ASSERT(game.is_alive(cell) == 1);
    }

      void test_life_make_alive_1(){
        Life<ConwayCell> game(2,2, ConwayCell(0,0,0));
        game.make_alive(1,1);
        CPPUNIT_ASSERT(game.board[0][0].get_status() == 0);
        CPPUNIT_ASSERT(game.board[0][1].get_status() == 0);
        CPPUNIT_ASSERT(game.board[1][0].get_status() == 0);
        CPPUNIT_ASSERT(game.board[1][1].get_status() == 1);
    }

    void test_life_make_alive_2(){
        Life<ConwayCell> game(2,2, ConwayCell(0,0,0));
        game.make_alive(0,0);
        game.make_alive(0,1);
        game.make_alive(1,0);
        game.make_alive(1,1);
        CPPUNIT_ASSERT(game.board[0][0].get_status() == 1);
        CPPUNIT_ASSERT(game.board[0][1].get_status() == 1);
        CPPUNIT_ASSERT(game.board[1][0].get_status() == 1);
        CPPUNIT_ASSERT(game.board[1][1].get_status() == 1);
    }

    void test_life_make_alive_3(){
        Life<ConwayCell> game(3,3, ConwayCell(0,0,0));
        game.make_alive(0,0);
        game.make_alive(0,1);
        game.make_alive(1,0);
        game.make_alive(1,1);
        CPPUNIT_ASSERT(game.board[0][0].get_status() == 1);
        CPPUNIT_ASSERT(game.board[0][1].get_status() == 1);
        CPPUNIT_ASSERT(game.board[0][2].get_status() == 0);
        CPPUNIT_ASSERT(game.board[1][0].get_status() == 1);
        CPPUNIT_ASSERT(game.board[1][1].get_status() == 1);
        CPPUNIT_ASSERT(game.board[1][2].get_status() == 0);
        CPPUNIT_ASSERT(game.board[2][0].get_status() == 0);
        CPPUNIT_ASSERT(game.board[2][1].get_status() == 0);
        CPPUNIT_ASSERT(game.board[2][2].get_status() == 0);
    }

    void test_life_find_neighbor_1(){
        Life<ConwayCell> game(2,2, ConwayCell(0,0,0));
        game.make_alive(0,0);
        game.make_alive(0,1);
        game.make_alive(1,0);
        game.make_alive(1,1);
        CPPUNIT_ASSERT(game.find_neighbor(0,0, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(0,1, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(1,0, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(1,1, game.board)== 3);
    }

    void test_life_find_neighbor_2(){
        Life<ConwayCell> game(3,3, ConwayCell(0,0,0));
        game.make_alive(0,0);
        game.make_alive(0,1);
        game.make_alive(1,0);
        game.make_alive(1,1);
        CPPUNIT_ASSERT(game.find_neighbor(0,0, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(0,1, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(0,2, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(1,0, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(1,1, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(1,2, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(2,0, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(2,1, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(2,2, game.board)== 1);
    }

    void test_life_find_neighbor_3(){
        Life<ConwayCell> game(1,1, ConwayCell(0,0,0));
        CPPUNIT_ASSERT(game.find_neighbor(0,0, game.board)== 0);
    }

    void test_life_find_neighbor_4(){
        Life<ConwayCell> game(1,2, ConwayCell(0,0,0));
        CPPUNIT_ASSERT(game.find_neighbor(0,0, game.board)== 0);
        CPPUNIT_ASSERT(game.find_neighbor(0,1, game.board)== 0);
    }

    void test_life_find_neighbor_5(){
        Life<ConwayCell> game(1,4, ConwayCell(0,0,0));
        game.make_alive(0,0);
        game.make_alive(0,1);
        game.make_alive(0,2);
        game.make_alive(0,3);
        CPPUNIT_ASSERT(game.find_neighbor(0,0, game.board)== 1);
        CPPUNIT_ASSERT(game.find_neighbor(0,1, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(0,2, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(0,3, game.board)== 1);
    }

    void test_life_find_neighbor_6(){
        Life<ConwayCell> game(2,1, ConwayCell(0,0,0));
        CPPUNIT_ASSERT(game.find_neighbor(0,0, game.board)== 0);
        CPPUNIT_ASSERT(game.find_neighbor(1,0, game.board)== 0);
    }

    void test_life_find_neighbor_7(){
        Life<ConwayCell> game(4,1, ConwayCell(0,0,0));
        game.make_alive(0,0);
        game.make_alive(1,0);
        game.make_alive(2,0);
        game.make_alive(3,0);
        CPPUNIT_ASSERT(game.find_neighbor(0,0, game.board)== 1);
        CPPUNIT_ASSERT(game.find_neighbor(1,0, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(2,0, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(3,0, game.board)== 1);
    }

    void test_life_find_neighbor_8(){
        Life<ConwayCell> game(3,3, ConwayCell(0,0,0));
        game.make_alive(0,1);
        game.make_alive(1,1);
        game.make_alive(2,1);
        CPPUNIT_ASSERT(game.find_neighbor(0,0, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(0,1, game.board)== 1);
        CPPUNIT_ASSERT(game.find_neighbor(0,2, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(1,0, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(1,1, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(1,2, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(2,0, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(2,1, game.board)== 1);
        CPPUNIT_ASSERT(game.find_neighbor(2,2, game.board)== 2);
    }

   void test_life_find_neighbor_9(){
        Life<ConwayCell> game(4,4, ConwayCell(0,0,0));
        game.make_alive(0,0);
        game.make_alive(0,1);
        game.make_alive(0,2);
        game.make_alive(0,3);
        game.make_alive(1,0);
        game.make_alive(2,0);
        game.make_alive(3,0);
        game.make_alive(3,1);
        game.make_alive(3,2);
        game.make_alive(3,3);
        game.make_alive(1,3);
        game.make_alive(2,3);
        CPPUNIT_ASSERT(game.find_neighbor(0,0, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(0,1, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(0,2, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(0,3, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(1,0, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(2,0, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(3,0, game.board)== 2);
        CPPUNIT_ASSERT(game.find_neighbor(3,1, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(3,2, game.board)== 3);
        CPPUNIT_ASSERT(game.find_neighbor(3,3, game.board)== 2);
    }

    void test_life_run_1(){
        Life<ConwayCell> game(3,3, ConwayCell(0,0,0));
        game.make_alive(0,1);
        game.make_alive(1,1);
        game.make_alive(2,1);
        vector<int> x;
        x.push_back(0);
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        x.push_back(5);
        game.run(5, "CONWAYCELL", x);
    }

    void test_life_run_2(){
        Life<ConwayCell> game(11,11, ConwayCell(0,0,0));
        game.make_alive(0,1);
        game.make_alive(1,1);
        game.make_alive(2,1);
        game.make_alive(3,7);
        game.make_alive(2,2);
        game.make_alive(5,5);
        game.make_alive(4,3);
        game.make_alive(4,4);
        game.make_alive(7,3);
        game.make_alive(8,9);
        game.make_alive(10,10);
        game.make_alive(10,1);
        game.make_alive(9,8);
        game.make_alive(6,6);
        game.make_alive(6,10);
        vector<int> x;
        x.push_back(0);
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        x.push_back(5);
        game.run(5, "CONWAYCELL", x);
    }
    
    void test_life_run_3(){
        Life<ConwayCell> game(1,1, ConwayCell(0,0,0));
        game.make_alive(0,0);
        vector<int> x;
        x.push_back(0);
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);                                
        game.run(5, "CONWAYCELL", x);
    }
    
    void test_life_run_4(){
        Life<FredkinCell> game(3,3, FredkinCell(0,0,0));
        game.make_alive(0,0);
        game.make_alive(0,1);
        game.make_alive(0,2);
        game.make_alive(1,0);
        game.make_alive(2,0);
        vector<int> x;
        x.push_back(0);
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);      
        x.push_back(100);  
        game.run(100, "CONWAYCELL", x);
    }
    
    void test_get_population_1(){
        Life<Cell> game(5,5, new FredkinCell(0,0,0));
        game.make_alive(1,1);
        CPPUNIT_ASSERT(game.get_population() == 1);
    }
    
    void test_get_population_2(){
        Life<Cell> game(5,5, new FredkinCell(0,0,0));
        game.make_alive(1,1);
        game.make_alive(1,2);
        game.make_alive(1,3);
        game.make_alive(1,4);
        CPPUNIT_ASSERT(game.get_population() == 4);
    }    

    void test_get_population_3(){
        Life<Cell> game(5,5, new FredkinCell(0,0,0));
        CPPUNIT_ASSERT(game.get_population() == 0);
    } 
    
    // -----
    // suite
    // -----

  	CPPUNIT_TEST_SUITE(TestLife);
    CPPUNIT_TEST(test_conway_cell_constructor_1);
    CPPUNIT_TEST(test_conway_cell_constructor_2);
    CPPUNIT_TEST(test_conway_cell_constructor_3);
    CPPUNIT_TEST(test_fredkin_cell_constructor_1);
    CPPUNIT_TEST(test_fredkin_cell_constructor_2);
    CPPUNIT_TEST(test_fredkin_cell_constructor_3);
    CPPUNIT_TEST(test_life_is_alive_1);
    CPPUNIT_TEST(test_life_is_alive_2);
    CPPUNIT_TEST(test_life_is_alive_3);
    CPPUNIT_TEST(test_life_make_alive_1);
    CPPUNIT_TEST(test_life_make_alive_2);
    CPPUNIT_TEST(test_life_make_alive_3);
    CPPUNIT_TEST(test_life_find_neighbor_1);
    CPPUNIT_TEST(test_life_find_neighbor_2);
    CPPUNIT_TEST(test_life_find_neighbor_3);
    CPPUNIT_TEST(test_life_find_neighbor_4);
    CPPUNIT_TEST(test_life_find_neighbor_5);
    CPPUNIT_TEST(test_life_find_neighbor_6);
    CPPUNIT_TEST(test_life_find_neighbor_7);
    CPPUNIT_TEST(test_life_find_neighbor_8);
    CPPUNIT_TEST(test_life_find_neighbor_9);
    CPPUNIT_TEST(test_life_run_1);
    CPPUNIT_TEST(test_life_run_2);
    CPPUNIT_TEST(test_life_run_3);
    CPPUNIT_TEST(test_life_run_4);
    CPPUNIT_TEST(test_get_population_1);  
    CPPUNIT_TEST(test_get_population_2);  
    CPPUNIT_TEST(test_get_population_2);          
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);    // turn off synchronization with C I/O
    cout << "TestLife.c++" << endl;

    CppUnit::TextTestRunner tr;

	tr.addTest(TestLife::suite()); // uncomment!

    tr.run();

    cout << "Done." << endl;
    return 0;}

