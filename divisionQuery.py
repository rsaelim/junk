'''
Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.

Example:
Given a / b = 2.0, b / c = 3.0.
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.

According to the example above:

equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 

a / b = 2.0 , d / c = 3.0, a / g = 5.0, g / c = 7.0

a / c = ? ( a / g ) * ( g / c ) => a / c

----------------------------------------------------

a / b = 2.0 , b / c = 3.0, c / d = 5.0, d / e = 7.0 , a / g = 3.0, a / z = 5.0

a / e = ?
a / e = a/b * b/c * c/d * d/e
        a/g */ 
        a/z
        
z / b = (a / b) / (a / z)
        
        a = [b, g, z]
        b = [c]
        c = [d]
        d = [e]
        
        b = [a]
        c = [b]
        d = [c]
        e = [d]
        g = [a]
        z = [a]
        
graphs are flexible
- node
  - state
  - a variable would be a state
- edge
  - transition between states
  - a/b
  - want to avoid cycles
  - there might not be a path (-1)
  - weighted
  - bi-directional or uni-directional?
    - bi-directional-ish
  - how do we accumulate our answer?
  
 
Bottlenecks
unnecessary work
duplicate work


"hello"  <- b
            
"world"  <- a

b = "hello "
test(b)

def test(a):
    a = "world"
    a +=1
    return test(a)
    

class Solution:
    def hasPathSum1(self, root: TreeNode, sum: int) -> bool:
        sumInTree = False
        
        a = "hello "
        a += "world"
        
        result = []
        
        def dfs(node, sofar=0):
            nonlocal sumInTree
            
            result.append(2)
            
            if node is None:
                sumInTree |= sofar == sum
                return

            dfs(node.left, sofar + node.val)
            dfs(node.right, sofar + node.val)

        dfs(root)
        return sumInTree


----------------------------------------------------

a / g = 5.0 , c / g = 8.0
                    1 / (c / g)
a / c = ? (a / g) * (c / g) => a / c 

    a -> g
         ^
         |
         c
a/g / c/g

----------------------------------------------------

a / c = 10.0

a / c = a / c

----------------------------------------------------

a / c = 10.0

c / a = 1 / a/c

'''

def divisionQuery( equations, values, queries ):

  knownValues = {}
  # Store known division values in the form:
  # { 
  #   a: {c: 2.0}
  #   c: {a: 0.5}
  # }
  def push(nodeFrom, nodeTo, value):
      if nodeFrom in knownValues.keys():
        knownValues[ nodeFrom ][ nodeTo ] = value
      else:
        knownownValues[ nodeFrom ] = { nodeTo : value }
      if nodeTo in knownValues.keys():
        knownValues[ nodeTo ][ nodeFrom ] = 1/value
      else:
        knownownValues[ nodeTo ] = { nodeFrom : 1/value }

  def findQueryValue(start, end):
    #Breath first search
    seen = Set([])
    bfsq = Queue(0)
    bfsq.put((start, 1))

    while ( !bfsq.empty() ):
      curNode, traversalCost = bfsq.get() # pop off queue
      seen.add( curNode ) # mark as seen
      if curNode == end: # If we have reached end from the start, we return current accumulative
        return traversalCost
      for next in knownValues[ curNode ].keys():
        if next not in seen:
          bfsq.put(next, traversalCost * knownValues[curNode][next])
        push(start, next, tarversalCost * knownValues[curNode][next]) # recording values along the way of exploration
    push(start, end, -1)
    return -1
    
    # load knownValues
    for i in range( len(equations) ):
      nodeFrom = equations[i][0]
      nodeTo = equations[i][1]
      push(nodeFrom, nodeTo, values[i])

    res = []
    for query in queries:
      res.append( findQueryValue(query[0], query[1]) )
    return res







    
  
  





