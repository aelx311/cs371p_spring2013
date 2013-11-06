// #include "Life.h"
// #include "FredkinCell.h"

// FredkinCell::FredkinCell(int r, int c, int s) :
// 	AbstractCell(r,c,s) {
// 	age = 0;
// 	AbstractCell::set_type(FREDKIN_CELL);
// }

// char FredkinCell::to_char() {
// 	if(get_status() == ALIVE){
// 		return (char)(((int)'0')+age);
// 	}else if(get_status() == DEAD){
// 		return '-';
// 	}else{
// 		return 'E';
// 	}
// }

// void FredkinCell::add_age() {
// 	age++;
// }

// char FredkinCell::type() {
// 	return AbstractCell::type();
// }

// int FredkinCell::get_row() {
// 	return AbstractCell::get_row();
// }

// int FredkinCell::get_col(){
// 	return AbstractCell::get_col();
// }

// int FredkinCell::get_status(){
// 	return  AbstractCell::get_status();
// }

// void FredkinCell::change_status(){
// 	if(get_status()==-1){
//                 //cout << "ERROR, can't change invalid status\n";
// 	}else{     
// 		AbstractCell::change_status();
// 	}
// }

// int FredkinCell::get_age() {
// 	return age;
// }

// ConwayCell FredkinCell::mutate(int i, int j) {
// 	return new ConwayCell(i, j, ALIVE);
// }