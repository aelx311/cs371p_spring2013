/*
CS371p: Quiz #28 (5 pts)
Explanation by Henri
*/

class Shape {
    private int _x;
    private int _y;

    public ... equals (...) {...}
    ...}

class Circle extends Shape {
    private int _r;
    ...}

/* -----------------------------------------------------------------------
1. Define Circle.Circle(...) in terms of Shape.Shape(...).
   (2 pts)
*/

// Takes in x,y coordinates and r radius
public Circle (int x, int y, int r) {

    // This is an example of refinement overriding. Must call super(x, y) constructor
    super(x, y);

    // Then take care of Circle-specific stuff, in this case setting _r
    _r = r;}

/* -----------------------------------------------------------------------
2. Define Circle.equals(...) in terms of Shape.equals(...).
   (2 pts)
*/

// Must take in Object (and not Circle)
// This is because if we don't treat it as an Object, it won't override Object's equals() method
// We have to do this because ultimately we're inheriting Object's equals() method
public boolean equals (Object rhs) {

    // Ensure it's a Circle
    if (rhs instanceof Circle)
        // Call parent equals() and checks Circle-specifics, this case _.r (make sure to Cast)
        return super.equals(rhs) && (_r == ((Circle) rhs)._r);
    return false;}

// Side note: in C++ we would have to make a temporary Circle object from rhs first before comparing