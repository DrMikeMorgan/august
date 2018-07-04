#include "biIndex.h"
#include <string>
#include <algorithm>
#include <limits>
#include <exception>

//Use case 1 - inserting a new key, value into the index
//Use case 2 - inserting a new value with a duplicate key TRAP OUT AND RECORD DUPLICATES, insert both in reverse index
//XUse case 2b- inserting a duplicate value with a new key!! THIS SHOULD NEVER HAPPEN, DO NOT TRAP OUT
//XUse case 3 - modifying a value with existing key CANNOT TELL APART FROM case 2 - make responsibility of some other method
//Use case 4 - modifying key for an existing value: identical to 2b

bool biIndex::insert(std::string s, size_t i)
  {
    if(i > reverse.size())
      return false;
    if(s.size() > longest_key)
	longest_key = s.size();    	
    
    if(i == reverse.size()) 
       reverse.push_back(s); 
    else {
	forward.erase(reverse[i]);
	reverse[i]=s; //Use Case 4
    }

    if(forward.find(s) != forward.end())
    {
	duplicates.insert(s); //Use Case 2
    }
    else forward[s]=i; 

    return true;
  }

size_t biIndex::get(std::string s)
{
	auto loc = forward.find(s);
	if(loc == forward.end())
		return std::numeric_limits<size_t>::max();
	return forward[s];
} 
