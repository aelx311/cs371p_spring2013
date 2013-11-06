/**
 * Darwin.c++
 */

#include "Darwin.h"


/**
 * the Species default constructor; not intended for any use
 * besides copying. Initializes fields to dummy variables
 */
Species::Species() {
	_name = '.';
}

/**
 * the Species char constructor; called by subclasses
 * @param name the char indicating the type of the Species
 */
Species::Species(char name) {
	_name = name;
}

/**
 * adds an instruction to the Species' instruction list
 * @param instruction the instructionType of the instruction
 * @param data the new program counter or -1 if the instruction is an action
 */
void Species::addInstruction(instructionType instruction, int data) {
	if((instruction == HOP && data > 0) || (instruction == LEFT && data > 0) 
										|| (instruction == RIGHT && data > 0) || (instruction == INFECT && data > 0)) {
		data = -1;
	} else if ((instruction == IF_EMPTY) || (instruction == IF_WALL) || (instruction == IF_RANDOM) || (instruction == IF_ENEMY) || (instruction == GO)) {
		if (data < 0) {
			throw invalid_argument("invalid line number specified");
		}
	}
	_program.push_back(make_pair(instruction, data));
}

/**
 * executes the instruction at line pc
 * @param pc the line in the Species' program to be executed
 * @param front the char directly in front of the creature
 * @returns new value of pc or a value indicating the action request
 */
int Species::execute(int pc, char front) {
	assert((pc >= 0) && (pc < (int)_program.size()));
	instructionType instruction = _program[pc].first;
	int new_pc = _program[pc].second;
	// an action is detected; return the instruction type for it
	int result;
	if (new_pc < 0) {
		return instruction;
	} else if(instruction == IF_EMPTY) {
		if(front == '.') {
			result = new_pc;
		} else {
			result = pc + 1;
		}
	} else if(instruction == IF_WALL) {
		if(front == '_') {
			result = new_pc;				
		} else {
			result = pc + 1;				
		}
	} else if(instruction == IF_RANDOM) {
		if(rand() % 2 != 0) {
			result = new_pc;				
		} else {
			result = pc + 1;				
		}
	} else if(instruction == IF_ENEMY) {
	if(front != '.' && front != '_' && _name != front) {
			result = new_pc;
		} else {
			result = pc + 1;				
		}
	} else {
		assert(instruction == GO);
		result = new_pc;
	}
	assert((result >= 0) && (result < (int)_program.size()));
	return result;
}

/**
 * @param pc a line in the Species' program
 * @returns true if the line of the program is an action
 */
bool Species::isAction(int pc) {
	assert((pc >= 0) && (pc < static_cast<signed int>(_program.size())));
	return (_program[pc].first == HOP) || (_program[pc].first == LEFT) || (_program[pc].first == RIGHT) || (_program[pc].first == INFECT);					
}

/**
 * The Food constructor. Sets its species name to f
 */
Food::Food() : Species('f') {
	addInstruction(LEFT);
	addInstruction(GO, 0);
}

/**
 * The Hopper constructor. Sets its species name to h
 */
Hopper::Hopper() : Species('h') {
	addInstruction(HOP);
	addInstruction(GO, 0);
}

/**
 * The Rover constructor. Sets its species name to r
 */
Rover::Rover() : Species('r') {
	addInstruction(IF_ENEMY, 9);
	addInstruction(IF_EMPTY, 7);
	addInstruction(IF_RANDOM, 5);
	addInstruction(LEFT);
	addInstruction(GO, 0);
	addInstruction(RIGHT);
	addInstruction(GO, 0);
	addInstruction(HOP);
	addInstruction(GO, 0);
	addInstruction(INFECT);
	addInstruction(GO, 0);
}

/**
 * The Trap constructor. Sets its species name to t
 */
Trap::Trap() : Species('t') {
	addInstruction(IF_ENEMY, 3);
	addInstruction(LEFT);
	addInstruction(GO, 0);
	addInstruction(INFECT);
	addInstruction(GO, 0);
}

/**
 * The Best constructor. Sets its species name to b
 */
Best::Best() : Species('b') {
	addInstruction(IF_ENEMY, 10);
	addInstruction(IF_EMPTY, 8);
	addInstruction(IF_RANDOM, 12);
	addInstruction(IF_RANDOM, 4);
	addInstruction(LEFT);
	addInstruction(GO, 0);
	addInstruction(RIGHT);
	addInstruction(GO, 0);
	addInstruction(HOP);
	addInstruction(GO, 0);
	addInstruction(INFECT);
	addInstruction(GO, 0);
	addInstruction(IF_ENEMY, 15);
	addInstruction(LEFT);
	addInstruction(GO, 0);
	addInstruction(INFECT);
	addInstruction(GO, 0);
}

/**
 * the Creature constructor
 * @param species the Species of the Creature
 * @param direction the Direction the Creature is facing
 */
