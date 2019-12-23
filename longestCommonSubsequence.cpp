#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Problem:
    Given two strings text1 and text2, return the length of their longest common subsequence.

    A subsequence of a string is a new string generated from the original string with some characters(can be none) deleted 
        without changing the relative order of the remaining characters. (eg, "ace" is a subsequence of "abcde" while "aec" is not). 
        A common subsequence of two strings is a subsequence that is common to both strings.

    If there is no common subsequence, return 0.

Example:

    // text1 and text2 are the two input strings of each stack
    // (a, b) meaning pointer pointing at a certain character ('a' of text1, and 'b' of text2) 
        ( should probably use index, but similar idea )

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

Idea for optimizations:

    BUD
        Bottleneck: ?? The whole process is a bottleneck... because every call branches out 4 times and depth is N + M ??
        Uncessary work: Everything before the pointers should be somewhat matching 
                        if input is text1 = "abc" text2 = "defbc" (c, e)
                            ^ in this case, we know we are already doomed because our pointer already moved 
                            passed "ab" in text1, and "d" in text2, they will never match

        Duplicate work: duplicate work is non-existent in the expanded example above, probably because there are 
                        no duplicate characters within text1 or text2

            Example with duplicate work:
                > if text1 = "aabc" , text2 = "adefbc" (0, 0)
                    text1 = "aabc", text2 = "adefbc" (1, 1)
                        text1 = "abc", text2 = "adefbc" (1, 2)   < same 
                    text1 = "aabc", text2 = "defbc" (1, 0)
                    text1 = "abc", text2 = "adefbc" (0, 1)
                        text1 = "abc", text2 = "adefbc" (1, 2)   < same ( duplicate work because we should've cached it )
                        text1 = "abc", text2 = "defbc" (0, 0)

    1. Pruning: Maybe before we recurse, we can check that it can possibly return something that isn't 0
    2. Cache: Cache every input with key being text1, text2 and the pair of index pointers
        > C++ unordered_map
            - O(1) look up
            - requires overloading ==
            - requires custom hash funciton which is probably overkill for an interview setting 
        > C++ map
            - O(logn) look up
            - Maybe just explain that in a real world setting probably worth it to push for O(1) and write a hash function?

*/

struct key {
    string text1;
    string text2;
    int text1Index;
    int text2Index;

    key( string one, string two, int oneIndex, int twoIndex ) :
        text1( one ), text2( two ), text1Index( ondIndex ), text2Index( twoIndex )
    {
    }

    bool const operator==(const key &o)  const {
        return ( text1 == o.text1 && text2 == o.text2 && text1Index == o.text1Index && text2Index == o.text2Index );
    }

    bool const operator<(const coord &o)  const {
        if ( text1 != o.text1 ) { return text1 < o.text1; }
        if ( text2 != o.text2 ) { return text2 < o.text2; }
        if ( text1Index != o.text1Index ) { return text1Index < o.text1Index; }
        if ( text2Index != o.text2Index ) { return text2Index < o.text2Index; } 
    }
};

string fixString( string text, int index ) {
    if ( index < text.length() ) {
        text.erase( index, 1 );
        return text;
    }
    return text;
}

class Solution {

public:
    int LCSHelper( string text1, string text2, int text1Index, int text2Index ) {
        // consult cache
        key ( text1, text2, text1Index, text2Index) curKey;
        if ( cache.find( curKey ) != cache.end() ) { return cache[ curKey ]; } // return cached result if found

        // base case
        if ( text1Index == text1.length() && text2Index == text2.length() ) // reached the end on both strings
            return ( text1 == text2 ) ? text1.length() : 0; // return length of text if text1 == text2, otherwise 0

        // check if it is impossible to obtain a non 0 return value, update cache
        int ptr1 = 0, ptr2 = 0;
        while ( ptr1 < text1Index && ptr2 < text2Index ) {
            if ( text1[ ptr1 ] != text2[ ptr2 ] ) { 
                cache.insert( make_pair( curKey, 0 ));
                return 0;
            }
            ptr1++; ptr2++;
        }

        // continually recurse ( branch out to 2-4 different options )
        int max = 0;
        // case1: don't remove
        {
            int next1Index = ( text1Index == text1.length() ) ? text1Index : text1Index + 1;
            int next2Index = ( text2Index == text2.length() ) ? text2Index : text2Index + 1;
            int subLCS = LCSHelper( text1, text2, next1Index, next2Index ); // solution subproblem
            max = ( subLCS > max ) ? subLCS : max; // udpate max when necessary
        }
        // case2: remove both
        {
            string nextText1 = fixString( text1, text1Index );
            string nextText2 = fixString( text2, text2Index );
            int subLCS = LCSHelper( nextText1, nextText2, text1Index, text2Index ); // solution subproblem
            max = ( subLCS > max ) ? subLCS : max; // udpate max when necessary
        }
        // case3: remove text1's character
        if ( text1Index == text1.length() ) {
            string nextText1 = fixString( text1, text1Index );
            int next2Index = ( text2Index == text2.length() ) ? text2Index : text2Index + 1;
            int subLCS = LCSHelper( nextText1, text2, text1Index, next2Index );
            max = ( subLCS > max ) ? subLCS : max;
        }
        // case4: remove text2's character
        if ( text2Index == text2.length() ) {
            string nextText2 = fixString( text2, text2Index );
            int next1Index = ( text1Index == text1.length() ) ? text1Index : text1Index + 1;
            int subLCS = LCSHelper( text1, nextText2, next1Index, text2Index );
            max = ( subLCS > max ) ? subLCS : max;
        }

        cache.insert( make_pair( curKey, max ));
        return max;
    }

    int longestCommonSubsequence(string text1, string text2) {
        return LCSHelper( text1, text2, 0, 0 );
    }

private:
    map<key, int> cache;
};