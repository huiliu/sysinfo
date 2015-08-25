#include <unistd.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

static long HZ = sysconf(_SC_CLK_TCK);

struct CPU_USAGE_DATA
{
    std::string tag;
    uint32_t    user;           // Time spent in user mode
    uint32_t    nice;           // Time spent in user mode with low priority
    uint32_t    system;         // Time spent in system mode
    uint32_t    idle;           // Time spent in the idle task
    uint32_t    iowait;         // Time waiting for I/O to complete
    uint32_t    irq;            // Time servicing interrupts
    uint32_t    softirq;        // Time servicing softirqs
    uint32_t    steal;          // time spent in other operating systems when running in a virtualized environment
    uint32_t    guest;          // Time spent running a virtual CPU for guest OS
    uint32_t    guest_nice;     // Time spent running a niced guest OS

    friend std::ostream& operator<<(std::ostream& os, const CPU_USAGE_DATA& info);
};

std::ostream& operator<<(std::ostream& os, const CPU_USAGE_DATA& info)
{
    os << info.tag
        << " " << info.user
        << " " << info.nice
        << " " << info.system
        << " " << info.idle
        << " " << info.iowait
        << " " << info.irq
        << " " << info.softirq
        << " " << info.steal
        << " " << info.guest
        << " " << info.guest_nice << std::endl;
    return os;
}

class CpuUsageInfo
{
public:
    CpuUsageInfo();
    ~CpuUsageInfo();

    void        Refresh();

    uint32_t    GetTotalCpuTime();
    double      GetUserRate();
    double      GetSystemRate();
    double      GetIdleRate();
    double      GetIowaitRate();
    double      GetIrqRate();
private:
    //static const std::string  STAT_FILE = "/proc/stat";
    static std::string  STAT_FILE;
    CPU_USAGE_DATA      m_data;
    uint32_t            m_totalTime;
};
std::string CpuUsageInfo::STAT_FILE = "/proc/stat";


CpuUsageInfo::CpuUsageInfo()
{
    Refresh();
}

CpuUsageInfo::~CpuUsageInfo()
{
}

void CpuUsageInfo::Refresh()
{
    std::ifstream   fi(STAT_FILE);
    std::string     line;

    std::getline(fi, line);

    std::istringstream  iss(line);

    iss >> m_data.tag;

    if (m_data.tag == "cpu") {
        iss >> m_data.user
            >> m_data.nice
            >> m_data.system
            >> m_data.idle
            >> m_data.iowait
            >> m_data.irq
            >> m_data.softirq
            >> m_data.steal
            >> m_data.guest
            >> m_data.guest_nice;

        m_totalTime = m_data.user
                    + m_data.nice
                    + m_data.system
                    + m_data.idle
                    + m_data.iowait
                    + m_data.irq
                    + m_data.softirq
                    + m_data.steal
                    + m_data.guest
                    + m_data.guest_nice;
    }else{
        std::cerr << "it's not cpu info" << std::endl;
    }
}

uint32_t CpuUsageInfo::GetTotalCpuTime()
{
    return m_totalTime / HZ;
}

double CpuUsageInfo::GetUserRate()
{
    return (double)m_data.user / m_totalTime;
}

double CpuUsageInfo::GetSystemRate()
{
    return (double)m_data.system / m_totalTime;
}

double CpuUsageInfo::GetIdleRate()
{
    return (double)m_data.idle / m_totalTime;
}

double CpuUsageInfo::GetIowaitRate()
{
    return (double)m_data.iowait / m_totalTime;
}

double CpuUsageInfo::GetIrqRate()
{
    return (double)(m_data.irq + m_data.softirq) / m_totalTime;
}

int main(int argc, const char *argv[])
{
    CpuUsageInfo cpu;

    std::cout << "Total Time: " << cpu.GetTotalCpuTime()
            << "\nUser use rate: " << cpu.GetUserRate()
            << "\nSystem use Rate: " << cpu.GetSystemRate()
            << "\niowait rate: " << cpu.GetIowaitRate()
            << "\nIDLE rate: " << cpu.GetIdleRate()
            << std::endl;

    return 0;
}
