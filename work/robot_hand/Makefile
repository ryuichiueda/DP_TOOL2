CXX = g++
CXXFLAGS = -Wall -O3 --static -std=c++11
LDFLAGS = -lm
SRCS = Action.cc  Arm.cc  Hand.cc  Part.cc  System.cc ParticleFilter.cc
OBJS := $(SRCS:.cc=.o)

all: calc_state_trans pos_known_motion pfc_motion

pfc_motion: $(OBJS) pfc_motion.o
	$(CXX) -o $@ $(OBJS) pfc_motion.o $(LDFLAGS)

calc_state_trans: $(OBJS) calc_state_trans.o
	$(CXX) -o $@ $(OBJS) calc_state_trans.o $(LDFLAGS)

pos_known_motion: $(OBJS) pos_known_motion.o
	$(CXX) -o $@ $(OBJS) pos_known_motion.o $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJS) calc_state_trans.o pos_known_motion.o pfc_motion.o
