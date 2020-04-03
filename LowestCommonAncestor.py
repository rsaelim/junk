''' Lowest Common Ancestor
Given one root node and two arbitrary nodes (node1 and node2) in a binary tree, return the Lowest Common Ancestor of those two nodes.

Nodes have a value, a parent pointer, and two child pointers (as part of a binary tree)

The Lowest Common Ancestor node of any two nodes is the lowest node that has both node1 and node2 as descendents; or put another way, the node that is farthest from the root node that has node1 and node2 as children.

'''

'''
During:
-I understand the question, its input and output
-Also have similar clarifying questions than the one listed in the doc.
-BruteForce: Go through every node and check to see if it is the answer by checking itself, recursing left, and recursing right. Do this for every node. 
O(n^2) with n being number of nodes in the tree
-

After:

			5
		/		\
	   11 		 4
	 /   \	   /   \         
    3     2    1    0

    input: [5, 11, 2]
    	   [5, 2, 0]
    -Derived an algo that is does not do (n^2), but runtime is not super apparent, need to run a few test case to confirm
    -Time is up and I have a solution, but code is a little convoluted and not clean. Runtime is not apparent, need to spend more time on this
    
'''


def findLowestCommonAncestor( root, node1, node2 ):

	def helper(root, nodes):
		if root is None:
			return (0, None)

		# recurse left to find nodes
		Lfindings, LpotentialLCA = helper(root->left, nodes)
		if Lfindings == 2:
			return LpotentialLCA
		# recurse right to find nodes
		Rfindings, LpotentialLCA = helper(root->right, nodes)
		if Rfindings == 2:
			return LpotentialLCA

		# return root if one node is in left subtree and the other is in right subtree
		if Lfindings == 1 and Rfindings == 1:
			return (2, root)

		# case that one of the subtree has a node, or neither
		totalFindings = max(Lfindings, Rfindings)
		if root in nodes:
			totalFindings += 1
		if totalFindings == 2:
			return (totalFindings, root)

		# otherwise, return
		return (totalFindings, None)


	

