#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

struct MEM_INFO_DATA
{
    uint64_t    MemTotal;
    uint64_t    MemFree;
    uint64_t    Buffers;
    uint64_t    Cached;
    uint64_t    SwapTotal;
    uint64_t    SwapFree;

    friend std::ostream& operator<< (std::ostream& os, const MEM_INFO_DATA& mem);
};

std::ostream& operator<< (std::ostream& os, const MEM_INFO_DATA& mem)
{
    os << "MemTotal: " << mem.MemTotal
        << " kB\nMemFree: " << mem.MemFree
        << " kB\nBuffers: " << mem.Buffers
        << " kB\nCached: " << mem.Cached
        << " kB\nSwapTotal: " << mem.SwapTotal
        << " kB\nSwapFree: " << mem.SwapFree
        << " kB" << std::endl;
    return os;
}

class MemUsageInfo
{
public:
    MemUsageInfo();
    ~MemUsageInfo();

    void        Refresh();

    uint64_t    GetMemTotal() const;
    uint64_t    GetMemFree() const;
    uint64_t    GetBuffers() const;
    uint64_t    GetCached() const;
    uint64_t    GetSwapTotal() const;
    uint64_t    GetSwapFree() const;

    void        Show() const;

private:
    void        SetValue(std::string& line);


    static const std::string STAT_FILE;
    MEM_INFO_DATA m_data;
};

const std::string MemUsageInfo::STAT_FILE = "/proc/meminfo";

MemUsageInfo::MemUsageInfo()
{
    Refresh();
}

MemUsageInfo::~MemUsageInfo()
{
}

void MemUsageInfo::Refresh()
{
    std::ifstream fi(STAT_FILE);
    std::string line;

    while (std::getline(fi, line)) {
        SetValue(line);
    }
}

void MemUsageInfo::SetValue(std::string& line)
{
    std::string tag;
    std::istringstream iss(line);

    iss >> tag;

    if (tag == "MemTotal:")
        iss >> m_data.MemTotal;
    else if (tag ==  "MemFree:")
        iss >> m_data.MemFree;
    else if (tag ==  "Buffers:")
        iss >> m_data.Buffers;
    else if (tag ==  "Cached:")
        iss >> m_data.Cached;
    else if (tag ==  "SwapTotal:")
        iss >> m_data.SwapTotal;
    else if (tag ==  "SwapFree:")
        iss >> m_data.SwapFree;
}


uint64_t MemUsageInfo::GetMemTotal() const
{
    return m_data.MemTotal;
}


uint64_t MemUsageInfo::GetMemFree() const
{
    return m_data.MemFree;
}


uint64_t MemUsageInfo::GetBuffers() const
{
    return m_data.Buffers;
}


uint64_t MemUsageInfo::GetCached() const
{
    return m_data.Cached;
}


uint64_t MemUsageInfo::GetSwapTotal() const
{
    return m_data.SwapTotal;
}


uint64_t MemUsageInfo::GetSwapFree() const
{
    return m_data.SwapFree;
}

void MemUsageInfo::Show() const
{
    std::cout << m_data;
}

int main(int argc, const char *argv[])
{
    MemUsageInfo mem;
    mem.Show();
    return 0;
}
