#include "Module.h"
#include <boost/algorithm/string.hpp>
#include <fstream>

std::string Module::getComponentList()
    {
       std::string ret = "";
       for(size_t i=0 ;i<recs.data[0].size(); i++){
         ret.append(cols.get(i));
         ret.append(" ");
         }
       return ret;
    }

std::string Module::getEditableList()
    {
       std::string ret = "";
       for(size_t i=0 ;i<recs.data[0].size(); i++){
	 if(!isEditable(cols.get(i))) 
		continue;		
         ret.append(cols.get(i));
         ret.append(" ");
         }
       return ret;
    }

void Module::init(std::string name)
  {
    rows.resize(3);
    cols.insert(name,recs.addCol());
    rgxs.push_back(boost::regex("J[0-9]{5}"));
    rgxs.push_back(boost::regex("[0-9]{7}"));
    rgxs.push_back(boost::regex("[A-Z][a-z]+ [A-Z][a-z]+"));//these should stay hard coded - no serialization
  }
  bool Module::addSubcomponent(std::string parent, std::string name, double weight)
  {
      size_t col = recs.addCol();
      cmps.addSubcomponent(parent, name, weight, col);
      cols.insert(name, col);
      return cols.testInvariant();
  }

  bool Module::importCSVIDs(std::string filename)
  {
       std::ifstream in(filename.c_str(), std::ios::in);
       while(in)
         {
              std::string input;
              std::vector<std::string> line;
              getline(in, input);
              boost::split(line, input, boost::is_any_of(","));
              if(line.size()!=rgxs.size()) break;
              this->addRecord(line[0]);
              
              for(size_t i=1; i<line.size(); ++i)
                   this->associateRecordID(line[0],line[i]);
              
              //std::cout << line[2] << std::endl;
              
         }
       in.close();
  }

  void Module::update()
  {
    for(int i=0; i<recs.data.size(); ++i)
      cmps.update(recs.data[i]);
  }

bool Module::isStudent(std::string s)
{
	size_t map = getMap(s);
	if(map >= rgxs.size())
		return false;
	size_t rowIdx = rows[map].get(s);
	if(rowIdx >= recs.data.size())
		return false;
	return true;
}

bool Module::insert(std::string id, std::string cmp, double value)
{
	size_t map = getMap(id);
	if(map >= rgxs.size())
		return false;
	size_t rowIdx = rows[map].get(id);
	if(rowIdx >= recs.data.size())
		return false;
	size_t colIdx = cols.get(cmp);
	if(colIdx >= recs.data[0].size())
		return false;
	recs.data[rowIdx][colIdx] = value;
}
