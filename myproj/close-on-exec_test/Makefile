# Common make definitions, customized for each platform

# Definitions required in all program directories to compile and link
# C programs using gcc.

# 注意这里home路径不能用“~”
WKDIR=
SRC=
CC		= gcc
CXX		= g++
LEX		= flex
YACC     	= yacc
CFLAGS   	= -DLINUX -g -ansi -Wall -D_GNU_SOURCE $(EXTRA)
CXXFLAGS 	= -g   -pipe -Werror -DENCODING_UTF8 -DCHARSET_SHOW_GBK


####### third party objects, that may be not need -g to make .o much smaller 
CXXFLAGS_3RD = 	
INCPATH	=
LINK     	= gcc

LIBS_REALEASE	=
LIBS_DEBUG		=

####### Files

OBJECTS =

TARGET=

# makefile 的首个目标视为默认目标，即只输入make就可执行的目标
all:	mkdir_debug	mkdir_bin	./bin/parent	./bin/child

mkdir_debug:	
	[ -d debug ] || mkdir -p debug

mkdir_bin:
	[ -d bin ] || mkdir -p bin


# object files
./debug/parent.o : parent.c
	$(CC) -c  $(CXXFLAGS) $(INCPATH) -o $@ $< 
./debug/child.o : child.c
	$(CC) -c  $(CXXFLAGS) $(INCPATH) -o $@ $< 

# execute files
./bin/parent: ./debug/parent.o
	$(LINK) -o $@ $<
#	$(LINK) -o ./bin/parent ./debug/parent.o
	
./bin/child: ./debug/child.o
	$(LINK) -o $@ $<
#	$(LINK) -o ./bin/child ./debug/child.o


clean:
	rm -rfv *~ core *.core
	rm -rfv ./debug/
	rm -rfv ./bin/
