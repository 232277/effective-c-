#pragma once
#include<functional>

namespace strategy {
	int defaultCalc(int num);
	class GameCharacter {
	public:
		using calHealthType = int(int);//���庯��ָ������
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
		//...׼��
		int healthPoint = calMethod(health);//ʹ�ú���ָ����ɹ���
		//...�ƺ�
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
		using calcType = std::function<int(int)>;//����ɵ��ö�������
		GameCharacter() :calcFun(defaultCalc), health(100) {}
		GameCharacter(calcType cal, int hp) :calcFun(cal), health(hp) {}
		virtual ~GameCharacter() {}
		int CalcHealth();
		int MemHealthCal(int num)
		{
			std::cout << "MemHealthCal" << std::endl;
			std::cout << "this->health: " << this->health << std::endl;
			//���ص����ֵ�ǵ����ߵ�health * 3,����������������ǵ����ߵ�
			//��this->Health���᲻ͬ�ڵ����ߵ�this->health
			return num * 3;
		}

	private:
		calcType calcFun;//�洢�ɵ��ö���
		int health;

	};
	int GameCharacter::CalcHealth()
	{
		//...ĳЩ׼��
		int healthPoint = calcFun(health);//ʵ��ʹ��int(int)��ʽ�Ŀɵ��ö���������
		//...�ƺ�
		return healthPoint;
	}

	int defaultCalc(int num)
	{
		std::cout << "defaultCalc" << std::endl;
		return num;
	}
	
	float defaultEBGcal(short num);//ע�ⷵ�����ͺͲ�������,short,float�ֱ��������/������int
	class EvilBadGuy :public GameCharacter
	{
	public:
		EvilBadGuy() :GameCharacter(defaultEBGcal,100) {}//non-member����
		//EvilBadGuy() :GameCharacter(evilHealthCal2, 100) {}//�������󣨽ṹ�壩
		EvilBadGuy(calcType cal, int hp) :GameCharacter(cal, hp) {}
		virtual ~EvilBadGuy() override{};

		struct EvilHealthCal2 {
			int operator()(int num)
			{
				std::cout << "EvilHealthCal2" << std::endl;
				return num / 2;
			}
		}evilHealthCal2;//��ʵӦ�÷�private,���������ⲿ���ò�����
	private:

	};
	float  defaultEBGcal(short num)
	{
		std::cout << "defaultEBGcal" << std::endl;
		return num * 2;
	}
}