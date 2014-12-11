#!/usr/bin/python
#-*- coding:utf8 -*-


import sys
import os
import random
import time



class RandStrings (object):
	def __init__ (
		self,
		seedVal,
		startChar = 0x20,
		endChar = 0x7E   # printable ascii characters
	):
		random.seed(seedVal)
		self.startChar = startChar
		self.endChar = endChar
		return
		
	def MakeString (self, strLen):
		resData = []
		
		while strLen > 1:
			resData.append(chr(random.randint (self.startChar, self.endChar)))
			strLen -= 1
		resData.append('\n')
		
		return ''.join(resData)


def WriteStringToFile(
	fileName,
	strNum,
	listOfStr,
	startPos = 1024*1024*100,
	deltaPos = 1024 * 1024
):
	totalPos = 0
	
	try:
		fOut = file (fileName, 'w')
		while strNum > 0:
			#
			# writing 
			#
			strNum -= 1
		fOut.close()
	except EEE as Exc:
		print "Have happened an exception: ", Exc
		return False
	
	return True


def main():
	strLen = 1025
	strNum = 1024 * 1024
	fileName = 'ascii_1gb.txt'
	if (len (sys.argv) < 2):
		print "Enter one or more strings"
		return 10001
	
	genStr = RandStrings(int ((time.time() % 1) * 1000))
	outStr = genStr.MakeString(strLen)
	#WriteStringToFile (fileName, strNum)
	print outStr
	
	return 0



if __name__ == '__main__':
	main()
else:
	raise RuntimeError ("Can't run like a module")
