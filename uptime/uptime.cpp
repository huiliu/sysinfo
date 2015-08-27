#include "uptime.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

static const char* PROC_UPTIME = "/proc/uptime";

void load(Uptime& data)
{
    data.Clear();

    std::ifstream ifs(PROC_UPTIME);
    if (!ifs.is_open()) {
        assert(false);
        return;
    }

    double val;
    ifs >> val;
    data.set_uptime(static_cast<int32_t>(val));
    ifs >> val;
    data.set_idletime(static_cast<int32_t>(val));
}

inline void print(const Uptime& data)
{
    std::cout << data.uptime() << "\t" << data.idletime() << std::endl;
}

int main(int argc, char *argv[])
{
    Uptime up;
    load(up);

    print(up);
    return 0;
}
