import java.util.concurrent.*;
import java.util.ArrayList;
import java.util.List;

public class MergeSort<T extends Comparable<T>> extends RecursiveTask<List<T>> {
    static final int THRESHOLD = 100;
    private int begin;
    private int end;
    private List<T> list;

    public MergeSort(List<T> list) {
        this.begin = 0;
        this.end = list.size() - 1;
        this.list = list;
    }

    protected List<T> compute() {
        if (end - begin <= THRESHOLD) {
            // Do Insertion Sort
            InsertionSort<T> insertionSort = new InsertionSort<T>();
            insertionSort.sort(begin, end, list);
            return list;
        } else {
            // Divide the list into tow halves and make copy of them
            int half = (begin + end) / 2;
            List<T> one = new ArrayList<>(list.subList(begin, half));
            List<T> other = new ArrayList<>(list.subList(half + 1, end));

            // Do merge sort on each divided list
            MergeSort<T> leftSort = new MergeSort<T>(one);
            MergeSort<T> rightSort = new MergeSort<T>(other);
            leftSort.fork();
            rightSort.fork();

            return merge(leftSort.join(), rightSort.join());
        }
    }

    private List<T> merge(List<T> one, List<T> other) {
        // Initialize merged list
        List<T> mergedList = new ArrayList<>(one.size() + other.size());
        int i = 0, j = 0, k = 0;

        // Merge the lists
        while (i < one.size() && j < other.size()) {
            if (one.get(i).compareTo(other.get(j)) < 0) {
                mergedList.set(k, one.get(i));
                i++;
            } else {
                mergedList.set(k, other.get(j));
                j++;
            }
            k++;
        }
        while (i < one.size()) {
            mergedList.set(k, one.get(i));
            i++;
            k++;
        }
        while (j < other.size()) {
            mergedList.set(k, other.get(i));
            j++;
            k++;
        }

        return mergedList;
    }
}
