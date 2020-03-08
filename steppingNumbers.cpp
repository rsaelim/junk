
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
Unnecessary work: incrementing number 1 by 1 and checking if it is valid, maybe instead we can just generate the next stepping number
Duplicate work: None

*/

class Solution {
public:
    vector<int> countSteppingNumbers(int low, int high) {
        vector<int> res;
        list<int> branch = { 0,1,2,3,4,5,6,7,8,9 };
        auto itr = branch.front();
        while ( itr != list.end() && *itr <= high ) {
            if ( *itr >= low ) { res.push_back( *itr ); }
            if ( *itr != 0 && (long)*itr * 10 < INT_MAX ) {
                int lastDigit = (*itr) % 10;
                if ( lastDigit > 0 ) { branch.push_back( (*itr * 10) + lastDigit - 1 ); }
                if ( lastDigit < 9 ) { branch.push_back( (*itr * 10) + lastDigit + 1); } 
            }
            itr++;
            branch.pop_front();            
        }
        return res;
    }
};
