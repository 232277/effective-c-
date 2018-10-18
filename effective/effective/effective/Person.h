#pragma once
#include<string>
#include<memory>
#include"personfwd.h"
#include"PersonImpl.h"
//��Ϊ�����Ǿ����ʵ�֣�����Ҫ����ʵ�����ͷ�ļ�

//������Ӧ�Ĺ��캯��
Person::Person(const std::string &name, const int age) :pImpl(new PersonImpl(name, age)) {}

Person::Person(std::shared_ptr<PersonImpl> p) : pImpl(p) {}

Person::~Person() {}

//����ͬ����Ա
std::string Person::name() { return pImpl->name; }

int Person::age() { return pImpl->age; }

