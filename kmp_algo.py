#!/usr/bin/python
#-*-  coding:utf-8 -*-



class KmpAlgo (object):
	def __init__ (self, pattern):
		self.m_pattern = pattern
		self.m_piArr = list()
		return
		
	def SetNewPattern (self, pattern):
		self.m_pattern = pattern
		return
		
	def GetPattern (self):
		return self.m_pattern
		
	def __MakePiArr (self, pattern):
		return []
		
	def Search (self, text):
		return []



def main():
	text = 'If an argument x is passed, and x is not empty, the weak_ptr object becomes part of the owning group'
	pattern = 'weak'
	kmpObj = KmpAlgo (pattern)
	res = kmpObj.Search (text)
	if res:
		print ("Pattern: %s" % (pattern))
		for i, val in enumerate (res):
			print ("{0}: position - {1}".format (i, val - len(pattern) + 1))
	else:
		print ("Nothing have found")
		
	return 0



if __name__ == '__main__':
	main ()
else:
	print "Importing like a module: {0}".format(__name__)
