#include "counter_of_unique_words.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

void Counter_of_unique_words::start(const std::string& path)
{
    std::string str;
    ifstream file;
    file.open(path);
    if (file.fail())
    {
        cout << "Filed to open" << endl;
        return ;
    }

    stringstream buffer;
    buffer << file.rdbuf();

    str = buffer.str();

    calculate_number_of_unique_words(str);
    print_number_of_unique_words();
}

void Counter_of_unique_words::print_number_of_unique_words()
{
    cout << unique_words.size() << endl;
}

void  Counter_of_unique_words::search_word(int &i,const std::string& str)
{
    mutex m2;
    std::string word;
    m2.lock();

    for (i; i < str.size() + 1; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            word.push_back(str[i]);
        }
        else if (str[i] == ' ' && (!word.empty()) || (i == str.size() && !word.empty()))
        {
            unique_words.insert(move(word));
            if (!word.empty())
            {
                word.clear();

            }
            i++;

            m2.unlock();

            return;
        }
        m2.unlock();
    }
}

void Counter_of_unique_words::calculate_number_of_unique_words(const std::string& str)
{
    mutex m;

    if (str.empty())
    {
        return ;
    }

    int cores_count = thread::hardware_concurrency();
    vector<thread> threads;
    threads.reserve(cores_count);

    int it = 0;

    resume:
    for (int i = 0; i < cores_count; ++i)
    {
        threads.push_back(thread([&]()
        {
            m.lock();

            search_word(it,str);

            if(it >= str.size())
            {
                i = cores_count;
            }
            m.unlock();

        }));

    }

    for (auto &t : threads)
    {
         if (t.joinable())
         {
             t.join();
         }

    }

    if(!(it >= str.size()))
    {
        threads.clear();
        goto resume;
    }

}
