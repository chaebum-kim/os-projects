import java.util.List;

public class InsertionSort<T extends Comparable<T>> {
    public void sort(int begin, int end, List<T> list) {
        for (int i = 1; i <= end; i++) {
            T key = list.get(i);
            int j = i - 1;
            while (j >= 0 && list.get(j).compareTo(key) > 0) {
                list.set(j + 1, list.get(j));
                j--;
            }
            list.set(j + 1, key);
        }
    }
}
