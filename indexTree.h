#ifndef INDEXTREE_H
#define INDEXTREE_H

#include <vector>
#include <string>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>

 class indexTree
 {
 protected:             //implementation currently too specific with update(), maybe inherit later?
   friend class boost::serialization::access;
   std::vector<indexTree> childs;
   double weight_;
   std::string name_;
   size_t col_;
   template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & childs;
        ar & weight_;
        ar & name_;
        ar & col_;
    }
   double getChildWeight(size_t i){return childs[i].weight_;}
   size_t getChildCol(size_t i){return childs[i].col_;}
 public:
   indexTree(){}
   indexTree(std::string name, double weight, size_t col):weight_(weight),name_(name),col_(col){}
   void set(std::string name, double weight, size_t col){weight_=weight; name_=name; col_=col;}
   bool addSubcomponent(std::string parent, std::string name, double weight, size_t col);
   bool isEditable(std::string name);
   void update(std::vector<double>& data);
 };

#endif
