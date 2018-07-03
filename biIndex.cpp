#include "biIndex.h"
#include <string>
#include <algorithm>
#include <limits>

bool biIndex::insert(std::string s, size_t i)
  {
    if(i > reverse.size())
      return false;
    if(s.size() > longest_key)
	longest_key = s.size();
    forward[s]=i; 
    if(i == reverse.size()) 
       reverse.push_back(s); 
    else reverse[i]=s;
    return true;
  }

size_t biIndex::get(std::string s)
{
	auto loc = forward.find(s);
	if(loc == forward.end())
		return std::numeric_limits<size_t>::max();
	return forward[s];
} 
