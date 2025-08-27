int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    
    static int *arr = NULL;   
    static int index = 0;       
    static int depth = 0;    

    if (depth == 0) {         
        index = 0;
        *returnSize = 0;
        arr = (int*)malloc(100 * sizeof(int)); 
    }

    if (root == NULL) {
       
        return arr;
    }

    depth++;
    inorderTraversal(root->left, returnSize);
    arr[index++] = root->val;          
    (*returnSize)++;
    inorderTraversal(root->right, returnSize);
    depth--;

 
    return arr;
}
