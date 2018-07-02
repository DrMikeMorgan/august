#include "dataGrid.h"
#include <iostream>

std::ostream& operator << (std::ostream& o, dataGrid & d)
{
  for(int i=0; i<d.data.size(); ++i){
    for(int j=0; j<d.data[i].size(); ++j)
      o << d.data[i][j] << ", ";
    o << std::endl;
  }
  return o;
}
