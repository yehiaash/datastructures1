#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class RotatedBinarySearch
{
private:
    vector<T> arr;
    int Comparisons = 0;

public:
    void setArray(vector<T> a)
    {
        arr = a;
    }
    int search(T target)
    {
        Comparisons = 0;
        if (arr.empty())
            return -1;
        int l = 0, r = arr.size() - 1;

        while (l <= r)
        {
            int mid = l + (r - l) / 2;

            Comparisons++;
            if (arr[mid] == target)
                return mid;

            Comparisons++;
            if (arr[l] <= arr[mid]) // left half sorted
            {
                Comparisons++;
                if (arr[l] <= target)
                {
                    Comparisons++;
                    if (target < arr[mid])
                    {
                        r = mid - 1;
                    }
                    else
                    {
                        l = mid + 1;
                    }
                }
                else
                {
                    l = mid + 1;
                }
            }
            else if (arr[r] >= arr[mid]) // right half sorted
            {
                Comparisons++;
                if (arr[mid] < target)
                {
                    Comparisons++;
                    if (target <= arr[r])
                    {
                        l = mid + 1;
                    }
                    else
                    {
                        r = mid - 1;
                    }
                }
                else
                {
                    r = mid - 1;
                }
            }
            else // handle duplicates
            {
                l++;
                r--;
            }
        }

        return -1;
    }

    int getComparisons()
    {
        return Comparisons;
    }
};
int main()
{
    RotatedBinarySearch<int> obj;

    vector<int> v = {2, 2, 2, 2, 2, 2, 2, 2};

    obj.setArray(v);

    int target = 7;

    int idx = obj.search(target);

    if (idx != -1)
        cout << "Found at index: " << idx << endl;
    else
        cout << "Not Found\n";

    cout << "Comparisons: " << obj.getComparisons() << endl;
}
/*
Best Case Complexity: O(1)
- When target is found at the first middle check.

Worst Case Complexity: O(n)
- Due to duplicate elements, we may shrink
  the search space one element at a time.

  
  Average:    O(log n) → normal rotated array without duplicates
*/
