#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <cstdlib>	// rand
#include <stdexcept>

using namespace std;

enum instructionType {HOP, LEFT, RIGHT, INFECT, IF_EMPTY, IF_WALL, IF_RANDOM, IF_ENEMY, GO};
enum Direction {WEST, NORTH, EAST, SOUTH};

class Species {
	private:
		char _name;
		vector<pair<instructionType, int>> _program;
		
	public:
        Species();
        Species(char);
        void addInstruction(instructionType, int data = -1);
        int execute(int, char);
        bool isAction(int);
};

class Food : public Species {
	public:
    Food();
};

class Hopper : public Species {
	public:
    Hopper();
};

class Rover : public Species {
	public:
    Rover();
};

class Trap : public Species {
	public:
    Trap();
};

class Best : public Species {
	public:
    Best();
};

class Creature {
	private:
		Species _species;
		Direction _direction;
		int _programCounter;
	
	public:
        Creature(Species, Direction);
        pair<instructionType, Direction> run(vector<char>);
        void turnLeft();
        void turnRight();
        void infect(Creature&);
};

class Game {
	private:
		int _rows, _cols, _nextIndex, _turnNum;
		vector<vector<int>> _grid;
		vector<vector<char>> _charGrid;
		vector<Creature> _creatureList;
		vector<int> _creatureOrdering;
		vector<pair<int,int>> _positions;
		
	public:
        Game(int, int);
        void addCreature(Creature, char, int, int);
        void print(ostream&);
        vector<char> lookSurrounding(int, int);
        void hop(int, int, Direction);
        void infect(int, int, Direction);
	void scan();
        void simulate(int, ostream&, int);
};
