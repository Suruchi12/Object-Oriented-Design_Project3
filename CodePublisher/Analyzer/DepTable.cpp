
#pragma once
/////////////////////////////////////////////////////////////////////
// Publish.h - Creates a Code Publisher			                   //
// ver 1.0                                                         //  
//								     							   //
// Language:    C++, Visual Studio 2015                            //
// Platform:    MacBook Pro, Windows 10(dual boot)                 //
// Application: Project #3, CSE687 - Object Oriented Design, S2017 //
// Author:      Suruchi Singh, Syracuse University                 //
//              ssingh11@syr.edu				                   //				   
/////////////////////////////////////////////////////////////////////
#include "DepTable.h"
#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
//--------------------Dependency Table TEST STUB
#ifdef TEST_DEPTABLE
#define TEST_DEPTABLE
int main()
{
	DepTable dt;
	unordered_map<std::string, std::pair<std::string, std::string>> typetable;
	std::unordered_map<std::string, std::set<std::string>> temp;
	
	/*string Key="",Key1="";
	cout << "HI from dep table!"<<endl;
	std::pair<std::string, std::string> value,value1;
	Key1 = "Key1";
	value1.first = "value.first1";
	value1.second = "value.second1";
	typetable.insert(std::make_pair(Key1, value1));
	Key = "Key2";
	value.first = "value.first2";
	value.second = "value.second2";
	typetable.insert(std::make_pair(Key, value));
*/
	/*for (auto it : typetable)
		cout << it.first<<it.second.first<<it.second.second;*/
	
	TypeAnal ta; //create an object of TypeTable
	typetable = ta.doTypeAnal();  //return populated type table 
	//create an object for dependency table
	 dt.getTypetable(typetable);  //get the populated typetable in the dependency class
	 dt.traverseFilePath();
	 dt.createDependencyTable();
	temp = dt.returndeptable();  //get the populated dependency table
	NoSqlDb<string> db1 = dt.getdb();			//gets the dependency database


	return 0;
}

#endif TEST_DEPTABLE
