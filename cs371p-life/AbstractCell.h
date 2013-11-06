#ifndef ABSTRACTCELL_H
#define ABSTRACTCELL_H

using namespace std;

class AbstractCell {
    private:
        int alive;     // 1 for alive, 0 for dead
        int row;
        int col;
        char cell_type;
        int age;

    public:
        virtual int get_row(){
        	return row;	
        }

        virtual int get_col(){
            return col;
        }

        virtual int get_status(){
            return alive;	
        }

        virtual void change_status(){
            alive = ((alive+1) % 2);
        }

        virtual void set_type(char type){
            cell_type = type;	
        }

        virtual void set_row(int r){
            row = r;
        }

        virtual void set_col(int c){
            col = c;
        }

        virtual void add_age(){
            age++;
        }

        virtual int get_age(){
            return age;
        }

        AbstractCell(int r, int c, int s){
            if(s == 0 || s == 1){
                alive = s;
                row = r;
                col = c;
                age = 0;
            }else{
                //cout << "ERROR: status must be 0 or 1\n";
                alive = -1;
                row = -1;
                col = -1;
            }
        }

        virtual char to_char() = 0;

        virtual char type() {
            return cell_type;
        }

        virtual AbstractCell* clone () const = 0;

        void operator = (AbstractCell* p){
            AbstractCell::set_row(p->get_row());
            AbstractCell::set_col(p->get_col());
        }

        virtual AbstractCell* mutate()=0;
};

#endif
