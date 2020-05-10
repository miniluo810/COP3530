#pragma once

#include <iostream>
#include <fstream>
#include <map>
class frequency_table {

public:
    std::map <char, int> freq;
    frequency_table(const std::string &file_name);
    ~frequency_table() ;
    int get_frequency(char c) const;
};