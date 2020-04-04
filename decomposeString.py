'''
Given a string T, the idea is to decompose it into a list of substrings called phrases.
these phrases follow three rules:
1. The concatenation of all of them is the original string T.
2. Every new phrase is either:
  a. A single character
  b. A previously seen phrase, or:
  c. A previously seen phrase with a single character appended to it
3. Each new phrase is as long as possible

Examples:
"goooooogle" -> ["g", "o", "oo", "ooo", "gl", "e"]
"banana" -> ["b","a","n","an", "a"]
"lalaland" -> ["l", "a", "la", "lan", "d"]
'''

def decomposeString( inStr ):
    res = []
    mySet = set()
    for index in range( len(inStr) ):
        string = inStr[index]
        while( index != len(inStr) - 1 and string in mySet ):
            index += 1
            string += inStr[index]
        mySet.add(string)
        res.append( string )
    return res

'''
        v
 01234567
 
      v 
 'aaaaaaaaaaaaaaa'
 [a, aa, aaa]
 
 a 
 a <
 
"aannaaaa" -> ["a", "an", "n", "aa", "aa"]
            string = "aa"
            index = 0
            mySet [ "a", "an", "n", "aa", "aaa", "aaaa", "aaaaa" ]
            res[ "a", "an", "n", "aa", "aa"]

Method: Trie
Runtime: O(n), n being length of string 
because we iterate the trie as we look at each character
Space O(n), worst case did not change but we are saving space on aaa example
'''

class node:
  self.children = {}
  def __init__():
    

def decomposeString( input ):
  res = []
  trie = node()
  current = trie
  word = ""
  
  for index, char in enumerate(input):
    word += char
    if char in current.children.keys() and index != len(input) #We were here before
      current = current.children[char]
    else:
      current.children[char] = new Node()
      res.append( word )
      word = ""
      current = trie

  return res

















