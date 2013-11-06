#ifndef FREDKINCELL_H
#define FREDKINCELL_H

#include "AbstractCell.h"
#include "ConwayCell.h"

class FredkinCell : public AbstractCell {
    public:
        int get_row() {
            return AbstractCell::get_row();
        }

        int get_col() {
            return AbstractCell::get_col();
        }

        int get_status() {
            return  AbstractCell::get_status();
        }

        void change_status() {
            if(get_status() == -1) {
                //cout << "ERROR, can't change invalid status\n";
            }else {     
                AbstractCell::change_status();
            }            
        }

        void set_type(char type) {
            AbstractCell::set_type(type);
        }

        void add_age() {
            AbstractCell::add_age();
        }

        int get_age() {
            return AbstractCell::get_age();
        }

        FredkinCell(int r, int c, int s):
            AbstractCell(r,c,s)
            {
                AbstractCell::set_type('f');
            }

        FredkinCell(FredkinCell* p):
            AbstractCell(p->get_row(),p->get_col(),p->get_status())
            {
                AbstractCell::set_type('f');     
            }


        char to_char(){
            if(get_status() == 1){
		        if(get_age()>=10){
			        return '+';
		        }else{
                        	return (char)(((int)'0') + get_age());
		        }
            }else if(get_status() == 0){
                return '-';
            }else{
                return 'E';
            }
        }

        char type(){
            return AbstractCell::type();
        }

        FredkinCell* clone () const {
            return new FredkinCell(*this);
        }

        AbstractCell* mutate(){
            int r = get_row();
            int c = get_col();
            int s = get_status();
            return new ConwayCell(r,c,s);
        }

};

#endif
