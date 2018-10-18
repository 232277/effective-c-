#pragma once
#include<string>
#include<memory>
//������ʵ�����ͷ�ļ�������ʵ���������ģ����ﲻ��Ҫ���룬ʹ�������ڵĿͻ�Ҳ�������±���

struct PersonImpl;//ǰ���������Ա�֮�������ʹ��
class Person
{
public:
	Person(const std::string &name, const int age);//�ṩһ���Ĺ��캯��
	Person(std::shared_ptr<PersonImpl> p);
	~Person();
	std::string name();
	int age();//�ṩ��ʵ����ĳ�Ա��ȫһ�µĽӿں���

private:
	std::shared_ptr<PersonImpl> pImpl;//ʹ������ָ���ֹ�ڴ�й©
};

/*��һ��ʹ�ù��������ķ�ʽ����δȷ�������ԣ�
struct PersonImpl;//ǰ���������Ա�֮�������ʹ��
class Person
{
public:
~Person();
std::string name();
int age();//�ṩ��ʵ����ĳ�Ա��ȫһ�µĽӿں���
static std::shared_ptr<Person> create(const std::string& name, const int age)
{
std::shared_ptr<Person> p = std::make_shared<Person>(new Person(name, age));
return p;
}//��ȡ����ָ�뱣�ϵĶ���

private:
Person(const std::string &name, const int age);//�ṩһ���Ĺ��캯��������ֹ����
Person(std::shared_ptr<PersonImpl> p);

std::shared_ptr<PersonImpl> pImpl;//ʹ������ָ���ֹ�ڴ�й©
};
*/