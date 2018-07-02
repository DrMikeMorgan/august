#ifndef DATAGRID_H
#define DATAGRID_H

#include <boost/serialization/vector.hpp>

struct dataGrid 
{
  std::vector<std::vector< double > > data;
  size_t rows,cols;
  dataGrid():rows(0),cols(0){};
  size_t addRow(){data.push_back(std::vector<double>(cols,0.0)); return rows++;}
  size_t addCol(){for(int i=0; i<data.size(); ++i) data[i].push_back(0.0); return cols++;}
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
      ar & data;
      ar & rows;
      ar & cols;
  }
};

std::ostream& operator << (std::ostream& o, dataGrid d);

#endif
