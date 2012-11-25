#!/usr/bin/env python
from mos import Mos
os = Mos()
flag = True
while flag:
	os.channel1()
	os.channel2()
	os.channel3()
	#os.bqueue.print_curr(['ifbq', 'ofbq', 'ebq'])
