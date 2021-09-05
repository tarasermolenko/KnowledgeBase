class Solution {
public:
    int lengthOfLongestSubstring(string s) 
    {
        // empty case 
        if (s.length() == 0)
        {
            return 0;           
        }

        // single case
	if (s.length() == 1)
        {
            return 1;           
        }

	int longestSub = 0;
	int start = 0;
	int i = 0;

        while (i < s.length())
	{
		bool repeating = false;
		int j = start;

		for (j = start; j < i; j++)
		{
			if (s[j] == s[i])
			{
				repeating = true;
				break;
			}
		}

		if (!repeating)
		{
			i++;
		}
		else
		{
		
			if(longestSub < i - start)
                	{
                    		longestSub = i - start;
                	}
                
			start = j + 1;
		}
		
	}

	if(longestSub < i - start)
        {
            longestSub = i - start;
        }
                
	return longestSub;
    }
};
