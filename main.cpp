
#include <iostream>
#include "ip.h"
#include "port.h"
#include <cstring>

extern void parse_input(Field&);
extern int check_args(int , char**);

int main(int argc , char** argv){
	
	const char* first_valid_port = "src-port";
	const char* second_valid_port = "dst-port";
	const char* first_valid_ip = "src-ip";
	const char* second_valid_ip = "dst-ip";
	
	if (check_args(argc , argv)){
		return 1;
	}
	

	size_t size_of_divided_data;
	String* divided_data;
	String rule(argv[1]);

	rule.split("=" , &divided_data , &size_of_divided_data);
	
	bool check_src_port = divided_data[0].trim().equals(String(first_valid_port));
	bool check_dst_port = divided_data[0].trim().equals(String(second_valid_port));
	bool check_src_ip 	= divided_data[0].trim().equals(String(first_valid_ip));
	bool check_dst_ip 	= divided_data[0].trim().equals(String(second_valid_ip));

	if(check_src_port || check_dst_port){
		Port port_rule(divided_data[0].trim());
		if(port_rule.set_value(divided_data[1].trim())){
			parse_input(port_rule); 
		}
	}

	if(check_src_ip || check_dst_ip){
		Ip ip_rule(divided_data[0].trim());
		if(ip_rule.set_value(divided_data[1].trim())){
			parse_input(ip_rule); 
		}
	}

}

