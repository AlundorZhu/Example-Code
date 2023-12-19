class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:

        hashmap = {} # initializing a hashmap
        for i in range(len(nums)): 
            # for each half, find the other half. Thus only one loop needed
            complement = target - nums[i]
            if complement in hashmap: # find the other half
                return [hashmap[complement], i]
            hashmap[nums[i]] = i
        
        return[]