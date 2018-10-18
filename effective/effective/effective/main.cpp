#include"main.h"

class A {
public:
	virtual ~A() noexcept
	{
		try {
			fun();
		}
		catch (exception e)
		{

		}
	}
	virtual void fun() = 0;
};

class B : A {
public:
	~B() override {}
	void fun()override {}
};

int main()
{
	B a;
	//a.fun();

	int z;
	cin >> z;
}
