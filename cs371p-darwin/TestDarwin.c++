//--------------
//TestDarwin.c++
//--------------

#define private public
#define protected public

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Darwin.h"

// -----------
// TestDarwin
// -----------

struct TestDarwin : CppUnit::TestFixture {
	
	// -------------------------
	// test_Species_constructor
	// -------------------------
	
	void test_Species_constructor_1() {
		Species s('f');
		CPPUNIT_ASSERT(s._name == 'f');
	}
	
	void test_Species_constructor_2() {
		Species s('h');
		CPPUNIT_ASSERT(s._name == 'h');
	}
	
	void test_Species_constructor_3() {
		Species s('r');
		CPPUNIT_ASSERT(s._name == 'r');
	}

	// ---------------------------
	// test_Species_addInstruction
	// ---------------------------
	
	void test_Species_addInstruction_1() {
		Species s('f');
		s.addInstruction(GO, 0);
		s.addInstruction(HOP);
		CPPUNIT_ASSERT((int)s._program.size() == 2);
	}

	void test_Species_addInstruction_2() {
		Species s('f');
		s.addInstruction(GO, 0);
		try {
		    s.addInstruction(HOP, 0);
		} catch(const invalid_argument&) {
			CPPUNIT_ASSERT((int)s._program.size() == 1);
		}
	}

	void test_Species_addInstruction_3() {
		Species s('x');
		for(int i = 0; i < 100; ++i) {
			s.addInstruction(HOP);
		}
		CPPUNIT_ASSERT((int)s._program.size() == 100);
	}

	// --------------------
	// test_Species_execute
	// --------------------
	
	void test_Species_execute_1() {
		Species s('h');
		s.addInstruction(HOP);
		s.addInstruction(GO, 0);
		CPPUNIT_ASSERT(s.execute(0, '.') == HOP);
		CPPUNIT_ASSERT(s.execute(1, '.') == 0);
	}

	void test_Species_execute_2() {
		srand(0);
		Species s('r');
		s.addInstruction(IF_EMPTY, 2);
		s.addInstruction(IF_ENEMY, 3);
		s.addInstruction(IF_WALL, 3);
		s.addInstruction(IF_RANDOM, 1);
		s.addInstruction(GO, 0);
		CPPUNIT_ASSERT(s.execute(0, '.') == 2);
		CPPUNIT_ASSERT(s.execute(0, 'h') == 1);
		CPPUNIT_ASSERT(s.execute(1, '.') == 2);
		CPPUNIT_ASSERT(s.execute(1, 't') == 3);
		CPPUNIT_ASSERT(s.execute(1, '_') == 2);
		CPPUNIT_ASSERT(s.execute(1, 'r') == 2);
		CPPUNIT_ASSERT(s.execute(2, '_') == 3);
		CPPUNIT_ASSERT(s.execute(2, '.') == 3);
		CPPUNIT_ASSERT(s.execute(2, 'h') == 3);
		CPPUNIT_ASSERT(s.execute(3, 'h') == 1);
		CPPUNIT_ASSERT(s.execute(3, 'h') == 4);
		CPPUNIT_ASSERT(s.execute(3, 'h') == 1);
	}

	void test_Species_execute_3() {
		Species s('h');
		s.addInstruction(LEFT);
		s.addInstruction(HOP);
		s.addInstruction(INFECT);
		s.addInstruction(RIGHT);
		CPPUNIT_ASSERT(s.execute(0, '.') == LEFT);
		CPPUNIT_ASSERT(s.execute(1, '.') == HOP);
		CPPUNIT_ASSERT(s.execute(2, '.') == INFECT);
		CPPUNIT_ASSERT(s.execute(3, '.') == RIGHT);

	}


	// ---------------------
	// test_Species_isAction
	// ---------------------

	void test_Species_isAction_1() {
		Species s('h');
		s.addInstruction(LEFT);
		s.addInstruction(IF_EMPTY, 0);
		s.addInstruction(HOP);
		s.addInstruction(INFECT);
		s.addInstruction(IF_ENEMY, 100000000);
		CPPUNIT_ASSERT(s.isAction(0));
		CPPUNIT_ASSERT(!s.isAction(1));
		CPPUNIT_ASSERT(s.isAction(2));
		CPPUNIT_ASSERT(s.isAction(3));
		CPPUNIT_ASSERT(!s.isAction(4));
	}

	void test_Species_isAction_2() {
		Species s('t');
		s.addInstruction(RIGHT);
		CPPUNIT_ASSERT(s.isAction(0));
	}

	void test_Species_isAction_3() {
		Species s('t');
		for(int i = 0; i < 100; ++i) {
			s.addInstruction(RIGHT);
		}
		for(int i = 0; i < 100; ++i) {
			s.addInstruction(GO, 100);
		}
		for(int i = 0; i < 100; ++i) {
			CPPUNIT_ASSERT(s.isAction(i));
		}
		for(int i = 100; i < 200; ++i) {
			CPPUNIT_ASSERT(!s.isAction(i));
		}
	}

	// ---------------------
	// test_Food_constructor
	// ---------------------
	
	void test_Food_constructor_1() {
		Food f;
		CPPUNIT_ASSERT(f._name == 'f');
		CPPUNIT_ASSERT(f._program.size() == 2);
	}

	void test_Food_constructor_2() {
		Food f;
		CPPUNIT_ASSERT(f._program[0].first == LEFT);
		CPPUNIT_ASSERT(f._program[1].first == GO);
	}

	void test_Food_constructor_3() {
		Food f;
		CPPUNIT_ASSERT(f._program[0].second == -1);
		CPPUNIT_ASSERT(f._program[1].second == 0);	
	}
	
	// -----------------------
	// test_Hopper_constructor
	// -----------------------

	void test_Hopper_constructor_1() {
		Hopper h;
		CPPUNIT_ASSERT(h._name == 'h');
		CPPUNIT_ASSERT(h._program.size() == 2);
	}

	void test_Hopper_constructor_2() {
		Hopper h;
		CPPUNIT_ASSERT(h._program[0].first == HOP);
		CPPUNIT_ASSERT(h._program[1].first == GO);
	}

	void test_Hopper_constructor_3() {
		Hopper h;
		CPPUNIT_ASSERT(h._program[0].second == -1);
		CPPUNIT_ASSERT(h._program[1].second == 0);	
	}
	
	// ----------------------
	// test_Rover_constructor
	// ----------------------
	
	void test_Rover_constructor_1() {
		Rover r;
		CPPUNIT_ASSERT(r._name == 'r');
		CPPUNIT_ASSERT(r._program.size() == 11);
	}

	void test_Rover_constructor_2() {
		Rover r;
		CPPUNIT_ASSERT(r._program[0].first == IF_ENEMY);
		CPPUNIT_ASSERT(r._program[1].first == IF_EMPTY);
		CPPUNIT_ASSERT(r._program[2].first == IF_RANDOM);
		CPPUNIT_ASSERT(r._program[3].first == LEFT);
		CPPUNIT_ASSERT(r._program[4].first == GO);
		CPPUNIT_ASSERT(r._program[5].first == RIGHT);
		CPPUNIT_ASSERT(r._program[6].first == GO);
		CPPUNIT_ASSERT(r._program[7].first == HOP);
		CPPUNIT_ASSERT(r._program[8].first == GO);
		CPPUNIT_ASSERT(r._program[9].first == INFECT);
		CPPUNIT_ASSERT(r._program[10].first == GO);
	}

