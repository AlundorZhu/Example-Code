# Brute force
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        longest_sub_str = ""
        for i in range(len(s)):
            existing_chars = []
            no_repeat = True
            curr_str = ""
            while no_repeat and i < len(s):
                # check if next charactor does repeat
                if s[i] not in existing_chars:
                    curr_str += s[i]
                    existing_chars.append(s[i])
                else:
                    no_repeat = False
                i += 1

            if len(curr_str) > len(longest_sub_str):
                longest_sub_str = curr_str
        
        return len(longest_sub_str)
    
# use set and pointers
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        maxLen = 0
        for i in range(len(s)):
            existing_chars = set(s[i])
            no_repeat = True
            j = i + 1
            while no_repeat and j < len(s):
                # check if next charactor does repeat
                if s[j] not in existing_chars:
                    existing_chars.add(s[j])
                    j += 1
                else:
                    no_repeat = False
                    break

            maxLen = max(maxLen, j - i)
        
        return maxLen
    
# use hash and indexes
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        maxLen = 1
        # gurantee no repeat between i and j
        i = 0
        existing_chars_and_their_indices = {}

        # put the first char in
        existing_chars_and_their_indices[s[i]] = i

        # check if next char is repeated
        j = i + 1
        
        while i < len(s) and j < len(s):

            # if next char is repeated
            if s[j] in existing_chars_and_their_indices and existing_chars_and_their_indices[s[j]] > i:
                # move the pointer and not update the maxLen
                i = existing_chars_and_their_indices[s[j]] + 1

                if len(s) - i + 1 <= maxLen:
                    # no way for the rest of the string be longer than the found maxLen
                    return maxLen

            # update the index in the hashmap of repeated
            existing_chars_and_their_indices[s[j]] = j
            # same for no repeat
            # put new char in hashmap

            # increment j
            j += 1

            maxLen = max(maxLen, j - i)
        
        return maxLen