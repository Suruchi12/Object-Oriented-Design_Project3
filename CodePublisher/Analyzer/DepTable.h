#pragma once
/////////////////////////////////////////////////////////////////////
// DepTable.h - Creates a Dependency Table			               //
// ver 1.0                                                         //  
//																   //
// Language:    C++, Visual Studio 2015                            //
// Platform:    MacBook Pro, Windows 10(dual boot)                 //
// Application: Project #2, CSE687 - Object Oriented Design, S2017 //
// Author:      Suruchi Singh, Syracuse University                 //
//              ssingh11@syr.edu								   //
/////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  ===================
*  DepTable uses TypeTable, FileSystem and AbstrSynTree packages to
*  provide create a dependency table such that all the files dependent
*  on other files are stored in the dependency table as well as the NoSqlDb.
*
*  It finds files for analysis using AbstrSynTree and, for each file found,
*  uses TypeTable to check whether the relationship exists
*  to build a Dependency Table
*
*  DepTable supports displays for:
*  - file name and a list of all .cpp and .h files that each file dependent on.
*  - the data when stored in NoSqlDb and when given an input to an XML file.
*
*
*  Required Files:
*  ---------------
*  - Parser.h, ActionsAndRules.h
*  - AbstrSynTree.h, AbstrSynTree.cpp
*  - IFileMgr.h, FileMgr.h, FileSystem.h
*  - DepAnal.h
*  - TypeTable.h
*  - NoSqlDb.h
*  - xmlpersist.h
*  - XMLDocument.h
*
*  Public Interface Document:
*  ---------------------------
*  - DepTable();     
*	 => Constructor to the class which initialises the ASTRef object.
*  - unordered_map<std::string, std::string> &getdepTable() { return dependencyTable; } 
*	 => returns the created dependency table
*  - vector<string> allfiles(); 
*	 => traverses all components of a given filePath*
*  - NoSqlDb<string> getdb();  
*	 => get the NoSqlDb
*  - void printdatabase();   
*	 => print the generated NoSqlDb
*  - void writexml();    
*	 => write generated NoSqlDb to an Xml File
*  - void getTypetable(unordered_map<std::string, std::pair<std::string, std::string>> typetable_);  
*	 => get the created Type Table
*  - std::unordered_map<std::string, std::set<std::string>> returndeptable();  
*	 => returns the Dependency Table 
*  - void traverseFilePath();   
*	 => get the root node of the FilePath and by recursive call, get each component of the FilePath
*  - void createDependencyTable(); 
*	 => calls a recursive function to add all dependencies into the dependency table of a given file
*  - void DFS(ASTNode* pNode); 
*	 => get all the components of the FilePath
*  - void makedeptable(string filespec);
*	 => recursive call that adds files and its dependencies into the dependency table
*
*  Maintanence History:
*  --------------------
*  ver 1.0
*  - first release
*
*/
#pragma warning (disable : 4101)
#ifndef DEPT_H
#define DEPT_H

#include <iostream>
#include <functional>
#include<unordered_map>
#include<vector>
#include<set>
//#include "../Parser/ActionsAndRules.h"
//#include "../Analyzer/TypeTable.h"
#include"../Analyzer/DepAnal.h"
#include "../FileSystem/FileSystem.h"
#include "../FileMgr/FileMgr.h"
#include "../FileMgr/IFileMgr.h"
#include "../NoSqlDb/NoSqlDb.h"
#//include"../xmlpersist/xmlpersist.h"
#//include "../XmlDocument/XmlDocument/XmlDocument.h"

using namespace std;
//using namespace XmlProcessing;
//using SPTr = std::shared_ptr<AbstractXmlElement>;
using StrData = std::string;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

using namespace CodeAnalysis;  

//class for Dependency Analysis
class DepTable
{
private:
	NoSqlDb<string> db;
	std::set<std::string> pathVector; //store FilePath
	using depTablevalues = std::unordered_map<std::string, std::set<std::string>>; 
	depTablevalues depTable;
	unordered_map<std::string, std::pair<std::string, std::string>> typetable; //store generated typetable 
	AbstrSynTree& ASTref_;

public:
	
	DepTable(); //Constructor to the class which initialises the ASTRef object.
	std::unordered_map<std::string, std::set<std::string>> &getdepTable() { return depTable; } //returns the created dependency table
	vector<string> allfiles(); //traverses all components of a given filePath
	NoSqlDb<string> getdb();  //get the NoSqlDb
	void printdatabase();   //print the generated NoSqlDb
	void dbtoxml(string args);    //write generated NoSqlDb to an Xml File
	void getTypetable(unordered_map<std::string, std::pair<std::string, std::string>> typetable_); //get the created Type Table
	std::unordered_map<std::string, std::set<std::string>> returndeptable(); //returns the Dependency Table 
	void traverseFilePath(); //get the root node of the FilePath and by recursive call, get each component of the FilePath
	void createDependencyTable(); //calls a recursive function to add all dependencies into the dependency table of a given file
	void DFS(ASTNode* pNode); //get all the components of the FilePath
	void makedeptable(string filespec); //recursive call that adds files and its dependencies into the dependency table

};
//constructor to initialize the AbstrSynTree object
inline DepTable::DepTable():ASTref_(Repository::getInstance()->AST())
{
}
//receive populated typetable
inline void DepTable::getTypetable(unordered_map<std::string, std::pair<std::string, std::string>> typetable_)
{
	typetable = typetable_;
}

