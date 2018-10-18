#pragma once

namespace NVI {
	class GameCharacter {
	public:
		GameCharacter() :health(100) {}
		GameCharacter(int h) :health(h) {}
		int healthCalc();

	private:
		int health;

		virtual int calcHealth(int num);
	};

	int GameCharacter::healthCalc()
	{
		//prepare
		int healthPoint = calcHealth(health);//执行实际功能
											 //after
		return healthPoint;
	}//定义非成员函数来取代virtual函数，隐式inline

	int GameCharacter::calcHealth(int num)
	{
		std::cout << "gamecharacter" << std::endl;
		return num;
	}//私有的virtual函数决定实际的功能


	class EvilBadGuy : public GameCharacter {
	public:
		EvilBadGuy() :GameCharacter() {}
		EvilBadGuy(int h) :GameCharacter(h) {}

	private:
		virtual int calcHealth(int num) override;
	};

	int EvilBadGuy::calcHealth(int num)
	{
		std::cout << "evilbadguy" << std::endl;
		return num * 2;
	}//不同的计算策略
}

/*
//执行代码 结果为 gamecharacter 100 evilbadguy 200
GameCharacter g;
EvilBadGuy e;
cout << g.healthCalc() << endl;
cout << e.healthCalc() << endl;
*/