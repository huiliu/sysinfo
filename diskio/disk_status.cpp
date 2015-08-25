#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

const uint16_t  DISK_MAJOR = 8;
const uint16_t  DISK_MINOR_RANGE = 16;

struct DISK_IO_DATA
{
    std::string     label;
    uint64_t        completed_read;     // the total number of reads completed successfully
    uint64_t        merged_read;
    uint64_t        read_sector;
    uint64_t        read_time;          // the total number of milliseconds spent by all reads.
    uint64_t        completed_write;
    uint64_t        merged_write;
    uint64_t        write_sector;
    uint64_t        write_time;

    friend std::ostream& operator<< (std::ostream& os, const DISK_IO_DATA& data);
};

std::ostream& operator<<(std::ostream& os, const DISK_IO_DATA& data)
{
    os << "Label: " << data.label
        << "\ncompleted read: " << data.completed_read
        << "\nmerged read: " << data.merged_read
        << "\nread sector: " << data.read_sector
        << "\nread time: " << data.read_time
        << "\ncompleted_write: " << data.completed_write
        << "\nmerged write: " << data.merged_write
        << "\nwrite sector: " << data.read_sector
        << "\nwrite time: " << data.write_time
        << std::endl;

    return os;
}


class DiskIoInfo
{
public:
    DiskIoInfo();
    ~DiskIoInfo();

    void            Refresh();
    void            Show() const;

    uint64_t        GetCompletedRead() const;
    uint64_t        GetCompletedWrite() const;
    const std::vector<DISK_IO_DATA>&     GetData() const;

private:

    void                    SetValue(std::string& line);

    static const std::string STAT_FILE;
    std::vector<DISK_IO_DATA>   m_dataVec;
};

const std::string DiskIoInfo::STAT_FILE = "/proc/diskstats";

DiskIoInfo::DiskIoInfo()
{
    Refresh();
}

DiskIoInfo::~DiskIoInfo()
{
}

void DiskIoInfo::Show() const
{
    for (auto& item : m_dataVec)
        std::cout << item;
}

void DiskIoInfo::Refresh()
{
    std::ifstream fi(STAT_FILE);
    std::string line;

    while (std::getline(fi, line)) {
        SetValue(line);
    }
}

void DiskIoInfo::SetValue(std::string& line)
{
    uint16_t    major,
                minor;

    DISK_IO_DATA data;

    std::istringstream iss(line);

    iss >> major
        >> minor;

    if (major != DISK_MAJOR)
        return;

    if (minor % DISK_MINOR_RANGE != 0)
        return;
    
    iss >> data.label
        >> data.completed_read
        >> data.merged_read
        >> data.read_sector
        >> data.read_time

        >> data.completed_write
        >> data.merged_write
        >> data.write_sector
        >> data.write_time;

    m_dataVec.push_back(data);
}

const std::vector<DISK_IO_DATA>& DiskIoInfo::GetData() const
{
    return m_dataVec;
}

int main(int argc, const char *argv[])
{
    DiskIoInfo disk;
    disk.Show();
    return 0;
}
