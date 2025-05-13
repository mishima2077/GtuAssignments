#include "shell.h"
#include "file.h"
#include <string>
#include <stdexcept>
#include <fstream>
#include <iomanip>


namespace GTUFile{

Shell::Shell():root("."),currentDir(&root){
    try{
        initialize();
    }
    catch(const std::exception& e){
        std::cout << "No previous shell has been found, creating a new shell.\n";
    }
}

Shell::~Shell(){
    try{
        saveShell();
    }
    catch(const std::exception& e){
        std::cout << "Shell saving has failed, terminating the program without saving.\n";
    }
}

void Shell::Start(){
    Shell::openingScreen();
    int exceptCount = 0;

    std::vector<std::string> input;
    do{
        try{
            std::cout << ">";

            input.clear();
            Shell::parseInput(input);

            commandSeperator(input);
        }
        catch(const std::exception& e){
            ++exceptCount;
            std::cout << e.what() << std::endl;
            if(exceptCount == 3){
                std::cout << "Type help to see the usage of the comands\n";
                exceptCount = 0;
            }
        }
    }while(input[0] != "exit");
}

void Shell::commandSeperator(const std::vector<std::string>& input){
    if(input.size() == 0)
        throw std::invalid_argument("Invalid command");

    if(input[0] == "mkdir")
        mkdir(input);
    else if(input[0] == "ls")
        ls(input);
    else if(input[0] == "cd")
        cd(input);
    else if(input[0] == "cp")
        cp(input);
    else if(input[0] == "cat")
        cat(input);
    else if(input[0] == "rm")
        rm(input);
    else if(input[0] == "link")
        link(input);
    else if(input[0] == "pwd")
        pwd(input);
    else if(input[0] == "help")
        Shell::helpMenu();
    else if(input[0] == "exit")
        return;
    else 
        std::cout << "Type help to see available commands\n";
}

void Shell::mkdir(const std::vector<std::string>& input){
    if(input.size() == 1)
        throw std::invalid_argument("No name given to the directory");

    if(input.size() != 2)
        throw std::invalid_argument("Invalid argument given to command mkdir");

    if(currentDir->find(input[1]) != nullptr)
        throw std::invalid_argument("Can't have files with same names in a directory");
    
    Directory* tempD = new Directory(input[1],currentDir);
    currentDir->addContent(tempD);
}

void Shell::ls(const std::vector<std::string>& input)const{
    if(input.size()==1){
        std::cout << "D " << std::left << std::setw(20) << "." << currentDir->formattedTime() << std::endl;
        if(currentDir->getUpper() != nullptr)
            std::cout << "D " << std::left << std::setw(20) << ".." << currentDir->getUpper()->formattedTime() << std::endl;
        
        currentDir->printContent();
    }
    else if(input.size()==2 && input[1] == "-R"){
        lsRecursive(currentDir);
    }
    else
        throw std::invalid_argument("Invalid argument given to command ls");
}

void Shell::lsRecursive(const Directory* d,int depth)const{
    for(int i = 0; i < d->fileCount(); ++i){
        for(int j = 0; j < depth; ++j) /*Spacing according to the depth*/
            std::cout << "    ";

        d->at(i)->printInfo();
        std::cout << "\n";
        if(dynamic_cast<Directory*>(d->at(i))!=nullptr)
            lsRecursive(dynamic_cast<Directory*>(d->at(i)),depth + 1);
    }
}

void Shell::cd(const std::vector<std::string>& input){
    if(input.size() != 2)
        throw std::invalid_argument("Invalid argument given to command cd");

    if(input[1] == "/"){
        currentDir = &root;
        return;
    }
    if(input[1] == ".." && currentDir->getUpper() != nullptr){
        currentDir = currentDir->getUpper();
        return;
    }
    
    File* temp = currentDir->find(input[1]);
    Directory* tempD = dynamic_cast<Directory*>(temp); /*Checks if the said file is a directory*/
    if(tempD != nullptr){
        currentDir = tempD;
        return;
    }

    Link* tempL = dynamic_cast<Link*>(temp); /*Checks if the said file is a link linked to a directory*/
    if(tempL != nullptr){
        if(tempL->getLink() == nullptr){
            std::cout << "Linked file has been deleted\n";
            return;
        }
        tempD = dynamic_cast<Directory*>(tempL->getLink());
        if(tempD != nullptr){
            currentDir = tempD;
            return;
        }
        else{
            std::cout << "Linked file is not a directory\n";
            return;
        }
    }

    throw std::invalid_argument("There is no directory named " + input[1] + " in current directory");
}

void Shell::cp(const std::vector<std::string>& input){
    if(input.size() != 3)
        throw std::invalid_argument("Invalid argument given to command cp");

    if(currentDir->find(input[2]) != nullptr)
        throw std::invalid_argument("Can't have files with same names in a directory");
    
    File* newFile;
    std::string path = input[1];
    if(path[0] != '/') /*This part changes the local path to a complete path*/
        path = completePath(path);
    File* targetFile = Directory::generalFind(path,&root);

    std::ifstream ifile;
    ifile.open(input[1]);
    if(ifile.is_open()){ /*Program priorities the OS to shell copy, checks it first.
                           If it can't find it on the OS, program then tries to find
                           the file at its shell.*/
        std::vector<char> _data;
        char byte;
        while(ifile.get(byte))
            _data.push_back(byte);
        newFile = new dataFile(input[2],_data);
        ifile.close();
    }
    else if(targetFile != nullptr){
        if(dynamic_cast<dataFile*>(targetFile)!=nullptr)
            newFile = new dataFile(*dynamic_cast<dataFile*>(targetFile));
        else if(dynamic_cast<Link*>(targetFile)!=nullptr)
            newFile = new Link(*dynamic_cast<Link*>(targetFile));
        else if(dynamic_cast<Directory*>(targetFile)!=nullptr){
            newFile = new Directory(input[2],currentDir);
            copyDir(dynamic_cast<Directory*>(newFile),dynamic_cast<Directory*>(targetFile));
        }
        newFile->setName(input[2]);
    }
    else
        throw std::invalid_argument("Failed to find the file");

    /*Checks if there is enought space for the new file on the disk*/
    if(root.getSize() + newFile->getSize() > 10000000){
        delete newFile;
        throw std::overflow_error("Not enough space in the disk");
    }
    
    if(input[2] == ".")
        newFile->setName(nameFromPath(input[1]));
    currentDir->addContent(newFile);
}

void Shell::cat(const std::vector<std::string>& input)const{
    if(input.size() != 2)
        throw std::invalid_argument("Invalid argument given to command cat");

    File* temp = currentDir->find(input[1]);
    if(temp == nullptr)
        throw std::invalid_argument("File has not been found");

    if(dynamic_cast<Directory*>(temp) != nullptr)
        throw std::invalid_argument(input[1] + " is a directory");

    Link* linkCheck = dynamic_cast<Link*>(temp);
    if(linkCheck != nullptr)
        if(dynamic_cast<Directory*>(linkCheck->getLink()))
            throw std::invalid_argument(input[1] + " is linked to a directory");

    temp->printContent();
    std::cout << std::endl;
}

void Shell::rm(const std::vector<std::string>& input){
    if(input.size() != 2)
        throw std::invalid_argument("Invalid argument given to command rm");

    if(currentDir->find(input[1]) == nullptr)
        throw std::invalid_argument("There is no file named " + input[1] + " in current directory");

    currentDir->deleteContent(input[1]);
}

void Shell::link(const std::vector<std::string>& input){
    if(input.size() != 3)
        throw std::invalid_argument("Invalid argument given to command link");

    std::string path = input[1];
    if(path[0] != '/') /*If the user has given a local path, starting from the current directory, we need to complete it*/
                       /*before sending it to the link. Paths must start from the root for the links*/
        path = completePath(std::move(path));

    Link* linkCandidate = new Link(input[2],path,&root);
    if(linkCandidate->getLink() == nullptr){
        delete linkCandidate;
        throw std::invalid_argument("Invalid path or file");
    }

    currentDir->addContent(linkCandidate);   
}

void Shell::pwd(const std::vector<std::string>& input)const{
    if(input.size() != 1)
        throw std::invalid_argument("Invalid argument given to command pwd");

    std::cout << completePath() << std::endl;
}

void Shell::parseInput(std::vector<std::string>& v){
    std::string temp;
    do{
        std::cin >> temp;
        v.push_back(temp);
    }while(getchar() != '\n');
}

std::string Shell::nameFromPath(const std::string& path){ 
    std::string name_reversed;
    std::string name;

    //UPDATE TO ITERATOR
    for(int i = path.size() - 1; i >= 0; --i){
        if(path[i] != '/')
            name_reversed.push_back(path[i]);
        else 
            break;
    }
    for(int i = name_reversed.size()-1; i >= 0; --i)
        name.push_back(name_reversed[i]);

    return name;
}

std::string Shell::completePath(const std::string& path)const{
    Directory* dirFollower = currentDir;
    std::vector<std::string> reversedRes;
    std::string res = "";
    while(dirFollower != &root){
        reversedRes.push_back(dirFollower->getName());
        dirFollower = dirFollower->getUpper();
    }

    for(auto p = reversedRes.rbegin(); p != reversedRes.rend(); ++p){
        res += '/';
        res += *p;
    }
    if(path != ""){
        res += '/';
        res += path;
    }
    return (res == "") ? "/" : res;
}

void Shell::openingScreen(){
    std::cout << "*";
    for(int i = 0; i < 63; ++i)
        std::cout << "-";
    std::cout << "*\n*";
    for(int i = 0; i < 29 ; ++i)
        std::cout << " ";
    std::cout << "MyShell\n";
    
    std::cout << "*Type help to see the commands\n";

    std::cout << "*";
    for(int i = 0; i < 63; ++i)
        std::cout << "-";
    std::cout << "*\n";
}

void Shell::helpMenu(){
    std::cout << "Commands:\n\n";
    std::cout << "ls : lists files in the current directory,\n"
              << "give -R as argument to use it recursively\n\n";
    std::cout << "mkdir |directoryName| : crates a directory named directoryName\n\n";
    std::cout << "rm |fileName| : deletes the file named fileName from the"
              << " current directory\n\n";
    std::cout << "cp |filePath| |fileName| : copies the file from the given path\n"
              << "to current directory, names it fileName. If fileName is . then\n"
              << "the name will be taken from the copied file.\n\n";
    std::cout << "link |sourceFile| |linkName| : makes a soft link between the\n"
              << "source file and a link named linkName\n\n";
    std::cout << "cd |dirName| : changes the current directory to directory named dirName\n\n";
    std::cout << "cat |fileName| : prints the content of the file named fileName\n\n"; 
    std::cout << "help : prints out the command menu\n\n";
}

void Shell::initialize(){
    std::ifstream ifile;
    ifile.open("myShell.txt");

    if(!ifile.is_open())
        throw std::exception();

    int rootFileCount;
    ifile >> rootFileCount;
    ifile.get();

    initDir(ifile,&root,rootFileCount);

    ifile.close();
}

void Shell::saveShell()const{
    std::ofstream ofile;
    ofile.open("myShell.txt");

    if(!ofile.is_open())
        throw std::exception();

    ofile << root.fileCount() << "\n";
    writeDir(ofile,&root);

    ofile.close();
}

void Shell::initDir(std::istream& in,Directory* d, int fileCount, int ind){
    if(ind >= fileCount)
        return;

    char fileType;
    std::string fileName;
    std::time_t c_time;

    in >> fileType >> fileName >> c_time;
    if(fileType == 'F'){
        int byte;
        in >> byte;
        in.get();

        std::vector<char> _data;
        for(int i = 0; i < byte; ++i)
            _data.push_back(in.get());
        in.get();

        dataFile* newFile = new dataFile(fileName,_data,c_time);
        d->addContent(newFile);
    }
    else if(fileType == 'L'){
        std::string _path;
        in >> _path;
        in.get();

        Link* newLink = new Link(fileName,_path,&root,c_time);
        d->addContent(newLink);
    }
    else if(fileType == 'D'){
        int newFileCount;
        in >> newFileCount;
        in.get();

        Directory* newDir = new Directory(fileName,d,c_time);
        initDir(in,newDir,newFileCount);
        d->addContent(newDir);
    }
    else
        throw std::exception();

    initDir(in,d,fileCount,++ind);
}

void Shell::writeDir(std::ostream& out,const Directory* d,int ind)const{
    if(ind >= d->fileCount())
        return;

    if(dynamic_cast<dataFile*>(d->at(ind)) != nullptr){ //If the file is a data file
        dataFile* temp = dynamic_cast<dataFile*>(d->at(ind));

        out << "F " << temp->getName() << " " << temp->getTime() << " " << temp->getSize() << "\n";
        temp->printContent(out);
        out << "\n";
    }
    else if(dynamic_cast<Link*>(d->at(ind)) != nullptr){ //If the file is a link
        Link* temp = dynamic_cast<Link*>(d->at(ind));

        out << "L " << temp->getName() << " " << temp->getTime() << " " << temp->getPath() << "\n";
    }
    else if(dynamic_cast<Directory*>(d->at(ind)) != nullptr){ //If the file is a directory
        Directory* temp = dynamic_cast<Directory*>(d->at(ind));

        out << "D " << temp->getName() << " " << temp->getTime()
            << " "  << temp->fileCount() << "\n";
        writeDir(out,temp);
    }
    else
        throw std::exception();

    writeDir(out,d,++ind);
}

void Shell::copyDir(Directory* target,Directory* source){
    File* newFile;
    for(int i = 0; i < source->fileCount(); ++i){
        if(dynamic_cast<dataFile*>(source->at(i))!=nullptr)
            newFile = new dataFile(*dynamic_cast<dataFile*>(source->at(i)));
        else if(dynamic_cast<Link*>(source->at(i))!=nullptr)
            newFile = new Link(*dynamic_cast<Link*>(source->at(i)));
        else{
            Directory* newD = new Directory(source->at(i)->getName(),target);
            copyDir(newD,dynamic_cast<Directory*>(source->at(i)));
            newFile = newD;
        }
        target->addContent(newFile);
    }
}

}//GTUFile
