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
/*
*  Package Operations:
*  ===================
*  Publishes all the files with extentions .cpp and .h and their dependent files on the browser.
*
*  Publish.h supports displays on the browser for:
*  - The contents of .cpp and .h files and the links to their dependent files and scope hiding and unhiding.
*
*
*
*  Public Interface Document:
*  ---------------------------
*  -void publishAllFiles();
*   =>creates html files obtained from the dependency table
*  -void toHtm(string pathof);
*    => generates html file of all the .h and .cpp files
*  -void createStartFile();
*    => creates an html file with all the links of the html files created
*
*  Maintanence History:
*  --------------------
*  ver 1.0
*  - first release
*
*/
#include <iostream>
#include <functional>
#include<unordered_map>
#include<vector>
#include<set>
#include <direct.h>
#include<fstream>
#include <iterator>
#include<string>

using namespace std;
using namespace CodeAnalysis;

class PublishFiles
{
    private:
		string dirName = "../HtmlFolder";
		vector<string> depfiles;
		vector<string> childvec;
		vector<string> filevector;
    public: 
	  using depTablevalues = std::unordered_map<std::string, std::set<std::string>>;
	  depTablevalues depTable;
	  PublishFiles(std::unordered_map<std::string, std::set<std::string>> getDepTable)
	  {
		  depTable = getDepTable;  
		  _mkdir(dirName.c_str());
	  }
	  void createStyleSheet();  //create style sheet
	  void createStartFile();   //create a home page
	  void publishAllFiles();   //runs on dependency table to get files and their dependencies
	  void toHtm(string pathof); //creates html files
	  void createJavaScript();
};

//creates a style sheet for the html files
inline void PublishFiles::createStyleSheet()
{
	string stylesheet = "../HtmlFolder/stylesheet.css";
	ofstream stylefile(stylesheet);
	stylefile << "body{" << endl;
	stylefile << "margin:20px; color:black; background-color:#E3E4FA;" << endl;
	stylefile << "font-family:Consolas; font-weight:600; font-size:110%;" << endl;
	stylefile << "}" << endl;
	stylefile << ".indent{ margin-left:20px; margin-right:20px; }" << endl;
	stylefile << "h4{ margin-bottom: 3px; margin-top:3px; }" << endl;
	stylefile.close();
}

//creates a JavaScript file for expanision and collapse of function and classes
inline void PublishFiles::createJavaScript()
{
	string javascriptfile = "../HtmlFolder/P3jsfile.js";
	ofstream jsfile(javascriptfile);
	jsfile << "function HideUnhide(count) {"<<endl;
	jsfile << "var x = document.getElementById(count);"<<endl;
	jsfile << "if (x.style.display === 'none')"<<endl;
	jsfile << "{"<<endl;
	jsfile << "x.style.display = 'block';"<<endl;
	jsfile << "}"<<endl;
	jsfile << "else"<<endl;
	jsfile << "{"<<endl;
	jsfile << "x.style.display = 'none';"<<endl;
	jsfile << "}"<<endl;
	jsfile << "}"<<endl;
	//jsfile << "</script>" << endl;
	jsfile.close();
}

//runs on the entire dependency table so as to get all the files and their dependencies
inline void PublishFiles::publishAllFiles()
{  
	cout << "\n\n PUBLISHING FILES!" << endl;
	for (auto it : depTable)
	{  
		cout << it.first<<endl;
		 string sourcepath = "";
		 sourcepath=  it.first; 
	
		string sourcefile = it.first;
		cout << "DEPENDENT FILES: " << endl;
		for (auto depTableit = depTable[it.first].begin(); depTableit != depTable[it.first].end(); depTableit++)
		{
			string dependencypath = *depTableit;string path; string tempath;
			size_t found = dependencypath.find_last_of("/\\");  //removing backslash
		    tempath = dependencypath.substr(found + 1);  //getting filename
			string fileName = "";
			tempath = "/" + tempath + ".htm";   //adding .htm extention
			fileName.append(dirName);
			fileName.append(tempath);
			cout << "File name : \t" << fileName;
			childvec.push_back(fileName);
			cout << "\n \n";
		}
		toHtm(sourcefile);
		filevector.push_back(sourcefile);
		childvec.clear();
	}
	createStartFile();
}

