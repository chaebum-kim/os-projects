
import java.util.concurrent.ForkJoinPool;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class Test {
    public static void main(String[] args) {

        int LENGTH = 100;
        List<Integer> list = new ArrayList<Integer>(LENGTH);
        ForkJoinPool pool = new ForkJoinPool();

        // Generate Integer list
        for (int i = 0; i < LENGTH; i++) {
            list.add(i);
        }

        // Shuffle the list
        Collections.shuffle(list);

        // Print the original list
        System.out.println("Original List");
        System.out.println(list);

        // Sort the list using Merge Sort
        MergeSort<Integer> mergeSort = new MergeSort<Integer>(list);
        list = pool.invoke(mergeSort);

        // Print the result
        System.out.println("Sorted List by Merge Sort");
        System.out.println(list);

        // Reshuffle the list
        Collections.shuffle(list);

        // Print the original list
        System.out.println("Original List");
        System.out.println(list);

        // Sort the list using Quck Sort
        QuickSort<Integer> quickSort = new QuickSort<Integer>(0, LENGTH - 1, list);
        pool.invoke(quickSort);

        // Print the result
        System.out.println("Sorted List by Quick Sort");
        System.out.println(list);
    }
}
