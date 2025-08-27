struct TreeNode* buildBalanced(int* arr, int l, int r) {
    if (l > r) return NULL;
    int mid = (l + r) / 2;
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = arr[mid];
    root->left = buildBalanced(arr, l, mid - 1);
    root->right = buildBalanced(arr, mid + 1, r);
    return root;
}

void inorder(struct TreeNode* root, int* arr, int* idx) {
    if (!root) return;
    inorder(root->left, arr, idx);
    arr[(*idx)++] = root->val;
    inorder(root->right, arr, idx);
}

struct TreeNode* balanceBST(struct TreeNode* root) {
    int arr[10000], idx = 0;   // constraint safe (nodes ≤ 10^4)
    inorder(root, arr, &idx);
    return buildBalanced(arr, 0, idx - 1);
}