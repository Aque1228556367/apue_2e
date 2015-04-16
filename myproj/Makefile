# Common make definitions, customized for each platform

# Definitions required in all program directories to compile and link
# C programs using gcc.

# 注意这里home路径不能用“~”
WKDIR=/home/sunrise/apue_2e_svn/apue_2e/trunk/src
SRC=./fig
CC		= gcc
CXX		= g++
LEX		= flex
YACC     	= yacc
#CFLAGS   	= -DLINUX -g -ansi -Wall -D_GNU_SOURCE $(EXTRA)
CFLAGS   	= -DLINUX -g -ansi -D_GNU_SOURCE -std=c99
#CXXFLAGS 	= -g   -pipe -Werror -DENCODING_UTF8 -DCHARSET_SHOW_GBK
CXXFLAGS 	= -g   -pipe -DENCODING_UTF8 -DCHARSET_SHOW_GBK


####### third party objects, that may be not need -g to make .o much smaller 
CXXFLAGS_3RD = 
INCPATH  	= -I$(WKDIR)/include -I$(SRC) -I/usr/inlclude 	
LINK     	= gcc
LIBAPUE		= $(WKDIR)/lib/libapue.a

LIBS_REALEASE	=-L$(WKDIR)/lib -lapue
LIBS_DEBUG		=-L$(WKDIR)/lib -lapueD

FIG_NAME	=	fig15.17

####### Files
OBJECTS	 = ./debug/$(FIG_NAME).o

# fig4.22 需要 fig2.15 支撑，注意 myerr.h 重复包含的问题
ifeq ($(FIG_NAME),fig4.22)
OBJECTS += ./debug/fig2.15.o
endif

# fig7.13 增加编译优化选项后的输出结果
ifeq ($(FIG_NAME),fig7.13)
CXXFLAGS += -O
CFLAGS += -O
endif

# fig10.9 需要 fig10.8 支撑，注意 myerr.h 重复包含的问题
ifeq ($(FIG_NAME),fig10.9)
OBJECTS += ./debug/fig10.8.o
endif

# fig13.7 需要 fig13.1, fig13.6, fig14.9 支撑，注意 myerr.h 重复包含的问题
ifeq ($(FIG_NAME),fig13.7)
LIBS_REALEASE += -lpthread
LIBS_DEBUG += -lpthread
OBJECTS += ./debug/fig13.1.o
OBJECTS += ./debug/fig13.6.o
OBJECTS += ./debug/fig14.9.o
endif

# fig15.18 需要 fig15.17 作为其子进程执行 "add2" 的过滤程序
ifeq ($(FIG_NAME),fig15.17)
TARGET   = ./bin/add2
else ifeq ($(FIG_NAME),fig15.19)
# fig15.18 需要 fig15.19 作为其子进程执行 "add3" 的过滤程序
TARGET   = ./bin/add3
else
TARGET   = ./bin/test
endif

# makefile 的首个目标视为默认目标，即只输入make就可执行的目标
all:  $(TARGET)
	echo "all"

./debug/$(FIG_NAME).o : $(SRC)/$(FIG_NAME).c
	$(CC) -c  $(CFLAGS) $(INCPATH) -o $@ $< 

ifeq ($(FIG_NAME),fig4.22)
./debug/fig2.15.o :  $(SRC)/fig2.15.c
	$(CC) -c  $(CFLAGS) $(INCPATH) -o $@ $< 
endif

ifeq ($(FIG_NAME),fig10.9)
./debug/fig10.8.o :  $(SRC)/fig10.8.c
	$(CC) -c  $(CFLAGS) $(INCPATH) -o $@ $< 
endif

ifeq ($(FIG_NAME),fig13.7)
./debug/fig13.1.o :  $(SRC)/fig13.1.c
	$(CC) -c  $(CFLAGS) $(INCPATH) -o $@ $< 
./debug/fig13.6.o :  $(SRC)/fig13.6.c
	$(CC) -c  $(CFLAGS) $(INCPATH) -o $@ $< 
./debug/fig14.9.o :  $(SRC)/fig14.9.c
	$(CC) -c  $(CFLAGS) $(INCPATH) -o $@ $< 
endif
	
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
