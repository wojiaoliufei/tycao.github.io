#pragma once
#include <string>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign.hpp>
#include <boost/algorithm/string.hpp>
#include <exception>




using namespace std;

#define DISALLOW_COPY_AND_ASSIGN(Typename) \
Typename(const Typename&); \
void operator=(const Typename&)

class TsDataCfg {
public:
	static TsDataCfg* GetInstance() {
		static TsDataCfg cfg;
		return &cfg;
	}
	
private:
	TsDataCfg();
	~TsDataCfg() { }
	int LoadXml(const char* filename);
	DISALLOW_COPY_AND_ASSIGN(TsDataCfg);
	
public:
	int error_no_;
	string error_msg_;
	string ip_address_;
	string mac_address_;
	string sys_id_;
	string srt_no_;
	string host_name_;
	string os_name_;
	string cpu_serial_no_;
	string disk_serial_no_;
	string dbname_;
	int opt_flag_;
	
	string ar_account_id_;
	int ar_account_type_;
	int ar_adapter_type_;
	int ar_adapter_scope_no_;
	int ar_opt_flag_;
};

int TsDataCfg::LoadXml(const char* filename) {
        using namespace boost;
        using namespace boost::property_tree;
        using namespace boost::assign;
        ptree pt;
        error_no_ = 0;

        try {
                read_xml(filename, pt, boost::property_tree::xml_parser::trim_whitespace);
                ip_address_ = pt.get<std::string>("CONFIG.CLOUD_RC.IP_ADDRESS", "");
                mac_address_ = pt.get<std::string>("CONFIG.CLOUD_RC.MAC_ADDRESS", "");
                sys_id_ = pt.get<std::string>("CONFIG.CLOUD_RC.SYS_ID", "");
                srt_no_ = pt.get<std::string>("CONFIG.CLOUD_RC.SRT_NO", "");
                host_name_ = pt.get<std::string>("CONFIG.CLOUD_RC.HOST_NAME", "");
                os_name_ = pt.get<std::string>("CONFIG.CLOUD_RC.OS_NAME", "");
                cpu_serial_no_ = pt.get<std::string>("CONFIG.CLOUD_RC.CPU_SERIAL_NO", "");
                disk_serial_no_ = pt.get<std::string>("CONFIG.CLOUD_RC.DISK_SERIAL_NO", "");
                dbname_ = pt.get<std::string>("CONFIG.CLOUD_RC.DBNAME", "");
                opt_flag_ = pt.get<int>("CONFIG.CLOUD_RC.OPT_FLAG", 3);

                ar_account_id_ = pt.get<std::string>("CONFIG.AR_CFG.ACCOUNT_ID", "");
                ar_account_type_ = pt.get<int>("CONFIG.AR_CFG.ACCOUNT_TYPE", 0);
                ar_adapter_type_ = pt.get<int>("CONFIG.AR_CFG.ADAPTER_TYPE", 0);
                ar_adapter_scope_no_ = pt.get<int>("CONFIG.AR_CFG.ADAPTER_S_NO", 0);
                ar_opt_flag_ = pt.get<int>("CONFIG.AR_CFG.OPT_FLAG", 3);

        } catch(std::exception& e) {
                error_no_ = -1;
                error_msg_ = e.what();
                return error_no_;
        }
	return error_no_;
}


TsDataCfg::TsDataCfg() {
	error_no_ = 0;
	error_msg_ = "";
	if (0 != LoadXml("/home/zogy/Desktop/Project/test_data.xml")) {
		std::cout << "Load test_data.xml failed. MSG:" << error_msg_ << std::endl;
	}

	printf("ip_address_:%s\nmac_address_:%s\nsys_id_:%s\nsrt_no_:%s\nhost_name_:%s\nos_name_:%s\ncpu_serial_no_:%s\ndisk_serial_no_:%s\ndbname_:%s\nopt_flag_:%d\nar_account_id_:%s\nar_account_type_:%d\nar_adapter_type_:%d\nar_adapter_scope_no_:%d\nar_opt_flag_:%d\n", ip_address_.c_str(), mac_address_.c_str(), sys_id_.c_str(), srt_no_.c_str(), host_name_.c_str(), os_name_.c_str(), cpu_serial_no_.c_str(), disk_serial_no_.c_str(), dbname_.c_str(), opt_flag_, ar_account_id_.c_str(), ar_account_type_, ar_adapter_type_, ar_adapter_scope_no_, ar_opt_flag_);

}
