/**
 * FileSystem class is the core class of the program. It contains the root directory and the current directory.
 * It provides the main functionalities of the file system.
 * It is responsible for adding, removing, moving, searching, listing, sorting and changing directories.
 */
public class FileSystem {
    private Directory root;
    private Directory currentDirectory;

    /**
     * Constructor for the file system.
     * Initializes the root directory and sets the current directory to root.
     */
    public FileSystem(){
        root = new Directory("root", null);
        currentDirectory = root;

        //Adding some initial directories and files
        root.addChild(new Directory("home", root));
        root.addChild(new Directory("etc", root));
        root.addChild(new Directory("var", root));
        root.addChild(new File("fahrenheit.c", root));
        root.addChild(new File("rand.c", root));
        root.addChild(new File("donut.c", root));

        Directory home = (Directory) root.getChild("home");
        home.addChild(new Directory("user1", home));
        home.addChild(new Directory("user2", home));
        home.addChild(new File("py.py", home));

        Directory user1 = (Directory) home.getChild("user1");
        user1.addChild(new File("document.doc", user1));
        user1.addChild(new File("music.mp3", user1));
        user1.addChild(new File("chess.exe", user1));

        Directory user2 = (Directory) home.getChild("user2");
        user2.addChild(new File("image.jpg", user2));
        user2.addChild(new File("video.mp4", user2));
        user2.addChild(new File("mhw.exe", user2));        
    }

    public void print(){
        root.print("");
    }

    /**
     * Adds a new element to the current directory.
     * @param name name of the element
     * @param type type of the element ('d' for directory, 'f' for file)
     * @return true if the element is added successfully, false otherwise
     */
    public boolean addElement(String name, char type){
        if(type == 'd'){
            return currentDirectory.addChild(new Directory(name, currentDirectory));
        }else if(type == 'f'){
            return currentDirectory.addChild(new File(name, currentDirectory));
        } 

        return false;
    }

    /**
     * Removes an element from the current directory with the given name.
     * @param name name of the element to be removed
     * @return true if the element is removed successfully, false otherwise
     */
    public boolean removeElement(String name){
        if(currentDirectory.removeChild(name) != null)
            return true;

        return false;   
    }

    /**
     * Prints the directory tree starting from the root to current directory.
     */
    public void printDirectoryTree(){
        String[] directories = currentDirectory.getPath().split("/");
        String depthSpace = "    ";
        System.out.println("* /");
        for(int i = 2; i < directories.length; i++){
            System.out.println(depthSpace + "* " + directories[i] + "/");
            depthSpace += "    ";
        }
        currentDirectory.listDir(depthSpace);
    }

    /**
     * Sorts and prints out the current directory by creation date.
     */
    public void sortCurrentDir(){
        currentDirectory.sortByDate();
        currentDirectory.listDirWithDate("");
    }

    /** 
     * Moves an element from the current directory to the given path.
     * @param name name of the element to be moved.
     * @param path path to move the element to.
     * @return true if the element is moved successfully, false otherwise
     */
    public boolean moveElement(String name, String path){
        //First, program tries to find and remove the element from the current directory
        FileSystemElement element = currentDirectory.removeChild(name);

        //If the element is found, program tries to find the new directory to add the element
        if(element != null){
            Directory newDirectory = findDirectoryFromPath(path);
            if(newDirectory != null){
                //If the new directory is found, program adds the element to the new directory
                newDirectory.addChild(element);
                return true;
            } else {
                //If the new directory is not found, program adds the element back to the current directory
                currentDirectory.addChild(element);
                return false;
            }
        }
        //If the element is not found, program returns false
        return false;
    }

    /**
     * Searches for an element with the given name starting from the root.
     * @param name name of the element to be searched.
     * @return the element if found, null otherwise.
     */
    public FileSystemElement searchElement(String name){
        return root.recSearch(name);
    }

    /**
     * Changes the current directory to the given path.
     * @param path path to change the current directory to.
     * @return true if the directory is changed successfully, false otherwise.
     */
    public boolean changeDir(String path){
        Directory newDirectory = findDirectoryFromPath(path);
        if(newDirectory != null){
            currentDirectory = newDirectory;
            return true;
        } else
            return false;
    }

    /**
     * Lists the contents of the current directory.
     * @param prefix prefix to print before the file system element.
     */
    public void listCurrentDir(String prefix){
        currentDirectory.listDir(prefix);
    }

    /**
     * Returns the path of the given element, with linux path format.
     * @param element element to get the path of.
     * @return the path of the element.
     */
    public static String getPathOfElement(FileSystemElement element){
        String[] seperated = element.getPath().split("/");

        //First element is null and second element is root, we don't need them on the path
        String res = "";
        for(int i = 2; i < seperated.length; ++i)
            res += "/" + seperated[i];
        return (res.equals("") ? "/" : res);
    }

    /**
     * Returns the path of the current directory, with linux path format.
     * @return the path of the current directory.
     */
    public String getCurrentPath(){
        return getPathOfElement(currentDirectory);
    }

    /**
     * Finds the directory from the given path.
     * @param path path to find the directory from.
     * @return the directory if found, null otherwise.
     */
    private Directory findDirectoryFromPath(String path){
        if(path.equals("/")) return root;
        String[] pathSeperated = path.split("/");
        if(pathSeperated.length == 0) return null;

        Directory dir = root;
        FileSystemElement test;

        //If there is only one element, program checks the special conditions and looks at the current Directory
        if(pathSeperated.length == 1){
            if(pathSeperated[0].equals("..")){
                if(currentDirectory.getParent() != null) return (Directory) currentDirectory.getParent();
                else return currentDirectory;
            }
            if(pathSeperated[0].equals("."))
                return currentDirectory;
            test = currentDirectory.getChild(pathSeperated[0]);
            if(test != null && test instanceof Directory)
                return (Directory) test;
            else
                return null;
        }

        //Otherwise, program tracks the given path from root
        for(int i = 1; i < pathSeperated.length; i++){
            test = dir.getChild(pathSeperated[i]);
            if(test != null && test instanceof Directory){
                dir = (Directory) test;
            }else{
                return null;
            }
        }
        return dir;
    }
}
