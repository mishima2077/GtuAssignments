package GtuContainer;
import java.util.Iterator;

/**
 * A generic implementation of JavaContainer using a dynamically resizing array.
 *
 * @param <T> the type of elements held in the vector.
 */
public class JavaVector<T> implements JavaContainer<T> {
    private Object[] data;
    private int size;

    /**
     * Constructs a new JavaVector with an initial capacity of 10.
     */
    public JavaVector() {
        this(10);
    }

    /**
     * Constructs a new JavaVector with given capacity.
     * 
     * @param cap Initial capacity of the Vector.
     */
    public JavaVector(int cap){
        if(cap <= 0)
            throw new IllegalArgumentException("Capacity can't be less than 1");

        data = new Object[cap];
        size = 0;
    }

    @Override
    public void add(T element) {
        checkCapacity();
        data[size++] = element;
    }

    @Override
    public void remove(T element) {
        int index = indexOf(element);
        if (index != -1) {
            for (int i = index; i < size - 1; ++i)
                data[i] = data[i + 1];
            --size;
        }
    }

    private int indexOf(T element) {
        for (int i = 0; i < size; i++) 
            if (element.equals(data[i]))
                return i;
   
        return -1;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public String toString() {
        StringBuilder res = new StringBuilder();
        for (int i = 0; i < size; i++) {
            res.append(data[i]);
            res.append(" ");
        }
        return res.toString();
    }

    @Override
    @SuppressWarnings("unchecked")
    public boolean equals(Object element) {
        if (this == element)
            return true;
        if (element == null || getClass() != element.getClass())
            return false;

        JavaVector<T> other = (JavaVector<T>) element;

        if(this.size != other.size)
            return false;
        for(int i = 0; i < size; ++i)
            if(this.data[i].equals(other.data[i]) != true)
                return false;

        return true;
    }

    /**
     * Creates and returns a clone of the JavaSet.
     * 
     * @return clone of the JavaSet.
     */
    @Override
    public JavaVector<T> clone(){
        JavaVector<T> res = new JavaVector<T>();
        res.data = data.clone();
        res.size = size;

        return res;
    }

    @Override
    public Iterator<T> getIterator() {
        return new JavaVectorIterator();
    }

    private class JavaVectorIterator implements Iterator<T> {
        private int index;

        /**
         * Constructs a new JavaVectorIterator with initial index 0.
         */
        public JavaVectorIterator() {
            index = 0;
        }

        @Override
        public boolean hasNext() {
            return index < size;
        }

        @Override
        @SuppressWarnings("unchecked")
        public T next() {
            if (hasNext())
                return (T) data[index++];
            else 
                throw new IndexOutOfBoundsException("No more elements in the JavaSet");
        }
    }

    private void checkCapacity() {
        if (size >= data.length) {
            int newCapacity = data.length * 2;
            Object[] temp = new Object[newCapacity];
            for(int i = 0; i < size; ++i)
                temp[i] = data[i];
            data = temp;
        }
    }
}
