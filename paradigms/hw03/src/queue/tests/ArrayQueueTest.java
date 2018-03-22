package queue.tests;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import queue.ArrayQueue;

import static org.junit.jupiter.api.Assertions.*;

class ArrayQueueTest {
    private ArrayQueue queue;

    @BeforeEach
    void setUp() {
        queue = new ArrayQueue();
    }

    @Test
    public void testBasics() {
        queue.enqueue(1);
        queue.enqueue("hello");
        Object result = queue.dequeue();
        assertEquals(result, 1);
    }

    @Test
    public void test1() {
        Object veryBigNumber = 1234567891234111111L;
        queue.enqueue(1);
        queue.enqueue("hello");
        queue.dequeue();
        queue.enqueue(veryBigNumber);
        queue.dequeue();
        Object result = queue.dequeue();
        assertEquals(result, veryBigNumber);
    }

    @Test
    public void test2() {
        queue.enqueue(1);
        queue.enqueue(2);
        queue.dequeue();
        queue.enqueue(3);
        int result = queue.size();
        assertEquals(result, 2);
    }

    @Test
    public void test3() {
        queue.enqueue(1);
        queue.enqueue(2);
        queue.clear();
        int result = queue.size();
        assertEquals(result, 0);
    }

    @Test
    public void test4() {
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(2);
        queue.enqueue(322);
        queue.enqueue(228);
        queue.enqueue(1488);
        boolean result = queue.isEmpty();
        assertEquals(result, false);
    }

    @Test
    public void test5() {
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(2);
        queue.enqueue(322);
        queue.enqueue(228);
        queue.enqueue(1488);
        for (int i = 0; i < 6; i++)
            queue.dequeue();
        boolean result = queue.isEmpty();
        assertEquals(true, result);
    }

    @Test
    public void test6() {
        queue.push(1);
        queue.push(2);
        Object result = queue.remove();
        assertEquals(2, result);
    }

    @Test
    public void test7() {
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue("o-zh-v-p");
        queue.enqueue(1488);
        queue.remove();
        Object result = queue.peek();
        assertEquals("o-zh-v-p", result);
    }
}