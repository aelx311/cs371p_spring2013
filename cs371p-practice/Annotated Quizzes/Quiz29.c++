/*
CS371p: Quiz #29 (5 pts)
Explanation by Henri
*/

class Shape {
    private:
        int _x;
        int _y;

    public:
        virtual ... equals (...) {...}
    ...};

class Circle : public Shape {
    private:
        int _r;
    ...};

/* -----------------------------------------------------------------------
1. Define Circle::Circle(...) in terms of Shape::Shape(...).
   (2 pts)
*/

// C++ requires that we explicitly call the parent constructor (Shape and not super)
// This is due to C++ allowing for multple inheritance.
// Also note that this parent constructor call must be done before the code block!
Circle (int x, int y, int r) :
        Shape(x, y) {
    _r = r;}

/* -----------------------------------------------------------------------
2. Define Circle::equals(...) in terms of Shape::equals(...).
   (2 pts)
*/

// C++ is statically casted by default, so we must use dynamic_cast
// We try to create a Circle* out of the Shape that we're passed in
   // This is a clever trick, as it takes care of "instanceof" implicitly
   // If dynamic_cast doesn't work, it just returns 0, or false
// If it works, we send the Circle up to Shape's equals method (Shape::equals)
// And check the respective radii.
// Remember again that C++ doesn't user super, you have to explicitly call the particular parent
bool equals (const Shape& that) const {
    if (const Circle* const p = dynamic_cast<const Circle*>(&that))
        return Shape::equals(*p) && (_r == p->_r);
    return false;}
