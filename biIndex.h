#ifndef BIINDEX_H
#define BIINDEX_H

#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <string>

class biIndex
{
  friend class boost::serialization::access;
   std::map<std::string, size_t> forward;
   std::vector<std::string> reverse;
   template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
      ar & forward;
      ar & reverse;
  }
public:
   biIndex(){}
   bool insert(std::string s, size_t i);
   bool remove(std::string s, size_t i){forward.erase(s); reverse[i]="";} // TODO swapper - take out i in vector by swapping with back, then rewrite forward[reverse[i]] = forward[reverse[back]], erase back;
   std::string& get(size_t i){return reverse[i];}
   size_t get(std::string s);
   bool testInvariant() {for(int i=0; i<reverse.size(); ++i) if(forward[reverse[i]] != i) return false; return true;}   
};

#endif
