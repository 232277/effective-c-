#pragma once

namespace clause44 {
	namespace normal {
		template<typename T,std::size_t n>
		class SquareMatrix {
		public:
			void invert() { return matrix; }//不同数值类型或不同的n都引起新的invert()代码
		private:
			T matrix[n*n];
		};//整个类也比较大，采用指针会好一点
	}

	namespace withParameter {
		template<typename T>
		class SquareMatrixBase {
		public:
			T* invert(std::size_t n) { return matrix; }//执行实际的功能，需要绑定尺寸n
		private:
			T *matrix;//使用指针指向矩阵
		};//每个类型只有一份invert的代码

		template<typename T,std::size_t n>
		class SquareMatrix :private SquareMatrixBase<T>{
		public:
			using SquareMatrixBase<T>::invert;
			T* invert() { return this->invert(n); }//调用基类的处理
		private:
			T matrix[n*n];//存放实际的数据
		};//对象的体积会很大
	}

	namespace withNew {
		template<typename T>
		class SquareMatrixBase {
		public:
			SquareMatrixBase() :matrix(nullptr) {}
			SquareMatrixBase(T* m,size_t n) :size(n),matrix(m) {}
			T* invert() { return matrix; }//执行实际的功能，需要绑定尺寸n
		private:
			size_t size;//保存大小
			T* matrix;//使用指针指向矩阵
		};//每个类型才会有一个共有的invert版本（代码只有一份）

		template<typename T, std::size_t n>
		class SquareMatrix :private SquareMatrixBase<T> {
		public:
			using SquareMatrixBase<T>::invert;
			SquareMatrix() :matrix(new T[n*n]),//把矩阵数据放到动态内存
				SquareMatrixBase<T>(matrix.get(),n) {}//传递指针和大小
			
			T* invert() { return this->invert(n); }//调用基类的处理
		private:
			std::shared_ptr<T> matrix;//存放指针
		};
	}
}
