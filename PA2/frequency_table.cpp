#include "frequency_table.h"

frequency_table::frequency_table(const std::string &file_name) {
    std::ifstream file(file_name);
    if(!file.is_open()){
        throw std::runtime_error("Cannot be opened");
    }else {

        char c = file.get();
        while (c != EOF) {
            if (freq.count(c) != 0) {
                freq.at(c)++;
            } else {
                freq.emplace(c, 1);
            }

            c = file.get();
        }
        file.close();
    }
}

frequency_table::~frequency_table() {
    freq.clear();
}

int frequency_table::get_frequency(char c) const {
    if(freq.count(c)>0){
        return freq.at(c);
    }else{
        return 0;
    }
}