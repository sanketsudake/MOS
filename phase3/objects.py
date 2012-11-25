#!/usr/bin/env python
from collections import deque
import os
import random

def getrandom():
	return random.randint(0,30)


class Card(object):
	"""
	Card: Manages all Reading from input file
	@infile = input file ptr
	"""

	def __init__(self, inputfile = 'input.txt'):
		assert(os.path.exists(inputfile))
		self.infile = open(inputfile,'r')

	def read(self):
		return self.infile.readline()

	def __del__(self):
		self.infile.close()

class LinePrinter(object):
	"""
	LinePrinter: Manages all lineprinting for output file
	@outfile = output file ptr
	"""
	
	def __init__(self, outputfile = 'output.txt'):
		self.outfile = open(outputfile, 'w')

	def write(self, line = ''):
		#assert(line) 
		self.outfile.write(line + '\n')

	def jobend(self):
		self.outfile.write('\n\n')

	def __del__(self):
		self.outfile.close()	

class Cpu(object):
	"""
	Cpu: Core of mos for execution
	@SI = SI interrupt
	@PI = PI interrupt
	@TI = TI interrupt
	@IR = Instruction register
	@R =  Cpu register
	@C = Toggle flag
	@MODE = OS Mode
	"""
	
	def __init__(self):
		self.SI = 3
		self.PI = 0
		self.TI = 0
		self.IR = ('','','','')
		self.R = ('','','','')
		self.C = True #True or false0
		self.MODE = 'slave' #master or slave
		self.loadq = deque()
		self.readyq = deque()
		self.termq = deque()

	def curr_ir(self):
		return self.IR[0] + self.IR[1] + self.IR[2] + self.IR[3]

	def curr_reg(self):
		return self.R[0] + self.R[1] + self.R[2] + self.R[3]

	def change_mode(self):
		if self.mode =='slave':
			self.mode = 'master'
		else:
			self.mode == 'slave'

class Pblock(object):
	"""
	Pblock: Process block for each Process
	@PTR = Page Table Register 
	@IC = Instruction Counter
	@TTL = Total Time Limit
	@TLL = Total Line Limit
	@TTC = Total Time Counter
	@TLC = Total Line Counter
	@TSC = Time Slice Counter
	"""
	
	def __init__(self, line):
		assert len(line)>=16
		self.JID = int(line[4:8])	
		self.TTL = int(line[8:12])
		self.TLL = int(line[12:16])	
		self.PTR = 0
		self.IC = 0
		self.TTC = 0
		self.TLC = 0
		self.TSC = 0 
		self.randlist = deque()
		self.output = deque()

	def __str__(self):
		final = "JID:{0} TTL:{1} TLL {2}".format(self.JID, self.TTL, self.TLL)
		return final

class BufferQueue(object):
	"""
	BufferQueue: all buffer queue goes here
	@ebq = Empty buffer queue
	@ifbq = Inputful buffer queue
	@ofbq = Outputful buffer queue
	"""
	def __init__(self):
		self.buffno = -1
		self.ebq = deque()
		self.ifbq = deque()
		self.ofbq = deque()

	def get_buffer(self):
		"""
		get_buffer : returns first empty buffer 
			from ebq ; if not present generates it
		"""
		if len(self.ebq) == 0:
			self.buffno = self.buffno + 1
			return self.buffno
		else:
			temp = self.ebq.popleft()
			assert temp>=0
			return temp

	def add_ebq(self,buff_no):
		if (self.ebq.count(buff_no) or self.ifbq.count(buff_no) or self.ofbq.count(buff_no)) != 0:
			print "add_ebq: Error"
			assert False 
		self.ebq.append(buff_no)
		return 0

		
	def add_ifbq(self,buff_no):
		if (self.ebq.count(buff_no) or self.ifbq.count(buff_no) or self.ofbq.count(buff_no)) != 0:
			print "add_ifbq: Error"
			assert False
		self.ifbq.append(buff_no)
		return 0

	def add_ofbq(self,buff_no):
		if (self.ebq.count(buff_no) or self.ifbq.count(buff_no) or self.ofbq.count(buff_no)) != 0:
			print "add_ofbq: Error"
			assert False
		self.ofbq.append(buff_no)
		return 0

	def print_curr(self, options=[]):
		if options.count('ebq'):
			print "EBQ => ",self.ebq
		if options.count('ifbq'):
			print "IFBQ => ",self.ifbq
		if options.count('ofbq'):
			print "OFBQ => ",self.ofbq


class Memory(object):
	"""
	Memory: Whole memory block for operating system
	@super_mem = Supervisor Memory
	@drum = Drum Memory
	@main_mem = Main Memory 	
	"""
	def __init__(self):
		self.super_mem = dict()
		self.drum = dict()
		self.main_mem = dict()
		self.dtrack = deque()

	def super_mem_add(self, buff_no, line):
		self.super_mem[buff_no] = line

	def drum_add(self, buff_no):
		num = getrandom()
		if num in self.dtrack:
			while num in self.dtrack:
				num = getrandom()
		self.drum[num] = self.super_mem[buff_no]
		self.dtrack.append(num)

	def main_mem_add(self, buff_no, line):
		self.main_mem[buff_no] = line

	def  print_curr(self, options=[]):
		if options.count('s'):
			print "Supervisor Memory"
			for key in self.super_mem:
				print str(key) + '\t' + str(self.super_mem[key])
		if options.count('d'):
			print "Drum Memory"
			for key in self.drum:
				print str(key) + '\t' + str(self.drum[key])
		if options.count('m'):
			print "Main Memory"
			for key, value in self.main_mem:
				print str(key) + '\t' + str(self.main_mem[key])