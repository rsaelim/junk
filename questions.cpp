#include <iostream>
#include <string>
#include <vector>

/*
Given two integers dividend and divisor, divide two integers without using multiplication, division and mod operator.

Return the quotient and remainder after dividing dividend by divisor.

Example 1:

Input: dividend = 10, divisor = 3
Output: 3 r 1
Example 2:

Input: dividend = 7, divisor = 3
Output: 2 r 1
Note:

Both dividend and divisor will be 32-bit signed integers.
The divisor will never be 0.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 231 − 1 when the division result overflows.

150 / 3

3 (3 * 1)
6 (3 * 2)
12 (3 * 4)
24 (3 * 8)
48 (3 * 16)
96 (3 * 38)
192 - over

1. Divisor cannot be 0

*/

using namespace std;

void divideHelper( int dividend, int divisor, int &remain) {

    // Base Case
    if ( divisor >= dividend ) {
        remain = divisor - dividend;
        return (divisor > dividend) ? 0 : 1;
    }

    // Recursive
    int count = 1;
    int originalDiv = divisor;
    while ( divisor <= dividend ) {
        divisor = divisor < 1;
        count = count < 1;
    }
    divisor = divisor > 1;
    count = count > 1;
    int newDividen = dividend - divisor;

    return count + divideHelper(newDividen, originalDiv, remain); 
}

void divide( int dividend, int divisor ) {

    int remain = 0;
    int quotient = divideHelper( dividend, divisor, remain);
    cout << quotient << " r " << remain << endl;
}

int main() {
    return 0;
}



/*
https://leetcode.com/problems/trapping-rain-water/
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
*/

/*

Input: [0,1,0,2,1,0,1,3,2,1,2,1]
            1   1 2 1     1
Output: 6

left absolute peak
right absolute peak
left local peaks
right local peaks

keep track of the absolute right peak: O(lg(n))

[2k,1k,1k,100,10,9,..,1]
         L                                                                                          R 
Input: [ 50, 1000, 90000,1,500, 500, 500, 500, 700, 900, 9,10,100,1000,2000, 3, 4, 100, 1, 100, 1, 100]
  
           L                                                            R
Input: [ 10000, 9999, 9998, 9997, 9996, 3999, 1000, 4000, 3001, 2000, 3000 ]
Input: [ 10000, 9999, 9998, 9997, 9996, 9995, 9994, 9993, 9992, 9991, 9990 ]

Bottleneck : If I have a high left bound, and I traverse the numbers on the right and they get bigger, 
I'd have to go back and change water trapped as long as the elevation keeps rising

Unnecessary : calculating water height for current right bound, if there is a higher right bound afterwards
Duplicate : None

*/

 int trap( vector<int>& height ) {
        
        if ( height.size() == 0 ) { return 0; }
        
        int res = 0;
        int left = 0;
        int right = height.size( ) - 1;
        int lowBound = min( height[ left ] , height[ right ] );
        
        while( left < right ) {
            if( height[ left ] <= height[ right ] ) { // if left is lower, incr left and evaluate if needed
                left++;
                if( height[ left ] < lowBound )
                    res += ( lowBound - height[ left ] );
                else if( height[ left ] > lowBound )
                    lowBound = min( height[ left ] , height[ right ] );
            }
            else { // else decr right
                right--;
                if( height[ right ] < lowBound )
                    res += ( lowBound - height[ right ] );
                else if( height[ right ] > lowBound )
                    lowBound = min( height[ left ] , height[ right ] );
            }
        }
        
        return res;
    }

