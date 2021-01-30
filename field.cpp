#include "field.h"
#include "ip.h"
#include "port.h"
#include <iostream>
#include <cstring>


Field::Field(String pattern, field_type type){
	this -> pattern = pattern;
	this -> type = type;
}

Field::Field(String pattern){
	this -> pattern = pattern;
	this -> type = GENERIC; 
}

Field::~Field(){
}


field_type Field::get_type() const{
	return this->type;
}



bool Field::set_value(String val){
	if (this->type == PORT) {
		return (Port*)this->set_value(val);
	}
	if (this->type == IP) {
		return (Ip*)this->set_value(val);
	}
	return false;
}


bool Field::match_value(String val) const {
	if ((this->type) == PORT) {
		return ((Port*)this)->match_value(val);
	}
	if ((this->type) == IP) {
		return ((Ip*)this)->match_value(val);
	}
	return false;
}


//this method will check if a packet is matching the rule in pattern
// the rule is in one field, we will find this field by its type and then  and then check the /

bool Field::match(String packet) {
	//splitting packet to patterns
	String *splitted_packet; //holds patterns in splitted_packet[i]
	size_t splitted_packet_len = 0;
	packet.split(",", &splitted_packet, &splitted_packet_len);

	//intializing, will be changed every iteration of the for loop
	String *splitted_pattern;
	size_t splitted_pattern_len = 0;
	
	
	//split and check each pattern 
	for (size_t i = 0; i < splitted_packet_len; i++) {
		
		splitted_packet[i].split("=", &splitted_pattern, &splitted_pattern_len);
		if (pattern.trim().equals(splitted_pattern[0].trim())) //check type
		{
				bool check_match = this->match_value(splitted_pattern[1].trim());
				delete[] splitted_packet;
				delete[] splitted_pattern;
				return check_match;
		}
		delete[] splitted_pattern;
	}
	delete[] splitted_packet;
	return false;
}
