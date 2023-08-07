#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<stdio.h>
#include<map>
#include<fstream>
class Manager;
class Speaker;

// Usage:
//std::vector<Speaker> myVector;
//std::sort(myVector.begin(), myVector.end(), MyClass::CompareFunction);

//std::vector<Speaker> myVector;
//std::sort(myVector.begin(), myVector.end(), [&class](const Speaker& a, const Speaker& b) {
//	return myObject.CompareFunction(a, b);
//});

/********************************************************************************************************************/
//bool ComapareVector(const Speaker& spkr1, const Speaker& spkr2)
//{
//	return spkr1.
//}

void VectorBubble(Manager& man);

class Speaker
{
public:
	std::string NameSeed[12] = { "A","B","C","D","E","F","G","H","I","J","K","L" };
	Speaker(int i);
	~Speaker();

	void PrintID();
	void PrintName();
	void PrintGrade(const Manager& man);
	void SetGrade(double Score,const Manager& man);
	double GetGrade(const Manager& man);

	std::string m_name;
	int m_number;
public:
	double GeadeArray[2];
};

class Manager
{
public:
	Manager();
	~Manager();

	void ShowMenu();

	void Quit();

	void Init();

	void ContestBegin();

	void Draw();

	void UpLoadContestors(const Speaker& spkr);

	void RoundOneBegin();

	static bool CompareVec(const Speaker& spkr1, const Speaker& spkr2);

	void SaveRecord();

	void CheckRecord();

	void ShowRecord();

	void ClearRecord();
	//bool FileEmpty();

	std::map<int,std::vector<std::string>>m_Record;

	std::vector<Speaker> Round1;//初始十二名参赛选手
	std::vector<Speaker> Round2;//晋级的六位选手
	std::vector<Speaker> Final;//决赛三名选手
	
	 int Round;//比赛轮次
};

