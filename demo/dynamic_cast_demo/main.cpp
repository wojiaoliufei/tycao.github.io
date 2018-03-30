#include<iostream>
#include <typeinfo>

using namespace std;


class A;
class B;
class C;

class A {
public:
    A() {}
    virtual ~A() { cout << "A's destructor called...\n";}
};

class B : public A {
public:
    B() { }
    virtual ~B() {}
};

class C : public B {
public:
    C() {}
    virtual ~C() {}
};


int main(int argc, char *argv[])
{
    A *pa = new A;

    try {
        C& c = dynamic_cast<C&>(*pa);
    }
    catch(std::bad_cast& error) {
        cout << "dynamic_cast failed..." << error.what() << endl;
    }
    delete pa;
    return 0;
}


