#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class RotatedBinarySearch
{
private:
    vector<T> arr;
    int com = 0;

public:
    void setArray(vector<T> a)
    {
        arr = a;
    }
    int search(T target)
    {
        com = 0;
        int l = 0, r = arr.size() - 1;

        while (l <= r)
        {
            int mid = l + (r - l) / 2;

            com++;
            if (arr[mid] == target)
                return mid;

            com++;
            if (arr[l] < arr[mid])// arr[mid] belongs to left sorted array
            {
                com += 2;
                if (arr[l] <= target && target < arr[mid])
                    r = mid - 1;
                else
                    l = mid + 1;
            }
            else if (arr[mid] < arr[r])// arr[mid] belongs to right sorted array
            {
                com += 2;
                if (arr[mid] < target && target <= arr[r])
                    l = mid + 1;
                else
                    r = mid - 1;
            }
            else
            {
                l++;
                r--;
            }
        }
        return -1;
    }

    int getComparisons()
    {
        return com;
    }
};
int main()
{
    RotatedBinarySearch<int> obj;

    vector<int> v = {5, 6, 7, 1, 2, 3, 4};

    obj.setArray(v);

    int target = 9;

    int idx = obj.search(target);

    if (idx != -1)
        cout << "Found at index: " << idx << endl;
    else
        cout << "Not Found\n";

    cout << "Comparisons: " << obj.getComparisons() << endl;
}