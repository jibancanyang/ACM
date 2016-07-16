#include <iostream>
using namespace std;

template <typename T>
class testClass {
public:
    static int _data;
};

template <>
int testClass<int>::_data = 1;


int main()
{
    cout << testClass<int>::_data << endl;
    testClass<char> ch;
    cout << ch._data << endl;
    return 0;
}
