''' Balance the paraenthesis in a string 
Given a string of alphanumeric characters and paranthesis, 
return a string with balanced parantehses by removing the fewest characters possible.

e.g. "b(a)r)"

During: 
-I completely understand the problem and understand the input and output
-Brute force solution would be iterating through the string and for each character we branch out to remove and not remove. And for each solution, we check vilidity of the string of whether the parantheses are balanced,
and we compute the difference in length between each result to the original string. We would then keep track of which string has the lowest diff as well as the result string itself.
This would be O(2^n) with n being length of the string.
-This is the bruteforce because it blindly exhausts all possible combinations without regards on any observations or insights.
-Optimization:
	-If it is not a '(' or ')' we do not consider removing it
	-We can keep track of a stack of read in parantheses and their index, 
	so every parantheses we encounter, we could either add it in the stack for future reference or we could conclude as no removal for an existing top of the stack
		-Any left over parantheses at the end would be considered removal needed

After:
-The solution seems to work per the tests I walked through. 
I haven't ran it because it's not on leetcode. However, it seems that I might have overthink or did it in a way that's not the most straightforward
-O(n) time, O(n) space
-")))((("
-")(()()("
'''

def balanceParan( input ):

	openRemoval = []
	closeRemoval = []

	# Decide and keep track which char in the input needs to be removed
	for index, element in enumerate(input):
		if element == '(':
			openRemoval.append( index )
		elif element == ')':
			if ( openRemoval ):
				del openRemoval[-1]
			else:
				closeRemoval.append( index )

	# Construct res
	res = ""
	openIndex = 0
	closeIndex = 0
	for index, element in enumerate(input) :
		if openIndex < len(openRemoval) :
			if index == openRemoval[openIndex]: # we remove
				openIndex += 1
				continue
		elif closeIndex < len(closeRemoval):
			if index == closeRemoval[closeIndex]:
				closeIndex += 1
				continue
		res.append( element )

	return res