/*

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Given two strings text1 and text2, return the length of their longest common subsequence.

A subsequence of a string is a new string generated from the original string with some characters(can be none) deleted without changing the relative order of the remaining characters. (eg, "ace" is a subsequence of "abcde" while "aec" is not). A common subsequence of two strings is a subsequence that is common to both strings.

 

If there is no common subsequence, return 0.




everything is a graph problem:

Nodes: state
edges: transitions between states

Node: permutation of text1 and text2
Edges: valid permutations of text1 and text2



## Remember the steps to solving a problem

### Understand the problem
- Ask clarifying questions
- Understand input bounds
- Write your own test cases and ask questions based off it
- Solve the problem intuitively by hand

### Design a solution
- Create a brute force solution, potentially inspired off your by-hand solution
- Understand and explain the algorithm and data structures associated with it
- Understand and explain the big O time and space
- Look for bottlenecks, unnecessary work, and duplicate work and design an optimization
- If you’re not making progress for 5 minutes, just code the brute force and then come back to optimizing

### Code the solution
- Test as you go
- Use useful variable names

### Explain your solution while you test
- Run through an example or two with clear edge cases in mind
- Track some important variables as you go and run through it step by step like a debugger


 

Example 1:

Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.
Example 2:

Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.
Example 3:

Input: text1 = "abc", text2 = "def"
Output: 0 
Explanation: There is no such common subsequence, so the result is 0.

O(3^n)

Examples:

// text1 and text2 are the two input strings of each stack
// (a, b) meaning pointer pointing at a certain character ('a' of text1, and 'b' of text2) ( should probably use index, but similar idea )

Input: tex1 = "abc", tex2 = "adbefc"  pointer (a, a)
    Input: tex1 = "abc", tex2 = "adbefc" (b, d)
        Input: tex1 = "abc", tex2 = "adbefc" (c, b)
            Input: tex1 = "abc", tex2 = "adbefc" (*, e)
                Input: tex1 = "abc", tex2 = "adbefc" (*, f)
                    Input: tex1 = "abc", tex2 = "adbefc" (*, c)
                        Input: tex1 = "abc", tex2 = "adbef" (*, *)   ----> return 0;
                        Input: tex1 = "abc", tex2 = "adbefc" (*, *)  ----> return 0;
                    Input: tex1 = "abc", tex2 = "adbec" (*, c)
                        Input: tex1 = "abc", tex2 = "adbec" (*, c) ----> return 0;
                        Input: tex1 = "abc", tex2 = "adbe" (*, *) ----> return 0;      
                Input: tex1 = "abc", tex2 = "adbfc" (*, f)
                    ...
            Input: tex1 = "abc", tex2 = "adefc" (*, e)
                ...
            Input: tex1 = "ab", tex2 = "adbefc" (*, e)
                ...
            Input: tex1 = "ab", tex2 = "adefc" (*, e)
                ...
        Input: tex1 = "abc", tex2 = "abefc" (c, b)
            ...
        Input: tex1 = "ac", tex2 = "adbefc" (c, b)
            ...
        Input: tex1 = "ac", tex2 = "abefc" (c, b)
            ...
    Input: tex1 = "abc", tex2 = "dbefc" (b, d)
        Input: tex1 = "abc", tex2 = "dbefc" (c, b)
            ...
        Input: tex1 = "abc", tex2 = "befc" (c, b)
            ...
        Input: tex1 = "ac", tex2 = "dbefc" (c, b)
            ...
        Input: tex1 = "ac", tex2 = "befc" (c, b)
            ...
    Input: tex1 = "bc", tex2 = "adbefc" (b, d)
        Input: tex1 = "bc", tex2 = "adbefc" (c, b)
            ...
        Input: tex1 = "bc", tex2 = "adbefc" (c, b)
            ...
        Input: tex1 = "c", tex2 = "adbefc" (c, b)
            ...
        Input: tex1 = "c", tex2 = "adbefc" (c, b)
            ...
    Input: tex1 = "bc", tex2 = "dbefc" (b, d)
        Input: tex1 = "bc", tex2 = "defc" (c, b)
            ...
        Input: tex1 = "bc", tex2 = "dbefc" (c, b)
            ...
        Input: tex1 = "c", tex2 = "defc" (c, b)
            ...
        Input: tex1 = "c", tex2 = "dbefc" (c, b)
            ...

// Idea for optimizations:

    BUD
    Bottleneck: ?? The whole process is a bottleneck... ??
    Uncessary work: Everything before the pointers should be somewhat matching 
                    if input is text1 = "abc" text2 = "defbc" (c, e)
                        ^ in this case, we know we are already doomed because our pointer already moved 
                        passed "ab" in text1, and "d" in text2, they will never match

    Duplicate work: duplicate work is non-existent in the expanded example above, probably because there are 
                    no duplicate characters within text1 / text2

    Example with duplicate work:
        > if text1 = "aabc" , text2 = "adefbc" (0, 0)
            text1 = "aabc", text2 = "adefbc" (1, 1)
                text1 = "abc", text2 = "adefbc" (1, 2)   < same 
            text1 = "aabc", text2 = "defbc" (1, 0)
            text1 = "abc", text2 = "adefbc" (0, 1)
                text1 = "abc", text2 = "adefbc" (1, 2)   < same ( duplicate work because we should've cached it )
            text1 = "abc", text2 = "defbc" (0, 0)

commonChild("shinchanshinchanshinchanshinchanshinchanshinchan", "noharaaanoharaaanoharaaanoharaaanoharaaanoharaaa")

Input: tex1 = "bcdefg", tex2 = "bbbbbcdeagaeifg"
Input: tex1 = "abcdefg", tex2 = "bbbbcdeagaeifg"
Input: tex1 = "bcdefg", tex2 = "bbbbcdeagaeifg"
               ^                         ^

string current = "";



*/






