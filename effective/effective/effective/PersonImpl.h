#pragma once
#include<string>
struct PersonImpl
{
	PersonImpl(const std::string& n, int a) :name(n), age(a) {}
	~PersonImpl();
	std::string name;
	int age;
};//�ṩ������Ա�͹��죬����Ҫ��class����Ϊ�ⲿ�ӿ��ṩ�˷�װ

