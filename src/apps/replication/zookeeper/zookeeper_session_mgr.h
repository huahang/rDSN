#include <dsn/internal/singleton_store.h>

#pragma once

namespace dsn { namespace dist{

class zookeeper_session;
class zookeeper_session_mgr: public utils::singleton<zookeeper_session_mgr>
{
public:
    zookeeper_session_mgr()
    {
        _zoo_hosts = dsn_config_get_value_string("zookeeper", "hosts_list", "", "zookeeper_hosts");
        _timeout_ms = dsn_config_get_value_uint64("zookeeper", "timeout_ms", 30000, "zookeeper_timeout_milliseconds");
        _zoo_logfile = dsn_config_get_value_string("zookeeper", "logfile", "", "zookeeper logfile");
    }

    zookeeper_session* get_session(void* service_node);
    const char* zoo_hosts() const { return _zoo_hosts.c_str(); }
    int timeout() const { return _timeout_ms; }
    const char* zoo_logfile() const { return _zoo_logfile.c_str(); }

private:
    utils::ex_lock_nr _store_lock;

private:
    std::string _zoo_hosts;
    int _timeout_ms;
    std::string _zoo_logfile;
};

}}
