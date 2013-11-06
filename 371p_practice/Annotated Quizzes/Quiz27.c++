/*
CS371p: Quiz #27 (5 pts)
*/

/* -----------------------------------------------------------------------
1. Describe the difference in binding time between overloading and
   overriding.
   [Sec. 15.0, Pg. 287]
   (1 pt)

compile time vs. run time

    Explanation (Henri)
      Quick review - overriding is where a child method replaces a parent method
      of the same name and same type signature. Done at runtime.
      Overloading is when you define two methods with the same name with different 
      type signatures. Done at compile time.
*/

/* -----------------------------------------------------------------------
2. What two concepts characterize two broad categories of overloading?
   [Sec. 15.1, Pg. 289]
   (1 pt)

type signature and scope

    Explanation (Henri)
      Type signature
        equals(Object x) vs equals(Object x, double p).

      Scope
          You can have two methods with the same name and type signature
          if/when they're outside of each other's scopes (i.e. different classes).
          This allows for no ambiguity, and they can really do completely different 
          things depending on how you want to use them.
*/

/* -----------------------------------------------------------------------
3. What is the output of the following?
   (2 pts)

A() A()
A(A) =(A) ~A()
~A() ~A()
*/

#include <iostream> // cout, endl

using namespace std;

struct A {
    A             ()         {cout << "A() ";}                  // default constructor
    A             (const A&) {cout << "A(A) ";}                 // copy constructor
    ~A            ()         {cout << "~A() ";}                 // destructor
    A& operator = (A)        {cout << "=(A) "; return *this;}}; // copy assignment operator

int main () {
    {

    // Create two instances of A, two default constructors
    A x;
    A y;
    // A() A()
    cout << endl;

    // Creates a tmp copy of x
    // sets current y equal to tmp
    // deletes the old y
    // doesn't go out of scope because it's occuring in the same block. Implicitly done
    // Not 100% sure about this though
    y = x;
    // A(A) =(A) ~A()
    cout << endl;
    }
    // Both objects go out of scope
    // ~A() ~A()
    cout << endl;

    return 0;}
