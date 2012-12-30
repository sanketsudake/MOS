
- This is my Operating System Course Project. 
- A Virtual Implemention of routines of OS.
- Project consited of three phases. Phase3 is final phase for project.
- Works for any no. of jobs. Supports input spooling, output spooling,
  paging.
- First two phases consist of only C code.Phase 3 consist of python wrapper
  over original code.

* MOS(Multiprogramming Operating System)
- Used for execution of multiple jobs
- Job should be defined ,well structured.
- System Will Report Error ,For Wrong Jobs With Proper Error Messages.
- Series of Jobs should be kept in input.txt.
- Afer processing of jobs output can be seen output.txt
- Random memory allocation for program card used using paging.

* Job can consist of Instruction
- GD-Get Data
- PD-Print Data
- LR-Load Register From Memory
- SR-Store Register From Memory
- CR-Compare Register And Memory
- BT-Branch Toggle(Checks Toggle Variable)
- H- Denotes end of job.
- Job should start with $AMJ
- There is $DTA after declaration of program cards
  and before data cards
- Job should end with $END


* Tools used
- Gcc compiler
- Emacs
- Gdb
- Gprof,Gcov,Cscope
- Python

* Using...
- git clone https://github.com/tripples/MOS.git
- cd MOS/`your desired phase`
- make
- ./mos
- cat output.txt
- Edit input.txt for more fun.
