CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
LDFLAGS = -lpcap
TARGET = airodump
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = main.h radioheader.h beaconheader.h wirelessheader.h

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJS): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $(SRCS)

run:
	sudo ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

