#ifndef COUNTER_OF_UNIQUE_WORDS_H
#define COUNTER_OF_UNIQUE_WORDS_H

#include <unordered_set>
#include <string>
#include <mutex>
#include <sstream>
class Counter_of_unique_words
{
public:

    std::int64_t countUnique(const std::string& path);

private:

    std::mutex m;

    std::mutex m2;

    void countWord(std::stringstream& buffer);

    std::unordered_set<std::string> unique_words;
};

#endif
