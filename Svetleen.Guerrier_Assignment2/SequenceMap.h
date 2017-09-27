//Svetleen Guerrier
//Spring 2017 CSCI 335
#ifndef SEQUENCE_MAP
#define SEQUENCE_MAP

#include <vector>
#include <iostream>
using namespace std;

class SequenceMap
{
public:
	
	SequenceMap() = default;
  	// Copy-constructor.

  	SequenceMap(const SequenceMap &rhs) = default;

  	// Copy-assignment. 
  	SequenceMap& operator=(const SequenceMap &rhs) = default;

  	// Move-constructor. 
  	SequenceMap(SequenceMap &&rhs) = default;
  	
  	// Move-assignment.
  	SequenceMap& operator=(SequenceMap &&rhs) = default;

  	//Initializes new sequence along with given enzyme
	SequenceMap(const string& a_rec_seq, const string an_enz_acro)
	{
		recognition_sequence_ = a_rec_seq;
		enzyme_acronyms_.push_back(an_enz_acro);
	}
	//compares given Sequences. If less return true otherwise false.
	friend bool operator<(const SequenceMap& s1, const SequenceMap& rhs)
	{	
		return (s1.recognition_sequence_<rhs.recognition_sequence_);
	}

	//outstream operator, outputs enzymes along with given recognition sequence.
	friend ostream& operator<<(ostream &out, const SequenceMap &a_sequence)
	{
		out<<a_sequence.recognition_sequence_<<endl;
    	for(unsigned int i = 0; i < a_sequence.enzyme_acronyms_.size();i++)
    	{
      		out<<a_sequence.enzyme_acronyms_[i]<<" ";
    	}
    	out<<endl;
   		return out;
	}

	//adds enzyme to given recognition sequence along with one it already has.
	void Merge(const SequenceMap&other_sequence)
	{
		for(unsigned int i = 0; i<other_sequence.enzyme_acronyms_.size();i++)
		{
			enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
		}
	}

	//outputs the enzyme vector values to given sequence
	void output_vector(const SequenceMap& given_sequence)
	{
		for(unsigned int i = 0; i<given_sequence.enzyme_acronyms_.size();i++)
		{
			cout<<given_sequence.enzyme_acronyms_[i]<<" ";
		}
		cout<<endl;
	}
private:
	//recognition sequence along with enzyme vector.
	string recognition_sequence_;
	vector<string> enzyme_acronyms_;


};
#endif