	void test_Rover_constructor_3() {
		Rover r;
		CPPUNIT_ASSERT(r._program[0].second == 9);
		CPPUNIT_ASSERT(r._program[1].second == 7);
		CPPUNIT_ASSERT(r._program[2].second == 5);
		CPPUNIT_ASSERT(r._program[3].second == -1);
		CPPUNIT_ASSERT(r._program[4].second == 0);
		CPPUNIT_ASSERT(r._program[5].second == -1);
		CPPUNIT_ASSERT(r._program[6].second == 0);
		CPPUNIT_ASSERT(r._program[7].second == -1);
		CPPUNIT_ASSERT(r._program[8].second == 0);
		CPPUNIT_ASSERT(r._program[9].second == -1);
		CPPUNIT_ASSERT(r._program[10].second == 0);
	}
	
	// ---------------------
	// test_Trap_constructor
	// ---------------------
	
	void test_Trap_constructor_1() {
		Trap t;
		CPPUNIT_ASSERT(t._name == 't');
		CPPUNIT_ASSERT(t._program.size() == 5);
	}

	void test_Trap_constructor_2() {
		Trap t;
		CPPUNIT_ASSERT(t._program[0].first == IF_ENEMY);
		CPPUNIT_ASSERT(t._program[1].first == LEFT);
		CPPUNIT_ASSERT(t._program[2].first == GO);
		CPPUNIT_ASSERT(t._program[3].first == INFECT);
		CPPUNIT_ASSERT(t._program[4].first == GO);
	}

	void test_Trap_constructor_3() {
		Trap t;
		CPPUNIT_ASSERT(t._program[0].second == 3);
		CPPUNIT_ASSERT(t._program[1].second == -1);
		CPPUNIT_ASSERT(t._program[2].second == 0);
		CPPUNIT_ASSERT(t._program[3].second == -1);
		CPPUNIT_ASSERT(t._program[4].second == 0);
	}
	
	// ----------------------
	// test_Best_constructor
	// ----------------------
	
	void test_Best_constructor_1() {
		Best b;
		CPPUNIT_ASSERT(b._name == 'b');
		CPPUNIT_ASSERT(b._program.size() == 17);
	}

	void test_Best_constructor_2() {
		Best b;
		CPPUNIT_ASSERT(b._program[0].first == IF_ENEMY);
		CPPUNIT_ASSERT(b._program[1].first == IF_EMPTY);
		CPPUNIT_ASSERT(b._program[2].first == IF_RANDOM);
		CPPUNIT_ASSERT(b._program[3].first == IF_RANDOM);
		CPPUNIT_ASSERT(b._program[4].first == LEFT);
		CPPUNIT_ASSERT(b._program[5].first == GO);
		CPPUNIT_ASSERT(b._program[6].first == RIGHT);
		CPPUNIT_ASSERT(b._program[7].first == GO);
		CPPUNIT_ASSERT(b._program[8].first == HOP);
		CPPUNIT_ASSERT(b._program[9].first == GO);
		CPPUNIT_ASSERT(b._program[10].first == INFECT);
		CPPUNIT_ASSERT(b._program[11].first == GO);
		CPPUNIT_ASSERT(b._program[12].first == IF_ENEMY);
		CPPUNIT_ASSERT(b._program[13].first == LEFT);
		CPPUNIT_ASSERT(b._program[14].first == GO);
		CPPUNIT_ASSERT(b._program[15].first == INFECT);
		CPPUNIT_ASSERT(b._program[16].first == GO);
	}

	void test_Best_constructor_3() {
		Best b;
		CPPUNIT_ASSERT(b._program[0].second == 10);
		CPPUNIT_ASSERT(b._program[1].second == 8);
		CPPUNIT_ASSERT(b._program[2].second == 12);
		CPPUNIT_ASSERT(b._program[3].second == 4);
		CPPUNIT_ASSERT(b._program[4].second == -1);
		CPPUNIT_ASSERT(b._program[5].second == 0);
		CPPUNIT_ASSERT(b._program[6].second == -1);
		CPPUNIT_ASSERT(b._program[7].second == 0);
		CPPUNIT_ASSERT(b._program[8].second == -1);
		CPPUNIT_ASSERT(b._program[9].second == 0);
		CPPUNIT_ASSERT(b._program[10].second == -1);
		CPPUNIT_ASSERT(b._program[11].second == 0);
		CPPUNIT_ASSERT(b._program[12].second == 15);
		CPPUNIT_ASSERT(b._program[13].second == -1);
		CPPUNIT_ASSERT(b._program[14].second == 0);
		CPPUNIT_ASSERT(b._program[15].second == -1);
		CPPUNIT_ASSERT(b._program[16].second == 0);
	}

	// -------------------------
	// test_Creature_constructor
	// -------------------------
	
	void test_Creature_constructor_1() {
		Creature c(Food(), WEST);
		CPPUNIT_ASSERT(c._species._name == 'f');
		CPPUNIT_ASSERT(c._programCounter == 0);
		CPPUNIT_ASSERT(c._direction == WEST);
		CPPUNIT_ASSERT(c._species._program.size() == 2);
	}
	
	void test_Creature_constructor_2() {
		vector<Creature> cList;
		cList.push_back(Creature(Food(), WEST));
		cList.push_back(Creature(Hopper(), SOUTH));
		cList.push_back(Creature(Rover(), EAST));
		CPPUNIT_ASSERT(cList[0]._species._name == 'f');
		CPPUNIT_ASSERT(cList[0]._programCounter == 0);
		CPPUNIT_ASSERT(cList[0]._direction == WEST);
		CPPUNIT_ASSERT(cList[0]._species._program.size() == 2);
		CPPUNIT_ASSERT(cList[1]._species._name == 'h');
		CPPUNIT_ASSERT(cList[1]._programCounter == 0);
		CPPUNIT_ASSERT(cList[1]._direction == SOUTH);
		CPPUNIT_ASSERT(cList[1]._species._program.size() == 2);
		CPPUNIT_ASSERT(cList[2]._species._name == 'r');
		CPPUNIT_ASSERT(cList[2]._programCounter == 0);
		CPPUNIT_ASSERT(cList[2]._direction == EAST);
		CPPUNIT_ASSERT(cList[2]._species._program.size() == 11);
	}
	
