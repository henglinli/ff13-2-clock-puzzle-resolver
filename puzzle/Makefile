CXX = g++ #color-g++
CC  = gcc #color-gcc

#-----------------------------------------------
# Uncomment exactly one of the lines labelled (A), (B), and (C) below
# to switch between compilation modes.

# OPT ?= -Os -DNDEBUG -Wall      # (A) Production use (optimized mode)
 OPT ?= -O0 -g -Wall             # (B) Debug mode, w/ full line-level debugging symbols
# OPT ?= -O2 -g2 -DNDEBUG -Wall  # (C) Profiling mode: opt, but w/debugging symbols
#-----------------------------------------------
###################################
#defined by users
BOOST = $(HOME)/Downloads/src/boost_1_49_0
###################################
CFLAGS += $(OPT) -I$(BOOST)
CXXFLAGS += $(CFLAGS) -std=c++11

BIN = puzzle

all: $(BIN) 

test: puzzle
	./puzzle 1 1 4 2 2 4 1 2 4

.PTHONY: clean help
help: 
	echo "make for $(BIN) "
clean:
	$(RM) -f $(BIN)
	$(RM) -rf *~ a.out *.o *.dSYM
