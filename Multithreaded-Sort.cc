//归并实现多线程排序

#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>

using namespace std;

const int THREAD_MAX_LIMIT = 11;
const int SMALL_SIZE_THRESHOLD = 64;

void Merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left +1;
    int n2 = right - mid;

    vector<int> a1(n1), a2(n2);
    
    for(int i = 0; i < n1; i++)
    {
        a1[i] = arr[i + left];
    }
    for(int i = 0; i < n2; i++)
    {
        a2[i] = arr[i + mid + 1];
    }

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2)
    {
        if(a1[i] <= a2[j])
        {
            arr[k] = a1[i];
            i++;
            k++;
        }
        else
        {
            arr[k] = a2[j];
            j++;
            k++;
        }
    }

    while(i < n1)
    {
        arr[k] = a1[i];
        k++;
        i++;
    }

    while(j < n2)
    {
        arr[k] = a2[j];
        k++;
        j++;
    }
}


void MergeSort(vector<int>& arr, int left, int right, int depth)
{
    if(right - left + 1 < SMALL_SIZE_THRESHOLD)
    {
        sort(arr.begin() + left, arr.begin() + right +1 );
        return;
    }

    if (left >= right) return;

    if(left < right)
    {
        int mid = left + (right - left)/2;

            if(depth > THREAD_MAX_LIMIT)
        {
            cout << "most Thread" << endl;
            MergeSort(arr, left, mid, depth + 1);
            MergeSort(arr, mid + 1, right, depth + 1);
        }
        else
        {
            std::thread liftThread(MergeSort, std::ref(arr), left, mid, depth + 1);
            std::thread rightThread(MergeSort, ref(arr), mid + 1, right, depth + 1);
        
            liftThread.join();
            rightThread.join();

        }
        
        Merge(arr, left, mid, right);
    }
}

void MultiThreadMergeSort(vector<int>& arr)
{
    if(arr.empty())
    return;
    MergeSort(arr, 0, arr.size() - 1, 0);
}

int main()
{
    vector<int> arr = {546, 752, 430, 404, 591, 446, 957, 490, 226, 620, 97, 738, 581, 807, 703, 70, 908, 564, 87, 206, 889, 688, 973, 310, 672, 799, 426, 980, 453, 571, 464, 780, 858, 839, 906, 503, 574, 31, 156, 342, 793, 149, 53, 813, 61, 412, 593, 982, 388, 89, 977, 879, 795, 174, 450, 850, 540, 281, 154, 275, 876, 434, 376, 942, 536, 723, 309, 555, 638, 976, 877, 996, 469, 852, 324, 530, 364, 973, 425, 585, 776, 91, 263, 716, 92, 142, 682, 252, 543, 705, 678, 296, 143, 531, 656, 765, 959, 414, 671, 828};

    MultiThreadMergeSort(arr);

    for(int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}

