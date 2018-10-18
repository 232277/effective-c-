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
		std::list<T> rep;//使用list实现set

	};
	template<typename T>
	bool Set<T>::member(const T& mem) const
	{
		//使用泛型算法
		return std::find(rep.begin(),rep.end(),mem) != rep.end();
	}
	template<typename T>
	void Set<T>::insert(const T& mem)
	{
		//不存在则加入（set是不能有同样成员的）
		if (!member(mem))rep.push_back(mem);
	}
	template<typename T>
	void Set<T>::remove(const T& mem)
	{
		typename std::list<T>::iterator it
			= std::find(rep.begin(), rep.end(), mem);//获取迭代器
			if (it != rep.end())//对象在内
				rep.erase(it);//删除
	}
	template<typename T>
	std::size_t Set<T>::size() { return rep.size(); }
}