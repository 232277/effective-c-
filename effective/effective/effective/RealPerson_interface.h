#pragma once
#include"Person_Interface.h"


class RealPerson : public Person//实现接口的函数
{
public:
	RealPerson(const std::string& n, int a) :pname(n), page(a) {}
	~RealPerson() override {};

	std::string name() const override { return pname; }
	
	int age() const override { return page; }

private:
	std::string pname;
	int page;
};

std::shared_ptr<Person> Person::create(const std::string &name, int age)
{
	std::shared_ptr<Person> p = std::make_shared<Person>(new RealPerson(name, age));
	return p;
}//提供了实际类定义后就可以实现接口程序