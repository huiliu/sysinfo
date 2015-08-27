#include "cpustat.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>

static const char* PROC_STAT = "/proc/stat";
static const char* TAG = "cpu";

void Load(CpuStat& data)
{
    data.Clear();

    std::ifstream ifs(PROC_STAT);
    std::string line;
    std::string tag;
    uint64_t val;

    while(std::getline(ifs, line)) {
        if (0 != line.compare(0, 3, TAG)) {
            continue;
        }

        std::istringstream iss(line);
        CpuTime* pcputime = data.add_cpus();

        iss >> tag;
        pcputime->set_tag(tag);
        iss >> val;
        pcputime->set_user(val);
        iss >> val;
        pcputime->set_nice(val);
        iss >> val;
        pcputime->set_system(val);
        iss >> val;
        pcputime->set_idle(val);
        iss >> val;
        pcputime->set_iowait(val);
        iss >> val;
        pcputime->set_irq(val);
        iss >> val;
        pcputime->set_softirq(val);
        iss >> val;
        pcputime->set_steal(val);
        iss >> val;
        pcputime->set_guest(val);
        iss >> val;
        pcputime->set_guest_nice(val);
    }
}

void Print(const CpuStat& data)
{
    for (int i = 0; i < data.cpus_size(); ++i) {
        auto& item = data.cpus(i);
        std::cout << item.tag() << " " 
                  << item.user() << " " 
                  << item.nice() << " " 
                  << item.system() << " " 
                  << item.idle() << " " 
                  << item.iowait() << " " 
                  << item.irq() << " " 
                  << item.softirq() << " " 
                  << item.steal() << " " 
                  << item.guest() << " " 
                  << item.guest_nice()
                  << std::endl;
    }
}

int main(int argc, char *argv[])
{
    CpuStat stat;
    Load(stat);

    Print(stat);
    return 0;
}
