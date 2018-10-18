#pragma once
#include <utility>

namespace ForSwapStuff {
	//�ػ���std�İ汾����ʹ��std::swapʱҲ��ʹ���ػ��汾
	class ForSwap {
	public:
		void swap(ForSwap& rhs)
		{
			int *temp = pointer;
			pointer = rhs.pointer;
			rhs.pointer = temp;
		}

	private:
		int *pointer;
	};
	void swap(ForSwap& lhs, ForSwap& rhs)
	{
		lhs.swap(rhs);
	}
}
namespace std {
	template<>
	void swap<ForSwap>(ForSwapStuff::ForSwap& lhs, ForSwapStuff::ForSwap& rhs)
	{
		lhs.swap(rhs);
		cout << "swap" << endl;
	}
}