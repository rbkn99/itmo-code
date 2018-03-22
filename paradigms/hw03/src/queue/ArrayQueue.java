package queue;

// INV: FIFO
//      capacity > 0 && size >= 0
//      head < tail => array[head]..array[tail - 1] - queue
//      head >= tail && tail == 0 => array[head]..array[capacity - 1] - queue
//      head >= tail && tail > 0 => array[head]..array[capacity - 1], array[0]..array[tail - 1] - queue
public class ArrayQueue {
    private Object[] array;
    private int head;
    private int tail;

    public ArrayQueue() {
        array = new Object[10];
        head = tail = 0;
    }

    // PRE: size = array.length
    private void extendArray() {
        Object[] buffer = new Object[array.length * 2];
        int queueSize = size();
        int count = tail < head ? array.length - head : queueSize;
        System.arraycopy(array, head, buffer, 0, count);
        if (tail < head)
            System.arraycopy(array, 0, buffer, count, tail);
        head = 0;
        tail = queueSize;
        array = buffer;
    }
    // POST: array.length' = 2 * array.length
    //       i=0..size queue[i]' = queue[i]
    //       queue.size' = queue.size

    // PRE: element is immutable
    public void enqueue(Object element) {
        if (size() + 1 == array.length) {
            extendArray();
        }
        array[tail] = element;
        tail = (tail + 1) % array.length;
    }
    // POST: size' = size + 1
    //       previous elements are immutable
    //       queue.tail = element

    // PRE: size > 0
    public Object element() {
        assert size() > 0;
        return array[head];
    }
    // POST: R = queue.head
    //       queue is immutable

    // PRE: size > 0
    public Object dequeue() {
        Object obj = array[head];
        head = (head + 1) % array.length;
        return obj;
    }
    // POST: R = queue.head
    //       next elements are immutable
    //       size' = size - 1

    // PRE: none
    public int size() {
        return head <= tail ? tail - head : array.length - (head - tail);
    }
    // POST: R = size

    // PRE: none
    public boolean isEmpty() {
        return size() == 0;
    }
    // POST: if size > 0 R = true; else R = false

    // PRE: none
    public void clear() {
        head = tail = 0;
        array = new Object[10];
    }
    // POST: queue is clear

    // PRE: element is immutable
    public void push(Object element) {
        if (size() + 1 == array.length) {
            extendArray();
        }
        head = (array.length + head - 1) % array.length;
        array[head] = element;
    }
    // POST: size' = size + 1
    //       next elements are immutable
    //       queue.head = element

    // PRE: size > 0
    public Object peek() {
        return array[(array.length + tail - 1) % array.length];
    }
    // POST: R = queue.tail
    //       queue is immutable

    // PRE: size > 0
    public Object remove() {
        tail = (array.length + tail - 1) % array.length;
        return array[tail];
    }
    // POST: R = queue.tail
    //       previous elements are immutable
    //       size' = size - 1
}
