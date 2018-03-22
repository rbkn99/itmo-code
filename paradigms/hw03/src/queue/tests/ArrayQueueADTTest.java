package queue.tests;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import queue.ArrayQueueADT;

import static org.junit.jupiter.api.Assertions.*;

class ArrayQueueADTTest {
    private ArrayQueueADT queue;

    @BeforeEach
    void setUp() {
        queue = new ArrayQueueADT();
    }

    @Test
    public void testBasics() {
        ArrayQueueADT.enqueue(queue, 1);
        ArrayQueueADT.enqueue(queue,"hello");
        Object result = ArrayQueueADT.dequeue(queue);
        assertEquals(result, 1);
    }

    @Test
    public void test1() {
        Object veryBigNumber = 1234567891234111111L;
        ArrayQueueADT.enqueue(queue,1);
        ArrayQueueADT.enqueue(queue,"hello");
        ArrayQueueADT.dequeue(queue);
        ArrayQueueADT.enqueue(queue,veryBigNumber);
        ArrayQueueADT.dequeue(queue);
        Object result = ArrayQueueADT.dequeue(queue);
        assertEquals(result, veryBigNumber);
    }

    @Test
    public void test2() {
        ArrayQueueADT.enqueue(queue,1);
        ArrayQueueADT.enqueue(queue,2);
        ArrayQueueADT.dequeue(queue);
        ArrayQueueADT.enqueue(queue,3);
        int result = ArrayQueueADT.size(queue);
        assertEquals(result, 2);
    }

    @Test
    public void test3() {
        ArrayQueueADT.enqueue(queue,1);
        ArrayQueueADT.enqueue(queue,2);
        ArrayQueueADT.clear(queue);
        int result = ArrayQueueADT.size(queue);
        assertEquals(result, 0);
    }

    @Test
    public void test4() {
        ArrayQueueADT.enqueue(queue,1);
        ArrayQueueADT.enqueue(queue,2);
        ArrayQueueADT.enqueue(queue,2);
        ArrayQueueADT.enqueue(queue,322);
        ArrayQueueADT.enqueue(queue,228);
        ArrayQueueADT.enqueue(queue,1488);
        boolean result = ArrayQueueADT.isEmpty(queue);
        assertEquals(result, false);
    }

    @Test
    public void test5() {
        ArrayQueueADT.enqueue(queue,1);
        ArrayQueueADT.enqueue(queue,2);
        ArrayQueueADT.enqueue(queue,2);
        ArrayQueueADT.enqueue(queue,322);
        ArrayQueueADT.enqueue(queue,228);
        ArrayQueueADT.enqueue(queue,1488);
        for (int i = 0; i < 6; i++)
            ArrayQueueADT.dequeue(queue);
        boolean result = ArrayQueueADT.isEmpty(queue);
        assertEquals(result, true);
    }
}