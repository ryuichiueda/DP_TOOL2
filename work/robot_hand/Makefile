CXX = g++
CXXFLAGS = -Wall -O3 --static -std=c++11
LDFLAGS = -lm
SRCS = Action.cc  Arm.cc  Hand.cc  Part.cc  System.cc
OBJS := $(SRCS:.cc=.o)

all: calc_state_trans motion

calc_state_trans: $(OBJS) calc_state_trans.o
	$(CXX) -o $@ $(OBJS) calc_state_trans.o $(LDFLAGS)

motion: $(OBJS) motion.o
	$(CXX) -o $@ $(OBJS) motion.o $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJS) calc_state_trans.o motion.o
