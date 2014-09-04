# Common make definitions, customized for each platform

# Definitions required in all program directories to compile and link
# C programs using gcc.

WKDIR=~/apue_2e_svn/apue_2e/trunk/src
CC		= gcc
CXX		= g++
LEX		= flex
YACC     	= yacc
CFLAGS   	= -DLINUX -g -ansi -Wall -D_GNU_SOURCE $(EXTRA)
CXXFLAGS 	= -g   -pipe -Werror -DENCODING_UTF8 -DCHARSET_SHOW_GBK


####### third party objects, that may be not need -g to make .o much smaller 
CXXFLAGS_3RD = 
INCPATH  	= -I$(WKDIR)/include	
LINK     	= g++
LIBAPUE		= $(WKDIR)libapue.a

LIBS_REALEASE	= -L./$(WKDIR)/lib -lapue
LIBS_DEBUG		= -L./$(WKDIR)/lib -lapueD

####### Files
OBJECTS	 = ./debug/fig1.3.o
TARGET   = ./bin/test

./debug/fig1.3.o : $(WKDIR)/fig1.3.c
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