Creature::Creature(Species species, Direction direction) {
	_species = species;
	_direction = direction;
	_programCounter = 0;
}

/**
 * runs the Creature's turn until an action instruction is reached
 * @param surroundings the chars in the four cardinal directions around the Creature
 * @return pair of instructionType request and Creature's Direction to caller
 */
pair<instructionType, Direction> Creature::run(vector<char> surroundings) {
	assert((int)surroundings.size() == 4);
	char front = surroundings[_direction];
	int last_pc = _programCounter;
	while(!_species.isAction(_programCounter)) {
		last_pc = _species.execute(_programCounter, front);
		_programCounter = last_pc;
		assert(_programCounter >= 0);
	}
	return make_pair(static_cast<instructionType>(_species.execute(_programCounter++, front)), _direction);
}
		
/**
 * change Creature's direction to face left from its current direction
 */
void Creature::turnLeft() {
	if(_direction == NORTH) {
		_direction = WEST;
	} else if(_direction == WEST) {
		_direction = SOUTH;
	} else if(_direction == SOUTH) {
		_direction = EAST;
	} else {
		_direction = NORTH;
	}
}

/**
 * change Creature's direction to face right from its current direction
 */
void Creature::turnRight() {
	if(_direction == NORTH) {
		_direction = EAST;
	} else if(_direction == EAST) {
		_direction = SOUTH;
	} else if(_direction == SOUTH) {
		_direction = WEST;
	} else {
		_direction = NORTH;
	}
}

/**
 * @param c Creature to be infected
 * changes a Creature so it becomes its own species
 */
void Creature::infect(Creature& c) {
	assert(&c._species != &_species);
	c = Creature(Species(_species), c._direction);
}


/**
  * the Game constructor; initializes the game board
  * @param rows the number of rows of the game board
  * @param cols the number of columns of the game board
  */
Game::Game(int rows, int cols) {
	assert(rows > 0);
	assert(cols > 0);
	_rows = rows;
	_cols = cols;
	_nextIndex = 0;
	_turnNum = 0;
	for(int r = 0; r < rows; ++r) {
		_grid.push_back(vector<int>(cols, -1));
		_charGrid.push_back(vector<char>(cols, '.'));
	}
}

/**
  * adds a Creature to the Game's creature list
  * @param creature the Creature object to be added to the list
  * @param x the x-position of the new Creature
  * @param y the y-position of the new Creature
  */
void Game::addCreature(Creature creature, char name, int x, int y) {
	if(x > _rows || y > _cols || x < 0 || y < 0)
		throw out_of_range("out_of_range");
	_creatureList.push_back(creature);
	assert(_grid[x][y] == -1);
	_grid[x][y] = _nextIndex++;
	_charGrid[x][y] = name;
	_positions.push_back(make_pair(x,y));
}

/**
  * prints the current state of the board to the ostream argument
  * @param o the ostream to write the current state of the board to
  */
void Game::print(ostream& o) {
	o << "Turn = " << _turnNum <<  "."<< endl;
	o << "  ";
	for(int c = 0; c < _cols; ++c) {
		o << c%10;
	}
	o << endl;
	for(int r = 0; r < _rows; ++r) {
		o << r%10 << " ";
		for(int c = 0; c < _cols; ++c) {
			o << _charGrid[r][c];
		}
		o << endl;
	}
	o << endl;
}
		
/**
 * @param x the x-position of the Creature
 * @param y the y-position of the Creature
 * @returns vector of chars indicating the objects surrounding the Creature in all 4 directions
 */
vector<char> Game::lookSurrounding(int r, int c) {
	assert(r >= 0 && r < _rows);
	assert(c >= 0 && c < _cols);
	vector<char> surroundings;

	// WEST
	if(c-1 >= 0) {
		surroundings.push_back(_charGrid[r][c-1]);
	}
	else {
		surroundings.push_back('_');
	}

	// NORTH
	if(r-1 >= 0) {
		// push the character on
		surroundings.push_back(_charGrid[r-1][c]);
	} else {
		// there is a wall
		surroundings.push_back('_');
	}

	// EAST
	if(c+1 < _cols) {
		surroundings.push_back(_charGrid[r][c+1]);
	} else {
		surroundings.push_back('_');
	}

	// SOUTH
	if(r+1 < _rows) {
		surroundings.push_back(_charGrid[r+1][c]);
	} else {
		surroundings.push_back('_');
	}
		assert(surroundings.size() == 4);

	assert((int)surroundings.size() == 4);
	return surroundings;
}

/**
 * executes the hop instruction
 */
