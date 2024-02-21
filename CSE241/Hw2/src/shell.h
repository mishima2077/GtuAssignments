#ifndef SHELL_H
#define SHELL_H
#include "file.h"
#include <vector>
namespace GTUFile{

class Shell{
public:
    Shell();
    ~Shell();

    void Start();
private:
    Directory root;
    Directory* currentDir;

    /*Shell commands*/
    void mkdir(const std::vector<std::string>& input);
    void ls(const std::vector<std::string>& input)const;
    void cd(const std::vector<std::string>& input);
    void cp(const std::vector<std::string>& input);
    void cat(const std::vector<std::string>& input)const;
    void rm(const std::vector<std::string>& input);
    void link(const std::vector<std::string>& input);
    void pwd(const std::vector<std::string>& input)const;

    /*-----------------Helper Functions-----------------*/
    static void parseInput(std::vector<std::string>& v);
    /*Seperates the strings in given input, puts them into string vector*/

    void commandSeperator(const std::vector<std::string>& input);
    /*Calls the commands according to the given input*/

    void lsRecursive(const Directory* d,int depth = 0)const;
    static std::string nameFromPath(const std::string& path);
    std::string completePath(const std::string& path = "")const; 
    /*Non complete path: myDir2/myFile */
    /*Complete path: /myDir/myDir2/myFile  myDir is on the root*/

    static void openingScreen();
    static void helpMenu();
    void initialize();
    void saveShell()const;

    void writeDir(std::ostream& out,const Directory* d,int ind = 0)const;
    void initDir(std::istream& in,Directory* d, int fileCount, int ind = 0);
    void copyDir(Directory* target,Directory* source);
};

}//GTUFile
#endif