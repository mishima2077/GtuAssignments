package GtuContainer;
import java.util.Iterator;

/**
 * A generic implementation of JavaContainer using a dynamically resizing array.
 *
 * @param <T> the type of elements held in the set.
 */
public class JavaSet<T> implements JavaContainer<T> {
    private Object[] data;
    private int size;

    /**
     * Constructs a new JavaSet with an initial capacity of 10.
     */
    public JavaSet() {
        this(10);
    }

    /**
     * Constructs a new JavaSet with given capacity.
     * 
     * @param cap Initial capacity of the Set.
     */
    public JavaSet(int cap){
        if(cap <= 0)
            throw new IllegalArgumentException("Capacity can't be less than 1");

        data = new Object[cap];
        size = 0;
    }

    /**
     * Adds an element to the set if it does not already exist.
     *
     * @param element the element to be added.
     */
    @Override
    public void add(T element) {
        if (!contains(element)) {
            checkCapacity();
            data[size++] = element;
        }
    }

    /**
     * Removes the first occurrence of the specified element from the set.
     *
     * @param element the element to be removed.
     */
    @Override
    public void remove(T element) {
        int index = indexOf(element);
        if (index != -1) {
            for (int i = index; i < size - 1; ++i)
                data[i] = data[i + 1];
            --size;
        }
    }

    /**
     * Returns the index of the first occurrence of the specified element, -1 if not found.
     *
     * @param element the element to find.
     * @return the index of the element, -1 if not found.
     */
    private int indexOf(T element) {
        for (int i = 0; i < size; i++)
            if (element.equals(data[i]))
                return i;

        return -1;
    }

    /**
     * Returns the current size of the set.
     *
     * @return size of the set.
     */
    @Override
    public int size() {
        return size;
    }

    /**
     * Returns a string representation of the set.
     *
     * @return string representation of the set.
     */
    @Override
    public String toString() {
        StringBuilder res = new StringBuilder();
        for (int i = 0; i < size; i++) {
            res.append(data[i]);
            res.append(" ");
        }
        return res.toString();
    }

    /**
     * Checks if this set is equal to another object.
     *
     * @param element the object to compare.
     * @return true if equal, false otherwise.
     */
    @Override
    @SuppressWarnings("unchecked")
    public boolean equals(Object element) {
        if (this == element)
            return true;
        if (element == null || getClass() != element.getClass())
            return false;

        JavaSet<T> other = (JavaSet<T>) element;

        if (this.size != other.size)
            return false;
        for (int i = 0; i < size; ++i)
            if (!this.data[i].equals(other.data[i]))
                return false;

        return true;
    }

    /**
     * Creates and returns a clone of the JavaSet.
     * 
     * @return a clone of the JavaSet.
     */
    @Override
    public JavaSet<T> clone(){
        JavaSet<T> res = new JavaSet<T>();
        res.data = data.clone();
        res.size = size;

        return res;
    }

    /**
     * Returns an iterator over the elements in the set.
     *
     * @return an iterator over the elements in the set.
     */
    @Override
    public Iterator<T> getIterator() {
        return new JavaSetIterator();
    }

    /**
     * Iterator for the JavaSet class.
     */
    private class JavaSetIterator implements Iterator<T> {
        /**
         * The current index of the iterator.
         */
        private int index;

        /**
         * Constructs a new JavaSetIterator with an initial index of 0.
         */
        public JavaSetIterator() {
            index = 0;
        }

        /**
         * Checks if there are more elements in the set.
         *
         * @return true if there are more elements, false otherwise.
         */
        @Override
        public boolean hasNext() {
            return index < size;
        }

        /**
         * Returns the next element in the set.
         *
         * @return the next element in the set.
         * @throws IndexOutOfBoundsException if there are no more elements.
         */
        @Override
        @SuppressWarnings("unchecked")
        public T next() {
            if (hasNext())
                return (T) data[index++];
            else
                throw new IndexOutOfBoundsException("No more elements in the JavaSet");
        }
    }

    /**
     * Checks if the set contains a specific element.
     *
     * @param element the element to check for.
     * @return true if the set contains the element, false otherwise.
     */
    private boolean contains(T element) {
        for (int i = 0; i < size; ++i)
            if (data[i].equals(element))
                return true;

        return false;
    }

    /**
     * Checks the capacity of the set and expands it if needed.
     */
    private void checkCapacity() {
        if (size >= data.length) {
            int newCapacity = data.length * 2;
            Object[] temp = new Object[newCapacity];
            for (int i = 0; i < size; ++i)
                temp[i] = data[i];
            data = temp;
        }
    }
}
