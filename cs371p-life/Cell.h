#ifndef Cell_h
#define Cell_h

#include <iostream>
#define protected public
#define private public
#include "Handle.h"
#include "AbstractCell.h"
#include "FredkinCell.h"
#include "ConwayCell.h"

class Cell : public Handle<AbstractCell> {
	public:
		Cell(AbstractCell* p):
			Handle<AbstractCell> (p)
		{}

        char to_char(){
            return Handle<AbstractCell>::get()->to_char();
        }
        
        char type(){
            return Handle<AbstractCell>::get()->type();
        }

        Cell* clone () const {
            return new Cell(*this);
        }

        int get_row(){
            return Handle<AbstractCell>::get()->get_row();
        }

        int get_col(){
            return Handle<AbstractCell>::get()->get_row();            
        }

        int get_status(){
            return Handle<AbstractCell>::get()->get_status();   
        }
        void change_status(){
            return Handle<AbstractCell>::get()->change_status();  
        }

        void set_type(char type){
            return Handle<AbstractCell>::get()->set_type(type);
        }
        void add_age(){
            return Handle<AbstractCell>::get()->add_age();  
        }
        int get_age(){
            return Handle<AbstractCell>::get()->get_age();
        }

        void mutate(){
            _p = (*(_p)).mutate();
        }

        
};

#endif
