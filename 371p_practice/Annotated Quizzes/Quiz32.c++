/*
CS371p: Quiz #32 (5 pts)
*/

/* -----------------------------------------------------------------------
1. What is the output of the following program?
   (4 pts)

A() A(A) A(A) ~A()
~A() ~A()
*/

#include <algorithm> // swap
#include <iostream>  // cout, endl
#include <vector>    // vector

using namespace std;

struct A {
    A             ()         {cout << "A() ";}                // default constructor
    A             (int)      {cout << "A(int) ";}             // int constructor
    A             (const A&) {cout << "A(A) ";}               // copy constructor
    ~A            ()         {cout << "~A() ";}               // destructor
    A& operator = (const A&) {cout << "=(A) "; return *this;} // copy assignment operator
    A* clone      ()         {return new A(*this);}};

struct H {
    A* _p;
    H             (A* p)          {_p = p;}
    H             (const H& that) {_p = that._p->clone();}
    H& operator = (H rhs)         {swap(_p, rhs._p); return *this;}
    ~H            ()              {delete _p;}};

int main () {
    {

    /**
     * new A()
     *     A()
     * copies the A() over the array (via x's copy constructor and internal std::copy function), thus 
     *     A(A) A(A)
     * Then deletes the new A() we made 
     *     ~A()
     * Two A's in vector destructed when they go out of scope
     *     ~A() ~A()
     * 
     */

    vector<H> x(2, new A());
    cout << endl;
    }
    cout << endl;

    return 0;}
