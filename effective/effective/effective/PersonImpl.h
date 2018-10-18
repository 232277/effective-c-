#pragma once
#include<string>
struct PersonImpl
{
	PersonImpl(const std::string& n, int a) :name(n), age(a) {}
	~PersonImpl();
	std::string name;
	int age;
};//提供各个成员和构造，不需要是class，因为外部接口提供了封装

