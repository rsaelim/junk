'''
https://fellows.pathrise.com/knowledge/guides/problem-find-intersection-of-two-sorted-integer-arrays

During:
	-The problem is straight forwad, input and out are clear and edge cases are addressed
	-Immediately a 1 pass algorithm comes to mind and that also seems like the optimal algorithm
After:
	-The solution is a 2 pointer 1 pass algorithm since both arrays are sorted. 
	-Runtime: O(n+m), Space: O(1)
	-[1,3,100,224,225,226], []
	-[1,3,100,224,225,226], [3000, 4100, 4500]
	-[5], [1, 20]
'''

'''
[1,3,100,224,225,226], []
[1,3,100,224,225,226], [3000, 4100, 4500]
[5], [1, 20]
'''
def intersectionArray( arr1, arr2 ):

	arr1Index = 0
	arr2Index = 0
	res = []

	while ( arr1Index != len( arr1 ) and arr2Index != len( arr2 ) ):

		if (arr1[ arr1Index ] == arr2[ arr2Index ]):
			res.append( arr1[ arr1Index ] )
			arr1 += 1
			arr2 += 1
		elif ( arr1[ arr1Index ] > arr2[ arr2Index ] ):
			arr2 += 1
		else:
			arr1 += 1

	return res