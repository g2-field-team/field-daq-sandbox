#####################################################################
#
#  Name:         Makefile
#  Created by:   Matthias Smith
#
#  Contents:     Makefile for MIDAS NMR frontends, based on
#		 a sample Makefile written by Stefan Ritt.
#
#####################################################################

OBJECTS = $(patsubst obj/%.cxx, build/%.o, $(wildcard obj/*.cxx))
TARGETS = $(patsubst src/%.cxx,bin/%,$(wildcard src/*.cxx))

#-------------------------------------------------------------------
# This is for Linux
CPPFLAGS = -fpermissive -O2
CXXFLAGS = -std=c++0x

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)

#-------------------------------------------------------------------
# The following lines define direcories. Adjust if necessary
MID_INC = $(MIDASSYS)/include
MID_LIB = $(MIDASSYS)/linux/lib

# Libraries && include flags
LIBS += -L$(MID_LIB) -Lcore/lib -L/usr/lib64/mysql
LIBS += -lmidas-shared  -lmysqlclient -lsqlite3
LIBS += -lboost_system -lboost_filesystem
LIBS += -lm -lz -lpthread -lodbc
CPPFLAGS += -I$(MID_INC) -Icore/include -Iobj -Iinclude
CPPFLAGS += -I/usr/local/include/labdaq
CPPFLAGS += -Wl,-rpath,/usr/local/lib

# Set compilers
CC = gcc
CXX = g++

#-------------------------------------------------------------------
# Finally we have the actual make directives.

# Make commands

all: $(OBJECTS) $(TARGETS)

build/%.o: obj/%.cxx obj/%.hh
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(ROOTFLAGS) -c $< -o $@

bin/%: src/%.cxx $(MID_LIB)/mfe.o $(OBJECTS)
	$(CXX) -o $@ $+ $(CPPFLAGS) $(CXXFLAGS) $(ROOTFLAGS) \
	$(LIBS) $(ROOTLIBS)

clean:
	rm -f *~ $(TARGETS) $(OBJECTS)