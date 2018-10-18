#pragma once
#include<memory>

namespace clause49 {
	
	class ReturnHandler_RAII {
	public:
		ReturnHandler_RAII(std::new_handler old) :oldHandler(old) { std::cout << "use handler RAII" << std::endl; }
		ReturnHandler_RAII(const ReturnHandler_RAII &) = delete;//阻止拷贝构造与其他类到此类的转换
		ReturnHandler_RAII &operator=(const ReturnHandler_RAII &) = delete;//阻止赋值运算
		~ReturnHandler_RAII() { 
			std::set_new_handler(oldHandler);//重新绑定global的handler
			std::cout << "set global handler" << std::endl;
		}
	private:
		std::new_handler oldHandler;
	};

	namespace selfHandler {
		class selfHandler {
		public:
			std::new_handler set_new_handler(std::new_handler handler) noexcept;//用以改变类内的handler
			void *operator new(std::size_t n) throw(std::bad_alloc);
			//使用内部set_new_handler，并用RAII控制global_handler的装填，new为隐式static

		private:
			static std::new_handler myHandler;//由于new为static故handler需要是static才可以使用
		};

		void defaultHandler()
		{
			std::cout << "defaultHandler" << std::endl;
		}

		std::new_handler selfHandler::myHandler = defaultHandler;//设定默认处理

		std::new_handler selfHandler::set_new_handler(std::new_handler handler) noexcept
		{
			std::cout << "set a new handler" << std::endl;
			std::new_handler old = myHandler;
			myHandler = handler;
			return old;//交换并返回
		}

		void* selfHandler::operator new(std::size_t n) throw(std::bad_alloc)
		{
			std::cout << "called operator new" << std::endl;
			ReturnHandler_RAII raii(std::set_new_handler(myHandler));
			//使用RAII自动在内存请求完毕后绑回原来的handler
			return ::operator new(n);//调用全局的operator new
		}


		/*测试
		using namespace clause49;
		using namespace clause49::selfHandler;
		selfHandler *sh1 = new selfHandler();
		sh1->set_new_handler(testHandler);
		selfHandler *sh2 = new selfHandler();
		*/
	}

	namespace TMPhandler {//与之前的版本一致，但是可以让任何类继承这个support类(public继承)然后使用
		template<typename T>//T实际上没有用到，其作用是区分不同类型然后生成不同Static handler
		class NewHandlerSupport {//使用模板另一个好处是你还可以定制（特例化）不同类的方式
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
