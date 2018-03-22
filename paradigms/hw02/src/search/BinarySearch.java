package search;

public class BinarySearch {
    //PRE: args.length > 0
    public static void main(String[] args) {
        int key = Integer.parseInt(args[0]);
        int size = args.length - 1;
        int[] arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = Integer.parseInt(args[i + 1]);
        }

        //int result = iterativeBinarySearch(arr, key);
        int result = recursiveBinarySearch(arr, -1, size, key);
        System.out.println(result);
    }

    // PRE: i = 0..size - 1 arr[i] >= arr[i + 1]
    // POST: arr is immutable
    // POST: 0 <= out <= size
    // POST: a[out] <= key && a[out - 1] > key
    // POST: if out == 0 => key >= max(arr[0..size])
    // POST: if out == size => key < min(arr[0..size])
    private static int iterativeBinarySearch(int[] arr, int key) {
        int l = -1, r = arr.length, mid;
        // INV: a[0..l - 1] > key >= a[r..size]
        // INV: if r - l <= 1 => a[r] <= key && a[r - 1] > key
        while (r - l > 1) {
            // INV && r - l > 1
            mid = (l + r) / 2;
            // l <= mid < r
            if (arr[mid] <= key)
                // INV && key >= arr[mid]
                r = mid;
            else
                // INV && key < arr[mid]
                l = mid;
            // INV: a[0..l - 1] > a[mid] >= a[r..size]
        }
        return r;
    }

    // PRE: i = 0..size - 1 arr[i] >= arr[i + 1]
    // PRE: -1 <= l, r <= size
    // POST: arr is immutable
    // POST: 0 <= out <= size
    // POST: a[out] <= key && a[out - 1] > key
    // POST: if out == 0 => key >= max(arr[0..size])
    // POST: if out == size => key < min(arr[0..size])
    private static int recursiveBinarySearch(int[] arr, int l, int r, int key) {
        // INV: a[0..l - 1] > key >= a[r..size]
        // INV: if r - l <= 1 => a[r] <= key && a[r - 1] > key
        if (r - l > 1) {
            // INV && r - l > 1
            int m = (l + r) / 2;
            // l <= mid < r
            if (arr[m] > key)
                // INV && key > arr[mid]
                return recursiveBinarySearch(arr, m, r, key);
            else
                // INV && key <= arr[mid]
                return recursiveBinarySearch(arr, l, m, key);
        }
        else
            // r - l <= 1
            return r;
    }
}
