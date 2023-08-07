#include <iostream>
#include <string>
#include"SpeechContest.h"
#include<vector>


int main()
{
	Manager manager;
	int choice = 1;
	//Test Code
	for (int i = 0; i < 12; i++)
	{
		Speaker speaker(i);
		manager.UpLoadContestors(speaker);
	}
	//
	while (choice != 0)
	{

		//弹出主菜单
		manager.ShowMenu();
		std::cout << "请输入您的选择:" << std::endl;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			std::cout << "比赛开始!" << std::endl;
			manager.ContestBegin();
			break;
		case 2:
			std::cout << "以下是往届比赛记录:" << std::endl;
			manager.CheckRecord();
			break;
		case 3:
			manager.ClearRecord();
			break;
		case 0:
			manager.Quit();
			
			break;
		default:
			system("cls");//清屏
			break;
		}
	}

	system("pause");
}



//speaker.PrintName();
//std::cout << "的编号是：";
//speaker.PrintID();
//std::cout << std::endl;

//VectorBubble(manager);
//Test Code,检验是否能将平均分转存并且排序
//for (size_t k = 0; k < manager.Round1.size(); k++)
//{
//	manager.Round1[k].PrintName();
//	std::cout << "的成绩是:";
//	manager.Round1[k].PrintGrade(manager);
//}
