bool validate(struct TreeNode* root, long minVal, long maxVal) {
    if (root == NULL) 
        return true;

    // Check if current node's value is within range
    if (root->val <= minVal || root->val >= maxVal) 
        return false;

    // Recursively validate left and right subtrees
    return validate(root->left, minVal, root->val) &&
           validate(root->right, root->val, maxVal);
}

bool isValidBST(struct TreeNode* root) {
    return validate(root, LONG_MIN, LONG_MAX);
}