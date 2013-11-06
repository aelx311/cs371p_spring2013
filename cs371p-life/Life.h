#include <iostream>
#include <vector>
#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"
#include <cstring>

static const char CONWAY_CELL = 'c';
static const char FREDKIN_CELL = 'f';
static const int ALIVE = 1;
static const int DEAD = 0;


using namespace std;

template <typename T>
class Life {

    private: 
        int num_row;
        int num_col;
        int max_row_index;
        int max_col_index;
        int population;
        vector< vector<T> > board;

    public:
        Life(int r, int c, T cell_type) {
            if(r<1 || c<1) {
                cout <<"WARNING: invalid board size!\n";
            }
            num_row = r;
            num_col = c;
            max_row_index = r-1;
            max_col_index = c-1;
            population = 0;
            vector<T> one_row;
            
            for(int j=0; j<num_col; j++){
                one_row.push_back(cell_type);
            }

            for (int i=0; i<num_row; i++) {
                board.push_back(one_row);
            }
       }

        int is_alive(T c){
            return c.get_status();
        }

        bool is_conway_cell(T cell){
            return (cell.type() == 'c');
        }

        bool is_fredkin_cell(T cell) {
            return (cell.type() == 'f');
        }

        int find_neighbor(int row, int col, vector< vector<T> >& board){
            int num_neighbor = 0;

            if(num_row == 1 && num_col == 1){
                return 0;
            }else if(num_row == 1 && num_col == 2){
                if(col == 0){
                    return is_alive(board[0][1]);
                }else{
                    return is_alive(board[0][0]);
                }
            }else if(num_row == 1 && num_col >2){
                if(col == 0){
                    return is_alive(board[0][1]);
                }else if(col == max_col_index){
                    return is_alive(board[0][col-1]);
                }else{
                    return (is_alive(board[row][col-1]) 
                        + is_alive(board[row][col+1]));
                }                
            }else if(num_col == 1 && num_row == 2){
                if(row == 0){
                    return is_alive(board[1][0]);
                }else{
                    return is_alive(board[0][0]);
                }                
            }else if(num_col == 1 && num_row >2){
                if(row == 0){
                    return is_alive(board[1][0]);
                }else if(row == max_row_index){
                    return is_alive(board[row-1][0]);
                }else{
                    return (is_alive(board[row+1][col]) 
                        + is_alive(board[row-1][col]));
                }                
            }

            
            if(row == 0 && col == 0){   //upper left
                num_neighbor+=(is_alive(board[row+1][col]));
                num_neighbor+=(is_alive(board[row][col+1]));
                if(is_conway_cell(board[row][col])){
                    num_neighbor+=(is_alive(board[row+1][col+1]));
                }
            }else if(row == 0 && col == max_col_index){   //upper right
                num_neighbor+=(is_alive(board[row+1][col]));
                num_neighbor+=(is_alive(board[row][col-1]));
                if(is_conway_cell(board[row][col])){
                    num_neighbor+=(is_alive(board[row+1][col-1]));
                }
            }else if(row == max_row_index && col == 0){   //lower left
                num_neighbor+=(is_alive(board[row-1][col]));
                num_neighbor+=(is_alive(board[row][col+1]));
                if(is_conway_cell(board[row][col])){
                    num_neighbor+=(is_alive(board[row-1][col+1]));
                }
            }else if(row == max_row_index && col == max_col_index){ //lower right
                num_neighbor+=(is_alive(board[row-1][col]));
                num_neighbor+=(is_alive(board[row][col-1]));
                if(is_conway_cell(board[row][col])){
                    num_neighbor+=(is_alive(board[row-1][col-1]));
                }
            }else if(row == 0 && (col != 0) && (col != max_col_index) ){  //upper edge, not corner
                num_neighbor+=(is_alive(board[row][col-1]));
                num_neighbor+=(is_alive(board[row][col+1]));
                num_neighbor+=(is_alive(board[row+1][col]));
                if(is_conway_cell(board[row][col])){
                    num_neighbor+=(is_alive(board[row+1][col-1]));
                    num_neighbor+=(is_alive(board[row+1][col+1]));
                }
            }else if(row == max_row_index && (col != 0) && (col != max_col_index)){  //lower edge,not corner
                num_neighbor+=(is_alive(board[row][col-1]));
                num_neighbor+=(is_alive(board[row][col+1]));
                num_neighbor+=(is_alive(board[row-1][col]));
                if(is_conway_cell(board[row][col])){
                    num_neighbor+=(is_alive(board[row-1][col-1]));
                    num_neighbor+=(is_alive(board[row-1][col+1]));
                }
            }else if(col == 0 && row != 0 && row != max_row_index ){        //left edge,not corner
                num_neighbor+=(is_alive(board[row-1][col]));
                num_neighbor+=(is_alive(board[row+1][col]));
                num_neighbor+=(is_alive(board[row][col+1]));
                if(is_conway_cell(board[row][col])){
                    num_neighbor+=(is_alive(board[row-1][col+1]));
                    num_neighbor+=(is_alive(board[row+1][col+1]));
                }                
            }else if(col == max_col_index && row != 0 && row != max_row_index){   //right edge,not corner
                num_neighbor+=(is_alive(board[row-1][col]));
                num_neighbor+=(is_alive(board[row+1][col]));
                num_neighbor+=(is_alive(board[row][col-1]));
                if(is_conway_cell(board[row][col])){
                    num_neighbor+=(is_alive(board[row-1][col-1]));
                    num_neighbor+=(is_alive(board[row+1][col-1]));
                } 
            }else{      //internal cell
                num_neighbor+=(is_alive(board[row][col-1]));
                num_neighbor+=(is_alive(board[row][col+1]));
                num_neighbor+=(is_alive(board[row-1][col]));
                num_neighbor+=(is_alive(board[row+1][col]));
                if(is_conway_cell(board[row][col])){
		            num_neighbor+=(is_alive(board[row-1][col-1]));
		            num_neighbor+=(is_alive(board[row-1][col+1]));
		            num_neighbor+=(is_alive(board[row+1][col-1]));
		            num_neighbor+=(is_alive(board[row+1][col+1]));
                } 
            }
            return num_neighbor;
        }

