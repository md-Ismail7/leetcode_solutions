int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize=numsSize-k+1;
    if(*returnSize<=0)
    {
        *returnSize=0;
        return NULL;
    }
    int *result = (int *)malloc((*returnSize)*sizeof(int));
    
    for(int start=0; start < *returnSize; start++)
    {
       int max=nums[start];
          for(int j=start+1;j<start+k;j++)
          {
            if(nums[j]> max)
            {
                max=nums[j];
            }
          }
          result[start]=max;
    }
    return result;
}