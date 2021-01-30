
#include <cstring>
#include "string.h"
#include <iostream>
#include "ip.h" 

using namespace std;

#define NUMBER_OF_BYTES 4
#define NUMBER_OF_BITS_EACH_DIVIDE 8
#define NUMBER_OF_ALL_IP_BITS 32


String::String (){
	data = NULL;
	length = 0;
}

String::String (const char* str) {
	if (str == NULL) {
		data = NULL;
		length = 0;
		return;
	}
	length = strlen(str);
	data = new char[length + 1];
	data = strncpy (data , str , length);
}

String::String (const String &str) {
	length = str.length;
	// if the length is zero we don't have data
	if (length == 0 ) {
		data = NULL;
		return;
	}
	else {
		data = new char[length + 1];
		data = strncpy (data , str.data , str.length);

	}
}

String::~String(){
	if (data != NULL){
		delete[] data;
	}
}

String& String::operator=(const String &rhs){
	if (this == &rhs){
		return *this;
	}
	if (data != NULL){
		delete[] data;
	}
	length = rhs.length;
	// if the length is zero we don't have data
	if (length == 0){
		data = NULL;
		return *this;
	}
	else
	{
	data = new char[length + 1];
	data = strncpy (data , rhs.data , rhs.length);
	}	

	return *this;
}

String& String::operator=(const char *str){
	if (str == NULL){
		data = NULL;
		length = 0;
	}
	if (data != NULL){
		delete[] data;
	}
	length = strlen(str);
	data = new char[length + 1];
	data = strncpy (data , str , length);
	return *this;
}

bool String::equals(const String &rhs) const 
{
	if ((length == rhs.length) && (strcmp(data , rhs.data) == 0)) {
		return true;
	}

	return false;
}

bool String::equals(const char *rhs) const{
	if ((length == strlen(rhs)) && (strcmp(data , rhs) ==0 )){
		return true;
	}
	return false;
}

void String::split(const char *delimiters, String **output, size_t *size) const { 
	int new_length = 0;
	char new_data[length + 1] = {0};
	strncpy(new_data, data, length);
	int num_of_delimiter = 0;
	if (delimiters == NULL) {
		*size = 1;
	}
	else{
		new_length = strlen(delimiters);
		new_data[length] = '\0'; 
		for (size_t i = 0; i < length; i++) { 
			for (int j = 0; j < new_length; j++) {
				if (new_data[i] == delimiters[j]) {
					num_of_delimiter++;
					continue;
				}
			}
		}
		*size = (num_of_delimiter + 1); 
	}
	if (output != NULL) {
		*output = new String[*size]; 
		for (int i = 0; i < (int)length; i++) {
			for (int j = 0; j < new_length; j++) {
				if (new_data[i] == delimiters[j]) {
					new_data[i] = '\0'; 
				}
			}
		}
		int string_num = 0;
		int string_ctr = 0;
		int counter = 0;
		for (counter = 0; counter < (int)(*size); counter++) {
			for(;(counter == 0) && (new_data[string_num] == '\0') && (string_num < (int)length + 1);){
				string_num++;
				string_ctr++;
			}
			for (;(counter == 0) && (new_data[string_num] == '\0') && (string_num < (int)length + 1);) { 
				string_num++;
				string_ctr++;
			}
			for (;(new_data[string_num] != '\0') && (string_num < (int)length + 1);) {
				string_num++;
			}
			(*output)[counter] = String(&new_data[string_ctr]);
			string_ctr = string_num;
			for (;((new_data[string_num]) == '\0') && (string_num < (int)length + 1);) { 
				string_num++;
				string_ctr++;
			}
		}
	}
}

String String::trim() const 
{
	int num_of_spaces_begin = 0 ;
	int num_of_spaces_end = length - 1;

	if (data == NULL)
	{
		return String();
	}

	while (data[num_of_spaces_begin] == ' ')
	{
		num_of_spaces_begin++;
	}
	
	while( (data[num_of_spaces_end] == ' ') && (num_of_spaces_begin != num_of_spaces_end) )
	{
		num_of_spaces_end--;
	}
	
	num_of_spaces_end++;

	if (num_of_spaces_begin >= num_of_spaces_end)
	{
		return String();
	}

	char newData[num_of_spaces_end - num_of_spaces_begin + 1];
	strncpy(newData, &data[num_of_spaces_begin], num_of_spaces_end - num_of_spaces_begin);  
	newData[num_of_spaces_end - num_of_spaces_begin] = '\0';

	return String(newData);
}

int String::to_integer() const{
	int new_integer = 0;
	unsigned number_of_IP_bytes = NUMBER_OF_BYTES;
	size_t size_of_divided_data = 0;
	String* divided_data = NULL;
	int part_of_integer = 0;
	 //If "divided_data" is set to NULL, do not allocated memory, only compute "size".
	split("." , &divided_data , &size_of_divided_data);
	if (size_of_divided_data != number_of_IP_bytes){
		new_integer = atoi(data);
		delete [] divided_data;
		return new_integer;
	}
	else { // we want to make the new integer from the IP
		for (int i = 0; i < NUMBER_OF_BYTES; i++){
			part_of_integer =  divided_data[i].trim().to_integer();
			if (part_of_integer >=0 && part_of_integer <= 255){
				int num_of_bytes_to_shift = NUMBER_OF_ALL_IP_BITS - (i + 1)*NUMBER_OF_BITS_EACH_DIVIDE;
				part_of_integer = part_of_integer << num_of_bytes_to_shift;
				new_integer = new_integer | part_of_integer;
			}
			else {
				delete [] divided_data;
				return 0;
			}
		}
		delete [] divided_data;
		return new_integer;
	}
}

