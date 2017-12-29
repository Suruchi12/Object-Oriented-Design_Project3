#pragma once
#include "SCC.h"
#include<iostream>
//-------------------- SCC Test Stub 
using namespace std;

#ifdef TEST_SCC
#define TEST_SCC
int main()
{
	cout << "In SCC";
	std::unordered_map<std::string, std::set<std::string>> temp;
	unordered_map<std::string, std::pair<std::string, std::string>> typetable;
	TypeAnal ta; //create an object of TypeTable
	typetable = ta.doTypeAnal();  //return populated type table 
	DepTable dt;				 //create an object for dependency table
	dt.getTypetable(typetable);  //get the populated typetable in the dependency class
	dt.traverseFilePath();
	dt.createDependencyTable();
	temp = dt.returndeptable();  //get the populated dependency table
	NoSqlDb<string> db1 = dt.getdb();			//gets the dependency database
	SCC scc(temp.size(), db1);  //constructor for strongly connected components
	scc.startgraph();           //makes a graph for scc
	scc.sccomponent();			//creates all strongly connected components
	dt.printdatabase(); //print the dependency table
	dt.writexml();      //writes the data to an XML File
	
	return 0;
}

#endif // TEST_SCC