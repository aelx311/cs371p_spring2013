/*
CS371p: Quiz #30 (5 pts)
*/

/* -----------------------------------------------------------------------
1. In Java dynamic binding is enabled by default.
   Under what FOUR conditions will static binding occur instead?
   (2 pts)

final class
final method
	// Because final means it's not extendable

private method
	// thus not inherited by derived class

static method
	// Automatically marks a method as private and final
*/

/* -----------------------------------------------------------------------
2. In C++ static binding is enabled by default.
   Dynamic binding is enabled with the keyword "virtual".
   Under what FOUR conditions will static binding occur anyway?
   (2 pts)

on an object
	// Think Shape x = new Circle;

with an explicit reference to the base class
	// Circle x; x.Shape::equals()

in a constructor of the base class
in the destructor of the base class
*/
