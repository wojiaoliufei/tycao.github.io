#include "tsd_config.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign.hpp>
#include <boost/algorithm/string.hpp>
#include <exception>

/*
TsDataCfg::TsDataCfg() {
	error_no_ = 0;
	error_msg_ = "";
	if (0 != LoadXml("test_data.xml")) {
		std::cout << "Load test_data.xml failed. MSG:" << error_msg_ << std::endl;
	}
}


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
}
*/
