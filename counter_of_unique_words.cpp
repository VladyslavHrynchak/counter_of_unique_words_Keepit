#include "counter_of_unique_words.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

using namespace std;

std::int64_t Counter_of_unique_words::countUnique(const std::string& path)
{

    ifstream file;

    file.open(path);
    if (file.fail())
    {
        cout << "Filed to open" << endl;
        return -1;
    }

    stringstream buffer;
    buffer << file.rdbuf();

    if (!buffer)
    {
        return -1;
    }

    int cores_count = thread::hardware_concurrency();
    vector<thread> threads;
    threads.reserve(cores_count);

    for (int i = 0; i < cores_count; ++i)
    {
        threads.push_back(thread([&]()
        {

            countWord(buffer);

        }));
    }

    for (auto &t : threads)
    {
        t.join();
    }

    return unique_words.size();
}

void Counter_of_unique_words::countWord(stringstream& buffer)
{

    while(true)
    {
        string word;
        lock_guard<mutex> g(m);
        buffer >> word;

        if(word == "")
        {
            m.unlock();
            return;
        }

        lock_guard<mutex> g2(m2);
        unique_words.insert(move(word));
    }

}
