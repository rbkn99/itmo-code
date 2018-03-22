package queue;

import java.util.function.Function;

import java.util.function.Predicate;

// INV: FIFO && size >= 0
public interface Queue {
    // PRE: element is immutable
    void enqueue(Object element);
    // POST: size' = size + 1
    //       previous elements are immutable
    //       queue.tail = element

    // PRE: size > 0
    Object element();
    // POST: R = queue.head
    //       queue is immutable

    // PRE: size > 0
    Object dequeue();
    // POST: R = queue.head
    //       next elements are immutable
    //       size' = size - 1

    // PRE: none
    int size();
    // POST: R = size

    // PRE: none
    boolean isEmpty();
    // POST: if size > 0 R = true; else R = false

    // PRE: none
    void clear();
    // POST: queue is clear

    // PRE: predicate != null
    Queue filter(Predicate<Object> predicate);
    // POST: R is queue
    //       queue.size >= R.size >= 0
    //       for i=0..R.size predicate.test(R[i]) = true
    //       for i=0..R.size-1 R[i] belongs queue && R[i + 1] belongs queue
    //          && len(queue.head, R[i]) < len(queue.head, R[i + 1])
    //       queue is immutable

    // PRE: function != null
    Queue map(Function<Object, Object> function);
    // POST: R is queue
    //       queue.size == R.size
    //       for i=0..R.size R[i] function.apply(queue[i]) = R[i]
    //       for i=0..R.size-1 R[i] belongs queue && R[i + 1] belongs queue
    //          && len(queue.head, R[i]) < len(queue.head, R[i + 1])
    //       queue is immutable

    // PRE: none
    Queue makeCopy();
    // POST: R is queue
    //       queue.size == R.size
    //       for i=0..R.size queue[i] = R[i]
    //       queue is immutable
}
