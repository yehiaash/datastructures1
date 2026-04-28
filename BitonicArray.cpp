#include <iostream>
using namespace std;

int totalComparisons = 0;
int totalSwaps = 0;

void bubbleSortAscending(int arr[], int start, int end)
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

void selectionSortDescending(int arr[], int start, int end)
{
	for (int i = start; i <= end; i++)
	{
		int maxIdx = i;
		for (int j = i + 1; j <= end; j++)
		{
			totalComparisons++;
			if (arr[j] > arr[maxIdx])
			{
				maxIdx = j;
			}

		}
		if (maxIdx != i)
		{
			swap(arr[i], arr[maxIdx]);
			totalSwaps++;
		}
	}
}

void bitonicSort(int arr[], int n)
{
	int mid = n / 2;

	bubbleSortAscending(arr, 0, mid);
	selectionSortDescending(arr, mid + 1, n - 1);

}

int linearSearch(const int arr[], int n, int target)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == target)
		{
			return i;
		}

	}
	return -1;
}

void printArray(const int arr[], int n) {
	cout << "[ ";
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
		if (i != n - 1)
			cout << ", ";
	}
	cout << "]";
}

void runTestCase(int arr[], int n, int target, const char* description)
{
	totalComparisons = 0;
	totalSwaps = 0;

	cout << "--------------------------------------------\n";
	cout << "Test: " << description << "\n";
	cout << "Original array: ";
	printArray(arr, n);
	cout << "\n";

	bitonicSort(arr, n);

	int mid = n / 2;

	cout << "Bitonic Array : ";
	printArray(arr, n);
	cout << " (Bitonic point = " << arr[mid] << " at index " << mid << ")\n";
	cout << "Comparisons: " << totalComparisons << ", Swaps: " << totalSwaps << "\n";

	int result = linearSearch(arr, n, target);
	if (result != -1)
		cout << "Search Target " << target << ": Found at index " << result << "\n";
	else
		cout << "Search Target " << target << ": Not Founded \n";

	cout << "\n";
}

int main() {

	int arr1[] = { 3, 1, 7, 12, 9, 6, 4 };
	runTestCase(arr1, 7, 12, "Target at bitonic point (target=12)");

	int arr2[] = { 5, 2, 8, 15, 11, 7, 1 };
	runTestCase(arr2, 7, 5, "Target in left half / ascending portion (target=5)");

	int arr3[] = { 4, 1, 9, 20, 14, 6, 3 };
	runTestCase(arr3, 7, 6, "Target in right half / descending portion (target=6)");

	int arr4[] = { 10, 3, 7, 18, 13, 8, 2 };
	runTestCase(arr4, 7, 100, "Target not present in array (target=100)");

	int arr5[] = { 5, 3, 5, 9, 9, 3, 1 };
	runTestCase(arr5, 7, 5, "Array with duplicate elements (target=5)");

	return 0;
}
