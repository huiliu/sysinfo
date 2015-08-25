
LDFLAGS = -lprotobuf
CXXFLAGS = -g -std=c++11 -Wall
OBJECTS = diskio.pb.o
TARGETS = disk_status diskstats

all: $(TARGETS)

diskstats: diskstats.cpp diskio.pb.o

diskio.pb.cc: diskio.proto
	protoc --cpp_out=./ $^

clean:
	rm -f $(TARGETS) $(OBJECTS) diskio.pb.*

.PHONY: all clean