//generates the html files of all the files in the dependency table and stores them in a directory
inline void PublishFiles::toHtm(string filepath){
	string filename = ""; 
    ifstream inputFile(filepath);
	string path = filepath; string tempath; string str; 
	size_t found = path.find_last_of("/\\");  //removing backslash
	tempath = path.substr(found + 1);  //getting filename
	string NameofFile = ""; NameofFile.append(tempath);
	tempath = "/" + tempath + ".htm";  //append with .htm 
	filename.append(dirName); //append with directory name
	filename.append(tempath);  //append with .htm after directory name
	ofstream file(filename);
	file << "<html>"<<endl<< "<pre>"<<endl<<"<head>";
	file << "<link rel=" << "stylesheet" << " type=" << "text/css" << " href=" << "../HtmlFolder/stylesheet.css" << ">";
	file << "<script>";
	file << "function HideUnhide(count) {";
	file << "var x = document.getElementById(count);";
	file << "if (x.style.display === 'none')"<< "{";
	file << "x.style.display = 'block';"<< "}";
	file << "else"<< "{";
	file << "x.style.display = 'none';"<<"}"<< "}";
	file<<"</script>" << endl;
	file << NameofFile << endl; file << "</head>" << endl;
	for (auto depit = childvec.begin(); depit != childvec.end(); depit++){  //iterate on the dependent files to create links
		string dependentfile = *depit;
		cout <<"Dependent File:"<< dependentfile <<endl;
		file << "Dependent File: "; 
		size_t found = dependentfile.find_last_of("/\\");  //removing backslash
		string templink = ""; string link = "";
		templink.append(dependentfile.substr(found + 1));
		size_t found1 = templink.find_last_of(".");  //removing .htm
		link.append(templink.substr(0,found1));      
		file << "<a href =" << dependentfile << ">" << link << " </a>";file << "<br>";  //creating links for the dependent files
	}char getchar; int count = 0;
	while (inputFile.get(getchar)){
		if (getchar == '<')
			file << "&lt;";  //replaces all < with &lt
		else if (getchar == '>')
			file << "&gt;";      //replaces all > with &gt
		else if (getchar == '{'){
			file << "<button onclick=\"HideUnhide(" << count << ")\">-</button>";    
			file << "<div id=" << "\"" << count << "\"" << ">";
			count++;}
		else if (getchar == '}')
			file << getchar << "</div>" << endl;  
		else 
			file << getchar;}  //writing to the file
	file << "</pre>"<<endl<< "</html>";
	inputFile.close(); file.close();
}
//creating a home page with all the links of the files to be published
void PublishFiles::createStartFile()
{	string start = ""; string sfile = "startfile";string tempath;
	start.append(dirName);
	start.append("/" + sfile + ".htm");
	ofstream startfile(start);
	startfile << "<html>";
	startfile << "<pre>";
	startfile << "<head>" << endl;
	startfile << "Home Page:" << endl;
	startfile << "All the Files present are as follows:" << endl;	
	startfile << endl;
	//startfile << "<script type=\"text/javascript\" src=\"../CodePublisher/Project2Script1.js\">" << endl;
	startfile << "</script>" << endl;
	startfile << "<link rel=" << "stylesheet" << " type=" << "text/css" << " href=" << "../HtmlFolder/stylesheet.css" << ">";
	startfile << "</head>";
	//startfile << "<body>";
	//startfile << "<button onclick = \"StartHidUnhide()\">-</button>";
	//startfile << "<div id =\"hideDIV\">";
	for (auto fileit : filevector)
	{
		string templink = ""; string link = "";
		size_t found = fileit.find_last_of("/\\");  //removing backslash
		tempath = fileit.substr(found + 1);  //getting filename
		string fileName = "";
		tempath = "/" + tempath + ".htm";  //adding extention
		fileName.append(dirName);
		fileName.append(tempath);
		size_t found2 = fileName.find_last_of("/\\");  //removing backslash
		templink.append(fileName.substr(found2 + 1));
		size_t found3 = templink.find_last_of(".");  //removing .htm
		link.append(templink.substr(0, found3));
		startfile << "<a href =" << fileName << ">" << link << " </a>";
		startfile << endl;
	}
	//startfile << "</div>" << endl;
	startfile << "</body>";
	startfile << "</pre>";
	startfile << "</html>";
	startfile.close();
	std::string runonbrowser("start \"\" \"" + start + "\"");  
	std::system(runonbrowser.c_str());
}

