#include "meminfo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

static const char* PROC_MEMINFO = "/proc/meminfo";

void load(MemInfo& data)
{
    data.Clear();

    std::string line, tag;
    uint64_t val;
    std::ifstream ifs(PROC_MEMINFO);

    while(std::getline(ifs, line)) {
        std::istringstream iss(line);
        iss >> tag;
        if (0 == tag.compare(c_mem_total)) {
            iss >> val;
            data.set_mem_total(val);
        }
        else if (0 == tag.compare(c_mem_free)) {
            iss >> val;
            data.set_mem_free(val);
        }
        else if (0 == tag.compare(c_mem_buffers)) {
            iss >> val;
            data.set_mem_buffers(val);
        }
        else if (0 == tag.compare(c_mem_cached)) {
            iss >> val;
            data.set_mem_cached(val);
        }
        else if (0 == tag.compare(c_swap_cached)) {
            iss >> val;
            data.set_swap_cached(val);
        }
        else if (0 == tag.compare(c_swap_total)) {
            iss >> val;
            data.set_swap_total(val);
        }
        else if (0 == tag.compare(c_swap_free)) {
            iss >> val;
            data.set_swap_free(val);
        }
        else if (0 == tag.compare(c_hight_mem_total)) {
            iss >> val;
            data.set_hight_mem_total(val);
        }
        else if (0 == tag.compare(c_hight_mem_free)) {
            iss >> val;
            data.set_hight_mem_free(val);
        }
        else if (0 == tag.compare(c_low_mem_total)) {
            iss >> val;
            data.set_low_mem_total(val);
        }
        else if (0 == tag.compare(c_low_mem_free)) {
            iss >> val;
            data.set_low_mem_free(val);
        }
    }
}

void print(const MemInfo& data)
{
    std::cout << data.mem_total() << "\t"
              << data.mem_free() << "\t"
              << data.mem_buffers() << "\t"
              << data.mem_cached() << "\t"
              << data.swap_cached() << "\t"
              << data.swap_total() << "\t"
              << data.swap_free() << "\t"
              << data.hight_mem_total() << "\t"
              << data.hight_mem_free() << "\t"
              << data.low_mem_total() << "\t"
              << data.low_mem_free() << "\t"
              << std::endl;
}

int main(int argc, char *argv[])
{
    MemInfo mem;
    load(mem);

    print(mem);
    return 0;
}
