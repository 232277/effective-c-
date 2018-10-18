#pragma once

namespace clause44 {
	namespace normal {
		template<typename T,std::size_t n>
		class SquareMatrix {
		public:
			void invert() { return matrix; }//��ͬ��ֵ���ͻ�ͬ��n�������µ�invert()����
		private:
			T matrix[n*n];
		};//������Ҳ�Ƚϴ󣬲���ָ����һ��
	}

	namespace withParameter {
		template<typename T>
		class SquareMatrixBase {
		public:
			T* invert(std::size_t n) { return matrix; }//ִ��ʵ�ʵĹ��ܣ���Ҫ�󶨳ߴ�n
		private:
			T *matrix;//ʹ��ָ��ָ�����
		};//ÿ������ֻ��һ��invert�Ĵ���

		template<typename T,std::size_t n>
		class SquareMatrix :private SquareMatrixBase<T>{
		public:
			using SquareMatrixBase<T>::invert;
			T* invert() { return this->invert(n); }//���û���Ĵ���
		private:
			T matrix[n*n];//���ʵ�ʵ�����
		};//����������ܴ�
	}

	namespace withNew {
		template<typename T>
		class SquareMatrixBase {
		public:
			SquareMatrixBase() :matrix(nullptr) {}
			SquareMatrixBase(T* m,size_t n) :size(n),matrix(m) {}
			T* invert() { return matrix; }//ִ��ʵ�ʵĹ��ܣ���Ҫ�󶨳ߴ�n
		private:
			size_t size;//�����С
			T* matrix;//ʹ��ָ��ָ�����
		};//ÿ�����ͲŻ���һ�����е�invert�汾������ֻ��һ�ݣ�

		template<typename T, std::size_t n>
		class SquareMatrix :private SquareMatrixBase<T> {
		public:
			using SquareMatrixBase<T>::invert;
			SquareMatrix() :matrix(new T[n*n]),//�Ѿ������ݷŵ���̬�ڴ�
				SquareMatrixBase<T>(matrix.get(),n) {}//����ָ��ʹ�С
			
			T* invert() { return this->invert(n); }//���û���Ĵ���
		private:
			std::shared_ptr<T> matrix;//���ָ��
		};
	}
}
