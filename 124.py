''' 124
Given a non-empty binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

Example 1:

Input: [1,2,3]

       1
      / \
     2   3

Output: 6
Example 2:

Input: [-10,9,20,null,null,15,7]

https://leetcode.com/problems/binary-tree-maximum-path-sum/

   -10
   / \
  9  20
       \
        7
   
            10
           /  \
          9    20
         / \   / \
        1   2 15  7
             /    \
            200   300
           /  
         -10 (-5)
            \
             5



            10
          /    \
      -1000    200
      /   \
     5     500
          
            5
        /      \
       4         8
     /         /   \  
    11       13     4
  /   \              \
 7     2               1

Output: 42
'''
# return max sum of a node taking any single path without splitting, 
# maximum is the node->val if all paths yield a lower sum, still possible to return a negative value
# O(n) | n is number of nodes


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
        
class Solution:
    
    def __init__(self):
        self.cache = {}
    
    def maxPathSum(self, root: TreeNode) -> int:
        
        def maxSum( node ) -> int:

            toAdd = node.val
            LeftSum = 0
            RightSum = 0
            if node.left:
                leftSum = maxSum(node.left)
            if node.right:
                rightSum = maxSum(node.right)
            
            self.cache[node] = toAdd + max(leftSum, 0) + max(RightSum, 0) # memoize 
            return max( toAdd + leftSum, toAdd + RightSum, toAdd )
    
        garbage = maxSum( root )
        orderedList = sorted(self.cache.values())
        print(orderedList)
        return orderedList[-1]
    
    
    
    

