class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        
        int len = nums.size();
        
        if(len <= 10000 && len >= 2 && target <= 1000000000 && target >= -1000000000)
        {
            for(int i = 0; i < len; i++) 
            {
                for(int j = i + 1; j < len; j++) 
                {
                    if(target == nums[j] + nums[i])
                    {
                        return { i, j };
                    }
                }
            }
            return {-1, -1};
        }
        else
        {
            cout << "Error, Input outside constraints";
            return {-1, -1};
        }
    }
};
