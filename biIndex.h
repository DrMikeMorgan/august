#ifndef BIINDEX_H
#define BIINDEX_H

#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <string>
#include <set>

class biIndex
{
  friend class boost::serialization::access;
   std::map<std::string, size_t> forward;
   std::vector<std::string> reverse;
   std::set<std::string> duplicates;
   size_t longest_key;
   template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
      ar & forward;
      ar & reverse;
      ar & longest_key;
  }
public:
   biIndex():longest_key(0){}
   bool insert(std::string s, size_t i);
   bool remove(std::string s, size_t i){forward.erase(s); reverse[i]="";} // TODO swapper - take out i in vector by swapping with back, then rewrite forward[reverse[i]] = forward[reverse[back]], erase back;
   std::string& get(size_t i){return reverse[i];}
   size_t get(std::string s);
   bool testInvariant() {for(int i=0; i<reverse.size(); ++i) if(forward[reverse[i]] != i) return false; return true;}   
   size_t size(){return reverse.size();}
   size_t maxKeyLength(){return longest_key;}
   bool contains(std::string s){return forward.find(s) != forward.end();}
   bool isDuplicate(std::string key) {return duplicates.find(key) != duplicates.end();} 
};

#endif
