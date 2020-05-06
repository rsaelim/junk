'''
We are given hours, a list of the number of hours worked per day for a given employee.

A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.

A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.

Return the length of the longest well-performing interval.

 

Example 1: 
 start            v
 end              v
Input: hours = [ 9, 9, 6, 0, 6, 6, 6, 6, 9, 9, 9, 9]

 net (start 0) [ 1, 2, 1, 0,-1,-2,-3,-4,-3,-2,-1, 0]
 net (start 1) [ -, 1, 0,-1,-2,-3,-4,-5,-4,-3,-2,-1] -1
 net (start 2) [ -, -,-1,-2,-3,-4,-5,-6,-5,-4,-3,-2] -1
 net (start 3) [ -, -, -,-1,-2,-3,-4,-5,-4,-3,-2,-1] +1
 net (start 4) [ -, -, -, -,-1,-2,-3,-4,-3,-2,-1, 0] +1
 net (start 5) [ -, -, -, -, -,-1,-2,-3,-2,-1, 0, 1] +1
 net (start 6) [ -, -, -, -, -, -,-1,-2,-1, 0, 1, 2] +1
 net (start 7) [ -, -, -, -, -, -, -,-1, 0, 1, 2, 3] +1
 net (start 8) [ -, -, -, -, -, -, -, -, 1, 2, 3, 4] +1
 net (start 9) [ -, -, -, -, -, -, -, -, -, 1, 2, 3] -1
 net (start 10)[ -, -, -, -, -, -, -, -, -, -, 1, 2] -1
 net (start 11)[ -, -, -, -, -, -, -, -, -, -, -, 1] -1
 net (start 12)[ -, -, -, -, -, -, -, -, -, -, -, -] -1

 Observations:
    -We know if (start n) qualifies to have an interval if there is a 1
    -The interval of a particular (start n) is from the start index n to the position of the last "1"
    	-aka position of the last "1" minus n plus 1
    	k - n + 1 = interval length
    -If we iterate through n, we can keep track of our net plus and minuses
    	-e.g.: If we look at the above example of (start 6) the net sum of all the + and - can be fetched in O(1) if we keep track
    	-(start 6) would have -2 +4 ----> +2.
    	+2 + x is 1 if x is (-1). So if we find (-1) in (start 0) that position would be (1) in (start 6)
    		-To find where the last (-1) is in (start 0) means we need to store start(0) array in a dictionary like so:
    			dictstart0[-1] = 10
    			-1 is the value and 10 is the index of the last occurence of the value in array (start 0)
	    	-This however is incorrect when evluating the max well-performing interval for (start 6) because there is a "2" in the array
	    		-A 2 should never be part of a max interval solution because that indicates you can extend the interval to include more non-well-performing days
	    		-This means that to utilize this method, we need to code around the edge case that the whole input hours array is well-performing
 
Output: 3
Explanation: The longest well-performing interval is [9,9,6].

[6,6,9,9,9] => 5
[6] => 0
[6,9] => 1

B : We have to try all start / end combinations.
U : 
D :

Constraints:

1 <= hours.length <= 10000
0 <= hours[i] <= 16
'''

def findMaxWellPerforming( inputHours ):

	if inputHours is None:
		return 0
	''' 
	index     	     0  1  2  3  4  5  6  7  8  9 10 11
	Input: hours = [ 9, 9, 6, 0, 6, 6, 6, 6, 9, 9, 9, 9]
 rolling (start 0) [ 1, 2, 1, 0,-1,-2,-3,-4,-3,-2,-1, 0]
 									^
 									dict [-2] = 5
 										   ^    ^
 									   rolling  index
 	'''
	# Generate dictStart0 {}
 	dictStart0 = {}
 	rolling = 0
 	for index, num in enumerate( inputHours ):
 		if num >= 9:
 			rolling += 1
 		else:
 			rolling -= 1
 		dictStart0[ rolling ] = index

 	# if after iterating the whole inputHours the rolling is greater than 0, 
 	#that means the whole inputHours is a well-performing interval
 	if rolling > 0:
 		return len(inputHours)

 	netSum = 0
 	previous = inputHours[0]
 	maxIntervalSize = 0
 	for index in range(1, len(inputHours)):
 		if previous >= 9:
 			netSum -= 1
 		else:
 			netSum += 1
 		key = 1 - netSum # netSum + key = 1 (because 1 means we have a surplus of well-performing)
 		intervalEndIndex = dictStart0[ key ]
 		thisIntervalSize = intervalEndIndex - index + 1
 		if thisIntervalSize > maxIntervalSize:
 			maxIntervalSize = thisIntervalSize

 	return maxIntervalSize