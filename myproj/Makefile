# Common make definitions, customized for each platform

# Definitions required in all program directories to compile and link
# C programs using gcc.

# 注意这里home路径不能用“~”
WKDIR=/home/qqsprite/apue_2e_svn/apue_2e/trunk/src
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

LIBS_REALEASE	=-L$(WKDIR)/lib -lapue
LIBS_DEBUG		=-L$(WKDIR)/lib -lapueD

####### Files
OBJECTS	 = ./debug/fig1.3.o
TARGET   = ./bin/test

# makefile 的首个目标视为默认目标，即只输入make就可执行的目标
all:  $(TARGET)
	echo "all"

./debug/fig1.3.o : $(SRC)/fig1.3.c
	$(CXX) -c  $(CXXFLAGS) $(INCPATH) -o $@ $< 
	
$(TARGET): $(OBJECTS)
	$(LINK) -o $(TARGET) $(OBJECTS) $(LIBS_REALEASE)

link:
	$(LINK) -o $(TARGET) $(OBJECTS) $(LIBS_REALEASE)
	
# g++ -o ./bin/test ./debug/fig1.3.o -L/home/qqsprite/apue_2e_svn/apue_2e/trunk/src/lib -lapue
# g++ -o ./bin/test ./debug/fig1.3.o -L/home/qqsprite/apue_2e_svn/apue_2e/trunk/src/lib/libapue.a

clean:
	rm -rfv *~ core *.core
	rm -rfv ./debug/*.o
	rm -rfv $(TARGET)

# http://blog.csdn.net/mtawaken/article/details/7416332
# 只编译不链接，注意：如果要用 gdb 调试，-g 选项必须加在生成 .o 这步
# g++ -g -o ./debug/fig1.3.o -c ./fig/fig1.3.c -I/home/qqsprite/apue_2e_svn/apue_2e/trunk/src/include/ -I/usr/inlclude
# 下面两种方式都可由 .o 和静态库直接链接成二进制文件
# (1) g++ -o bin/test ./debug/fig1.3.o ../src/lib/libapue.a -I/usr/inlclude
# (2) g++ -o ./bin/test ./debug/fig1.3.o -L../src/lib -lapue -I/usr/inlclude