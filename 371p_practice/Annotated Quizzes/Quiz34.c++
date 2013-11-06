/*
CS371p: Quiz #34 (5 pts)
*/

/* -----------------------------------------------------------------------
1. What is the output of the following program?
   (4 pts)

B::f(double)
A::f(int)
*/

#include <iostream> // cout, endl

using namespace std;

struct A {
    virtual void f (int) {
        cout << "A::f(int)" << endl;}};

struct B : A {
    void f (double) {
        cout << "B::f(double)" << endl;}};

int main () {
    B x;
    x.f(2);

    /* B::f(double) because x is a B */

    A& r = x;
    r.f(2);

    /* A::f(int) even though it's virtual because f(int) is defined in A, not B */

    return 0;}
