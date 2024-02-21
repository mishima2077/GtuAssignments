#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <string>
#include <ctime>
#include <vector>

namespace GTUFile{

class File{ //Abstract File class
public:
    File(const std::string& _name, const std::time_t c_time = time(0));
    
    virtual void printInfo(std::ostream& out = std::cout)const = 0;
    /*Prints out information about the file*/
    virtual void printContent(std::ostream& out = std::cout)const = 0;
    /*Prints the contents of the file*/

    void setName(const std::string& _name) {name = _name;}
    int getSize()const {return size;}
    std::string getName()const {return name;}
    std::time_t getTime()const {return creationTime;}
    std::string formattedTime()const;
    //Returns the creation time in a formatted way, the format:
    //Mmm Ddd hh::mm

    //Default big three is fine
    virtual ~File()
    {/*Left blank intentionally*/}
private:
    std::string name;
    std::time_t creationTime;
protected:
    int size;
};

class dataFile : public File{
public:
    dataFile(const std::string&, const std::vector<char>&,const std::time_t c_time = time(0));

    virtual void printInfo(std::ostream& out = std::cout)const override;
    virtual void printContent(std::ostream& out = std::cout)const override;

    std::vector<char> getData()const{return data;}

    //Default big three is fine

    //Iterator class for the dataFile
    class Iterator{
    public:
        Iterator(const dataFile& _file, int _ind = 0) : file(_file), ind(_ind)
        {/*Left blank intentionally*/}

        Iterator& operator++() {
            ++ind;
            return *this;
        }

        bool operator==(const Iterator& o)const{return (ind == o.ind && &file == &o.file);}
        bool operator!=(const Iterator& o)const{return !(*this == o);}

        char operator*() const {return file.data[ind];}
    private:
        const dataFile& file;
        int ind;
    };

    Iterator begin()const{
        return Iterator(*this, 0);
    }

    Iterator end()const{
        return Iterator(*this, data.size());
    }
private:
    std::vector<char> data;

    int calc_size()const;
};

class Directory : public File{ 
public:
    Directory(const std::string&, Directory* _upper = nullptr,const std::time_t c_time = time(0));

    virtual void printInfo(std::ostream& out = std::cout)const override;
    virtual void printContent(std::ostream& out = std::cout)const override;

    void addContent(File* f);
    void deleteContent(const std::string& fileName);

    File* at(int i)const;

    File* find(const std::string& fName)const; 
    /*Find a file within itself*/
    static File* generalFind(const std::string& fPath ,Directory* root); 
    /*Find a file from a path within given directory*/

    Directory* getUpper()const {return upperDir;}
    void setUpper(Directory* d) {upperDir = d;}

    int fileCount()const {return files.size();}

    Directory(const Directory& src) = delete;
    Directory& operator=(const Directory& src) = delete;
    /*Implementing copy and assignment operations would require the knowledge
      of all of the classes that are inherited from abstract File class. To make 
      it suitable for further development, I decided not to implement them.*/

    virtual ~Directory();    

    //Iterator class for Directory
    class Iterator{
    public:
        Iterator(Directory& _file, size_t _ind = 0) : file(_file), ind(_ind) 
        {/*Left blank intentionally*/}

        Iterator& operator++() {
            ++ind;
            return *this;
        }

        bool operator==(const Iterator& o)const{return (ind == o.ind && &file == &o.file);}
        bool operator!=(const Iterator& o)const{return !(*this == o);}

        File* operator*()const{return file.at(ind);}
    private:
        const Directory& file;
        int ind;
    };

    Iterator begin(){
        return Iterator(*this, 0);
    }

    Iterator end(){
        return Iterator(*this, files.size());
    }
private:
    std::vector<File*> files;
    Directory* upperDir;

    static std::vector<std::string> parsePath(const std::string&);
};

class Link : public File{
public:
    Link(const std::string& _name ,const std::string& _path,Directory* _root, std::time_t ctime = time(0));

    virtual void printInfo(std::ostream& out = std::cout)const override;
    virtual void printContent(std::ostream& out = std::cout)const override;

    File* getLink()const;
    std::string getPath()const{return path;}

    //Default big three is fine

    /*An Iterator class for Link was not feasible, because it would have to behave differently
      according to the file that it has been linked. Those can be a dataFile, a directory and 
      a link. Because of the nature of the link, there is nothing to iterate from, thats why
      I didn't implement an Iterator class for the Link.*/
private:
    std::string path;
    Directory* root;
};

}//GTUFile
#endif