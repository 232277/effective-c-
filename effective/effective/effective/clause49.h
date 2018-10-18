#pragma once
#include<memory>

namespace clause49 {
	
	class ReturnHandler_RAII {
	public:
		ReturnHandler_RAII(std::new_handler old) :oldHandler(old) { std::cout << "use handler RAII" << std::endl; }
		ReturnHandler_RAII(const ReturnHandler_RAII &) = delete;//��ֹ���������������ൽ�����ת��
		ReturnHandler_RAII &operator=(const ReturnHandler_RAII &) = delete;//��ֹ��ֵ����
		~ReturnHandler_RAII() { 
			std::set_new_handler(oldHandler);//���°�global��handler
			std::cout << "set global handler" << std::endl;
		}
	private:
		std::new_handler oldHandler;
	};

	namespace selfHandler {
		class selfHandler {
		public:
			std::new_handler set_new_handler(std::new_handler handler) noexcept;//���Ըı����ڵ�handler
			void *operator new(std::size_t n) throw(std::bad_alloc);
			//ʹ���ڲ�set_new_handler������RAII����global_handler��װ�newΪ��ʽstatic

		private:
			static std::new_handler myHandler;//����newΪstatic��handler��Ҫ��static�ſ���ʹ��
		};

		void defaultHandler()
		{
			std::cout << "defaultHandler" << std::endl;
		}

		std::new_handler selfHandler::myHandler = defaultHandler;//�趨Ĭ�ϴ���

		std::new_handler selfHandler::set_new_handler(std::new_handler handler) noexcept
		{
			std::cout << "set a new handler" << std::endl;
			std::new_handler old = myHandler;
			myHandler = handler;
			return old;//����������
		}

		void* selfHandler::operator new(std::size_t n) throw(std::bad_alloc)
		{
			std::cout << "called operator new" << std::endl;
			ReturnHandler_RAII raii(std::set_new_handler(myHandler));
			//ʹ��RAII�Զ����ڴ�������Ϻ���ԭ����handler
			return ::operator new(n);//����ȫ�ֵ�operator new
		}


		/*����
		using namespace clause49;
		using namespace clause49::selfHandler;
		selfHandler *sh1 = new selfHandler();
		sh1->set_new_handler(testHandler);
		selfHandler *sh2 = new selfHandler();
		*/
	}

	namespace TMPhandler {//��֮ǰ�İ汾һ�£����ǿ������κ���̳����support��(public�̳�)Ȼ��ʹ��
		template<typename T>//Tʵ����û���õ��������������ֲ�ͬ����Ȼ�����ɲ�ͬStatic handler
		class NewHandlerSupport {//ʹ��ģ����һ���ô����㻹���Զ��ƣ�����������ͬ��ķ�ʽ
		public:
			std::new_handler set_new_handler(std::new_handler handler) noexcept;
			void *operator new(std::size_t n) throw(std::bad_alloc);

		private:
			static std::new_handler classHandler;
		};
		template<typename T>
		std::new_handler NewHandlerSupport<T>::classHandler = nullptr;

		template<typename T>
		std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler handler) noexcept
		{
			std::new_handler old = classHandler;
			classHandler = handler;
			return old;
		}

		template<typename T>
		void *NewHandlerSupport<T>::operator new(std::size_t n) throw(std::bad_alloc)
		{
			ReturnHandler_RAII raii(std::set_new_handler(classHandler));
			return ::operator new(n);
		}
	}
}
