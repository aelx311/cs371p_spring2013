// #include "Life.h"
// #include "ConwayCell.h"

// ConwayCell::ConwayCell(int r, int c, int s):
//     AbstractCell(r,c,s) {
//     AbstractCell::set_type(CONWAY_CELL);
// }

// char ConwayCell::to_char() {
//     if(get_status() == ALIVE){
//         return '*';
//     }else if(get_status() == DEAD){
//         return '.';
//     }else{
//         return 'E';
//     }
// }

// char ConwayCell::type() {
//     return AbstractCell::type();
// }

// int ConwayCell::get_row() {
//     return AbstractCell::get_row();
// }

// int ConwayCell::get_col() {
//     return AbstractCell::get_col();
// }

// int ConwayCell::get_status() {
//     return  AbstractCell::get_status();
// }

// void ConwayCell::change_status() {
//     if(get_status()==-1){
//             //cout << "ERROR, can't change invalid status\n";
//     }else{     
//         AbstractCell::change_status();
//     }
// }

// void ConwayCell::add_age() {
//     // do nothing
// }
