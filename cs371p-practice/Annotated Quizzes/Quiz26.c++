/*
CS371p: Quiz #26 (5 pts)
*/

/* -----------------------------------------------------------------------
2. In C++  constructors, refinement overriding is forced. True or False?
   In Java constructors, refinement overriding is forced. True or False?
   (2 pts)

true
true

	Explanation (Henri)
	Nuance of the two languages. 
	Overriding is where a method in a child class replaces 
	a method in parent class if they have the same name and type signature. 
	The refinement aspect means the parent and child methods merge to form 
	new behavior (aka super(...) IS ALWAYS called).
	
	Some other notes:
		- C++ requires the parent to indicate replacement is permitted with "virtual"
		- final methods prohibit replacement
		- final classes prohibit subclassing altogether
		- In java, the default parent constructor is called
*/

/* -----------------------------------------------------------------------
2. In C++  a static 'const double' data member must be initialized in its
   definition. True or False?
   In Java a static 'final double' data member must be initialized in the
   static initializer block. True or False?
   (2 pts)

true
false

	Explanation (Henri)
		It's a nuance of C++ vs Java. In C++, any const variable must be initialized at declaration.
		In java however you can initialize it outside of the initializer block, as long as it does get initialized somewhere else.
			// I'm pretty sure the java explanation is right, but correct me if I'm wrong
*/
