#pragma once
#include<functional>

namespace strategy {
	int defaultCalc(int num);
	class GameCharacter {
	public:
		using calHealthType = int(int);//定义函数指针类型
		GameCharacter() :calMethod(defaultCalc), health(100) {}
		GameCharacter(calHealthType *p, int hp) :calMethod(p), health(hp) {}
		int CalcHealth() const;

	private:
		calHealthType * calMethod;
		int health;

	};
	int defaultCalc(int num)
	{
		std::cout << "defaultCalc" << std::endl;
		return num;
	}

	int GameCharacter::CalcHealth() const
	{
		//...准备
		int healthPoint = calMethod(health);//使用函数指针完成工作
		//...善后
		return healthPoint;
	}

	int EvilBadGuyHealthCal(int num)
	{
		std::cout << "EvilBadGuyCalc" << std::endl;
		return num * 2;
	}
}


namespace funStrategy {
	int defaultCalc(int num);
	class GameCharacter
	{
	public:
		using calcType = std::function<int(int)>;//定义可调用对象类型
		GameCharacter() :calcFun(defaultCalc), health(100) {}
		GameCharacter(calcType cal, int hp) :calcFun(cal), health(hp) {}
		virtual ~GameCharacter() {}
		int CalcHealth();
		int MemHealthCal(int num)
		{
			std::cout << "MemHealthCal" << std::endl;
			std::cout << "this->health: " << this->health << std::endl;
			//返回的这个值是调用者的health * 3,但是这个函数并不是调用者的
			//故this->Health将会不同于调用者的this->health
			return num * 3;
		}

	private:
		calcType calcFun;//存储可调用对象
		int health;

	};
	int GameCharacter::CalcHealth()
	{
		//...某些准备
		int healthPoint = calcFun(health);//实际使用int(int)形式的可调用对象来计算
		//...善后
		return healthPoint;
	}

	int defaultCalc(int num)
	{
		std::cout << "defaultCalc" << std::endl;
		return num;
	}
	
	float defaultEBGcal(short num);//注意返回类型和参数类型,short,float分别可以提升/降级到int
	class EvilBadGuy :public GameCharacter
	{
	public:
		EvilBadGuy() :GameCharacter(defaultEBGcal,100) {}//non-member函数
		//EvilBadGuy() :GameCharacter(evilHealthCal2, 100) {}//函数对象（结构体）
		EvilBadGuy(calcType cal, int hp) :GameCharacter(cal, hp) {}
		virtual ~EvilBadGuy() override{};

		struct EvilHealthCal2 {
			int operator()(int num)
			{
				std::cout << "EvilHealthCal2" << std::endl;
				return num / 2;
			}
		}evilHealthCal2;//其实应该放private,但是这样外部就用不了了
	private:

	};
	float  defaultEBGcal(short num)
	{
		std::cout << "defaultEBGcal" << std::endl;
		return num * 2;
	}
}