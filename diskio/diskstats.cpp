#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cassert>
#include "diskio.pb.h"

#define     DISKSTATS   "/proc/diskstats"
#define     LINE_SIZE   1024
static const int8_t PREFIX_LEN = 3;

namespace diskstat
{

// 过滤一些无关数据
bool filter(const std::string& str)
{
    // assert(PREFIX_LEN == str.size());
    static const std::vector<std::string> vecKey{"ram", "loo", "dm-"};
    
    for (auto& item : vecKey) {
        if (item.compare(0, PREFIX_LEN, str.c_str(), PREFIX_LEN) == 0) {
            return true;
        }
    }

    return false;
}

void parser()
{
    std::ifstream ifs(DISKSTATS);
    assert(ifs.is_open());

    std::vector<DiskIO> m_data;
    std::string line;

    while (std::getline(ifs, line)) {
        std::string partition_name;
        int64_t tmpValue;

        std::istringstream iss(line);
        iss >> tmpValue >> tmpValue
            >> partition_name;
        if (filter(partition_name)) {
            continue;
        }

        DiskIO tmpData;

        tmpData.set_partition_name(partition_name);
        iss >> tmpValue;
        tmpData.set_count_read_completed(tmpValue);
        iss >> tmpValue;
        tmpData.set_count_read_merged(tmpValue);
        iss >> tmpValue;
        tmpData.set_count_read_sectors(tmpValue);
        iss >> tmpValue;
        tmpData.set_time_read_consume(tmpValue);
        iss >> tmpValue;
        tmpData.set_count_write_completed(tmpValue);
        iss >> tmpValue;
        tmpData.set_count_write_merged(tmpValue);
        iss >> tmpValue;
        tmpData.set_count_write_sectors(tmpValue);
        iss >> tmpValue;
        tmpData.set_time_write_consume(tmpValue);
        iss >> tmpValue;
        tmpData.set_count_current_io(tmpValue);
        iss >> tmpValue;
        tmpData.set_time_io_spend(tmpValue);
        iss >> tmpValue;
        tmpData.set_time_weight_current_io(tmpValue);

        m_data.push_back(tmpData);
    }

    for (auto& item : m_data) {
        std::cout << item.partition_name()

                    << "\t" << item.count_read_completed()
                    << "\t" << item.count_read_merged()
                    << "\t" << item.count_read_sectors()
                    << "\t" << item.time_read_consume()

                    << "\t" << item.count_write_completed()
                    << "\t" << item.count_write_merged()
                    << "\t" << item.count_write_sectors()
                    << "\t" << item.time_write_consume()

                    << "\t" << item.time_io_spend()
                    << "\t" << item.time_weight_current_io()
        << std::endl;
    }
}

}

int main(int argc, const char *argv[])
{
    diskstat::parser();
    return 0;
}
