#include <iostream>
using namespace std;

#include <boost/thread.hpp>
using namespace boost;

void ThrdFunc(void)
{
    for (char i = 'a'; i <= 'z'; ++i) cout << i;
}

class TThrdClass
{
public:
    void ThrdFunc(int j)
    {
        for (int i = 0; i < 10; ++i) cout << i;
    }
};

int main()
{
    TThrdClass obj;
    thread thr1(&ThrdFunc);
    thread thr2(&TThrdClass::ThrdFunc, &obj, 0);
    if (thr1.joinable()) thr1.join();
    if (thr2.joinable()) thr2.join();
    return 0;
}
