# Common make definitions, customized for each platform

# Definitions required in all program directories to compile and link
# C programs using gcc.

WKDIR=~/apue_2e_svn/apue_2e/trunk/src

LDDIR=-L../lib
LDLIBS=../lib/libapue.a $(EXTRALIBS)


# Our library that almost every program needs.
LIB=../libapueD.a



####### Compiler, tools and options
COMMONPATH	= ../../common# common file include path
CC		= gcc
CXX		= g++
LEX		= flex
YACC     	= yacc
CFLAGS   	= -DLINUX -g -ansi -Wall -D_GNU_SOURCE $(EXTRA)
CXXFLAGS 	= -g   -pipe -Werror  -D_ANTIBOT_ -DENCODING_UTF8 -DCHARSET_SHOW_GBK \
			-DUSE_LOG4CPP -DGAMESERVER -DUSE_SHM -DLINUX -DUSE_SK_ASSERT  \
			-DWEST_SERVER -D_USE_MESSAGE_BUFF_  -D_USE_TIMER_ -DNDEBUG   -DUSE_COREDUMPER \
			 -Winvalid-pch -DDEBUG_NEW_NO_NEW_REDEFINITION   -DUSE_PERF_FUN \
			-DLEAK_CHK_DEBUG_NEW  -DMEMPOOL -D_DEBUG_ -D_GATE_CTRL_CORPS_ # -D_FB_


####### third party objects, that may be not need -g to make .o much smaller 
CXXFLAGS_3RD = 

LEXFLAGS 	= 
YACCFLAGS	= -d
INCPATH  	= -I$(WKDIR)/include
			
LINK     	= g++
LFLAGS   	= 
LIBS     	= 



LIBS_BASE	= -lpthread -L/usr/local/gcc-4.3.3/lib -L./$(COMMONPATH)/log4cpp/lib -llog4cpp \
                        -L./$(COMMONPATH)/lua/ -llua -L./$(COMMONPATH)/protobuf/lib -lprotobuf \
                        -L./$(COMMONPATH)/coredumper/lib -lcoredumper -rdynamic -L./bin/lib -ldl \
			-L./$(COMMONPATH)/lib -lgson -lmemcached

LIBS_REALEASE	= -L./$(COMMONPATH)/lib -lgamecommon  -lmsg

LIBS_DEBUG	= -L./$(COMMONPATH)/lib -lgamecommonD  -lmsg

DEL_FILE 	= rm -f
PCH_X_H = inc/stdafx.hpp
PCH_X = inc/stdafx.hpp.gch

####### Files

OBJECTS	 = ./debug/main.o 
	

TARGET   	= ./bin/sceneserver

MSG_OBJS = ./debug/message_pb.hxx.pb.o 
 

_LOGIC_OBJECTS_ = ./debug/taskmodule.o ./debug/taskmanager.o



SCENE_OBJS = $(OBJECTS) $(_LOGIC_OBJECTS_)  $(ANTIBOT_OBJS)

#_TARGET_OBJECTS_= $(foreach OBJECT, $(_LOGIC_OBJECTS_), ../logic/src/$(OBJECT).o )
#_SRC_OBJECTS_	= $(foreach OBJECT, $(_LOGIC_OBJECTS_), ../logic/src/$(OBJECT).cpp )
LIBCOMMON=
MSG_LIB = ${COMMONPATH}/lib/libmsg.a
debug:LIBS=${LIBS_DEBUG} ${LIBS_BASE} 
debug:LIBCOMMON=libgamecommonD.a
debug: all 
realease:LIBS= ${LIBS_REALEASE} ${LIBS_BASE}
realease:LIBCOMMON=libgamecommon.a
realease: all
msglib: ${MSG_LIB}
${MSG_LIB} : ${MSG_OBJS}
	ar r  $@ $?
####### Compile



./debug/playerinfo_yqs.o : src/playerinfo_yqs.cpp
	$(CXX) -c  $(CXXFLAGS) $(INCPATH) -o $@ $<

####### Build rules
echo:
	echo hello

all:  $(TARGET)
#	cp $(TARGET) ../scene/bin/
#	cp $(TARGET) ../fb/bin/
	
$(TARGET): $(SCENE_OBJS) ${LIBCOMMON}
	$(LINK) $(LFLAGS) -o $(TARGET)  $(SCENE_OBJS) $(LIBS)

$(SCENE_OBJS): $(PCH_X)

$(PCH_X): $(PCH_X_H)
	$(CXX) $(CXXFLAGS) $(INCPATH) -x c++-header $> $^


install:all
	cp $(TARGET) $(TRITON_BIN)

clean:
	-$(DEL_FILE)  
	-$(DEL_FILE) *~ core *.core
	rm -f ./debug/*.o
	rm -f ../logic/src/*.o
	rm -f $(TARGET)
	rm -f $(PCH_X)
#	touch $(TRITON_HOME)/