//Checks for all files when a path is given by traversing the directory
inline vector<string> DepTable::allfiles()
{
	FileSystem::Directory directory;
	FileSystem::Path path;
	vector<string> directoryVector, fileVector,filefound;
	string extention = "";
	string currentDirectory = directory.getCurrentDirectory();
	directoryVector = directory.getDirectories(currentDirectory);
	for (auto ite = directoryVector.begin(); ite != directoryVector.end(); ite++)
	{
		fileVector = directory.getFiles(*ite); auto it = fileVector.begin();
		for (auto it = fileVector.begin(); it != fileVector.end(); it++)
		{
			extention = path.getExt(*it);
			if (extention == "cpp" || extention == "h")
			{
				string filename = "";
				filename.append(*ite);
				filename.append("/");
				filename.append(*it);
				filefound.push_back(filename);
			}
		}
	}
	return filefound;
}

//returns the created dependency table
inline std::unordered_map<std::string, std::set<std::string>> DepTable::returndeptable()
{
	return depTable;
}

//print the generated NoSqlDb
inline void DepTable::printdatabase()
{
	cout << "\n\n---------------------------------------------------\nStoring all dependencies in my NoSql Database\n--------------------------------------------------- \n";
	Keys keys = db.keys();
	for (Key key : keys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
}
//Get the populated Dependency Table
inline NoSqlDb<string> DepTable::getdb()
{
	return db;
}

//function to wrie the populated dependency table to an XML File 
//inline void DepTable::dbtoxml(string args)
//{
//	cout << "\n==================== \nREQUIREMENT 7 \n====================" << endl;
//	cout << "------------------------------------------------------------------------------" << endl;
//	cout << "Witing the dependencies from the database to an XML File called Project2.xml" << endl;
//	cout << "------------------------------------------------------------------------------" << endl;
//	std::ofstream DependencyXML;//DependencyXML.open("./Project2.xml");
//	DependencyXML.open(args);
//	if (DependencyXML.good())
//	{
//		persistxml<string> pxml;
//		string xmlString = pxml.toXml(db);
//		DependencyXML << xmlString;
//		cout << xmlString <<endl;
//	}
//	DependencyXML.close();
//}

//get the root node of the FilePath and by recursive call, get each component
inline void DepTable::traverseFilePath()
{
	ASTNode* pRoot = ASTref_.root();
	DFS(pRoot);
}
//recursive call to get each component(directory,files) of the FilePath provided
inline void DepTable::DFS(ASTNode* pNode)
{
	static std::string path = "";
	if (pNode->path_ != path)
	{
		path = pNode->path_;
		/*path = path + ".htm";
		cout << "Path : "<<path;*/
		
	}
	pathVector.insert(pNode->path_);
	for (auto pChild : pNode->children_)
		DFS(pChild);
}
//create a dependency table by calling a recursive function
inline void DepTable::createDependencyTable()
{
	//cout << "\n==================== \nREQUIREMENT 5 \n====================" << endl;
	cout << "\n****************** \nDEPENDENCY TABLE\n******************\n" << "--------------------------------------------------------------\n";
	cout << std::left<<std::setw(30)<<"FileName" << "Dependent FileName \n" << "--------------------------------------------------------------\n";
	for (auto iter = pathVector.begin(); iter != pathVector.end(); ++iter)
	{
		makedeptable(*iter);
	}
}
//recursive function to store all dependencies of a file
inline void DepTable::makedeptable(string filespec) 
{string fname="";
	if (filespec != "") {
		static std::string path = "";
		try {
			std::ifstream file(filespec);
			if (file.good()) {
				Scanner::Toker toker;
				Element<string> elem;
				vector<string> children;
				std::set<std::string> depVector;
				//elem.name = filespec;
				toker.returnComments();	toker.attach(&file);
				do{
					std::string tok = toker.getTok();
					for (auto tl : typetable){
						if (tok == tl.first)
						{
							//fname = tl.first;      //get the filename
							string packagenamae = tl.second.second;   //get each dependency of the filename
							//packagenamae.pop_back(); //packagenamae.pop_back();
							depVector.insert(packagenamae); //store dependencies in a vector 
						}
					}
				} while (file.good());
				//elem.name = fname;
				elem.name = filespec;
				
				for (auto vecit = depVector.begin(); vecit != depVector.end(); ++vecit){
					children.push_back(*vecit);
				}
				elem.child = db.insertchild(children);    //save dependencies as children of each element into the database
				db.save(elem.name, elem);				  //save each element into the database	
				depTable.insert(std::make_pair(filespec, depVector));
			}
			else{
				cout << "Cannot open the file!";
				exit(0);} std::cout << std::endl;    
			for (auto depTableit = depTable[filespec].begin(); depTableit != depTable[filespec].end(); ++depTableit) {
				//cout << std::left << std::setw(30) << filespec <<"\n"<< *depTableit <<endl;  //print the dependency table
				cout << std::left  << filespec << "\n \t \t" << std::setw(30)<< *depTableit << endl;  //print the dependency table
				cout << "\n \n";
			}
		}
		catch (std::logic_error& ex){
			std::cout << "\n  " << ex.what();
		}
	}
}


#endif

