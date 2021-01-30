#include <iostream>
#include "ip.h"
#include <cstring>
#include <iostream>
#define NUMBER_OF_ALL_IP_BITS 32




Ip::Ip(String pattern) : Field (pattern , IP){
// c'tor 
}

bool Ip::set_value(String val){
	size_t size_of_divided_data = 0;
	String* divided_data;
	int ip = 0;
	int mask = 0;
	val.split("/" , &divided_data , &size_of_divided_data);

	if(size_of_divided_data == 2){
		ip = divided_data[0].trim().to_integer();
		mask = divided_data[1].trim().to_integer();
		if (mask <= 32 && mask >= 0){
			long low_ip = 1 << (NUMBER_OF_ALL_IP_BITS - 1);
			low_ip = low_ip >> (mask - 1);
			low = ip & low_ip;
			long high_ip = ~low_ip;
			high = ip | high_ip;
			delete[] divided_data;
			return true;
		}
	}
	delete[] divided_data;
	return false;
}

bool Ip::match_value(String val) const{
	unsigned int ip_check = val.trim().to_integer();
	if (ip_check > high || ip_check <low){
		return false;
	}
	else {
		return true;
	}

}

