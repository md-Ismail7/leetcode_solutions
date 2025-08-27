int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* res = (int*)calloc(numsSize, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        int cnt = 0;
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[j] < nums[i]) cnt++;
        }
        res[i] = cnt;
    }
    return res;
}
