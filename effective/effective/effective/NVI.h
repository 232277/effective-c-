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
		int healthPoint = calcHealth(health);//ִ��ʵ�ʹ���
											 //after
		return healthPoint;
	}//����ǳ�Ա������ȡ��virtual��������ʽinline

	int GameCharacter::calcHealth(int num)
	{
		std::cout << "gamecharacter" << std::endl;
		return num;
	}//˽�е�virtual��������ʵ�ʵĹ���


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
	}//��ͬ�ļ������
}

/*
//ִ�д��� ���Ϊ gamecharacter 100 evilbadguy 200
GameCharacter g;
EvilBadGuy e;
cout << g.healthCalc() << endl;
cout << e.healthCalc() << endl;
*/