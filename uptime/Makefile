
LDFLAGS = -lprotobuf
CXXFLAGS = -g -Wall -std=c++11
OBJECTS = uptime.pb.o
TARGETS = uptime

all: $(TARGETS)

uptime.pb.cc: uptime.proto
	protoc --cpp_out=./ $^

uptime: uptime.cpp uptime.h $(OBJECTS)
	g++ -o $@ $(CXXFLAGS) $(LDFLAGS) $^

clean:
	rm -f $(TARGETS) $(OBJECTS) uptime.pb.*
