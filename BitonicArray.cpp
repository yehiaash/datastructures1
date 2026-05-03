#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BitonicSorter {
private:
    int totalComparisons;
    int totalSwaps;

    void bubbleSortAscending(vector<int>& arr, int start, int end) 
    {
        for (int i = start; i < end; i++) 
        {
            for (int j = start; j < end - (i - start); j++) 
            {
                totalComparisons++;
                if (arr[j] > arr[j + 1]) 
                {
                    swap(arr[j], arr[j + 1]);
                    totalSwaps++;
                }
            }
        }
    }

    void selectionSortDescending(vector<int>& arr, int start, int end) 
    {
        for (int i = start; i <= end; i++) 
        {
            int maxIndex = i;
            for (int j = i + 1; j <= end; j++) 
            {
                totalComparisons++;
                if (arr[j] > arr[maxIndex])
                    maxIndex = j;
            }
            if (maxIndex != i) 
            {
                swap(arr[i], arr[maxIndex]);
                totalSwaps++;
            }
        }
    }

public:
    BitonicSorter() : totalComparisons(0), totalSwaps(0) {}

    void sort(vector<int>& arr) 
    {
        int mid = arr.size() / 2;
        bubbleSortAscending(arr, 0, mid);
        selectionSortDescending(arr, mid + 1, arr.size() - 1);
    }

    int findBitonicPoint(const vector<int>& arr) {
        int maxIndex = 0;
        for (int i = 1; i < arr.size(); i++) 
        {
            if (arr[i] > arr[maxIndex])
                maxIndex = i;
        }
        return maxIndex;
    }

    int linearSearch(const vector<int>& arr, int target) 
    {
        for (int i = 0; i < arr.size(); i++) 
        {
            if (arr[i] == target) 
                return i;
        }
        return -1;
    }

    void printArray(const vector<int>& arr) 
    {
        cout << "[ ";
        for (int i = 0; i < arr.size(); i++) 
        {
            cout << arr[i];
            if (i != arr.size() - 1) 
                cout << ", ";
        }
        cout << " ]";
    }

    void runTestCase(vector<int> arr, int target, const string& description) {
        totalComparisons = 0;
        totalSwaps = 0;

        cout << "--------------------------------------------\n";
        cout << "Test: " << description << "\n";
        cout << "Original Array : "; printArray(arr); cout << "\n";

        sort(arr);
        int bitonicIndex = findBitonicPoint(arr);

        cout << "Bitonic Array  : "; printArray(arr);
        cout << " (Bitonic point = " << arr[bitonicIndex]
            << " at index " << bitonicIndex << ")\n";
        cout << "Comparisons: " << totalComparisons << ", Swaps: " << totalSwaps << "\n";

        int resultIndex = linearSearch(arr, target);
        if (resultIndex != -1)
            cout << "Search Target " << target << ": Found at index " << resultIndex << "\n";
        else
            cout << "Search Target " << target << ": Not Found\n";

        cout << "\n";
    }
};

int main() {
    BitonicSorter sorter;

    sorter.runTestCase({ 3, 1, 7, 12, 9, 6, 4 }, 12, "Target at bitonic point (target=12)");
    sorter.runTestCase({ 5, 2, 8, 15, 11, 7, 1 }, 5, "Target in left half (target=5)");
    sorter.runTestCase({ 4, 1, 9, 20, 14, 6, 3 }, 6, "Target in right half (target=6)");
    sorter.runTestCase({ 10, 3, 7, 18, 13, 8, 2 }, 100, "Target not present (target=100)");
    sorter.runTestCase({ 5, 3, 5, 9, 9, 3, 1 }, 5, "Duplicate elements (target=5)");
    sorter.runTestCase({ 1, 2, 3, 4, 5, 6, 20 }, 20, "Largest at last index (target=20)");



    return 0;
}