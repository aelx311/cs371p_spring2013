/*
CS371p: Quiz #25 (5 pts)
*/

/* -----------------------------------------------------------------------
1. Name the two mechanisms through which interfaces can be separated.
   [The Interface Segregation Principle]
   (2 pts)

delegation
multiple inheritance


 * EXPLANATION:
 *     Delegation - Allows for a subclass to just inherit from one parent,
 *     but at the same time allows it to require another object that can do the functions
 *     needed by another class. I think this would be useful in cases where you
 *     don't need ALL of the other parent's methods, or in languages such as java
 *     that don't support multiple inheritance. Allows a class to not be dependent 
 *     directly on the other parent.
 *         Example - Classes A and B are both abstract classes. Class C requires all of 
 *         A's functionality (directly inherits) and only some of B's. So we created a 
 *         class D that inherits from B and implements the functionality that C needs, 
 *         and have C only inherit from A, and require an instance of D for functionality.
 *         The effect of this is that class C is only directly affected by changes to A; 
 *         it is shielded from changes to B by class D. 
 *         A        B
 *         ^        ^
 *         |        |
 *         C------<>D
 *
 *
 *      Multiple Inheritance - Pretty straightforward. Allows a subclass to inherit
 *      from multiple parent interfaces. Not available in Java though. Allows you to keep 
 *      separate parent classes so that other classes can extend from either class without 
 *      being dependent on both.
 *          Example 
 *          A       B
 *          ^       ^
 *          |       |
 *           \     /
 *            \   /
 *              C
 *
 *
 *      What we DON'T want:
 *      
 *          A <----- B <------ C
 *
 *          Explanation: Because now if you want to extend from B, you must also extend from 
 *          A, which may not be what you want. (A - Timer, B - Door, C - TimerDoor, but what 
 *          if you want an UnTimed Door?)
 * 


*/

/* -----------------------------------------------------------------------
2. Define operator != only in terms of ! and ==.
   Define the operators <=, >, and >= only in terms of ! and <.
   (2 pts)
*/

#include <cassert>  // assert
#include <iostream> // cout, endl

using namespace std;

class A {

    /**
     * Friend because we want it available to class A 
     */
    friend bool operator == (const A& lhs, const A& rhs) {
        return lhs._i == rhs._i;}

    friend bool operator < (const A& lhs, const A& rhs) {
        return lhs._i < rhs._i;}

    private:
        int _i;

    public:
        A (int i) {
            _i = i;}};

template <typename T>
bool operator != (const T& lhs, const T& rhs) {
    return !(lhs == rhs);}

template <typename T>
bool operator <= (const T& lhs, const T& rhs) {
    return !(rhs < lhs);}

template <typename T>
bool operator > (const T& lhs, const T& rhs) {
    return (rhs < lhs);}

template <typename T>
bool operator >= (const T& lhs, const T& rhs) {
    return !(lhs < rhs);}

int main () {
    A x = 2;
    A y = 3;

    assert(!(x == y));
    assert(x != y);

    assert(x <  y);
    assert(x <= y);
    assert(!(x >  y));
    assert(!(x >= y));

    cout << "Done." << endl;
    return 0;}
