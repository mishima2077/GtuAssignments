import java.util.LinkedList;

/**
 * Represents a directory in the file system.
 * Directories can contain other file system elements.
 */
public class Directory extends FileSystemElement{

    private LinkedList<FileSystemElement> children;

    /**
     * Constructor for the directory.
     * @param name name of the directory.
     * @param parent parent of the directory.
     */
    public Directory(String name, FileSystemElement parent) {
        super(name, parent);
        this.children = new LinkedList<FileSystemElement>();
    }

    /**
     * Adds a child to the directory.
     * @param child child to be added.
     * @return true if the child was added, false if the child already exists.
     */
    public boolean addChild(FileSystemElement child) {
        if(getChild(child.getName()) == null){
            child.setParent(this);
            children.add(child);
            return true;
        }
        return false;
    }

    /**
     * Removes a child from the directory.
     * @param index index of the child to be removed.
     * @return the child that was removed, null otherwise.
     */
    public FileSystemElement removeChild(int index){
        FileSystemElement childToRemove = children.get(index);
        if(childToRemove == null) return null;

        if(childToRemove instanceof Directory){
            ((Directory)childToRemove).removeAllChildren();
        }
        children.remove(index);

        return childToRemove;
    }

    /**
     * Removes a child from the directory with the given name.
     * @param name name of the child to be removed.
     * @return the child that was removed, null otherwise.
     */
    public FileSystemElement removeChild(String name){
        FileSystemElement childToRemove = null;
        for(FileSystemElement child : children){
            if(child.getName().equals(name)){
                childToRemove = child;
            }
        } if(childToRemove == null) return null;

        if(childToRemove instanceof Directory){
            ((Directory)childToRemove).removeAllChildren();
        }
        children.remove(childToRemove);

        return childToRemove;
    }

    /**
     * Removes all children of the directory.
     */
    private void removeAllChildren(){
        for(int i = 0; i < children.size(); ++i){
            FileSystemElement child = children.get(i);
            if(child instanceof Directory){
                ((Directory)child).removeAllChildren();
            }
            children.remove(i);
        }
    }

    /**
     * Returns the child at given index.
     * @param index index of the child.
     * @return the child at the given index if it exists, null otherwise.
     */
    public FileSystemElement getChild(int index) {
        return children.get(index);
    }

    /**
     * Returns the child with the given name.
     * @param name name of the child.
     * @return the child with the given name if it exists, null otherwise.
     */
    public FileSystemElement getChild(String name){
        for(FileSystemElement child : children){
            if(child.getName().equals(name)){
                return child;
            }
        }
        return null;
    }

    /**
     * Searches for a child in the directory recursively.
     * @param name name of the child to be searched.
     * @return the child if found, null otherwise.
     */
    public FileSystemElement recSearch(String name){
        for(FileSystemElement child : children){
            if(child.getName().equals(name)){
                return child;
            }
            if(child instanceof Directory){
                FileSystemElement result = ((Directory)child).recSearch(name);
                if(result != null){
                    return result;
                }
            }
        }
        return null;
    }

    @Override
    public void print(String prefix) {
        System.out.println(prefix + "Directory : " + name);
        for(FileSystemElement child : children){
            child.print(prefix + "  ");
        }
    }

    /**
     * Sorts the children of the directory by creation date.
     */
    public void sortByDate(){
        children.sort((FileSystemElement a, FileSystemElement b) -> a.getDateCreated().compareTo(b.getDateCreated()));
    }

    /**
     * Lists the contents of the directory with creation date.
     * @param prefix prefix to print before the file system element.
     */
    public void listDirWithDate(String prefix){
        listDir(prefix, true);
    }

    /**
     * Lists the contents of the directory.
     * @param prefix prefix to print before the file system element.
     */
    public void listDir(String prefix){
        listDir(prefix, false);
    }

    /**
     * Inner method to list the contents of the directory.
     */
    private void listDir(String prefix, boolean date){
        for(FileSystemElement child : children){
            if(child instanceof Directory)
                System.out.print(prefix + "* " + child.getName() + "/");
            else
                System.out.print(prefix + child.getName());

            if(date) System.out.println(" ( " + child.getDateCreated() + " )");
            else System.out.println();
        }
    }
}
