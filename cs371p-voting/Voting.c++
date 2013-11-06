//--------
//includes
//--------
#include <iostream> //istream, ostream
#include <vector> //vector
#include <cassert> //assert
#include <sstream> //istringstream
#include <algorithm> //min, max
#include "Voting.h"

using namespace std;

//-----------
//voting_read
//-----------
bool voting_read (AllCandidates& everyCandidates, istream& reader, int& numberOfVoters){
	string line;
	string candidateName;
    Candidates candidate;
    int candidateIndex;
    
    //read number of candidates
    getline(reader, line);
    int numberOfCandidates = atoi(line.c_str());
    assert(numberOfCandidates <= 20);
    
    //read names of candidates
    for(int i = 0; i < numberOfCandidates; ++i){
        getline(reader, candidateName);
        assert (candidateName.length() <= 80);
        candidate.name = candidateName;
        candidate.winning = true;
        everyCandidates.allCandidates.push_back(candidate);
    }
    
    //read all votes
    do{
        getline(reader, line);
        if(line == ""){
            break;
        }
        
        istringstream iss(line);
        int rank;
        Ballots eachBallot;
        
        for(int i = 0; i < numberOfCandidates; ++i){
            iss >> rank;
            if(rank != 0){
                eachBallot.votes.push_back(rank);
                eachBallot.currentIndex = 0;
                ++numberOfVoters;
            }
        }
        candidateIndex = eachBallot.votes[0]-1;
        everyCandidates.allCandidates[candidateIndex].ballot.push_back(eachBallot);
    }while(!reader.eof());
    numberOfVoters /= numberOfCandidates;
    
    return true;
}

//-----------
//voting_eval
//-----------
bool voting_eval(AllCandidates& candidates, ostream& writer, int& numberOfVoters){
	int maximum = 0;
	int minimum = numberOfVoters;
	int winnerIndex;
	AllCandidates loserList;

    //find maximum and minimum number of votes
    for(unsigned int i = 0; i < candidates.allCandidates.size(); ++i){
        if(candidates.allCandidates[i].winning){
            minimum = min(minimum, (int)candidates.allCandidates[i].ballot.size());
            maximum = max(maximum, (int)candidates.allCandidates[i].ballot.size());
            if(maximum == (int)candidates.allCandidates[i].ballot.size()){
            	winnerIndex = i;
            }
        }
    }
	
	//check for candidates with no ballots
    for(unsigned int i = 0; i < candidates.allCandidates.size(); ++i) {
    	if(candidates.allCandidates[i].ballot.size() == 0)
    		candidates.allCandidates[i].winning = false;
    }
    	
	//check for losers
	for(unsigned int i = 0; i < candidates.allCandidates.size(); ++i){
		int temp = (int)candidates.allCandidates[i].ballot.size();
		if(temp == minimum && candidates.allCandidates[i].winning){		
			candidates.allCandidates[i].winning = false;
			loserList.allCandidates.push_back(candidates.allCandidates[i]);
		}
	}
	
	// majority wins (more than 50%)
	if(maximum > (numberOfVoters/2)){
		writer << candidates.allCandidates[winnerIndex].name << endl;
		return true;
	}
	
	//all tied
	if(minimum == maximum){
		for(unsigned int i = 0; i < candidates.allCandidates.size(); ++i){
			if(maximum == (int)candidates.allCandidates[i].ballot.size()){
				writer << candidates.allCandidates[i].name << endl;
			}
		}
		return true;
	}
		
	// find the losers and take their votes
	for(unsigned int i = 0; i < loserList.allCandidates.size(); ++i){
		bool notDone = true;	
		for(unsigned int j = 0; j < loserList.allCandidates[i].ballot.size(); ++j){
			notDone = true;
			for(unsigned int k = 0; k < loserList.allCandidates[i].ballot[j].votes.size() && notDone; ++k){
				int currentVote = loserList.allCandidates[i].ballot[j].votes[k];
				if(candidates.allCandidates[currentVote-1].winning){
					currentVote = loserList.allCandidates[i].ballot[j].votes[k];
					candidates.allCandidates[currentVote-1].ballot.push_back(loserList.allCandidates[i].ballot[j]);
					notDone = false;
				}
			}
		}
	}
	return voting_eval(candidates, writer, numberOfVoters);
}

//------------
//voting_print
//------------
bool voting_print(ostream& writer){
	if(!writer.good())
		return false;
	assert(writer.good() == true);
	return true;
}

//------------
//voting_solve
//------------
void voting_solve(istream& reader, ostream& writer){
    string testCases;
    getline(reader, testCases);
    
    int numberOfTestCases = atoi(testCases.c_str());
    getline(reader, testCases);
    
    for (int i = 0; i < numberOfTestCases; ++i) {
        AllCandidates everyCandidates;
        int numberOfVoters = 0;
        voting_read(everyCandidates, reader, numberOfVoters);
      	voting_eval(everyCandidates, writer, numberOfVoters);
        voting_print(writer);
        if(i != numberOfTestCases -1)
        	cout << endl;
    }
}
