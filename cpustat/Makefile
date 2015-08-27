
LDFLAGS = -lprotobuf
CXXFLAGS = -g -Wall -std=c++11
OBJECTS = cpustat.pb.o
TARGETS = cpustat

all: $(TARGETS)

cpustat.pb.cc: cpustat.proto
	protoc --cpp_out=./ $^

cpustat: cpustat.cpp cpustat.h $(OBJECTS)
	g++ -o $@ $(CXXFLAGS) $(LDFLAGS) $^

clean:
	rm -f $(TARGETS) $(OBJECTS) cpustat.pb.*
