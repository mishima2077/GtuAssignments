#include "file.h"
#include <iostream>
#include <iomanip>

namespace GTUFile{

File::File(const std::string& _name, const std::time_t c_time)
        :name(_name),creationTime(c_time),size(0)
{
    /*Left blank intentionally*/
}

std::string File::formattedTime()const {
    char res[50];
    strftime(res,50,"%b %d %H:%M",localtime(&creationTime));
    return res;
}

dataFile::dataFile(const std::string& _name, const std::vector<char>& _data,const std::time_t c_time):
        File(_name,c_time),data(_data)
{
    size = calc_size();
}

void dataFile::printInfo(std::ostream& out)const{
    out << "F " << std::left << std::setw(20) << getName() << formattedTime() << " "
        << getSize() << " Bytes";
}

void dataFile::printContent(std::ostream& out)const{
        for(const auto& p : data)
            out << p;
}

int dataFile::calc_size()const{
    return sizeof(char) * data.size();
}

Directory::Directory(const std::string& _name,Directory* _upper,const std::time_t c_time):
                File(_name,c_time),upperDir(_upper)
{
    /*Left blank intentionally*/
}

Directory::~Directory(){
    for(int i = 0; i < fileCount(); ++i)
        delete files[i];
}

void Directory::printInfo(std::ostream& out)const{
    out << "D " << std::left << std::setw(20) << getName() << formattedTime();
}

void Directory::printContent(std::ostream& out)const{
    for(int i = 0; i < files.size(); ++i){
        files[i]->printInfo(out);
        out << std::endl;
    }
}

void Directory::addContent(File* f){
    Directory* directoryFollower = this;
    while(directoryFollower != nullptr){
        directoryFollower->size += f->getSize();
        directoryFollower = directoryFollower->upperDir;
    }
    files.push_back(f);
}

void Directory::deleteContent(const std::string& fileName){
    if(find(fileName) == nullptr) return;
    int ind;
    for(ind = 0; ind < fileCount(); ++ind)
        if(files[ind]->getName() == fileName) break;

    Directory* directoryFollower = this;
    while(directoryFollower != nullptr){
        directoryFollower->size -= files[ind]->getSize();
        directoryFollower = directoryFollower->upperDir;
    }
    delete files[ind];
    files.erase(files.begin() + ind);
}

File* Directory::at(int i)const{
    if(i >= 0 && i < fileCount())
        return files[i];
    return nullptr;
}

File* Directory::find(const std::string& fName)const{
    for(int i = 0; i < fileCount(); ++i)
        if(files[i]->getName() == fName)
            return files[i];
    return nullptr;
}

File* Directory::generalFind(const std::string& fPath ,Directory* root){
    std::vector<std::string> parsedPath = Directory::parsePath(fPath);
    Directory* pathFollower = root;

    for(int i = 0; i < parsedPath.size()-1; ++i){        /*This loop travels the path given by the user to*/
                                                         /*find the file that will be link*/
        if(pathFollower->find(parsedPath[i]) != nullptr && dynamic_cast<Directory*>(pathFollower->find(parsedPath[i])) != nullptr)
            pathFollower = dynamic_cast<Directory*>(pathFollower->find(parsedPath[i]));
        else    
            return nullptr;
    }

    File* linkCandidate = pathFollower->find(parsedPath[parsedPath.size()-1]);
    return linkCandidate;
}

std::vector<std::string> Directory::parsePath(const std::string& path){
    std::vector<std::string> res;
    std::string temp = "";

    for(int i = 0; i < path.size(); ++i){
        if(path[i] != '/')
            temp += path[i];
        else{
            if(temp != ""){
                res.push_back(temp);
                temp.clear();
            }
        }
    }
    res.push_back(temp);
    return res;
}

Link::Link(const std::string& _name,const std::string& _path ,Directory* _root,std::time_t ctime)
        :File(_name,ctime),path(_path),root(_root)
{
    /*Left blank intentionally*/
}

void Link::printInfo(std::ostream& out)const{
    out << "L " << std::left << std::setw(20) << getName() << formattedTime() << " link: " << getPath();
}

void Link::printContent(std::ostream& out)const{
    File* linkedFile = Directory::generalFind(path,root);
    if(linkedFile == nullptr){
        out << "Linked file has been deleted";
        return;
    }

    linkedFile->printContent();
}

File* Link::getLink()const{
    File* linkedFile = Directory::generalFind(path,root);
    Link* linkTest = dynamic_cast<Link*>(linkedFile);

    if(linkedFile!=nullptr && linkTest != nullptr) /*If the linked file is another link, it follows the link to get the main file*/
        return linkTest->getLink();
    else
        return linkedFile;
}

} //GTUFile