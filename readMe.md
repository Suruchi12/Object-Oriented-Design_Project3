# Code Publisher

#### Object Oriented Design
#### CSE 687
#### Project 3

## Workings of the Project
There are three arguments in my command line.
-The first one is to run the Code Publisher on any given directory(file path) such that all the files in that directory will be published on the
browser with its dependencies.
-The second argument has the extentions .cpp or .h(file patterns) which will publish the files with those extentions as they are being inserted into
the dependency table.
-The third argument contains the name of any HTML file which will open on the broswer after you run the project.

-The project opens on two browsers because one is from the command line where when you give any HTML file as an input, 
it runs that HTML file and all the links associated with it.
The other browser opens the main page which is the start file where all the links of all the files are present and 
you can traverse to any other file through it.

***Requirement 1***

Used Visual Studio 2015 and its C++ Windows console projects, as provided in the ECS computer labs.

***Requirement 2***

Used the C++ standard library's streams for all console I/O and new and delete for all heap-based memory management1.

***Requirement 3***

Provides creation of web pages of .cpp and .h files from the dependency table

***Requirement 4***

Expands and collapses classes and functions

***Requirement 5***

Provides a css file

***Requirement 6***

The head of the HTML file contains links to the css file

***Requirement 7***

Each HTML file has its name on top and then the links to the depenedency files

***Requirement 8***

There is a command line processing for file path and patterns

***Requirement 9***

The code runs on the Analyzer Project
