#pragma once
#include<string>
#include<memory>
#include"personfwd.h"
#include"PersonImpl.h"
//因为这里是具体的实现，故需要保护实际类的头文件

//调用相应的构造函数
Person::Person(const std::string &name, const int age) :pImpl(new PersonImpl(name, age)) {}

Person::Person(std::shared_ptr<PersonImpl> p) : pImpl(p) {}

Person::~Person() {}

//返回同名成员
std::string Person::name() { return pImpl->name; }

int Person::age() { return pImpl->age; }

