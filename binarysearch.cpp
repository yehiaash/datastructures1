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
            else // right half sorted
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

    vector<int> v = {5, 6, 7, 1, 2, 3, 4};

    obj.setArray(v);

    int target = 7;

    int idx = obj.search(target);

    if (idx != -1)
        cout << "Found at index: " << idx << endl;
    else
        cout << "Not Found\n";

    cout << "Comparisons: " << obj.getComparisons() << endl;
}
