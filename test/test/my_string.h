
#include "stdafx.h"
struct string
{
	string(int size, char* str) : size(size), str(str)
	{}

	string(const char *str = "")
	{
		int len = 0;
		const char* str1 = str;
		while( *str1 != '\0')
		{
			len++;
			str1++;
		}
		char* new_str = new char [len+1];
		for(int i = 0; i < len+1; i++)
			new_str[i] = str[i];
		string::size = len;
		string::str = new_str;
	}

	string(size_t n, char c)
	{
		char* new_str = new char[n+1];
		for(int i = 0; i < n + 1; i++)
			new_str[i] = c;
		new_str[n] = '\0';
		string::size = n;
		string::str = new_str;
	}

	void append(string &other)
	{
		int new_size = this->size + other.size;
		char* new_str = new char[new_size + 1];
		for(int i = 0; i < this->size; i++)
			new_str[i] = this->str[i];
		for(int i = 0; i < other.size + 1; i++)
			new_str[this->size + i] = other.str[i];
		delete [] this->str;
		string::size = new_size;
		string::str = new_str;
	}

	~string()
	{
		delete [] str;
	}

	int size;
	char* str;
};