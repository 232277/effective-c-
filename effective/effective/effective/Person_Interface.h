#pragma once
#include<memory>
#include<string>


class Person {
public:
	virtual ~Person() {}//���������Ǵ���
	virtual std::string name() const = 0;
	virtual int age() const = 0;//��Ա�ӿ�
	static std::shared_ptr<Person> create(const std::string &name,int age);//��������
};