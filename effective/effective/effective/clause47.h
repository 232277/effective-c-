#pragma once
#include<iostream>


namespace clause47 {
	struct iterType1 {
		iterType1() {
			std::cout << "iterType1构造" << std::endl;
		}
	};
	struct iterType2 {
		iterType2() {
			std::cout << "iterType2构造" << std::endl;
		}
	};

	class iterClass1
	{
	public:
		class iterator {
		public:
			using iterator_category = iterType1;
		};
	};

	class iterClass2
	{
	public:
		class iterator {
		public:
			using iterator_category = iterType2;
		};
	};


	template<typename T>
	struct myTraits {
		using iterator_category = typename T::iterator::iterator_category;
	};

	template<typename T>
	struct myTraits<T*>
	{
		using iterator_category = iterType2;
	};

	template<typename T>
	void doAdvance(T, iterType1)
	{
		std::cout << "T类型:" << typeid(T).name() << std::endl;
		std::cout << "doAdvance(iterType1)" << std::endl;
	}

	template<typename T>
	void doAdvance(T, iterType2)
	{
		std::cout << "T类型:" << typeid(T).name() << std::endl;
		std::cout << "doAdvance(iterType2)" << std::endl;
		std::cout << "-------------" << std::endl;
	}

	template<class T>
	void myAdvance(T)
	{
		std::cout << "myAdvance" << std::endl;
		doAdvance(T(), typename myTraits<T>::iterator_category());
	}

	/*
	iterClass1 *itcp1 = new iterClass1();
	iterClass2 itcp2;
	
	myAdvance(itcp1);
	myAdvance(itcp2);
	*/
}