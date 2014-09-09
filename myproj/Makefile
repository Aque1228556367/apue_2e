# Common make definitions, customized for each platform

# Definitions required in all program directories to compile and link
# C programs using gcc.

WKDIR=~/apue_2e_svn/apue_2e/trunk/src
SRC=./fig
CC		= gcc
CXX		= g++
LEX		= flex
YACC     	= yacc
CFLAGS   	= -DLINUX -g -ansi -Wall -D_GNU_SOURCE $(EXTRA)
CXXFLAGS 	= -g   -pipe -Werror -DENCODING_UTF8 -DCHARSET_SHOW_GBK


####### third party objects, that may be not need -g to make .o much smaller 
CXXFLAGS_3RD = 
INCPATH  	= -I$(WKDIR)/include -I/usr/inlclude 	
LINK     	= g++
LIBAPUE		= $(WKDIR)/lib/libapue.a

LIBS_REALEASE	= -L./$(WKDIR)/lib -lapue
LIBS_DEBUG		= -L./$(WKDIR)/lib -lapueD

####### Files
OBJECTS	 = ./debug/fig1.3.o
TARGET   = ./bin/test

./debug/fig1.3.o : $(SRC)/fig1.3.c
	$(CXX) -c  $(CXXFLAGS) $(INCPATH) -o $@ $<
	

####### Build rules
echo:
	echo hello

all:  $(TARGET)
	
$(TARGET): $(OBJECTS) ${LIBAPUE}
	$(LINK) -o $(TARGET)  $(OBJECTS) $(LIBS_REALEASE)

clean:
	rm -rfv *~ core *.core
	rm -rfv ./debug/*.o
	rm -rfv $(TARGET)

# http://blog.csdn.net/mtawaken/article/details/7416332
# 只编译不链接
# g++ -c ./debug/fig1.3.o ./fig/fig1.3.c -I/home/qqsprite/apue_2e_svn/apue_2e/trunk/src/include/ -I/usr/inlclude
# 由 .o 和静态库直接链接成二进制文件
# (1) g++ -g -o bin/test ./debug/fig1.3.o ../src/lib/libapue.a -I/usr/inlclude
# (2) g++ -g -o ./bin/test ./debug/fig1.3.o -L../src/lib -lapue

# g++ -g -o ./bin/test ./debug/fig1.3.o ../src/lib/libapue.a -I ~/apue_2e_svn/apue_2e/trunk/src/include/
# g++ -g -o bin/test debug/fig1.3.o libapue.a
# g++ -g -L~/apue_2e_svn/apue_2e/trunk/src/lib -lapue -o bin/test debug/fig1.3.o ../src/lib/libapue.a -I ~/apue_2e_svn/apue_2e/trunk/src/include/