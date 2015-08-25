#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct NET_TRAFFIC_DATA
{
    std::string if_name;
    uint64_t    recv_bytes;
    uint64_t    recv_packets;
    uint64_t    recv_errs;
    uint64_t    recv_drop;

    uint64_t    trans_bytes;
    uint64_t    trans_packets;
    uint64_t    trans_errs;
    uint64_t    trans_drop;

    friend std::ostream& operator<< (std::ostream& os, const NET_TRAFFIC_DATA& data);
};

std::ostream& operator<<(std::ostream& os, const NET_TRAFFIC_DATA& data)
{
    os << data.if_name
        << "\n\tReceived:"
        << "\n\t\tbytes: " << data.recv_bytes
        << "\n\t\tpackets: " << data.recv_packets
        << "\n\t\terrs: " << data.recv_errs
        << "\n\t\tdrop: " << data.recv_drop
        << "\n\tTransmit:"
        << "\n\t\tbytes: " << data.trans_bytes
        << "\n\t\tpackets: " << data.trans_packets
        << "\n\t\terrs: " << data.trans_errs
        << "\n\t\tdrop: " << data.trans_drop
        << std::endl;
    return os;
}

class NetTrafficInfo
{
public:
    NetTrafficInfo();
    ~NetTrafficInfo();

    void        Refresh();
    void        Show() const;

    std::string GetIfName() const;
    uint64_t    GetRecvBytes() const;
    uint64_t    GetRecvPackets() const;
    uint64_t    GetRecvErrs() const;
    uint64_t    GetRecvDrop() const;

    uint64_t    GetTransBytes() const;
    uint64_t    GetTransPackets() const;
    uint64_t    GetTransErrs() const;
    uint64_t    GetTransDrop() const;
private:
    static const std::string STAT_FILE;
    std::vector<NET_TRAFFIC_DATA> m_dataVec;
};

const std::string NetTrafficInfo::STAT_FILE = "/proc/net/dev";

NetTrafficInfo::NetTrafficInfo()
{
    Refresh();
}

NetTrafficInfo::~NetTrafficInfo()
{
}

void NetTrafficInfo::Refresh()
{
    std::ifstream       fi(STAT_FILE);
    std::string         line;
    NET_TRAFFIC_DATA    data;
    int32_t             tmp;

    std::getline(fi, line);
    std::getline(fi, line);

    while (std::getline(fi, line)) {
        std::istringstream iss(line);

        iss >> data.if_name
            >> data.recv_bytes
            >> data.recv_packets
            >> data.recv_errs
            >> data.recv_drop
            >> tmp
            >> tmp
            >> tmp
            >> tmp
            >> data.trans_bytes
            >> data.trans_packets
            >> data.trans_errs
            >> data.trans_drop;

        m_dataVec.push_back(data);
    }
}

void NetTrafficInfo::Show() const
{
    for (auto& item : m_dataVec)
        std::cout << item;
}

int main(int argc, const char *argv[])
{
    NetTrafficInfo net;
    net.Show();
    return 0;
}
