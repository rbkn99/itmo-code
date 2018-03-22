package queue;

public class ArrayQueueADT {
    private Object[] array;
    private int head;
    private int tail;

    public ArrayQueueADT() {
        array = new Object[10];
        head = tail = 0;
    }

    private static void extendArray(ArrayQueueADT adt) {
        Object[] buffer = new Object[adt.array.length * 2];
        int queueSize = getQueueSize(adt);
        int count = adt.tail < adt.head ? adt.array.length - adt.head : queueSize;
        System.arraycopy(adt.array, adt.head, buffer, 0, count);
        if (adt.tail < adt.head) {
            System.arraycopy(adt.array, 0, buffer, count, adt.tail);
        }
        adt.head = 0;
        adt.tail = queueSize;
        adt.array = buffer;
    }

    public static void enqueue(ArrayQueueADT adt, Object element) {
        if (getQueueSize(adt) + 1 == adt.array.length) {
            extendArray(adt);
        }
        adt.array[adt.tail] = element;
        adt.tail = (adt.tail + 1) % adt.array.length;
    }

    public static Object element(ArrayQueueADT adt) {
        return adt.array[adt.head];
    }

    public static Object dequeue(ArrayQueueADT adt) {
        Object obj = adt.array[adt.head];
        adt.head = (adt.head + 1) % adt.array.length;
        return obj;
    }

    public static int size(ArrayQueueADT adt) {
        return getQueueSize(adt);
    }

    public static boolean isEmpty(ArrayQueueADT adt) {
        return size(adt) == 0;
    }

    public static void clear(ArrayQueueADT adt) {
        adt.head = adt.tail = 0;
        adt.array = new Object[10];
    }

    public static void push(ArrayQueueADT adt, Object element) {
        if (getQueueSize(adt) + 1 == adt.array.length) {
            extendArray(adt);
        }
        adt.head = (adt.array.length + adt.head - 1) % adt.array.length;
        adt.array[adt.head] = element;
    }

    public static Object peek(ArrayQueueADT adt) {
        return adt.array[(adt.array.length + adt.tail - 1) % adt.array.length];
    }

    public static Object remove(ArrayQueueADT adt) {
        adt.tail = (adt.array.length + adt.tail - 1) % adt.array.length;
        return adt.array[adt.tail];
    }

    private static int getQueueSize(ArrayQueueADT adt) {
        return adt.head <= adt.tail ? adt.tail - adt.head : adt.array.length - (adt.head - adt.tail);
    }
}
