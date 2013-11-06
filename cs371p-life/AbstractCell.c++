// #include <iostream>
// #include "AbstractCell.h"

// using namespace std;

// // AbstractCell constructor
// AbstractCell::AbstractCell(int r, int c, int s) {
// 	if(s == 0 || s == 1){
// 		alive = s;
// 		row = r;
// 		col = c;
// 	}else{
// 		//cout << "ERROR: status must be 0 or 1\n";
// 	    alive = -1;
// 		row = -1;
// 		col = -1;
// 	}
// }

// AbstractCell& AbstractCell::operator = (const AbstractCell& that) {
// 	alive = that.alive;
//     row = that.row;
//     col = that.col;
//     return *this;
// }

// char AbstractCell::type() {
// 	return cell_type;
// }

// int AbstractCell::get_row() {
// 	return row;	
// }

// int AbstractCell::get_col() {
// 	return col;	
// }

// int AbstractCell::get_status() {
// 	return alive;	
// }

// void AbstractCell::set_type(char type) {
// 	cell_type = type;	
// }

// void AbstractCell::change_status() {
// 	alive = ((alive+1) % 2);
// }

