/*
CS371p: Quiz #33 (5 pts)
*/

/* -----------------------------------------------------------------------
1. Define Shape's constructor.
   (4 pts)
*/

struct Shape : Handle<AbstractShape> {
    Shape (AbstractShape* p) :
            Handle<AbstractShape> (p)
        {}
    ...};

/**
 * Takes in a pointer and passes it up to Handle's Handle(Handle*) constructor
 */
