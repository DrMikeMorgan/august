#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <vector>

#include "biIndex.h"
#include "dataGrid.h"
#include "indexTree.h"

#include <boost/regex.hpp>

class Module
  {
  friend class boost::serialization::access;
  dataGrid recs;
  std::vector<biIndex> rows; //for now, just use names as ...1 ...2 etc
  biIndex cols; //cols are uniquely named and indexed
  indexTree cmps;  //organises columns into recursive form
  std::vector<boost::regex> rgxs;
  std::string name_;
  size_t getMap(std::string s){for(size_t i=0; i<rgxs.size(); i++) if( boost::regex_match(s,rgxs[i])) return i; return rgxs.size();}
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
      ar & recs;
      ar & rows;
      ar & cols;
      ar & cmps;
  }
  public:
  Module(){}
  Module(std::string name):cmps(name,0.0,0),name_(name){init(name);}//at least 3 IDs J name stu num 
  void init(std::string);
  void addID(boost::regex rgx){rgxs.push_back(rgx); rows.resize(rows.size()+1);}
  void associateRecordID(std::string existingID, std::string newID){rows[getMap(newID)].insert(newID, rows[getMap(existingID)].get(existingID));}
  bool addRecord(std::string s){rows[this->getMap(s)].insert(s, recs.addRow());}
  bool addSubcomponent(std::string parent, std::string name, double weight);
  bool insert(std::string id, std::string cmp, double value);
  double get(std::string id, std::string cmp){return recs.data[rows[getMap(id)].get(id)][cols.get(cmp)];}
  double get(size_t id, std::string cmp){return recs.data[id][cols.get(cmp)];}
  bool importCSVIDs(std::string filename);
  void update();
  std::string getComponentList();
  std::string getName(){return name_;}
  bool isComponent(std::string s){return cols.get(s) < std::numeric_limits<size_t>::max();}
  bool isStudent(std::string s);
  std::string getEditableList();
  bool isEditable(std::string s){return cmps.isEditable(s);}
  std::string getName(size_t ID, std::string example = "J00000"){return rows[getMap(example)].get(ID);}
  std::size_t rowCount() {return recs.data.size();}
  size_t maxKeyLength(std::string example = "J00000"){return rows[getMap(example)].maxKeyLength();}
  };

#endif
