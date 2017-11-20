import operator
import sys

temp = None
res = ""

class Tree(object):
	def __init__(self, value = None, parent = None):
		self.value = value
		self.rchild = None
		self.lchild = None
		self.parent = parent
		self.label = None


	def add(self, root, first, second):
		node = self.find(root, first)
		if node == None:
			root.value = first
			root.lchild = Tree(second, root)

		else:
			if node.lchild == None:
				node.lchild = Tree(second, node)
			else:
				if node.lchild.value > second:
					dummy = node.lchild
					node.lchild = Tree(second, node)
					node.rchild = dummy
				else:
					node.rchild = Tree(second, node)




	def find(self, node, first):
		global temp
		if node.value == first:
			#print "found ",node.parent.value
			temp = node
			return temp
		else:
			if node.lchild !=None:
				self.find(node.lchild, first)
			if node.rchild !=None:
				self.find(node.rchild, first)

			return temp

	def _print(self, node):
		global res

		if node.lchild != None:
			self._print( node.lchild )
		if node.rchild != None:
			self._print( node.rchild )
		
		if node.lchild !=None or node.rchild != None:
			lval = ""
			rval = ""
			if node.lchild != None:
				lval = "(" + node.lchild.label + ")"
			if node.rchild != None:
				rval = "(" + node.rchild.label + ")"
			res =  node.value + lval + rval
			node.label = res
		else:
			node.label = node.value

		return 0


def check_2g(input):
	for pair in input:
		counter = 0
		for pair2 in input:
			if pair[0] == pair2[0]:
				counter = counter+1
				if counter>2:
					return False
	return True

def check_dupl(input):
	for pair in input:
		counter = 0
		for pair2 in input:
			if pair == pair2:
				counter = counter+1
				if counter>1:
					return False
	return True

def check_cycle(input):
	for pair in input:
		counter = 0
		for pair2 in input:
			if pair[1] in pair2[1]: 
				counter=counter+1
				if counter > 1:
					return True

def check_mroot(input):
	count =0
	ll=[]
	for pair in input:
		flag = True
		if pair[0] in ll:
			continue
		ll.append(pair[0])
		for pair2 in input: 
			if pair[0] == pair2[1]: 
				flag = False
				break
		if flag == True:
			count = count+1
	
	if count>1:
		return True
	else:
		return False

def check_other(input):
	for pair in input:
		if pair[0] == pair[1]:
			return True


if __name__ == "__main__":
	with open("output.txt", "w") as file:
		input = [ ["B", "D"],["D","E"],["A","B"],["C","F"],["E","G"],["A","C"] ]
		input = sorted( input, key = operator.itemgetter(0) )

		if check_2g(input) == False:
			print "E1"
			file.write("E1")
		elif check_dupl(input) == False:
			print "E2"
			file.write("E2")
		elif check_cycle(input) == True:
			print "E3"
			file.write("E3")
		elif check_mroot(input) == True:
			print "E4"
			file.write("E4")
		elif check_other(input) == True:
			print "E5"
			file.write("E5")

		else:
			root = Tree()
			for pair in input:
				root.add(root, pair[0], pair[1])

			root._print(root)
			result = "(" + root.label + ")"
			print result
			file.write(result)




