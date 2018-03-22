package search;

public class BinarySearchSpan {
    //PRE: args.length > 0
    public static void main(String[] args) {
        int key = Integer.parseInt(args[0]);
        int size = args.length - 1;
        int[] arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = Integer.parseInt(args[i + 1]);
        }

        int l = leftBinarySearch(arr, key);
        int r = rightBinarySearch(arr, -1, arr.length, key);
        System.out.println(l + " " + (r - l + 1));
    }

    // PRE: arr.size > 0 %size = arr.size%
    // PRE: i = 0..size - 2: arr[i] >= arr[i + 1]
    // POST: arr is immutable
    // POST: 0 <= R <= size
    // POST: if 0 < R < size => a[R] <= key && a[R - 1] > key
    // POST: if R == 0 => key >= max(arr[0..size])
    // POST: if R == size => key < min(arr[0..size])
    private static int leftBinarySearch(int[] arr, int key) {
        int l = -1, r = arr.length;
        // INV: a[0..l - 1] > key >= a[r..size-1]
        // INV: if r - l <= 1 => a[r] <= key && a[r - 1] > key
        while (r - l > 1) {
            // INV && r - l > 1
            int mid = (l + r) / 2;
            // INV && l < mid < r
            if (arr[mid] <= key)
                // INV && key >= arr[mid]
                // arr[0]..arr[l] > key >= arr[mid]..arr[size - 1]
                // m - l < r - l
                r = mid;
            else
                // INV && key < arr[mid]
                // arr[0]..arr[mid] > key >= arr[r]..arr[size - 1]
                // r - m < r - l
                l = mid;
            // INV: a[0..l - 1] > a[mid] >= a[r..size]
        }
        // R = r
        return r;
    }

    // PRE: arr.size > 0 %size = arr.size%
    // PRE: i = 0..size - 2: arr[i] >= arr[i + 1]
    // PRE: -1 <= l < size; 0 <= r < size
    // PRE: l <= r
    // POST: arr is immutable
    // POST: l <= R <= r
    // POST: (l < R < r => a[R] <= key) -> a[R - 1] > key
    // POST: if R == l => key >= max(arr[l..r])
    // POST: if R == r => key < min(arr[l..r])
    private static int rightBinarySearch(int[] arr, int l, int r, int key) {
        // INV: if r - l <= 1 => a[l] > key && a[l + 1] <= key
        if (r - l > 1) {
            // INV && r - l > 1
            int m = (l + r) / 2;
            // INV && l < mid <= r
            if (arr[m] >= key) {
                // INV && key <= arr[mid]
                // arr[0]..arr[mid] >= key > arr[r]..arr[size - 1]
                // r - m < r - l
                return rightBinarySearch(arr, m, r, key);
            } else {
                // INV && key > arr[mid]
                // arr[0]..arr[l] >= key > arr[mid]..arr[size - 1]
                // m - l < r - l
                return rightBinarySearch(arr, l, m, key);
            }
        } else {
            // r - l <= 1
            return l;
        }
    }
}
