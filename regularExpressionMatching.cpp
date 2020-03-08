#include <iostream>
#include <string>
#include <vector>

// 10. Regular Expression Matching

/*
    Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

    '.' Matches any single character.
    '*' Matches zero or more of the preceding element.
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        return isMatchHelper( s, p, 0, 0 );
    }

    bool isMatchHelper( string s, string p, int i, int j ) {
        // base case:
        if ( i == s.length() - 1 ) :
            if ( j == p.length() - 1 ) :
                if ( p[j] != '*') :
                    if ( p[j] == '.' || s[i] == p[j] ) : return 1
                    return 0
                else :
                    if ( p[j - 1] == s[i] ) : return 1
                    else : return memo[ (i-2, j) ]
            else:
                return 0 

        // memo case:
        if ( (i,j) in memo ) { return memo[ (i,j) ]; }

        // recursive cases:
        // 1. Match!
        if ( s[i] == p[j] || p[j] == '.' ) :
            memo[ (i,j) ] = isMatchHelper( s, p, i+1, j+1 )
            return memo[ (i, j) ]
        
        //2. Pruning 
        if ( p[j] != '*' || ( s[i] != p[j-1] && p[j-1] != '.' )) :
            memo[ (i,j) ] = 0
            return 0
        //3. 
        else : // p[j] == '*' && s[i] == p[j-1]
            memo[ (i,j) ] = isMatchHelper( s,p, i+1, j)
            return memo[ (i,j) ]
    }

    memo {};
};