	void test_Creature_constructor_3() {
		vector<Creature> cList;
		cList.push_back(Creature(Food(), WEST));
		cList.push_back(Creature(Hopper(), NORTH));
		cList.push_back(Creature(Hopper(), EAST));
		cList.push_back(Creature(Hopper(), WEST));
		cList.push_back(Creature(Rover(), NORTH));
		cList.push_back(Creature(Rover(), SOUTH));
		cList.push_back(Creature(Trap(), EAST));
		CPPUNIT_ASSERT(cList[0]._species._name == 'f');
		CPPUNIT_ASSERT(cList[0]._programCounter == 0);
		CPPUNIT_ASSERT(cList[0]._direction == WEST);
		CPPUNIT_ASSERT(cList[0]._species._program.size() == 2);
		CPPUNIT_ASSERT(cList[1]._species._name == 'h');
		CPPUNIT_ASSERT(cList[1]._programCounter == 0);
		CPPUNIT_ASSERT(cList[1]._direction == NORTH);
		CPPUNIT_ASSERT(cList[1]._species._program.size() == 2);
		CPPUNIT_ASSERT(cList[2]._species._name == 'h');
		CPPUNIT_ASSERT(cList[2]._programCounter == 0);
		CPPUNIT_ASSERT(cList[2]._direction == EAST);
		CPPUNIT_ASSERT(cList[2]._species._program.size() == 2);
		CPPUNIT_ASSERT(cList[3]._species._name == 'h');
		CPPUNIT_ASSERT(cList[3]._programCounter == 0);
		CPPUNIT_ASSERT(cList[3]._direction == WEST);
		CPPUNIT_ASSERT(cList[3]._species._program.size() == 2);
		CPPUNIT_ASSERT(cList[4]._species._name == 'r');
		CPPUNIT_ASSERT(cList[4]._programCounter == 0);
		CPPUNIT_ASSERT(cList[4]._direction == NORTH);
		CPPUNIT_ASSERT(cList[4]._species._program.size() == 11);
		CPPUNIT_ASSERT(cList[5]._species._name == 'r');
		CPPUNIT_ASSERT(cList[5]._programCounter == 0);
		CPPUNIT_ASSERT(cList[5]._direction == SOUTH);
		CPPUNIT_ASSERT(cList[5]._species._program.size() == 11);
		CPPUNIT_ASSERT(cList[6]._species._name == 't');
		CPPUNIT_ASSERT(cList[6]._programCounter == 0);
		CPPUNIT_ASSERT(cList[6]._direction == EAST);
		CPPUNIT_ASSERT(cList[6]._species._program.size() == 5);
	}
	
	// -----------------
	// test_Creature_run
	// -----------------
	
	void test_Creature_run_1() {
		vector<char> surroundings(4, '.');
		Creature c(Food(), WEST);
		pair<instructionType, Direction> r = c.run(surroundings);
		instructionType a = r.first;
		Direction d = r.second;
		CPPUNIT_ASSERT(a == LEFT);
		CPPUNIT_ASSERT(d == WEST);
		for(int i = 0; i < 10; ++i) {
			r = c.run(surroundings);
			a = r.first;
			d = r.second;
			CPPUNIT_ASSERT(a == LEFT);
			CPPUNIT_ASSERT(d == WEST);
		}
	}
	
	void test_Creature_run_2() {
		vector<char> surroundings(4, '.');
		surroundings[1] = 'h';

		Creature c(Hopper(), NORTH);
		pair<instructionType, Direction> r = c.run(surroundings);
		instructionType a = r.first;
		Direction d = r.second;
		CPPUNIT_ASSERT(a == HOP);
		CPPUNIT_ASSERT(d == NORTH);

		c = Creature(Rover(), NORTH);
		for(int i = 0; i < 10; ++i) {
			r = c.run(surroundings);
			a = r.first;
			d = r.second;
			CPPUNIT_ASSERT(a == INFECT);
			CPPUNIT_ASSERT(d == NORTH);
		}
		c = Creature(Trap(), SOUTH);
		for(int i = 0; i < 10; ++i) {
			r = c.run(surroundings);
			a = r.first;
			d = r.second;
			CPPUNIT_ASSERT(a == LEFT);
			CPPUNIT_ASSERT(d == SOUTH);
		}
	}

	void test_Creature_run_3() {
		srand(0);
		vector<char> surroundings(4, '.');
		Creature c(Rover(), NORTH);
		pair<instructionType, Direction> r = c.run(surroundings);
		instructionType a = r.first;
		Direction d = r.second;
		CPPUNIT_ASSERT(a == HOP);
		CPPUNIT_ASSERT(d == NORTH);
		surroundings[1] = 'h';
		r = c.run(surroundings);
		a = r.first;
		d = r.second;
		CPPUNIT_ASSERT(a == INFECT);
		CPPUNIT_ASSERT(d == NORTH);
		surroundings[1] = '_';
		r = c.run(surroundings);
		a = r.first;
		d = r.second;
		CPPUNIT_ASSERT(a == RIGHT);
		CPPUNIT_ASSERT(d == NORTH);
	}

	// ----------------------
	// test_Creature_turnLeft
	// ----------------------

	void test_Creature_turnLeft_1() {
		Creature c1(Rover(), NORTH);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == NORTH);

