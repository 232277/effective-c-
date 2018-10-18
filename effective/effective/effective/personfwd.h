#pragma once
#include<string>
#include<memory>
//不包含实际类的头文件，所以实际类若更改，这里不需要编译，使用这个借口的客户也不用重新编译

struct PersonImpl;//前置声明，以便之后的声明使用
class Person
{
public:
	Person(const std::string &name, const int age);//提供一样的构造函数
	Person(std::shared_ptr<PersonImpl> p);
	~Person();
	std::string name();
	int age();//提供和实际类的成员完全一致的接口函数

private:
	std::shared_ptr<PersonImpl> pImpl;//使用智能指针防止内存泄漏
};

/*另一种使用工厂函数的方式（尚未确定可行性）
struct PersonImpl;//前置声明，以便之后的声明使用
class Person
{
public:
~Person();
std::string name();
int age();//提供和实际类的成员完全一致的接口函数
static std::shared_ptr<Person> create(const std::string& name, const int age)
{
std::shared_ptr<Person> p = std::make_shared<Person>(new Person(name, age));
return p;
}//获取智能指针保障的对象

private:
Person(const std::string &name, const int age);//提供一样的构造函数，但防止构造
Person(std::shared_ptr<PersonImpl> p);

std::shared_ptr<PersonImpl> pImpl;//使用智能指针防止内存泄漏
};
*/