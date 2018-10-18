#pragma once
#include<memory>
using std::shared_ptr;

namespace clause29 {
	class Mutex {//�����õ�Mutex
	public:
		Mutex() :locked(false) {  }
		~Mutex() {  }
		void lock() { locked = true; }
		void unlock() { locked = false; }

	private:
		bool locked;
	};

	class Lock {//����Mutex��RAII��
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
		//����change����ǿ���쳣��ȫ��ǰ����Picture�Ĺ��첻����ָı�����
		//״̬�����⣬�������������Ĳ�����Ϊ��������ôPicture����ʧ��ʱ
		//�ܿ��ܾ͸ı���stream�Ķ�ȡλ��״̬��������ȻMenu״̬���䣬����
		//������ȡ�����û��ܵ�Ӱ�졣
	public:
		void changePicture(Picture *p)
		{
			Lock lock(&mutex);//ʹ�ö������Mutex
			pic.reset(new Picture(*p));
			//ʹ��reset�㲻����ɾ��ԭ������Ϊreset�Ѿ�����������
			//������new������Picture�ɹ�ǰ���ǲ���reset��

			changeTimes++;
		}//��ͨ��ǿ���쳣��ȫ

		void copyAndSwapPicture(Picture *p)
		{
			using std::swap;
			Lock lock(&mutex);
			shared_ptr<MenuBar> newPic(new MenuBar(*mb));//����ԭ����
			newPic->pic.reset(p);//�ı丱������
			newPic->changeTimes++;

			swap(mb, newPic);//����ԭ�����븱��
		}//ʹ��copy and swapʵ��ǿ���쳣��ȫ

	private:
		shared_ptr<Picture> pic;
		shared_ptr<MenuBar> mb;
		int changeTimes;
		Mutex mutex;
	};
}