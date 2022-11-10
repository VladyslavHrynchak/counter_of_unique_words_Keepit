#ifndef COUNTER_OF_UNIQUE_WORDS_H
#define COUNTER_OF_UNIQUE_WORDS_H

#include <set>
#include <string>
class Counter_of_unique_words
{
public:

    void start(const std::string& path);

private:
    void calculate_number_of_unique_words(const std::string& str);

    void print_number_of_unique_words();

    void search_word(int &i,const std::string& str);

    std::set<std::string> unique_words;
};

#endif
