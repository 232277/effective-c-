#pragma once


namespace classic {
	class HealthCalcFunc {
	public:
		int calcHealth(int num);
	}defaultCalcFunc;//计算策略类
	int HealthCalcFunc::calcHealth(int num)
	{
		return num;
	}

	class GameCharacter
	{
	public:
		GameCharacter() : healthCalFunc(&defaultCalcFunc), health(100) {}
		GameCharacter(HealthCalcFunc *hcf, int hp) :healthCalFunc(hcf), health(hp) {}
		~GameCharacter();
		int CalcHealth();

	private:
		HealthCalcFunc *healthCalFunc;
		int health;
	};

	int GameCharacter::CalcHealth()
	{
		healthCalFunc->calcHealth(health);//使用策略类的方法
	}
}