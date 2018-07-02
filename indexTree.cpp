#include "indexTree.h"



bool indexTree::addSubcomponent(std::string parent, std::string name, double weight, size_t col)
  {
      if(this->name_ == parent){
           childs.push_back(indexTree(name,weight,col));
             return true;
      }
      else 
        for(int i=0; i<childs.size(); ++i)
          if(childs[i].addSubcomponent(parent, name, weight, col))
              return true;
      return false;
   }

bool indexTree::isEditable(std::string name)
{
	if(name_ == name)
		if(childs.size()==0)
			return true;
		else return false;
	for(int i = 0; i<childs.size(); ++i)
		if(childs[i].isEditable(name))
			return true;
	return false;	
}

void indexTree::update(std::vector<double>& data)
  {
    if(childs.size()==0) return;
    
    data[col_]=0;
    for(int i = 0; i<childs.size(); ++i){
      childs[i].update(data);
    
    data[col_] += data[childs[i].col_]*childs[i].weight_;
   }
}
