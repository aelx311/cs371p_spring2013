#ifndef CONWAYCELL_H
#define CONWAYCELL_H

#include "AbstractCell.h"

class ConwayCell : public AbstractCell {
    public:
        int get_row(){
            return AbstractCell::get_row();
        }

        int get_col(){
            return AbstractCell::get_col();
        }

        int get_status(){
            return  AbstractCell::get_status();
        }

        void change_status(){
            if(get_status()==-1){
                    //cout << "ERROR, can't change invalid status\n";
            }else{     
                AbstractCell::change_status();
            }            
        }

        void set_type(char type){
            AbstractCell::set_type(type);
        }

        void add_age(){
            AbstractCell::add_age();
        }

        int get_age(){
            return AbstractCell::get_age();
        }

        ConwayCell(int r, int c, int s):
            AbstractCell(r,c,s)
            {
                AbstractCell::set_type('c');
            }

        ConwayCell(ConwayCell* p):
            AbstractCell(p->get_row(),p->get_col(),p->get_status())
            {
                AbstractCell::set_type('c');     
            }

        char to_char(){
            if(get_status() == 1){
                return '*';
            }else if(get_status() == 0){
                return '.';
            }else{
                return 'E';
            }
        }

        char type(){
            return AbstractCell::type();
        }

        ConwayCell* clone () const {
            return new ConwayCell(*this);
        }

        AbstractCell* mutate(){
            return 0;
        }

};

#endif
