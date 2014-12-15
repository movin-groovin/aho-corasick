#!/usr/bin/python
#-*- coding:utf-8 -*-



def SimpleCompute (strDec):
	summ = 0
	mul = 10 ** (len(strDec) - 1)
	
	for i in xrange (len(strDec)):
		summ += int(strDec[i]) * mul
		mul /= 10
	
	return summ

def GornerRule (strDec):
	summ = 0
	mul = 10
	
	summ = int(strDec[0])
	for i in xrange(1, len(strDec)):
		summ = summ * mul + int(strDec[i])
	
	return summ

def main():
	strr = '125423123163467'
	print ("Simple: {}, Gorner: {}".format (SimpleCompute(strr), GornerRule(strr)))



main()
