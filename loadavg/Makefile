
LDFLAGS +=  -lprotobuf $(OBJECTS)
CXXFLAGS = -g -Wall -std=c++11
OBJECTS = loadavg.pb.o
TARGETS = loadavg

all: $(OBJECTS) $(TARGETS)

loadavg.pb.cc: loadavg.proto
	protoc --cpp_out=./ $^

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGETS) loadavg.pb.*
