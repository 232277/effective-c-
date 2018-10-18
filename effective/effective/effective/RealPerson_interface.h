#pragma once
#include"Person_Interface.h"


class RealPerson : public Person//ʵ�ֽӿڵĺ���
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
}//�ṩ��ʵ���ඨ���Ϳ���ʵ�ֽӿڳ���