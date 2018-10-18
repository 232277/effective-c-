#pragma once
#include<memory>
#include<string>


class Person {
public:
	virtual ~Person() {}//析构不能是纯虚
	virtual std::string name() const = 0;
	virtual int age() const = 0;//成员接口
	static std::shared_ptr<Person> create(const std::string &name,int age);//工厂函数
};