/* Stepping Numbers

    A Stepping Number is an integer such that all of its adjacent digits have an absolute difference of exactly 1. 
    For example, 321 is a Stepping Number while 421 is not.

    Given two integers low and high, find and return a sorted list of all the Stepping Numbers in the range [low, high] inclusive.

    

    Example 1:

    Input: low = 0, high = 200
    Output: [0,1,2,3,4,5,6,7,8,9,10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98,123,]
    

    Constraints:

    0 <= low <= high <= 2 * 10^9

Bruteforce:
    loop through all the numbers from low to high     *O( high - low )
        -check if a number is stepping number
            -loop through every digit to see if it is stepping    *O(1) because number of digits is essentially bounded by 10

Bottleneck: We have to iterate through from low to high and increment


*/






/* Get Equal Substrings Within Budget

You are given two strings s and t of the same length. You want to change s to t. Changing the i-th character of s to i-th character of t costs |s[i] - t[i]| that is, the absolute difference between the ASCII values of the characters.

You are also given an integer maxCost.

Return the maximum length of a substring of s that can be changed to be the same as the corresponding substring of twith a cost less than or equal to maxCost.

If there is no substring from s that can be changed to its corresponding substring from t, return 0.

 

Example 1: Get Equal Substrings Within Budget

Input: s = "abcd", t = "bcdf", maxCost = 3
Output: 3
Explanation: "abc" of s can change to "bcd". That costs 3, so the maximum length is 3.
Example 2:

Input: s = "abcd", t = "cdef", maxCost = 3
Output: 1
Explanation: Each character in s costs 2 to change to charactor in t, so the maximum length is 1.
Example 3:

Input: s = "abcd", t = "acde", maxCost = 0
Output: 1
Explanation: You can't make any change, so the maximum length is 1.

*/







/* Remove Sub-Folders from the Filesystem

Given a list of folders, remove all sub-folders in those folders and return in any order the folders after removing.

If a folder[i] is located within another folder[j], it is called a sub-folder of it.

The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters. For example, /leetcode and /leetcode/problems are valid paths while an empty string and / are not.

 

Example 1:

Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
Output: ["/a","/c/d","/c/f"]
Explanation: Folders "/a/b/" is a subfolder of "/a" and "/c/d/e" is inside of folder "/c/d" in our filesystem.
Example 2:

Input: folder = ["/a","/a/b/c","/a/b/d"]
Output: ["/a"]
Explanation: Folders "/a/b/c" and "/a/b/d/" will be removed because they are subfolders of "/a".
Example 3:

Input: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
Output: ["/a/b/c","/a/b/ca","/a/b/d"]
 

Constraints:

1 <= folder.length <= 4 * 10^4
2 <= folder[i].length <= 100
folder[i] contains only lowercase letters and '/'
folder[i] always starts with character '/'
Each folder name is unique.


*/