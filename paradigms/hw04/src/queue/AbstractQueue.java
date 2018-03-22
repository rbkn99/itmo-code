package queue;

import java.util.function.Function;
import java.util.function.Predicate;

abstract class AbstractQueue implements Queue {

    protected abstract void enqueueImpl(Object element);

    protected abstract Object elementImpl();

    protected abstract Object dequeueImpl();

    // PRE: none
    protected abstract Queue queueInstance();
    // POST: R is instance of empty queue

    @Override
    public void enqueue(Object element) {
        enqueueImpl(element);
    }

    @Override
    public Object dequeue() {
        assert size() > 0;
        return dequeueImpl();
    }

    @Override
    public Object element() {
        assert size() > 0;
        return elementImpl();
    }

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    @Override
    public Queue filter(Predicate<Object> predicate) {
        Queue copyQueue = makeCopy();
        Queue filteredQueue = queueInstance();
        while (!copyQueue.isEmpty()) {
            // INV: copyQueue.size > 0
            //      for i=0..copyQueue.size copyQueue[i] == queue[i]
            //      filteredQueue is queue && copyQueue is queue
            //      for i=0..filteredQueue.size predicate.test(filteredQueue[i]) = true
            Object value = copyQueue.dequeue();
            if (predicate.test(value)) {
                filteredQueue.enqueue(value);
            }
        }
        return filteredQueue;
    }

    @Override
    public Queue map(Function<Object, Object> function) {
        Queue copyQueue = makeCopy();
        Queue mappedQueue = queueInstance();
        while (!copyQueue.isEmpty()) {
            // INV: copyQueue.size > 0
            //      for i=0..copyQueue.size copyQueue[i] == queue[i]
            //      mappedQueue is queue && copyQueue is queue
            //      for i=0..mappedQueue.size function.apply(mappedQueue[i]) = copyQueue[i]
            Object value = copyQueue.dequeue();
            mappedQueue.enqueue(function.apply(value));
        }
        return mappedQueue;
    }
}