		Creature c2(Food(), NORTH);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == WEST);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == SOUTH);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == EAST);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == NORTH);

		Creature c3(Hopper(), NORTH);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == WEST);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == SOUTH);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == EAST);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == NORTH);

		Creature c4(Trap(), NORTH);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == WEST);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == SOUTH);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == EAST);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == NORTH);
	}

	void test_Creature_turnLeft_2() {
		Creature c1(Rover(), WEST);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == WEST);

		Creature c2(Food(), WEST);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == SOUTH);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == EAST);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == NORTH);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == WEST);

		Creature c3(Hopper(), WEST);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == SOUTH);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == EAST);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == NORTH);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == WEST);

		Creature c4(Trap(), WEST);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == SOUTH);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == EAST);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == NORTH);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == WEST);
	}


	void test_Creature_turnLeft_3() {
		Creature c1(Rover(), SOUTH);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == SOUTH);

		Creature c2(Food(), SOUTH);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == EAST);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == NORTH);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == WEST);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == SOUTH);

		Creature c3(Hopper(), SOUTH);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == EAST);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == NORTH);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == WEST);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == SOUTH);

		Creature c4(Trap(), SOUTH);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == EAST);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == NORTH);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == WEST);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == SOUTH);
	}

	void test_Creature_turnLeft_4() {
		Creature c1(Rover(), EAST);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnLeft();
		CPPUNIT_ASSERT(c1._direction == EAST);

		Creature c2(Food(), EAST);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == NORTH);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == WEST);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == SOUTH);
		c2.turnLeft();
		CPPUNIT_ASSERT(c2._direction == EAST);

		Creature c3(Hopper(), EAST);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == NORTH);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == WEST);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == SOUTH);
		c3.turnLeft();
		CPPUNIT_ASSERT(c3._direction == EAST);

		Creature c4(Trap(), EAST);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == NORTH);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == WEST);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == SOUTH);
		c4.turnLeft();
		CPPUNIT_ASSERT(c4._direction == EAST);
	}

	// -----------------------
	// test_Creature_turnRight
	// -----------------------

	void test_Creature_turnRight_1() {
		Creature c1 = Creature(Rover(), NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1 = Creature(Food(), NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1 = Creature(Hopper(), NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1 = Creature(Trap(), NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
	}

	void test_Creature_turnRight_2() {
		Creature c1 = Creature(Rover(), EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1 = Creature(Food(), EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1 = Creature(Hopper(), EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1 = Creature(Trap(), EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
	}

	void test_Creature_turnRight_3() {
		Creature c1 = Creature(Rover(), SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1 = Creature(Food(), SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1 = Creature(Hopper(), SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1 = Creature(Trap(), SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
	}

	void test_Creature_turnRight_4() {
		Creature c1 = Creature(Rover(), WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1 = Creature(Food(), WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1 = Creature(Hopper(), WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
		c1 = Creature(Trap(), WEST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == NORTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == EAST);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == SOUTH);
		c1.turnRight();
		CPPUNIT_ASSERT(c1._direction == WEST);
	}

	// --------------------
	// test_Creature_infect
	// --------------------

	void test_Creature_infect_1() {
		Creature c1(Rover(), NORTH);
		Creature c2(Hopper(), WEST);
		++c2._programCounter;
		c1.infect(c2);
		CPPUNIT_ASSERT(&c1._species != &c2._species);
		CPPUNIT_ASSERT(c1._species._name == c2._species._name);
		CPPUNIT_ASSERT(c1._species._program.size() == c2._species._program.size());
		CPPUNIT_ASSERT(c1._direction == NORTH);
		CPPUNIT_ASSERT(c2._direction == WEST);
		CPPUNIT_ASSERT(c2._programCounter == 0);
	}

	void test_Creature_infect_2() {
		Creature c1(Trap(), WEST);
		Creature c2(Food(), SOUTH);
		++c2._programCounter;
		c1.infect(c2);
		CPPUNIT_ASSERT(&c1._species != &c2._species);
		CPPUNIT_ASSERT(c1._species._name == c2._species._name);
		CPPUNIT_ASSERT(c1._species._program.size() == c2._species._program.size());
		CPPUNIT_ASSERT(c1._direction == WEST);
		CPPUNIT_ASSERT(c2._direction == SOUTH);
		CPPUNIT_ASSERT(c2._programCounter == 0);
	}

	void test_Creature_infect_3() {
		Creature c1(Trap(), EAST);
		Creature c2(Hopper(), NORTH);
		++c2._programCounter;
		c1.infect(c2);
		CPPUNIT_ASSERT(&c1._species != &c2._species);
		CPPUNIT_ASSERT(c1._species._name == c2._species._name);
		CPPUNIT_ASSERT(c1._species._program.size() == c2._species._program.size());
		CPPUNIT_ASSERT(c1._direction == EAST);
		CPPUNIT_ASSERT(c2._direction == NORTH);
		CPPUNIT_ASSERT(c2._programCounter == 0);
	}

	// ---------------------
	// test_Game_constructor
	// ---------------------
	
	void test_Game_constructor_1() {
		Game game = Game(1,1);
		CPPUNIT_ASSERT(game._grid.size() == 1);
		CPPUNIT_ASSERT(game._grid[0].size() == 1);
		CPPUNIT_ASSERT(game._grid[0][0] == -1);
	}
	
	void test_Game_constructor_2() {
		Game game = Game(2,2);
		CPPUNIT_ASSERT(game._grid.size() == 2);
		CPPUNIT_ASSERT(game._grid[0].size() == 2);
		CPPUNIT_ASSERT(game._grid[1].size() == 2);
		for(int r = 0; r < 2; ++r) {
			for(int c = 0; c < 2; ++c){
				CPPUNIT_ASSERT(game._grid[r][c] == -1);
			}
		}
	}
	
	void test_Game_constructor_3() {
		Game game = Game(100,100);
		CPPUNIT_ASSERT(game._grid.size() == 100);
		for(int i = 0; i < 100; ++i) {
			CPPUNIT_ASSERT(game._grid[i].size() == 100);
		}
		for(int r = 0; r < 100; ++r) {
			for(int c = 0; c < 100; ++c){
				CPPUNIT_ASSERT(game._grid[r][c] == -1);
			}
		}
	}
	
	void test_Game_constructor_4() {
		Game game = Game(1000,10);
		CPPUNIT_ASSERT(game._grid.size() == 1000);
		for(int i = 0; i < 1000; ++i) {
			CPPUNIT_ASSERT(game._grid[i].size() == 10);
		}
		for(int r = 0; r < 1000; ++r) {
			for(int c = 0; c < 10; ++c){
				CPPUNIT_ASSERT(game._grid[r][c] == -1);
			}
		}
	}
	
	// ---------------------
	// test_Game_addCreature
	// ---------------------

	void test_Game_addCreature_1() {
		Game game(8,8);
		int x = 0;
		int y = 0;
		game.addCreature(Creature(Food(), WEST), 'f', x, y);
		CPPUNIT_ASSERT(game._grid[x][y] == 0);
		CPPUNIT_ASSERT(game._charGrid[x][y] == 'f');
		CPPUNIT_ASSERT(game._creatureList.size() == 1);
	}
	
	void test_Game_addCreature_2() {
		Game game(8,8);
		game.addCreature(Creature(Food(), WEST), 'f', 0, 0);
		game.addCreature(Creature(Rover(), SOUTH), 'r', 1, 2);
		game.addCreature(Creature(Trap(), NORTH), 't', 3, 5);
		CPPUNIT_ASSERT(game._grid[0][0] == 0);
		CPPUNIT_ASSERT(game._charGrid[0][0] == 'f');
		CPPUNIT_ASSERT(game._grid[1][2] == 1);
		CPPUNIT_ASSERT(game._charGrid[1][2] == 'r');
		CPPUNIT_ASSERT(game._grid[3][5] == 2);
		CPPUNIT_ASSERT(game._charGrid[3][5] == 't');
		CPPUNIT_ASSERT(game._creatureList.size() == 3);
	}
	
	void test_Game_addCreature_3() {
		Game game(8,8);
		try {
			game.addCreature(Creature(Food(), WEST), 'f', 0, 9);
			CPPUNIT_ASSERT(false);
		}
		catch(const out_of_range&) {
			CPPUNIT_ASSERT(true);
		}
	}

	// ---------------
	// test_Game_print
	// ---------------

	void test_Game_print_1() {
		ostringstream w;
		Game game(8,8);
		game.print(w);
		CPPUNIT_ASSERT(w.str() ==
		"Turn = 0.\n  01234567\n0 ........\n1 ........\n2 ........\n3 ........\n4 ........\n5 ........\n6 ........\n7 ........\n\n");
	}

	void test_Game_print_2() {
		ostringstream w;
		Game game(1,1);
		game.print(w);
		CPPUNIT_ASSERT(w.str() == "Turn = 0.\n  0\n0 .\n\n");
	}

	void test_Game_print_3() {
		ostringstream w;
		Game game(2,2);
		game.print(w);
		CPPUNIT_ASSERT(w.str() == "Turn = 0.\n  01\n0 ..\n1 ..\n\n");
	}

	void test_Game_print_4() {
		ostringstream w;
		Game game(8,8);
		game.print(w);
		CPPUNIT_ASSERT(w.str() ==
		"Turn = 0.\n  01234567\n0 ........\n1 ........\n2 ........\n3 ........\n4 ........\n5 ........\n6 ........\n7 ........\n\n");
		game.addCreature(Creature(Food(), EAST), 'f', 0, 0);
		game.addCreature(Creature(Hopper(), NORTH), 'h', 3, 3);
		game.addCreature(Creature(Hopper(), EAST), 'h', 3, 4);
		game.addCreature(Creature(Hopper(), SOUTH), 'h', 4, 4);
		game.addCreature(Creature(Hopper(), WEST), 'h', 4, 3);
		game.addCreature(Creature(Food(), NORTH), 'f', 7, 7);
		ostringstream w1;
		game.print(w1);
		CPPUNIT_ASSERT(w1.str() ==
		"Turn = 0.\n  01234567\n0 f.......\n1 ........\n2 ........\n3 ...hh...\n4 ...hh...\n5 ........\n6 ........\n7 .......f\n\n");
	}

	// -------------------------
	// test_Game_lookSurrounding
	// -------------------------
	void test_Game_lookSurrounding_1() {
		vector<char> v;		
		Game game(8,8);
		game.addCreature(Creature(Food(), EAST), 'f', 0, 0);
		game.addCreature(Creature(Hopper(), NORTH), 'h', 3, 3);
		game.addCreature(Creature(Hopper(), EAST), 'h', 3, 4);
		game.addCreature(Creature(Hopper(), SOUTH), 'h', 4, 4);
		game.addCreature(Creature(Hopper(), WEST), 'h', 4, 3);
		game.addCreature(Creature(Food(), NORTH), 'f', 7, 7);
		v = game.lookSurrounding(0,0);
		CPPUNIT_ASSERT(v[0] == '_');
		CPPUNIT_ASSERT(v[1] == '_');
		CPPUNIT_ASSERT(v[2] == '.');
		CPPUNIT_ASSERT(v[3] == '.');
		v = game.lookSurrounding(3,3);
		CPPUNIT_ASSERT(v[0] == '.');
		CPPUNIT_ASSERT(v[1] == '.');
		CPPUNIT_ASSERT(v[2] == 'h');
		CPPUNIT_ASSERT(v[3] == 'h');
		v = game.lookSurrounding(4,4);
		CPPUNIT_ASSERT(v[0] == 'h');
		CPPUNIT_ASSERT(v[1] == 'h');
		CPPUNIT_ASSERT(v[2] == '.');
		CPPUNIT_ASSERT(v[3] == '.');
		v = game.lookSurrounding(7,7);
		CPPUNIT_ASSERT(v[0] == '.');
		CPPUNIT_ASSERT(v[1] == '.');
		CPPUNIT_ASSERT(v[2] == '_');
		CPPUNIT_ASSERT(v[3] == '_');
	}

	void test_Game_lookSurrounding_2() {
		vector<char> v;		
		Game game(8,8);
		game.addCreature(Creature(Food(), EAST), 'f', 0, 0);
		game.addCreature(Creature(Food(), NORTH), 'f', 7, 0);
		game.addCreature(Creature(Food(), WEST), 'f', 0, 7);
		game.addCreature(Creature(Food(), NORTH), 'f', 7, 7);
		v = game.lookSurrounding(0,0);
		CPPUNIT_ASSERT(v[0] == '_');
		CPPUNIT_ASSERT(v[1] == '_');
		CPPUNIT_ASSERT(v[2] == '.');
		CPPUNIT_ASSERT(v[3] == '.');
		v = game.lookSurrounding(7,0);
		CPPUNIT_ASSERT(v[0] == '_');
		CPPUNIT_ASSERT(v[1] == '.');
		CPPUNIT_ASSERT(v[2] == '.');
		CPPUNIT_ASSERT(v[3] == '_');
		v = game.lookSurrounding(0,7);
		CPPUNIT_ASSERT(v[0] == '.');
		CPPUNIT_ASSERT(v[1] == '_');
		CPPUNIT_ASSERT(v[2] == '_');
		CPPUNIT_ASSERT(v[3] == '.');
		v = game.lookSurrounding(7,7);
		CPPUNIT_ASSERT(v[0] == '.');
		CPPUNIT_ASSERT(v[1] == '.');
		CPPUNIT_ASSERT(v[2] == '_');
		CPPUNIT_ASSERT(v[3] == '_');
	}

	void test_Game_lookSurrounding_3() {
		vector<char> v;
		Game game(9,9);
		game.addCreature(Creature(Food(), EAST), 'f', 4, 4);
		game.addCreature(Creature(Rover(), SOUTH), 'r', 3, 4);
		game.addCreature(Creature(Rover(), EAST), 'r', 4, 3);
		game.addCreature(Creature(Rover(), NORTH), 'r', 5, 4);
		game.addCreature(Creature(Rover(), WEST), 'r', 4, 5);
		v = game.lookSurrounding(4,4);
		CPPUNIT_ASSERT(v[0] == 'r');
		CPPUNIT_ASSERT(v[1] == 'r');
		CPPUNIT_ASSERT(v[2] == 'r');
		CPPUNIT_ASSERT(v[3] == 'r');
	}

	// -------------
	// test_Game_hop
	// -------------

	void test_Game_hop_1() {
		Game game(8,8);
		game.addCreature(Creature(Food(), EAST), 'f', 0, 0);
		game.addCreature(Creature(Hopper(), NORTH), 'h', 3, 3);
		game.addCreature(Creature(Hopper(), EAST), 'h', 3, 4);
		game.addCreature(Creature(Hopper(), SOUTH), 'h', 4, 4);
		game.addCreature(Creature(Hopper(), WEST), 'h', 4, 3);
		game.addCreature(Creature(Food(), NORTH), 'f', 7, 7);

		CPPUNIT_ASSERT(game._grid[3][3] == 1);
		CPPUNIT_ASSERT(game._charGrid[3][3] == 'h');
		game.hop(3,3, NORTH);
		CPPUNIT_ASSERT(game._grid[3][3] == -1);
		CPPUNIT_ASSERT(game._charGrid[3][3] == '.');
		CPPUNIT_ASSERT(game._grid[2][3] == 1);
		CPPUNIT_ASSERT(game._charGrid[2][3] == 'h');

		CPPUNIT_ASSERT(game._grid[3][4] == 2);
		CPPUNIT_ASSERT(game._charGrid[3][4] == 'h');
		game.hop(3,4, EAST);
		CPPUNIT_ASSERT(game._grid[3][4] == -1);
		CPPUNIT_ASSERT(game._charGrid[3][4] == '.');
		CPPUNIT_ASSERT(game._grid[3][5] == 2);
		CPPUNIT_ASSERT(game._charGrid[3][5] == 'h');

		CPPUNIT_ASSERT(game._grid[4][4] == 3);
		CPPUNIT_ASSERT(game._charGrid[4][4] == 'h');
		game.hop(4,4, SOUTH);
		CPPUNIT_ASSERT(game._grid[4][4] == -1);
		CPPUNIT_ASSERT(game._charGrid[4][4] == '.');
		CPPUNIT_ASSERT(game._grid[5][4] == 3);
		CPPUNIT_ASSERT(game._charGrid[5][4] == 'h');

		CPPUNIT_ASSERT(game._grid[4][3] == 4);
		CPPUNIT_ASSERT(game._charGrid[4][3] == 'h');
		game.hop(4,3, WEST);
		CPPUNIT_ASSERT(game._grid[4][3] == -1);
		CPPUNIT_ASSERT(game._charGrid[4][3] == '.');
		CPPUNIT_ASSERT(game._grid[4][2] == 4);
		CPPUNIT_ASSERT(game._charGrid[4][2] == 'h');
	}

	void test_Game_hop_2() {
		Game game(8,8);
		game.addCreature(Creature(Hopper(), NORTH), 'h', 0, 0);
		game.addCreature(Creature(Hopper(), NORTH), 'h', 0, 7);
		game.addCreature(Creature(Hopper(), SOUTH), 'h', 7, 0);
		game.addCreature(Creature(Hopper(), SOUTH), 'h', 7, 7);

		CPPUNIT_ASSERT(game._grid[0][0] == 0);
		CPPUNIT_ASSERT(game._charGrid[0][0] == 'h');
		game.hop(0,0, NORTH);
		CPPUNIT_ASSERT(game._grid[0][0] == 0);
		CPPUNIT_ASSERT(game._charGrid[0][0] == 'h');

		CPPUNIT_ASSERT(game._grid[0][7] == 1);
		CPPUNIT_ASSERT(game._charGrid[0][7] == 'h');
		game.hop(0,7, NORTH);
		CPPUNIT_ASSERT(game._grid[0][7] == 1);
		CPPUNIT_ASSERT(game._charGrid[0][7] == 'h');

		CPPUNIT_ASSERT(game._grid[7][0] == 2);
		CPPUNIT_ASSERT(game._charGrid[7][0] == 'h');
		game.hop(7,0, SOUTH);
		CPPUNIT_ASSERT(game._grid[7][0] == 2);
		CPPUNIT_ASSERT(game._charGrid[7][0] == 'h');

		CPPUNIT_ASSERT(game._grid[7][7] == 3);
		CPPUNIT_ASSERT(game._charGrid[7][7] == 'h');
		game.hop(0,7, SOUTH);
		CPPUNIT_ASSERT(game._grid[7][7] == 3);
		CPPUNIT_ASSERT(game._charGrid[7][7] == 'h');
	}

	void test_Game_hop_3() {
		Game game(10,1);
		game.addCreature(Creature(Hopper(), NORTH), 'h', 9, 0);
		for(int i = 9; i > 0; i--) {
			game.hop(i,0,NORTH);
			CPPUNIT_ASSERT(game._grid[i-1][0] == 0);
			CPPUNIT_ASSERT(game._charGrid[i-1][0] == 'h');
			CPPUNIT_ASSERT(game._grid[i][0] == -1);
			CPPUNIT_ASSERT(game._charGrid[i][0] == '.');
		}
		for(int i = 0; i < 100; ++i) {
			game.hop(0,0,NORTH);
			CPPUNIT_ASSERT(game._grid[0][0] == 0);
			CPPUNIT_ASSERT(game._charGrid[0][0] == 'h');
		}
	}

	// ----------------
	// test_Game_infect
	// ----------------
	void test_Game_infect_1() {
		Game game(2,1);
		game.addCreature(Creature(Food(), SOUTH), 'f', 0, 0);
		game.addCreature(Creature(Trap(), SOUTH), 't', 1, 0);
		game._creatureList[game._grid[1][0]]._programCounter++;
		for(int i = 0; i < 3; ++i) {
			game.infect(0,0, static_cast<Direction>(i));
	  	  	CPPUNIT_ASSERT(game._charGrid[0][0] == 'f');
			CPPUNIT_ASSERT(game._charGrid[1][0] == 't');
			CPPUNIT_ASSERT(game._creatureList[game._grid[0][0]]._species._name == 'f');
			CPPUNIT_ASSERT(game._creatureList[game._grid[1][0]]._species._name == 't');
			CPPUNIT_ASSERT(game._creatureList[game._grid[1][0]]._programCounter == 1);
		}
		game.infect(0,0, SOUTH);
	    CPPUNIT_ASSERT(game._charGrid[0][0] == 'f');
		CPPUNIT_ASSERT(game._charGrid[1][0] == 'f');
		CPPUNIT_ASSERT(game._creatureList[game._grid[0][0]]._species._name == 'f');
		CPPUNIT_ASSERT(game._creatureList[game._grid[1][0]]._species._name == 'f');
		CPPUNIT_ASSERT(game._creatureList[game._grid[1][0]]._programCounter == 0);
		CPPUNIT_ASSERT(game._creatureList[game._grid[0][0]]._species._program.size()
									   == game._creatureList[game._grid[1][0]]._species._program.size());
	}

	void test_Game_infect_2() {
		Game game(10,1);
		
		for(int i = 0; i < 10; i+=2) {
			game.addCreature(Creature(Trap(), SOUTH), 't', i, 0);
		}
		for(int i = 1; i < 10; i+=2) {
			game.addCreature(Creature(Rover(), SOUTH), 'r', i, 0);
		}
		for(int i = 0; i < 10; i+=2) {
			CPPUNIT_ASSERT(game._charGrid[i][0] == 't');
			CPPUNIT_ASSERT(game._charGrid[i+1][0] == 'r');
			CPPUNIT_ASSERT(game._creatureList[game._grid[i][0]]._species._name == 't');
			CPPUNIT_ASSERT(game._creatureList[game._grid[i+1][0]]._species._name == 'r');
			game._creatureList[game._grid[i+1][0]]._programCounter++;
			game.infect(i,0, SOUTH);
		    CPPUNIT_ASSERT(game._charGrid[i][0] == 't');
			CPPUNIT_ASSERT(game._charGrid[i+1][0] == 't');
			CPPUNIT_ASSERT(game._creatureList[game._grid[i][0]]._species._name == 't');
			CPPUNIT_ASSERT(game._creatureList[game._grid[i+1][0]]._species._name == 't');
			CPPUNIT_ASSERT(game._creatureList[game._grid[i+1][0]]._programCounter == 0);
		}
	}

	void test_Game_infect_3() {
		ostringstream w1, w2, w3, w4;
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
		game.infect(1,1, NORTH);
		game.print(w1);
		game.infect(1,1, WEST);
		game.print(w2);
		game.infect(1,1, EAST);
		game.print(w3);
		game.infect(1,1, SOUTH);
		game.print(w4);
		CPPUNIT_ASSERT(w1.str() == "Turn = 0.\n  012\n0 frf\n1 frf\n2 fff\n\n");
		CPPUNIT_ASSERT(w2.str() == "Turn = 0.\n  012\n0 frf\n1 rrf\n2 fff\n\n");
		CPPUNIT_ASSERT(w3.str() == "Turn = 0.\n  012\n0 frf\n1 rrr\n2 fff\n\n");
		CPPUNIT_ASSERT(w4.str() == "Turn = 0.\n  012\n0 frf\n1 rrr\n2 frf\n\n");
		CPPUNIT_ASSERT(game._creatureList[game._grid[1][0]]._species._name == 'r');
		CPPUNIT_ASSERT(game._creatureList[game._grid[1][0]]._programCounter == 0);
		CPPUNIT_ASSERT(game._creatureList[game._grid[0][1]]._species._name == 'r');
		CPPUNIT_ASSERT(game._creatureList[game._grid[0][1]]._programCounter == 0);
		CPPUNIT_ASSERT(game._creatureList[game._grid[1][2]]._species._name == 'r');
		CPPUNIT_ASSERT(game._creatureList[game._grid[1][2]]._programCounter == 0);
		CPPUNIT_ASSERT(game._creatureList[game._grid[2][1]]._species._name == 'r');
		CPPUNIT_ASSERT(game._creatureList[game._grid[2][1]]._programCounter == 0);
	}

	// ------------------
	// test_Game_scan
	// ------------------
	void test_Game_scan_1() {
		Game game(8,8);
		game.addCreature(Creature(Hopper(), SOUTH), 'h', 0, 0);
		game.scan();
		CPPUNIT_ASSERT(game._creatureOrdering[0] == 0);
		CPPUNIT_ASSERT(game._positions[0].first == 0);
		CPPUNIT_ASSERT(game._positions[0].second == 0);
		game.hop(0,0,SOUTH);
		game.scan();
		CPPUNIT_ASSERT(game._creatureOrdering[0] == 0);
		CPPUNIT_ASSERT(game._positions[0].first == 1);
		CPPUNIT_ASSERT(game._positions[0].second == 0);
	}

	void test_Game_scan_2() {
		Game game(8,8);
		game.addCreature(Creature(Food(), EAST), 'f', 0, 0);
		game.addCreature(Creature(Hopper(), SOUTH), 'h', 0, 1);
		game.addCreature(Creature(Hopper(), EAST), 'f', 0, 2);
		game.scan();
		CPPUNIT_ASSERT(game._creatureOrdering[0] == 0);
		CPPUNIT_ASSERT(game._creatureOrdering[1] == 1);
		CPPUNIT_ASSERT(game._creatureOrdering[2] == 2);
		CPPUNIT_ASSERT(game._positions[0].first == 0);
		CPPUNIT_ASSERT(game._positions[0].second == 0);
		CPPUNIT_ASSERT(game._positions[1].first == 0);
		CPPUNIT_ASSERT(game._positions[1].second == 1);
		CPPUNIT_ASSERT(game._positions[2].first == 0);
		CPPUNIT_ASSERT(game._positions[2].second == 2);
		game.hop(0,1,SOUTH);
		game.scan();
		CPPUNIT_ASSERT(game._creatureOrdering[0] == 0);
		CPPUNIT_ASSERT(game._creatureOrdering[1] == 2);
		CPPUNIT_ASSERT(game._creatureOrdering[2] == 1);
		CPPUNIT_ASSERT(game._positions[0].first == 0);
		CPPUNIT_ASSERT(game._positions[0].second == 0);
		CPPUNIT_ASSERT(game._positions[1].first == 1);
		CPPUNIT_ASSERT(game._positions[1].second == 1);
		CPPUNIT_ASSERT(game._positions[2].first == 0);
		CPPUNIT_ASSERT(game._positions[2].second == 2);
	}

	void test_Game_scan_3() {
		Game game(8,8);
		game.addCreature(Creature(Hopper(), EAST), 'f', 0, 0);
		game.addCreature(Creature(Hopper(), SOUTH), 'h', 0, 1);
		game.addCreature(Creature(Hopper(), EAST), 'f', 0, 2);
		game.scan();
		CPPUNIT_ASSERT(game._creatureOrdering[0] == 0);
		CPPUNIT_ASSERT(game._creatureOrdering[1] == 1);
		CPPUNIT_ASSERT(game._creatureOrdering[2] == 2);
		CPPUNIT_ASSERT(game._positions[0].first == 0);
		CPPUNIT_ASSERT(game._positions[0].second == 0);
		CPPUNIT_ASSERT(game._positions[1].first == 0);
		CPPUNIT_ASSERT(game._positions[1].second == 1);
		CPPUNIT_ASSERT(game._positions[2].first == 0);
		CPPUNIT_ASSERT(game._positions[2].second == 2);
		game.hop(0,1,SOUTH);
		game.scan();
		CPPUNIT_ASSERT(game._creatureOrdering[0] == 0);
		CPPUNIT_ASSERT(game._creatureOrdering[1] == 2);
		CPPUNIT_ASSERT(game._creatureOrdering[2] == 1);
		CPPUNIT_ASSERT(game._positions[0].first == 0);
		CPPUNIT_ASSERT(game._positions[0].second == 0);
		CPPUNIT_ASSERT(game._positions[1].first == 1);
		CPPUNIT_ASSERT(game._positions[1].second == 1);
		CPPUNIT_ASSERT(game._positions[2].first == 0);
		CPPUNIT_ASSERT(game._positions[2].second == 2);
		game.hop(0,0, EAST);
		game.hop(1,1, SOUTH);
		game.hop(0,2, EAST);
		game.scan();
		CPPUNIT_ASSERT(game._creatureOrdering[0] == 0);
		CPPUNIT_ASSERT(game._creatureOrdering[1] == 2);
		CPPUNIT_ASSERT(game._creatureOrdering[2] == 1);
		CPPUNIT_ASSERT(game._positions[0].first == 0);
		CPPUNIT_ASSERT(game._positions[0].second == 1);
		CPPUNIT_ASSERT(game._positions[1].first == 2);
		CPPUNIT_ASSERT(game._positions[1].second == 1);
		CPPUNIT_ASSERT(game._positions[2].first == 0);
		CPPUNIT_ASSERT(game._positions[2].second == 3);
	}

	// ------------------
	// test_Game_simulate
	// ------------------
	void test_Game_simulate_1() {
		ostringstream w;
		Game game(8,8);
		game.addCreature(Creature(Food(), EAST), 'f', 0, 0);
		game.addCreature(Creature(Hopper(), NORTH), 'h', 3, 3);
		game.addCreature(Creature(Hopper(), EAST), 'h', 3, 4);
		game.addCreature(Creature(Hopper(), SOUTH), 'h', 4, 4);
		game.addCreature(Creature(Hopper(), WEST), 'h', 4, 3);
		game.addCreature(Creature(Food(), NORTH), 'f', 7, 7);
		game.simulate(1, w, 1);
		CPPUNIT_ASSERT(w.str() ==
		"Turn = 0.\n  01234567\n0 f.......\n1 ........\n2 ........\n3 ...hh...\n4 ...hh...\n5 ........\n6 ........\n7 .......f\n\nTurn = 1.\n  01234567\n0 f.......\n1 ........\n2 ...h....\n3 .....h..\n4 ..h.....\n5 ....h...\n6 ........\n7 .......f\n\n");
	}

	void test_Game_simulate_2() {
		ostringstream w;
		Game game(8,8);
		game.addCreature(Creature(Food(), EAST), 'f', 0, 0);
		game.addCreature(Creature(Hopper(), NORTH), 'h', 3, 3);
		game.addCreature(Creature(Hopper(), EAST), 'h', 3, 4);
		game.addCreature(Creature(Hopper(), SOUTH), 'h', 4, 4);
		game.addCreature(Creature(Hopper(), WEST), 'h', 4, 3);
		game.addCreature(Creature(Food(), NORTH), 'f', 7, 7);
		game.simulate(3, w, 1);
		CPPUNIT_ASSERT(w.str() ==
		"Turn = 0.\n  01234567\n0 f.......\n1 ........\n2 ........\n3 ...hh...\n4 ...hh...\n5 ........\n6 ........\n7 .......f\n\nTurn = 1.\n  01234567\n0 f.......\n1 ........\n2 ...h....\n3 .....h..\n4 ..h.....\n5 ....h...\n6 ........\n7 .......f\n\nTurn = 2.\n  01234567\n0 f.......\n1 ...h....\n2 ........\n3 ......h.\n4 .h......\n5 ........\n6 ....h...\n7 .......f\n\nTurn = 3.\n  01234567\n0 f..h....\n1 ........\n2 ........\n3 .......h\n4 h.......\n5 ........\n6 ........\n7 ....h..f\n\n");
	}
	
	void test_Game_simulate_3() {
		srand(0);
		ostringstream w;
		Game game(7,9);
		game.addCreature(Creature(Trap(), SOUTH), 't', 0, 0);
		game.addCreature(Creature(Hopper(), EAST), 'h', 3, 2);
		game.addCreature(Creature(Rover(), NORTH), 'r', 5, 4);
		game.addCreature(Creature(Trap(), WEST), 't', 6, 8);
		game.simulate(5, w, 1);
		CPPUNIT_ASSERT(w.str() == 
		"Turn = 0.\n  012345678\n0 t........\n1 .........\n2 .........\n3 ..h......\n4 .........\n5 ....r....\n6 ........t\n\nTurn = 1.\n  012345678\n0 t........\n1 .........\n2 .........\n3 ...h.....\n4 ....r....\n5 .........\n6 ........t\n\nTurn = 2.\n  012345678\n0 t........\n1 .........\n2 .........\n3 ....r....\n4 ....r....\n5 .........\n6 ........t\n\nTurn = 3.\n  012345678\n0 t........\n1 .........\n2 .........\n3 ....rr...\n4 .........\n5 .........\n6 ........t\n\nTurn = 4.\n  012345678\n0 t........\n1 .........\n2 ....r....\n3 ......r..\n4 .........\n5 .........\n6 ........t\n\nTurn = 5.\n  012345678\n0 t........\n1 ....r....\n2 .........\n3 .......r.\n4 .........\n5 .........\n6 ........t\n\n");
		}

    // -----
    // suite
    // -----
    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(test_Species_constructor_1);
    CPPUNIT_TEST(test_Species_constructor_2);
    CPPUNIT_TEST(test_Species_constructor_3);
    CPPUNIT_TEST(test_Species_addInstruction_1);
    CPPUNIT_TEST(test_Species_addInstruction_2);
    CPPUNIT_TEST(test_Species_addInstruction_3);
    CPPUNIT_TEST(test_Species_execute_1);
    CPPUNIT_TEST(test_Species_execute_2);
    CPPUNIT_TEST(test_Species_execute_3);
    CPPUNIT_TEST(test_Species_isAction_1);
    CPPUNIT_TEST(test_Species_isAction_2);
    CPPUNIT_TEST(test_Species_isAction_3);
    CPPUNIT_TEST(test_Food_constructor_1);
    CPPUNIT_TEST(test_Food_constructor_2);
    CPPUNIT_TEST(test_Food_constructor_3);
    CPPUNIT_TEST(test_Hopper_constructor_1);
    CPPUNIT_TEST(test_Hopper_constructor_2);
    CPPUNIT_TEST(test_Hopper_constructor_3);
    CPPUNIT_TEST(test_Rover_constructor_1);
    CPPUNIT_TEST(test_Rover_constructor_2);
    CPPUNIT_TEST(test_Rover_constructor_3);
    CPPUNIT_TEST(test_Trap_constructor_1);
    CPPUNIT_TEST(test_Trap_constructor_2);
    CPPUNIT_TEST(test_Trap_constructor_3);
    CPPUNIT_TEST(test_Best_constructor_1);
    CPPUNIT_TEST(test_Best_constructor_2);
    CPPUNIT_TEST(test_Best_constructor_3);
    CPPUNIT_TEST(test_Creature_constructor_1);
    CPPUNIT_TEST(test_Creature_constructor_2);
    CPPUNIT_TEST(test_Creature_constructor_3);
    CPPUNIT_TEST(test_Creature_run_1);
    CPPUNIT_TEST(test_Creature_run_2);
    CPPUNIT_TEST(test_Creature_run_3);
    CPPUNIT_TEST(test_Creature_turnLeft_1);
    CPPUNIT_TEST(test_Creature_turnLeft_2);
    CPPUNIT_TEST(test_Creature_turnLeft_3);
    CPPUNIT_TEST(test_Creature_turnLeft_4);
    CPPUNIT_TEST(test_Creature_turnRight_1);
    CPPUNIT_TEST(test_Creature_turnRight_2);
    CPPUNIT_TEST(test_Creature_turnRight_3);
    CPPUNIT_TEST(test_Creature_turnRight_4);
    CPPUNIT_TEST(test_Creature_infect_1);
    CPPUNIT_TEST(test_Creature_infect_2);
    CPPUNIT_TEST(test_Creature_infect_3);
    CPPUNIT_TEST(test_Game_constructor_1);
    CPPUNIT_TEST(test_Game_constructor_2);
    CPPUNIT_TEST(test_Game_constructor_3);
    CPPUNIT_TEST(test_Game_constructor_4);
    CPPUNIT_TEST(test_Game_addCreature_1);
    CPPUNIT_TEST(test_Game_addCreature_2);
    CPPUNIT_TEST(test_Game_addCreature_3);
    CPPUNIT_TEST(test_Game_print_1);
    CPPUNIT_TEST(test_Game_print_2);
    CPPUNIT_TEST(test_Game_print_3);
    CPPUNIT_TEST(test_Game_print_4);
    CPPUNIT_TEST(test_Game_lookSurrounding_1);
    CPPUNIT_TEST(test_Game_lookSurrounding_2);
    CPPUNIT_TEST(test_Game_lookSurrounding_3);
    CPPUNIT_TEST(test_Game_hop_1);
    CPPUNIT_TEST(test_Game_hop_2);
    CPPUNIT_TEST(test_Game_hop_3);
    CPPUNIT_TEST(test_Game_infect_1);
    CPPUNIT_TEST(test_Game_infect_2);
    CPPUNIT_TEST(test_Game_infect_3);
    CPPUNIT_TEST(test_Game_scan_1);
    CPPUNIT_TEST(test_Game_scan_2);
    CPPUNIT_TEST(test_Game_scan_3);
    CPPUNIT_TEST(test_Game_simulate_1);
    CPPUNIT_TEST(test_Game_simulate_2);
    CPPUNIT_TEST(test_Game_simulate_3);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
