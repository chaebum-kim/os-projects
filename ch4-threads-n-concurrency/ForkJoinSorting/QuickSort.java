import java.util.concurrent.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

public class QuickSort<T extends Comparable<T>> extends RecursiveAction {
    static final int THRESHOLD = 10;
    private int begin;
    private int end;
    private List<T> list;

    public QuickSort(int begin, int end, List<T> list) {
        this.begin = begin;
        this.end = end;
        this.list = list;
    }

    protected void compute() {
        if (end - begin <= THRESHOLD) {
            // Do Insertion Sort
            InsertionSort<T> insertionSort = new InsertionSort<T>();
            insertionSort.sort(begin, end, list);

        } else {
            // Locate pivot value(last value)
            int pivotIndex = locatePivot(begin, end, list);
            QuickSort<T> leftSort = new QuickSort<T>(begin, pivotIndex - 1, list);
            QuickSort<T> rightSort = new QuickSort<T>(pivotIndex + 1, end, list);

            leftSort.fork();
            rightSort.fork();

            leftSort.join();
            rightSort.join();
        }
    }

    private int locatePivot(int begin, int end, List<T> list) {
        T pivot = list.get(end);
        int pivotIndex = begin;

        for (int i = begin; i < end; i++) {
            if (list.get(i).compareTo(pivot) < 0) {
                Collections.swap(list, i, pivotIndex);
                pivotIndex++;
            }
        }

        Collections.swap(list, pivotIndex, end);

        return pivotIndex;
    }
}
