/*
CS371p: Quiz #36 (5 pts)
*/

/* -----------------------------------------------------------------------
1. Define H's copy constructor and destructor.
   (4 pts)
*/

struct A {};

class H {
    private:
        struct RC {
            int _c;
            A*  _p;

            RC (A* p) {
                _c = 1;
                _p = p;}

            ~RC () {
                delete _p;}};

        RC* _q;

    public:
        H (A* p) {
            _q = new RC(p);}

        H (const H& that) {
            /* Point to the same reference counter */
            _q = that._q;

            /* Increment that RC object's count */
            ++_q->_c;}

        ~H () {
            if (!--_q->_c)
                delete _q;}};

int main () {
    H x = new A;
    H y = x;
    return 0;}
