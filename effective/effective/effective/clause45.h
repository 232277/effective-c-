#pragma once


namespace clause45 {
	template<class T>
	class SmartPtr {
	public:
		SmartPtr() :p(nullptr) {}
		template<class U>
		explicit SmartPtr(U* up) :p(up) {}//����ȫ�����͵�ָ���ʼ��
		template<class U>
		SmartPtr(const SmartPtr<U> &sp) :p(sp.get()) {}//���ܿ���ת����SmartPtr
		SmartPtr(const SmartPtr& sp) :p(sp.get()) {}//��ȻҪ����һ���Լ��汾�Ŀ�������
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