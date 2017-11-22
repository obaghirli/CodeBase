
# This algorithm uses bisection search
# Therefore it has complexisty of O( lon(n) )
# Which is suitable for the huge datasets as it is assumed by this problem

# this function finds the rotation point, if it exists
# if it does not, then returns -1
# Note: indexing starts from zero
def findRotation(arr, left, right):

	# if the array is empty, return -1,
	# if there is only one element in the array, then return that as a rotation point
	if left > right:
		return -1
	elif left == right:
		return left

	# bisection search starts here
	# recursion is a bad idea here,
	# because recursion depth can be exceeded
	# Therefore, I used the while loop
	while (left < right):

		mid = (left + right)/2
		# case: if middle index is the R(rotation) point, we need to catch it here first
		# otherwise, the rest of the algorithm would miss it
		# for that, we first check if mid > 0, so that we can check arr[mid-1]
		if mid > 0 and arr[mid] < arr[mid-1]:
			return mid

		# here, we change the course of the algorithm such that,
		# mid is the index right before the rotation index. This is 
		# required for the case where rotation point is at the index 1
		elif arr[mid]>arr[mid+1]:
			return mid+1
		# we decide the direction of the new search: left or right subarray,
		# based on relation between mid and left elements
		# then update the endpoints properly, and get back to the loop
		elif arr[mid] < arr[left]:
			right = mid -1
		elif arr[mid] > arr[left]:
			left = mid + 1
		# if any of the subarrays was shrinked to size 2 when entering the while loop,
		# and did not meet any of the conditions above, then there is no rotation point
		# and we return -1
		elif left == mid:
			return -1



if __name__ == "__main__":

	#the array is defined here
	arr=[  
		    "ptolemaic",
		    "retrograde",
		    "supplant",
		    "undulate",
		    "xenoepist",
		    "asymptote", #rotation point here
		    "babka",
		    "banoffee",
		    "engender",
		    "karpatka",
		    "othellolagkage",
		]

	# calling the function responsible for finding the rotation index
	# 1st argument: array itself
	# 2nd argument: left index of the array
	# 3rd argument: right index of the array 
	print findRotation(arr, 0, len(arr)-1 )