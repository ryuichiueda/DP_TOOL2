CXX = g++
CXXFLAGS = -Wall -O3 --static -std=c++11
LDFLAGS = -lm
SRCS := $(wildcard *.cc)
OBJS := $(SRCS:.cc=.o)

value_iteration: $(OBJS)
	$(CXX) -o $@ $(OBJS) 

clean:
	rm -f $(TARGET) $(OBJS)
