// ------------------------------
// projects/allocator/Allocator.h
// Copyright (C) 2013
// Glenn P. Downing
// ------------------------------

#ifndef Allocator_h
#define Allocator_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <new>       // new
#include <stdexcept> // invalid_argument

// ---------
// Allocator
// ---------
using namespace std;
template <typename T, int N>
class Allocator {
public:
    // --------
    // typedefs
    // --------
    
    typedef T                 value_type;
    
    typedef int               size_type;
    typedef ptrdiff_t    difference_type;
    
    typedef value_type*       pointer;
    typedef const value_type* const_pointer;
    
    typedef value_type&       reference;
    typedef const value_type& const_reference;
    
public:
    // -----------
    // operator ==
    // -----------
    
    friend bool operator == (const Allocator&, const Allocator&) {
        return true;}
    
    // -----------
    // operator !=
    // -----------
    
    friend bool operator != (const Allocator& lhs, const Allocator& rhs) {
        return !(lhs == rhs);}
    
private:
    // ----
    // data
    // ----
    
    char a[N];
    
    // -----
    // valid
    // -----
    
    /**
     * O(1) in space
     * O(n) in time
     * goes through block and checks for corresponding sentinels and values
     * returns true if sentinels and values match throughout the full array; false otherwise
     */
    bool valid () const {
        char* b = const_cast<char*>(a);
        int totalSize = 0;	// total size allocated
        int sentinel_value = 0;
        while(b < a + N){
	    sentinel_value = view(*b);			// head sentinel
            b += abs(sentinel_value) + (signed int)(sizeof(int));	// advance pointer to tail sentinel
	    if(abs(sentinel_value) < sizeof(value_type)	      // check for block size less than minimum size
		    || b > a + N - 4                              // check for too much advancing
			    || sentinel_value != view(*b)) {  // check for unmatched sentinel
		return false;
	    }
	    totalSize += abs(sentinel_value) + 2 * (signed int)(sizeof(int));
	    b += (signed int)(sizeof(int));
        }
        return totalSize == N;
    }

    /**
     * method provided by Professor Downing on Quiz 16
     * returns a reinterpreted int pointer given a character reference
     */
    int& view (char& c) const {
	return *reinterpret_cast<int*>(const_cast<char*>(&c));
    }

    /**
     * reinterprets given character reference as int and sets it to given value
     */
    void set (char& c, int val) {
        *reinterpret_cast<int*>(&c) = val;
    }
    
public:
    // ------------
    // constructors
    // ------------
    
    /**
     * O(1) in space
     * O(1) in time
     * creates a new Allocator object instance, and sets the value of the
     * two end sentinels to N - 2 * sizeof(int)
     */
    Allocator () {
	int minimum_size = sizeof(value_type) + 2 * (signed int)(sizeof(int));
	assert(minimum_size <= N);
	int free_block = N - 2 * (signed int)(sizeof(int));
	char* b = a;
	set(*b, free_block);
	b += free_block + (signed int)(sizeof(int));
	set(*b, free_block);
        assert(valid());
    }
    
    // Default copy, destructor, and copy assignment
    // Allocator  (const Allocator<T>&);
    // ~Allocator ();
    // Allocator& operator = (const Allocator&);
    
    // --------
    // allocate
    // --------
    
    /**
     * O(1) in space
     * O(n) in time
     * allocates first (big enough) block for given size
     * if the block has less than the minimum amount of space left after allocation,
     * the full block is allocated (rather than the given size)
     * minimum block size = sizeof(T) + (2 * sizeof(int))
     * returns pointer to first block of allocated space
     */
    pointer allocate (size_type n) {
	int offset = 0;
	char* b = a;
        int block_size = n * sizeof(value_type);
        assert(block_size > 0);
        int minimum_size = sizeof(value_type) + 2 * (signed int)(sizeof(int));
        
	// requested space is greater than total available space
	if(block_size > (N - 2 * (signed int)(sizeof(int)))) {
            bad_alloc exception;
	    throw exception;
        }
	while(offset <= N - 4) {
            int sentinel_value = view(*b);
            // find next available block
	    if(sentinel_value < block_size) {
	        int old_offset = offset;
		offset += abs(sentinel_value) + 2 * (signed int)(sizeof(int));
        	b += offset - old_offset;
            } else {
		// allocate all if the remaining space is less than minimum size
        	if(sentinel_value - block_size < minimum_size) {
        	    set(*b, sentinel_value * -1);
        	    b += sentinel_value + (signed int)(sizeof(int));
        	    set(*b, sentinel_value * -1);
        	} else {
        	    int new_free_block_size = sentinel_value - block_size - 2 * (signed int)(sizeof(int));
        	    set(*b, block_size * -1);
        	    b += block_size + (signed int)(sizeof(int));
        	    set(*b, block_size * -1);
        	    b += (signed int)(sizeof(int));
        	    set(*b, new_free_block_size);
        	    b += new_free_block_size + (signed int)(sizeof(int));
        	    set(*b, new_free_block_size);
        	}
        	break;
            }
        }
        assert(valid());
        return reinterpret_cast<pointer>(a + offset + (signed int)(sizeof(int)));
    }
    
    // ---------
    // construct
    // ---------
    
    /**
     * O(1) in space
     * O(1) in time
     * invokes copy constructor for type T at location pointed to by p
     */
    void construct (pointer p, const_reference v) {
        new (p) T(v);                            // uncomment!
        assert(valid());}
    
    // ----------
    // deallocate
    // ----------
    /**
     * O(1) in space
     * O(1) in time
     * deallocates given block by setting sentinels to positive
     * any adjacent free blocks found after deallocation are coalesced
     */
    void deallocate (pointer p, size_type = 0) {
        char* b = reinterpret_cast<char*>(p);
        char* head = b;
    	b -= (signed int)(sizeof(int));				// access sentinel before the pointer
	int sentinel_value = view(*b);
        assert(sentinel_value < 0);
        set(*b, sentinel_value * -1);	        	// set head sentinel to positive
	assert(view(*b) > 0);
	b += (signed int)(sizeof(int)) + abs(sentinel_value);
        assert(view(*b) == sentinel_value);
	set(*b, sentinel_value * -1);		        // set tail sentinel to positive
	assert(view(*b) > 0);
	b += (signed int)(sizeof(int));                               // at front sentinel of next block
	int new_free_block_size = abs(sentinel_value);
        if(b <= a + N - 4 && view(*b) > 0) {            // coalesce with next block
	    new_free_block_size += view(*b) + 2 * (signed int)(sizeof(int));
	    b += view(*b) + (signed int)(sizeof(int));
	    set(*b, new_free_block_size);
	    b = head - (signed int)(sizeof(int));
	    set(*b, new_free_block_size);
	}
	b = head - 2 * (signed int)(sizeof(int));			// at end sentinel of previous block
	if(b > a && view(*b) > 0) {                     // coalesce with previous block
	    new_free_block_size += view(*b) + 2 * (signed int)(sizeof(int));
	    b -= view(*b) + (signed int)(sizeof(int));
	    set(*b, new_free_block_size);
	    b += view(*b) + (signed int)(sizeof(int));
	    set(*b, new_free_block_size);
	}
        assert(valid());
    }
    
    // -------
    // destroy
    // -------
    
    /**
     * O(1) in space
     * O(1) in time
     * invokes destructor for type T at location pointed to by p
     */
    void destroy (pointer p) {
        p->~T();            // uncomment!
        assert(valid());}};

#endif // Allocator_==h
