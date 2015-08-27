
LDFLAGS = -lprotobuf
CXXFLAGS = -g -Wall -std=c++11
OBJECTS = meminfo.pb.o
TARGETS = meminfo

all: $(TARGETS)

meminfo.pb.cc: meminfo.proto
	protoc --cpp_out=./ $^

meminfo: meminfo.cpp meminfo.h $(OBJECTS)
	g++ -o $@ $(CXXFLAGS) $(LDFLAGS) $^

clean:
	rm -f $(TARGETS) $(OBJECTS) meminfo.pb.*
