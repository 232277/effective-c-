#pragma once


namespace clause45 {
	template<class T>
	class SmartPtr {
	public:
		SmartPtr() :p(nullptr) {}
		template<class U>
		explicit SmartPtr(U* up) :p(up) {}//接受全部类型的指针初始化
		template<class U>
		SmartPtr(const SmartPtr<U> &sp) :p(sp.get()) {}//接受可以转换的SmartPtr
		SmartPtr(const SmartPtr& sp) :p(sp.get()) {}//任然要定义一个自己版本的拷贝构造
		template<class U>
		explicit SmartPtr(std::unique_ptr<U> &up) : p(sp.get()) {}
		template<class U>
		explicit SmartPtr(std::weak_ptr<U> &wp) :p(wp.get()) {}

		template<class U>
		SmartPtr &operator=(SmartPtr<U> &sp);
		template<class U>
		SmartPtr &operator=(std::unique_ptr<U> &up);
		SmartPtr &operator=(const SmartPtr<T> &sp);

		T* get() { return p; }

	private:
		T * p;
	};
	template<class T>
	template<class U>
	SmartPtr<T> &SmartPtr<T>::operator=(SmartPtr<U> &sp)
	{
		p = sp.get();
		return *this;
	}

	template<class T>
	template<class U>
	SmartPtr<T> &SmartPtr<T>::operator=(std::unique_ptr<U> &up)
	{
		p = up.release();
		return *this;
	}

	template<class T>
	SmartPtr<T> &SmartPtr<T>::operator=(const SmartPtr<T> &sp)
	{
		p = sp.get();
		return *this;
	}
}