        void make_alive(int r, int c){
            T& cell = board[r][c];
            if(cell.get_status() == DEAD){
                cell.change_status();
            }else{
                cout << "cell is already alive" << endl;
            }
        }

        void run(int num_round, string game_type, vector<int>& round_to_print){
            int round = 0;
            population = get_population();
            while(round<=num_round){
                print_board(round, round_to_print);
                vector< vector<T> > old_board = board; 
                grow(board, old_board, game_type);
                round++;
            }
        }

        void grow(vector<vector<T> >& board, vector<vector<T> > old_board, string game_type){
            for (int i=0; i<num_row; i++){
                for(int j=0; j<num_col; j++){
                    int num_neighbor = find_neighbor(i,j,old_board);
                    T cell = old_board[i][j];
                    T& p = board[i][j];
                   if(p.type() == FREDKIN_CELL) {
                        if(cell.get_status() == ALIVE) {
                            if(game_type == "CELL" && p.get_age()==2){
                                cout << "MUTATE\n";
                                p.mutate();
                            }else{
                                if(num_neighbor % 2 == 0) {
                                    p.change_status();
                                    population--;
                                }else if(num_neighbor % 2 ==1){
                        		    p.add_age();
                                    if(p.get_age()==2){
                                        p.mutate();
                                    }
	                            }else{
		                            cout << "ERROR!\n";
	                            }
                            }
                        }else if(cell.get_status() == DEAD && num_neighbor % 2 == 1) {
                            p.change_status();
                            population++;
                            if(p.type() == FREDKIN_CELL && p.get_age()==2){
                                p.mutate();
                            }
                        }
                    }else if(p.type() == CONWAY_CELL) {
                        if(cell.get_status() == DEAD && num_neighbor == 3){
                            p.change_status();
                            population++;
                        }else if(cell.get_status() == ALIVE && (num_neighbor<2 || num_neighbor>3)){
                            p.change_status();
                            population--;
                        }
                    }else{
                        cout << "!!!!!!!!!!!!!!ERROR!!!\n";
                    }
                }
            }
        }

        void print_board(int round, vector<int>& round_to_print){
            if(round_to_print.size()!=0){
                int index= 0;
                int next = round_to_print[index];
                if(round == next && (unsigned)index <round_to_print.size()){
                    next = round_to_print[index];
                    round_to_print.erase(round_to_print.begin());
                    cout << "Generation = " << round  << ", Population = " << population << endl;
                    for(int i=0; i<num_row; i++){
                        for(int j=0; j<num_col; j++){
                            cout << board[i][j].to_char();
                        }
                        cout << endl;
                    }
                    cout << endl;
                    index++;
                }
            }
        }

        int get_population(){
            int result = 0;
            for (int i=0; i<num_row; i++){
                    for(int j=0; j<num_col; j++){
                        if(board[i][j].get_status()==1){
                            result++;
                        }
                    }
            }
            return result;
        }

};
