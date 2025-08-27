struct TreeNode* sortedListToBST(struct ListNode* head) {
    if(head==NULL)
    {
        return NULL;
    }
    struct ListNode *prev=NULL;
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    while(fast!=NULL && fast->next!=NULL)
    {
        prev=slow;
        slow = slow->next;
        fast =fast->next->next;
    }
    struct TreeNode *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val=slow->val;
    root->left =NULL;
    root->right =NULL;
    if(prev)
    {
       prev->next =NULL;
       root->left =sortedListToBST(head);
    }
   root->right = sortedListToBST(slow->next);
   return root;
}
```