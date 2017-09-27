/*
Svetleen Guerrier
Class: CSCI335

*/
#include "DoubleProbing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Adds a character to the mispelled word
template <typename HashTableType>
bool Add(HashTableType &hash_table, string dictword);

//Swaps a Character to the mispelled word.
template <typename HashTableType>
bool Swap(HashTableType &hash_table, string dictword);

//Removes a character to the mispelled word.
template <typename HashTableType>
bool Remove(HashTableType &hash_table, string dictword);

template <typename HashTableType>
void SpellCheck(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Dictionary filename: " << query_filename << endl;
  cout << "Text file filename: " << words_filename << endl;
  hash_table.MakeEmpty();  
  
  //Opens dictionary file to be used for hashed table.
  ifstream infile; 
  infile.open(query_filename);
  string get_line="";
  string value = "";

  //Inputs words to dictionary.
  while(!(infile.eof()))
  {
    infile>>get_line;
    hash_table.Insert(get_line);
  }

  get_line = "";
  bool result;

  //Opens testing file to be used for hash table
  ifstream nextfile;
  nextfile.open(words_filename);

  //each word is has punctuation and capitals removed
  while(!(nextfile.eof()))
  {
  	nextfile>>get_line;

  	for(size_t i = 0; i<get_line.size();i++)
  	{
  		if(ispunct(get_line[i]))
  		{
  			get_line.erase(i--,1); 
  		}
  	}

  	for(size_t i = 0; i<get_line.size();i++)
  	{
  		get_line[i] = tolower(get_line[i]);
  	}

    //If word if found move on.
  	result = hash_table.Contains(get_line);
  	if(result==true)
  		continue;
  	else
  	{
      
      //Locate mispelled word error and output correction.
  		while(result==false)
  		{
  			value = swap(hash_table,get_line);
  			if(value!= "Error")
  			{
  				cout<<get_line<<" -> "<<value<<endl;
  				result =true;
  				break;
  			}
  			value = add(hash_table,get_line);
  			if(value!= "Error")
  			{
  				cout<<get_line<<" -> "<<value<<endl;
  				result =true;
  				break;
  			}
  			value = remove(hash_table,get_line);
  			if(value!= "Error")
  			{
  				cout<<get_line<<" -> "<<value<<endl;
  				result =true;
  				break;
  			}
  			else
  				break;
  		}
  	}
  }
  
}
template <typename HashTableType>
string swap(HashTableType &hash_table, string dictword)
{
  //Checks each option for the character by swapping adjacent character.
	string temp = dictword;
	for(size_t i = 0; i<dictword.length();i++)
	{
		swap(dictword[i],dictword[i+1]);
		if(hash_table.Contains(dictword)==true)
			return dictword;

		dictword = temp;
	}
	return "Error";
}

template <typename HashTableType>
string add(HashTableType &hash_table, string dictword)
{

	string temp = dictword;
  //Checks each option for the character by Adding character in each index.
	for(size_t i= 0; i< dictword.length(); i++)
	{

		for(size_t j = 97; j<123; j++)
		{
			dictword.insert(i,1,(char)j);
			if(hash_table.Contains(dictword)==true)
				return dictword;
			dictword = temp;
		}
	}

	return "Error";
}
template <typename HashTableType>
string remove(HashTableType &hash_table, string dictword)
{
	string temp = dictword;

  //Checks each option for the character by removing character in each index.
	for(size_t i =0; i < dictword.length(); i++)
	{
		dictword.erase(i,1);
		if(hash_table.Contains(dictword)==true)
			return dictword;
		dictword = temp;
	}

	return "Error";
}
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document file> <dictionary file>" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const string query_filename(argv[2]);

  HashTableDouble<string> double_probing_table;
  SpellCheck(double_probing_table, words_filename, query_filename);    

  return 0;
}

















