class Solution {
public:
     ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
     {
        int sum = 0;
        
        // resulting linked list 
        ListNode result(0);
        // Points to position where we are inserting  
        ListNode *current = &result;
        
        // while they are not null add them together 
        while(l1 || l2)
        {
            // if list contains value add to sum
            if(l1)
            {
                sum += l1->val;
                l1 = l1->next;
            }

            if(l2)
            {
                sum += l2->val;
                l2 = l2->next;
            }
    
            current->next = new ListNode(sum % 10);
            current = current->next;
            
            // if some over 10 or over we will have carry bits over to next 
            // decimal place by adding it to the sum of next addition
            sum = sum / 10;
        }

        if(sum > 0)
        {
            current->next = new ListNode(sum % 10);
        }

        return result.next;
    }
};
