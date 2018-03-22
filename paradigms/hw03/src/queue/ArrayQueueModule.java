package queue;

public class ArrayQueueModule {
    private static Object[] array = new Object[10];
    private static int head = 0;
    private static int tail = 0;

    private static void extendArray() {
        Object[] buffer = new Object[array.length * 2];
        int queueSize = getQueueSize();
        int count = tail < head ? array.length - head : queueSize;
        System.arraycopy(array, head, buffer, 0, count);
        if (tail < head) {
            System.arraycopy(array, 0, buffer, count, tail);
        }
        head = 0;
        tail = queueSize;
        array = buffer;
    }

    public static void enqueue(Object element) {
        if (getQueueSize() + 1 == array.length) {
            extendArray();
        }
        array[tail] = element;
        tail = (tail + 1) % array.length;
    }

    public static Object element() {
        return array[head];
    }

    public static Object dequeue() {
        Object obj = array[head];
        head = (head + 1) % array.length;
        return obj;
    }

    public static int size() {
        return getQueueSize();
    }

    public static boolean isEmpty() {
        return size() == 0;
    }

    public static void clear() {
        head = tail = 0;
        array = new Object[10];
    }

    public static void push(Object element) {
        if (getQueueSize() + 1 == array.length) {
            extendArray();
        }
        head = (array.length + head - 1) % array.length;
        array[head] = element;
    }

    public static Object peek() {
        return array[(array.length + tail - 1) % array.length];
    }

    public static Object remove() {
        tail = (array.length + tail - 1) % array.length;
        return array[tail];
    }

    private static int getQueueSize() {
        return head <= tail ? tail - head : array.length - (head - tail);
    }
}
