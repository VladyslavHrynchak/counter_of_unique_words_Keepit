#include <iostream>
#include "counter_of_unique_words.h"

using namespace std;

int main()
{
    Counter_of_unique_words counter;
    cout << counter.countUnique("/home/vladuslav/C++programs_linux/Counter_of_unique_words_Keepit/counter_of_unique_words/text.txt") << endl;
    return 0;
}
