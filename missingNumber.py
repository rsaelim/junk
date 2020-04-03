'''
During: 
	-I understand the input and output, there are a few edge cases need to be clarified but the following slides demonstrated
	-Bruteforce would be counting every element from start to end and going up the array to see if each element is there
	-This would take O(k) k being the start, end range input

After:
	-[1,3,5,7,8,9,13] (arr, 5, 13)
	-[1,3,7,8,9] (arr, 5, 19)
	-[1,3,5,9] (arr, 5, 9)
	-This question seems easy at first but I realize that there are a lot of edge cases. Algorithmically it's not that difficult,
	but I should walk through more examples before writing code for it
	-The solution is optimal, it is O(n) worst case, with n being length of the array




'''

def main( arr, start, end ):
	res = []
	missingHead = start - 1
	missingTail = None
	for i in range(len(arr)):
		if arr[i] >= start:
			if missingHead + 1 != arr[i]:
				missingTail = arr[i]
				i = missingHead + 1
				j = missingTail - 1
				if i == j:
					res.append(str(i))
				else:
					res.append(str(i) + "-" + str(j))
			missingHead = arr[i]
		if arr[i] >= end
			break
	if missingHead < end:
		i = missingHead + 1
		if i == end:
			res.append(str(i))
		else:
			res.append(str(i) + "-" + str(end))

	output = ""
	for i in range (len(res)) :
		output += res[i]
		if i < len(res) - 1:
			output += ", "
	print(output)
