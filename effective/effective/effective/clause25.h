#pragma once
#include <utility>

namespace ForSwapStuff {
	//特化了std的版本，在使用std::swap时也会使用特化版本
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