void Game::hop(int r, int c, Direction creature_direction) {
	assert(r >= 0 && r < _rows);
	assert(c >= 0 && c < _cols);
	assert(_grid[r][c] >= 0);
	if(creature_direction == WEST) {
		if((c-1 >= 0) && (_grid[r][c-1] < 0)) {
			_grid[r][c-1] = _grid[r][c];
			_grid[r][c] = -1;
			_charGrid[r][c-1] = _charGrid[r][c];
			_charGrid[r][c] = '.';
		}
	} else if(creature_direction == NORTH) {
		if((r-1 >= 0) && (_grid[r-1][c] < 0)) {
			_grid[r-1][c] = _grid[r][c];
			_grid[r][c] = -1;
			_charGrid[r-1][c] = _charGrid[r][c];
			_charGrid[r][c] = '.';
		}
	} else if(creature_direction == EAST) {
		if((c+1 < _cols) && (_grid[r][c+1] < 0)) {
			_grid[r][c+1] = _grid[r][c];
			_grid[r][c] = -1;
			_charGrid[r][c+1] = _charGrid[r][c];
			_charGrid[r][c] = '.';
		}
	} else {
		if((r+1 < _rows) && (_grid[r+1][c] < 0)) {
			_grid[r+1][c] = _grid[r][c];
			_grid[r][c] = -1;
			_charGrid[r+1][c] = _charGrid[r][c];
			_charGrid[r][c] = '.';
		}
	}
}

/**
 * executes the infect instruction
 */
void Game::infect(int r, int c, Direction creature_direction) {
	assert(r >= 0 && r < _rows);
	assert(c >= 0 && c < _cols);
	assert(_grid[r][c] >= 0);

	char name = _charGrid[r][c];
	if(creature_direction == WEST) {
		if((c-1 >= 0) && (_grid[r][c-1] != '.') && (_charGrid[r][c] != _charGrid[r][c-1])) {
			_creatureList[_grid[r][c]].infect(_creatureList[_grid[r][c-1]]);
			_charGrid[r][c-1] = name;
		}
	} else if(creature_direction == NORTH) {
		if((r-1 >= 0) && (_grid[r-1][c] != '.') && (_charGrid[r][c] != _charGrid[r-1][c])) {
			_creatureList[_grid[r][c]].infect(_creatureList[_grid[r-1][c]]);
			_charGrid[r-1][c] = name;
		}
	} else if(creature_direction == EAST) {
		if((c+1 < _cols) && (_grid[r][c+1] != '.') && (_charGrid[r][c] != _charGrid[r][c+1])) {
			_creatureList[_grid[r][c]].infect(_creatureList[_grid[r][c+1]]);
			_charGrid[r][c+1] = name;
		}
	} else {
		assert(creature_direction == SOUTH);
		if((r+1 < _rows) && (_grid[r+1][c] != '.') && (_charGrid[r][c] != _charGrid[r+1][c])) {
			_creatureList[_grid[r][c]].infect(_creatureList[_grid[r+1][c]]);
			_charGrid[r+1][c] = name;
		}
	}
}

/**
 * builds new ordering of Creatures and updates the position list from left-to-right, top-to-bottom
 */
void Game::scan() {
	_creatureOrdering = vector<int>();
	for(int r = 0; r < _rows; ++r) {
		for(int c = 0; c < _cols; ++c) {
			if(_grid[r][c] >= 0) {
				_creatureOrdering.push_back(_grid[r][c]);
				_positions[_grid[r][c]] = make_pair(r,c);
			}
		}
	}
}

/**
 * runs the Darwin game for n turns; writes to the ostream after every turn
 * @param n the number of turns to run the game
 * @param o ostream to be written to
 * @param every the number of turns after which the game should write its current state to the ostream
 */
void Game::simulate(int n, ostream& o, int every) {
	assert(_creatureList.size() > 0);
	assert(n > 0);
	assert(every > 0);
	assert(every <= n);
	for(int t = 0; t <= n; ++t) {
		if(t % every == 0) {
			print(o);
		}
		scan();
		for(int i = 0; i < static_cast<int>(_creatureOrdering.size()); ++i) {
			int next_creature = _creatureOrdering[i];
			int r = _positions[next_creature].first;
			int c = _positions[next_creature].second;
			pair<instructionType, Direction> request = _creatureList[next_creature].run(lookSurrounding(r, c));
			// perform action based on the request received - HOP, LEFT, RIGHT, INFECT
			instructionType action = request.first;
			Direction creature_direction = request.second;
			if(action == LEFT) {
				_creatureList[next_creature].turnLeft();	
			} else if(action == RIGHT) {
				_creatureList[next_creature].turnRight();	
			} else if(action == HOP) {
				// check if it is safe to hop (no wall in front of creature, no enemies, etc.) and hop; else ignore
				hop(r, c, creature_direction);
			} else {
				// check if there is an enemy in front of the creature; if there is an enemy, infect it and replace it with an instance
				// of the current creature's class
				infect(r, c, creature_direction);
			}
		}
		++_turnNum;
	}
}
