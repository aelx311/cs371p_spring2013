#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>
#include <vector>

using namespace std;

struct Ballots{
    vector<int> votes;
    int currentIndex;
};

struct Candidates{
    string name;
    vector<Ballots> ballot;
    bool winning;
};

struct AllCandidates{
    vector<Candidates> allCandidates;
};

//-----------
//voting_read
//-----------
bool voting_read(AllCandidates&, istream&, int&);

//-----------
//voting_eval
//-----------
bool voting_eval(AllCandidates&, ostream&, int&);

//------------
//voting_print
//------------
bool voting_print(ostream&);

//------------
//voting_solve
//------------
void voting_solve(istream&, ostream&);

#endif // Voting_h
