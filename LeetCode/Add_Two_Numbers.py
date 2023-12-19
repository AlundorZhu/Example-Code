# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        carry = False
        head = ListNode(0) # needed to indicate the start of the list
        curr = head
        # nodes can't point to itself

        while l1 != None or l2 != None or carry == True:
            
            # vale or 0 is no node exist
            val1 = l1.val if l1 else 0
            val2 = l2.val if l2 else 0
            
            # add if have carried over
            if carry:
                sum1 = val1 + val2 + 1
            else:
                sum1 = val1 + val2

            # does it carries to the next digit
            carry = True if (sum1 >= 10) else False

            # put number(0-9) in the current digit
            sum1 = sum1 % 10
            newNode = ListNode(sum1)
            curr.next = newNode

            # updates the pointers for the next iteratoin
            curr = curr.next
            l1 = l1.next if l1 else None
            l2 = l2.next if l2 else None
        
        return head.next