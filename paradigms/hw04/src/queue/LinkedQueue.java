package queue;


// all PREs, POSTs and INVs below complement PREs, POSTs and INVs in the interface
// INV: path from head to tail by Node.next >= 0
public class LinkedQueue extends AbstractQueue implements Queue {
    private class Node {
        Node next;
        Object value;

        Node(Object value) {
            next = null;
            this.value = value;
        }
    }

    private Node head, tail;
    private int size;

    public LinkedQueue() {
        head = tail = null;
        size = 0;
    }

    @Override
    public void enqueueImpl(Object element) {
        Node newNode = new Node(element);
        if (tail != null) {
            tail.next = newNode;
        }
        if (head == null) {
            head = newNode;
        }
        tail = newNode;
        size++;
    }

    @Override
    public Object elementImpl() {
        return head.value;
    }

    @Override
    public Object dequeueImpl() {
        Object value = head.value;
        head = head.next;
        size--;
        return value;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public void clear() {
        while (size > 0) {
            dequeueImpl();
        }
    }

    @Override
    public Queue makeCopy() {
        LinkedQueue copy = new LinkedQueue();
        Node iterator = head;
        while (iterator != null) {
            copy.enqueue(iterator.value);
            iterator = iterator.next;
        }
        return copy;
    }

    @Override
    public Queue queueInstance() {
        return new LinkedQueue();
    }
}
