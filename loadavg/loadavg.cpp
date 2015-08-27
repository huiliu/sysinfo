#include "loadavg.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

const char* PROC_FILE = "/proc/loadavg";

static void load(LoadAvg& load)
{
    std::ifstream ifs(PROC_FILE);
    if (!ifs.is_open()) {
        assert(false);
        return;
    }

    double loadVal;
    std::string ProcCount;
    std::string line;
    std::getline(ifs, line);
    std::istringstream iss(line);

    iss >> loadVal;
    load.set_load1(loadVal);
    iss >> loadVal;
    load.set_load5(loadVal);
    iss >> loadVal;
    load.set_load15(loadVal);

    iss >> ProcCount;
    std::string curCount = ProcCount.substr(ProcCount.find("/")+1);
    load.set_proccounts(std::stoi(curCount));
}

int main(int argc, char *argv[])
{
    LoadAvg sysload;
    load(sysload);

    std::cout << sysload.proccounts() << std::endl;
    return 0;
}
