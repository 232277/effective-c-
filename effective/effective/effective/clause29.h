#pragma once
#include<memory>
using std::shared_ptr;

namespace clause29 {
	class Mutex {//测试用的Mutex
	public:
		Mutex() :locked(false) {  }
		~Mutex() {  }
		void lock() { locked = true; }
		void unlock() { locked = false; }

	private:
		bool locked;
	};

	class Lock {//管理Mutex的RAII类
	public:
		Lock() :mutex() { mutex->lock(); }
		Lock(Mutex *mu) :mutex(mu) { mutex->lock(); }
		~Lock() { mutex->unlock(); }

	private:
		Mutex * mutex;

	};


	struct Picture {

	};

	struct MenuBar {
		int changeTimes;
		shared_ptr<Picture> pic;
	};

	class Menu {
		//两个change函数强烈异常安全的前提是Picture的构造不会出现改变其他
		//状态的问题，假如两个函数的参数改为流对象，那么Picture构造失败时
		//很可能就改变了stream的读取位的状态，这样虽然Menu状态不变，但是
		//其他读取流的用户受到影响。
	public:
		void changePicture(Picture *p)
		{
			Lock lock(&mutex);//使用对象管理Mutex
			pic.reset(new Picture(*p));
			//使用reset便不用再删除原对象，因为reset已经帮我们做了
			//并且在new创建的Picture成功前，是不会reset的

			changeTimes++;
		}//普通的强烈异常安全

		void copyAndSwapPicture(Picture *p)
		{
			using std::swap;
			Lock lock(&mutex);
			shared_ptr<MenuBar> newPic(new MenuBar(*mb));//复制原对象
			newPic->pic.reset(p);//改变副本对象
			newPic->changeTimes++;

			swap(mb, newPic);//交换原对象与副本
		}//使用copy and swap实现强烈异常安全

	private:
		shared_ptr<Picture> pic;
		shared_ptr<MenuBar> mb;
		int changeTimes;
		Mutex mutex;
	};
}