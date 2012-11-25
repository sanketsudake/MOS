#!/usr/bin/env python
from collections import deque
from objects import *
import os
import commands

def innitialize(osproj):
	pass

def quit(osproj):
	print "entered quit"
	#print osproj.memory.dtrack
	exit(0)


class Mos(object):
	"""
	Mos: My core operating system
	"""
	def __init__(self, inputfile = 'input.txt',outputfile = 'output.txt'):
		self.card = Card(inputfile)
		self.linep = LinePrinter(outputfile)
		self.cpu = Cpu()
		self.bqueue = BufferQueue()
		self.memory = Memory()
		self.flags = []
		innitialize(self)

	def channel1(self,ch1_time = 4):
		if 'channel1' in self.flags:
			#print 'channel1 done'
			return 0

		ch1_time = 4
		for i in range(ch1_time):
			curr_line = self.card.read()
			if curr_line == '':
				print 'End of file'
				self.flags.append('channel1')
				return 0
			buff_no = self.bqueue.get_buffer()
			#print buff_no
			self.bqueue.add_ifbq(buff_no)
			self.memory.super_mem_add(buff_no,curr_line)

	def channel2(self, ch2_time = 2):
		ch2_time = 2
		if 'channel2' in self.flags:
			print 'channel2 done'
			return 0 
		if 'channel1' in self.flags:
			if 'channel3' in self.flags:
				#print 'Both and channel2'
				if len(self.bqueue.ofbq) == 0:
					self.flags.append('channel2')
					os.remove('temp_input.txt')
					os.remove('temp_output.txt')
					exit(0)

		for i in range(ch2_time):
			if len(self.bqueue.ofbq) != 0:
				buff_no = self.bqueue.ofbq.popleft()
				assert self.memory.super_mem.has_key(buff_no)
				self.linep.write(self.memory.super_mem[buff_no])
				self.memory.super_mem[buff_no] = ''
				self.bqueue.add_ebq(buff_no)

		

	def channel3(self, o_lines =[]):
		ch3_time = 4
		if 'channel3' in self.flags:
			#print 'channel3 done'
			return 0
		if 'channel1' in self.flags:
			if len(self.bqueue.ifbq)==0:
				self.flags.append('channel3')
		for i in range(ch3_time):
			if len(self.bqueue.ifbq)!= 0:
				buff_no = self.bqueue.ifbq.popleft()
				assert self.memory.super_mem.has_key(buff_no)
				#self.memory.drum[buff_no] = self.memory.super_mem[buff_no]
				self.memory.drum_add(buff_no)
				if self.memory.super_mem[buff_no].startswith('$AMJ'):
					self.cpu.loadq.append(Pblock(self.memory.super_mem[buff_no]))

				if self.memory.super_mem[buff_no].startswith('$DTA'):
					pass

				if self.memory.super_mem[buff_no].startswith('$END'):
					temp = self.cpu.loadq.popleft()
					self.load_in_main(temp)
					self.cpu.readyq.append(temp)
					self.execute()			
				self.memory.super_mem[buff_no] = ''
				self.bqueue.add_ebq(buff_no)

		for i in o_lines:
			buff_no = self.bqueue.get_buffer()
			self.memory.super_mem[buff_no] = i
			self.bqueue.add_ofbq(buff_no)

	def execute(self):
		fp = open('temp_input.txt','w')
		if len(self.cpu.readyq)>0:
			#print self.cpu.readyq[0]
			assert self.cpu.readyq[0]
			for i in self.cpu.readyq[0].randlist:
				#print i,self.memory.drum[i]
				fp.write(self.memory.drum[i])
			fp.close()
			fp =  open('temp_input.txt','r')
			text = fp.read()
			if len(text.split('\n')) <= 1:
				print "Buzigga"
				exit(0)

			fp.close()
			outtext = commands.getoutput('./mos')
			if os.path.exists('temp_output.txt'):
				outtext = commands.getoutput('cat temp_output.txt')
			for i in outtext.split('\n'):
				self.cpu.readyq[0].output.append(i)
			self.cpu.termq.append(self.cpu.readyq.popleft())

		#assert len(self.cpu.readyq) + len(self.cpu.loadq) + len(self.cpu.termq)
		if len(self.cpu.termq)>0:
			assert self.cpu.termq[0].output
			#print self.cpu.termq[0].output
			while len(self.cpu.termq[0].output) != 0:
				buff_no = self.bqueue.get_buffer()
				line = self.cpu.termq[0].output.popleft()
				self.memory.super_mem_add(buff_no, line)
				self.bqueue.add_ofbq(buff_no)
			print self.cpu.termq.popleft()



	def load_in_main(self, temp):
		while len(self.memory.dtrack)>0:
			temp.randlist.append(self.memory.dtrack.popleft())

		

	def services(self, options = []):
		pass
		

