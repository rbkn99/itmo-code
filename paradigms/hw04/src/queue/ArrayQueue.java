package queue;

import java.util.Arrays;

// all PREs, POSTs and INVs below complement PREs, POSTs and INVs in the interface
// INV: capacity > 0
//      head < tail => array[head]..array[tail - 1] - queue
//      head >= tail && tail == 0 => array[head]..array[capacity - 1] - queue
//      head >= tail && tail > 0 => array[head]..array[capacity - 1], array[0]..array[tail - 1] - queue
public class ArrayQueue extends AbstractQueue implements Queue {
    private Object[] array;
    private int head;
    private int tail;

    public ArrayQueue() {
        array = new Object[10];
        head = tail = 0;
    }

    // PRE: size = array.length
    // PRE: size > 0
    private void extendArray() {
        Object[] buffer = new Object[array.length * 2];
        int queueSize = size();
        int count = tail < head ? array.length - head : queueSize;
        System.arraycopy(array, head, buffer, 0, count);
        if (tail < head) {
            System.arraycopy(array, 0, buffer, count, tail);
        }
        head = 0;
        tail = queueSize;
        array = buffer;
    }
    // POST: array.length' = 2 * array.length
    // POST: i=0..size queue[i]' = queue[i]
    // POST: queue.size' = queue.size

    @Override
    public void enqueueImpl(Object element) {
        if (size() + 1 == array.length) {
            extendArray();
        }
        array[tail] = element;
        tail = (tail + 1) % array.length;
    }

    @Override
    public Object elementImpl() {
        return array[head];
    }

    @Override
    public Object dequeueImpl() {
        Object obj = array[head];
        head = (head + 1) % array.length;
        return obj;
    }

    @Override
    public int size() {
        return head <= tail ? tail - head : array.length - (head - tail);
    }

    @Override
    public void clear() {
        head = tail = 0;
        array = new Object[10];
    }

    @Override
    public Queue makeCopy() {
        ArrayQueue copy = new ArrayQueue();
        copy.head = head;
        copy.tail = tail;
        copy.array = Arrays.copyOf(array, array.length);
        return copy;
    }

    @Override
    public Queue queueInstance() {
        return new ArrayQueue();
    }
}
