#pragma once
#include<list>

namespace clause38 {
	template<typename T>
	class Set {
	public:
		bool member(const T&) const;
		void insert(const T&);
		void remove(const T&);
		std::size_t size();

	private:
		std::list<T> rep;//ʹ��listʵ��set

	};
	template<typename T>
	bool Set<T>::member(const T& mem) const
	{
		//ʹ�÷����㷨
		return std::find(rep.begin(),rep.end(),mem) != rep.end();
	}
	template<typename T>
	void Set<T>::insert(const T& mem)
	{
		//����������루set�ǲ�����ͬ����Ա�ģ�
		if (!member(mem))rep.push_back(mem);
	}
	template<typename T>
	void Set<T>::remove(const T& mem)
	{
		typename std::list<T>::iterator it
			= std::find(rep.begin(), rep.end(), mem);//��ȡ������
			if (it != rep.end())//��������
				rep.erase(it);//ɾ��
	}
	template<typename T>
	std::size_t Set<T>::size() { return rep.size(); }
}