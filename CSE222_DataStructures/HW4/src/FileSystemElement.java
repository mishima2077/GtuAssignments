import java.sql.Timestamp;

/**
 * Represents a file system element.
 */
public abstract class FileSystemElement {
    protected String name;
    protected Timestamp dateCreated;
    protected FileSystemElement parent;

    /**
     * Constructor for the file system element.
     * @param name name of the file system element.
     * @param parent parent of the file system element.
     */
    public FileSystemElement(String name, FileSystemElement parent) {
        this.name = name;
        this.parent = parent;
        this.dateCreated = new Timestamp(System.currentTimeMillis());
    }

    /**
     * Returns the name of the file system element.
     * @return the name of the file system element.
     */
    public String getName() {
        return name;
    }

    /**
     * Returns the date the file system element was created.
     * @return the date the file system element was created.
     */
    public Timestamp getDateCreated() {
        return dateCreated;
    }

    /**
     * Returns the parent of the file system element.
     * @return the parent of the file system element.
     */
    public FileSystemElement getParent() {
        return parent;
    }

    /**
     * Sets the parent of the file system element.
     * @param parent new parent of the file system element.
     */
    public void setParent(FileSystemElement parent) {
        this.parent = parent;
    }

    /**
     * Returns the path of the file system element.
     * @return the path of the file system element.
     */
    public String getPath(){
        return getPath("") + "/" + name;
    }

    /**
     * Recursive part of getPath.
     */
    private String getPath(String path){
        if(parent == null){
            return path;
        }
        return parent.getPath("/" + parent.getName() + path);        
    }

    /**
     * Prints the file system element.
     * @param prefix prefix to print before the file system element.
     */
    public abstract void print(String prefix);
}