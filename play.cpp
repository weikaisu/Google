#include <iostream>
#include <vector>

using namespace std;

class Play{
public:
    void BubbleSort(vector<int>& nums) {
        bool swapped = true;
        while(swapped) {
            swapped = false;
            for(int i=0; i<nums.size()-1; i++)
                if(nums[i]>nums[i+1]) {
                    swap(nums[i], nums[i+1]);
                    swapped = true;
                }
        }
    }
};