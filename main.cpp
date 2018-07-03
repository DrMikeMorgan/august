#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <fstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "Module.h"

void enter(Module& module, std::string& prompt)
  {  
	std::string cmp;     
       std::cout<< "Which component: " << module.getEditableList() << std::endl;
       getline(std::cin, cmp);
       while(!module.isComponent(cmp) || !module.isEditable(cmp)){
		std::cout<< "Not an editable component, enter again: " << module.getEditableList() << std::endl;
       		getline(std::cin, cmp);
	}
      
       for(;;)
         {
            std::string ID;
            double value;
            std::cout << "Enter ID: ";
            getline(std::cin, ID);
	    if(ID == "back") break;
	    while(!module.isStudent(ID)){
		std::cout << "ID does not exist, try again: ";
            	getline(std::cin, ID);
	    }
            
            std::cout << "Enter Mark: ";
            std::cin >> value; 
            std::cin.ignore(10,'\n');
	    while(value > 100 || value < 0){
		std::cout << "Should be between 0 and 100, again: ";
            	std::cin >> value; 
            	std::cin.ignore(10,'\n');
		}
	    std::cout << (module.insert(ID,cmp,value)? "\t\t\t\tEntry Successful":"\t\t\t\tUh-oh...") << std::endl;
         }
      module.update();
  }

  void lookup(Module module, std::string& prompt)
  {
       std::string cmp;
       std::cout<<"Enter Component(s), separated by spaces " << std::endl << module.getComponentList() << " ALL" << std::endl;
       getline(std::cin, cmp);
       if(cmp == "ALL") cmp = module.getComponentList();
       
       std::vector<std::string> line;
       boost::trim(cmp);
       boost::split(line, cmp, boost::is_any_of(" "));
       
        for(;;)
          {
             std::string ID;
             std::cout<<"Enter ID (or ALL): ";
             getline(std::cin, ID);
	     if(ID == "back") break;
	     

	     if(ID == "ALL")
		{
			std::cout << "\t\t";
			for(int j=0; j<line.size(); ++j){
				if(!module.isComponent(line[j])) continue;
					std::cout << '\t' << line [j];
			}
			std::cout << std::endl;

			for(size_t i=0; i<module.rowCount(); ++i)
			{
				std::cout << module.getName(i) << ": " ;
				size_t tabs = 3;
				tabs -= (module.maxKeyLength()+2)/8;
				std::cout << std::string(tabs,'\t');
				for(int j=0; j<line.size(); ++j)
				     {
					if(!module.isComponent(line[j])) continue;
					std::cout << module.get(i,line[j]) << (j<(line.size()-1)?"\t":"");
				     }
				     std::cout << std::endl;
			}
			continue;
		}
	     while(!module.isStudent(ID)){
		std::cout << "ID does not exist, try again: ";
            	getline(std::cin, ID);
	     }

		for(int j=0; j<line.size(); ++j){
			if(!module.isComponent(line[j])) continue;
				std::cout << '\t' << line [j];
		}
		std::cout << std::endl;
                  
             for(int i=0; i<line.size(); ++i)
	     {
		
		if(!module.isComponent(line[i])) continue;
                std::cout << '\t' << module.get(ID,line[i]);
	     }
             std::cout << std::endl;
          }
    }

void recursiveComponentEntry(Module& l, std::string& name, std::string& prompt)
{
  
  for(char more = 'y'; more != ']';){
    
    std::cin >> more;
    
    if(more == ']') break;
    
    else if(more == '['){
    std::string cmpName;
    double weight;
    std::cin >> cmpName >> weight;
    if(l.addSubcomponent(name,cmpName,weight))
	std::cout << "Added sub: " << name << "-->" << cmpName << std::endl;
    else std::cout << "Invariant invalidated: " << name << "-->" << cmpName << std::endl;
    recursiveComponentEntry(l,cmpName,prompt);
       }
    }
   
}

  void create(std::vector<Module>& modules, std::string& prompt)
  {
      std::string name;
      std::cout << "Enter Module Descriptor: ";
      std::cin >> name;
      size_t m = modules.size();
      modules.push_back(Module(name));
      prompt.append(name);
      recursiveComponentEntry(modules[m], name, prompt);
      std::cin.ignore (1000, '\n');
    
      //name.append(".csv"); swap with this when mod csvs set up - or do file search thingy (boost)
      name = "test.csv";
      modules[m].importCSVIDs(name);
  }
  
void manage( std::vector<Module>& modules, std::string prompt)
{
     std::string code;
       std ::cout << "Enter module code: ";
       getline(std::cin, code);
       size_t finder=modules.size();
       for(int i=0; i<modules.size(); ++i)
         if(modules[i].getName() == code)
           finder = i;
       if(finder == modules.size()){
         std::cout << "No such module" << std::endl;
         return;
       }
     
     for(;;)
	{
	     size_t choice;
	     std::cout << "\033[2J" << "Managing module " << code << std::endl << "Enter results (1), view (2) or go back (3): ";
	     std::cin >> choice;
	     std::cin.ignore(10,'\n');
	     switch(choice)
		{
			case 1: enter(modules[finder],prompt);break;
			case 2: lookup(modules[finder],prompt);break;
			case 3: return;
			default: break;
		} 
	}
}
int main()
  { 
       std::vector<Module> modules;
       std::string prompt = "-->";
       
       for(int choice=0;choice != 3; )
         {
	    std::cout << "\033[2J";
            std::cout << "Manage a module (1), Create a module (2) or quit (3): " << std::endl;//template iostream
   
            std::cin >> choice;
            std::cin.ignore(100,'\n');
	    
            switch(choice)
              {
                case 1: manage(modules, prompt);break;
                case 2: create(modules, prompt);break;
                default: break;

              }
         
         }   
        std::ofstream file("state.txt");
        {
            boost::archive::text_oarchive oa(file);
              // write class instance to archive
            oa << modules;
    	        // archive and stream closed when destructors are called
        }

        return 0;
  }
