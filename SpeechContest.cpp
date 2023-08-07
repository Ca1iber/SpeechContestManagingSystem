#include"SpeechContest.h"

void VectorBubble(Manager& man)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = i; j < 6; j++)
		{
			if (man.Round == 1)
			{
				if (man.Round1[j].GeadeArray[0] > man.Round1[i].GeadeArray[0])
				{
					Speaker Temp = man.Round1[j];
					man.Round1[j] = man.Round1[i];
					man.Round1[i] = Temp;
				}
			}
			else if (man.Round == 2)
			{
				if (man.Round2[j].GeadeArray[1] > man.Round2[i].GeadeArray[1])
				{
					Speaker Temp = man.Round2[j];
					man.Round2[j] = man.Round2[i];
					man.Round2[i] = Temp;
				}
			}

		}
	}
	for (int i = 6; i < 12; i++)
	{
		for (int j = i; j < 12; j++)
		{
			if (man.Round == 1)
			{
				if (man.Round1[j].GeadeArray[0] > man.Round1[i].GeadeArray[0])
				{
					Speaker Temp = man.Round1[j];
					man.Round1[j] = man.Round1[i];
					man.Round1[i] = Temp;
				}
			}
		}
	}
}



//管理系统构造函数
Manager::Manager()
{
	this->Init();

	//this->CheckRecord();//加载往届记录
}
//管理系统析构函数
Manager::~Manager()
{
	;
}
//展示菜单函数
void Manager::ShowMenu()
{
	std::cout << "*********************************************" << std::endl;
	std::cout << "******* Welcome to the speech contest *******" << std::endl;
	std::cout << "******* Press 1 to start the contest  *******" << std::endl;
	std::cout << "******* Press 2 to check the record   *******" << std::endl;
	std::cout << "******* Press 3 to clear the record   *******" << std::endl;
	std::cout << "************** Press 0 to quit **************" << std::endl;
	std::cout << "*********************************************" << std::endl;
	std::cout << std::endl;
}
//退出函数
void Manager::Quit()
{
	std::cout << "感谢使用,欢迎下次使用" << std::endl;
}
//初始化函数
void Manager::Init()
{
	this->Round1.clear();
	this->Round2.clear();
	this->Final.clear();
	this->Round = 1;

}

void Manager::ContestBegin()
{
	//第一步抽签
	this->Draw();
	//比赛
	this->RoundOneBegin();
	//显示晋级结果

	//第二轮比赛
	this->Round++;
	//抽签
	this->Draw();
	//比赛
	this->RoundOneBegin();
	//显示最终结果冠亚季

	//保存名单
	this->SaveRecord();
	std::cout << "本届比赛圆满结束！" << std::endl;
	system("pause");
	system("cls");
	this->Round--;
	this->Round2.clear();
	this->Final.clear();
}
//抽签函数
void Manager::Draw()
{
	if (this->Round == 1)
	{
		std::cout << "第" << this->Round << "轮比赛选手正在抽签" << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
		std::cout << "抽签结果如下：" << std::endl;
	}

	if (this->Round == 1)
	{
		std::random_shuffle(Round1.begin(), Round1.end());//随机打乱
		for (std::vector<Speaker>::iterator iter = Round1.begin(); iter != Round1.end(); iter++)
		{
			(*iter).PrintID();
		}
		std::cout << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
	}
	else if (this->Round == 2)
	{
		std::random_shuffle(Round2.begin(), Round2.end());//随机打乱
		for (std::vector<Speaker>::iterator iter = Round2.begin(); iter != Round2.end(); iter++)
		{
			(*iter).PrintID();
		}
		std::cout << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
	}
	//std::cout << "--------------------------------------------" << std::endl;
	system("pause");
	std::cout << std::endl;
}


//排序函数，根据Speaker的m_Grade大小对选手进行分组排序
//bool Manager::CompareVec(const Speaker& spkr1,const Speaker& spkr2 )
//{
//	if (Round == 1)
//	{
//		return spkr1.GeadeArray[0]>spkr2.GeadeArray[0];
//	}
//	else if (Round == 2)
//	{
//		return spkr1.GeadeArray[1] > spkr2.GeadeArray[1];
//	}
//}


//比赛函数
void Manager::RoundOneBegin()
{
	std::cout << "----------------第" << this->Round << "轮比赛开始-----------------" << std::endl;
	
	//统计六人一组,利用临时数据
	int num = 0;
	std::multimap<double, int, std::greater<double>> GroupScore;
	
	std::vector<Speaker>v_Src;
	if (this->Round == 1)
	{
		v_Src = this->Round1;
	}
	else
	{
		v_Src = this->Round2;
	}

	//遍历所有选手开始比赛
	for (std::vector<Speaker>::iterator iter = v_Src.begin(); iter != v_Src.end(); iter++)
	{
		num++;
		double score;

		//评委打分
		std::deque<double>d;//存储分数的容器
		for (int i = 0; i < 10; i++)
		{
		    score = (rand() % 401 + 600) / 10.0f;	//600~1000
			//printf("%.1f ", score);//打印分数
			d.push_back(score);

		}
		sort(d.begin(),d.end(),std::greater<double>());//排序
		d.pop_front();//去除最高分，最低分
		d.pop_back();
		double sum = std::accumulate(d.begin(), d.end(),0.0f);//总分
		double avg = sum / (double)d.size();//平均分
		
		//将成绩根据比赛轮数录入
		(*iter).SetGrade(avg,*this);
		if (this->Round == 1)
		{
			Round1 = v_Src;
		}
		else if (this->Round == 2)
		{
			Round2 = v_Src;
		}
		if (this->Round == 1)//第一轮的处理
		{
			//每六人取前三名
			if (num % 6 == 0)
			{
				std::cout << std::endl;
				std::cout << std::endl;
				std::cout << "第" << num / 6 << "小组比赛名次如下:" << std::endl;
				if (num / 6 == 1)//排序第一组
				{
					VectorBubble(*this);

					//Test Code,测试是否正确排序
					for (size_t u = 0; u < this->Round1.size()/2; u++)
					{
						this->Round1[u].PrintName();
						std::cout << "的成绩是:";
						this->Round1[u].PrintGrade(*this);

					}
					//取走第一组的前三名，根据当前比赛轮次将其放入新的容器中
					for (size_t q = 0; q < 3; q++)
					{
						this->Round2.push_back(this->Round1[q]);
					}
				}

				else if (num / 6 == 2)//排序第二组
				{
					//std::sort(this->Round1.begin()+5, this->Round1.end(), [this](const Speaker& sprk1, const Speaker& sprk2) {
					//	if (Round == 1)
					//	{
					//		return sprk1.GeadeArray[0] > sprk2.GeadeArray[0];
					//	}
					//	else if (Round == 2)
					//	{
					//		return sprk1.GeadeArray[1] > sprk2.GeadeArray[1];
					//	}

					//	});
					VectorBubble(*this);
					for (int u = 6; u < 12; u++)
					{
						this->Round1[u].PrintName();
						std::cout << "的成绩是:";
						this->Round1[u].PrintGrade(*this);

					}
					//取走第一组的前三名，根据当前比赛轮次将其放入新的容器中
					for (size_t q = 6; q < 9; q++)
					{
						this->Round2.push_back(this->Round1[q]);
					}

				}
			}
			//	std::cout << std::endl;
		}
		else if (this->Round == 2)//第二轮处理
		{
			if (num % 6 == 0)
			{
				std::cout << std::endl;
				std::cout << std::endl;
				std::cout << "第二轮比赛名次如下：" << std::endl;
				if (num / 6 == 1)
				{
					VectorBubble(*this);
					for (size_t u = 0; u < this->Round2.size(); u++)
					{
						this->Round2[u].PrintName();
						std::cout << "的成绩是";
						this->Round2[u].PrintGrade(*this);
					}
					//取走前三名，决定冠亚季军
					for (size_t q = 0; q < 3; q++)
					{
						this->Final.push_back(this->Round2[q]);
					}
				}
			}
		}
		//std::cout << std::endl;
	}
	if (this->Round == 1)
	{
		std::cout << std::endl;
		std::cout << "第" << this->Round << "轮比赛完毕，以下选手将晋级下一轮比赛："<<std::endl;
		for (std::vector<Speaker>::iterator iter2 = this->Round2.begin(); iter2 != this->Round2.end(); iter2++)
		{
			(*iter2).PrintName(); std::cout << " ";
		}
		std::cout << std::endl;
		system("pause");
	}
	else if (this->Round == 2)
	{
		std::cout << std::endl;
		std::cout << "第" << this->Round << "两轮比赛已完毕，将产生冠亚季军" << std::endl;
	}

}

//上传选手信息
void Manager::UpLoadContestors(const Speaker& spkr)
{
	this->Round1.push_back(spkr);
}

void Manager::SaveRecord()
{
	std::ofstream Out;
	Out.open("FormerRecord.csv",std::ios::out|std::ios::app);//用追加的方式写文件

	//将每个选手的数据写入文件中
	for (std::vector<Speaker>::iterator iter = this->Final.begin(); iter != this->Final.end(); iter++)
	{
		Out << iter->m_name << "," << iter->GeadeArray[1] << ", ";
	}
	Out << std::endl;
	Out.close();
	std::cout << "文件记录完毕" << std::endl;
}

void Manager::CheckRecord()
{
	std::ifstream In("FormerRecord.csv", std::ios::in);
	if (!In.is_open())
	{
		std::cout << "文件不存在" << std::endl;
		//this->FileEmpty() = true;
		In.close();
		return;
	}
	
	//文件清空
	char ch;
	In >> ch;
	if (In.eof())
	{
		//this->FileEmpty() = true;
		std::cout << "文件空" << std::endl;		
		In.close();
		return;
	}
	//文件不空
	//this->FileEmpty() = false;
	In.putback(ch);//将刚才读取的单个字符收回

	std::string data;
	int index = 0;
	while (In >> data)
	{
		std::vector<std::string> v;//存放六个string字符串
		//std::cout << data;// << std::endl;
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos=data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			else
			{
				std::string temp = data.substr(start, pos - start);
				//std::cout << temp << std::endl;
				v.push_back(temp);
				start = pos + 1;
			}
		}
		this->m_Record.insert(std::make_pair(index,v) );
		index++;
	}
	In.close();

	for (std::map<int, std::vector<std::string>>::iterator iter = m_Record.begin(); iter != m_Record.end(); iter++)
	{
		std::cout << (iter->first)/3+1 << "三甲编号： " << iter->second[0] << " 分数 " << iter->second[1] << std::endl;
	}
	std::cout << std::endl;
}

void Manager::ShowRecord()
{
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		std::cout << "第" << i + 1 << "届的冠军为:" << this->m_Record[i][0] << " 得分 " << this->m_Record[i][1] << " "
			<< "亚军为:" << this->m_Record[i][2] << " 得分 " << this->m_Record[i][3] << " "
			<< "季军为:" << this->m_Record[i][4] << " 得分 " << this->m_Record[i][5] << " "
			<< std::endl;
	}
	system("pause");
	system("cls");
}

void Manager::ClearRecord()
{
	std::cout << "确认要清空历史记录吗？" << std::endl;
	std::cout << "Press 1 to confirm" << std::endl;
	std::cout << "Press 2 to cancal" << std::endl;
	int Select = 0;
	std::cin >> Select;
	if (Select == 1)
	{
		std::ofstream ofs("FormerRecord.csv", std::ios::trunc);
		ofs.close();
		std::cout << "清空成功" << std::endl;
	}
		system("pause");
		system("cls");
}
/**************************************************************************************************************/


//选手构造函数

Speaker::Speaker(int i)
{
	this->m_name = "选手" + this->NameSeed[i];
	this->m_number = 10001 + i;
	for (int j = 0; j < 2; j++)
	{
		this->GeadeArray[j] = 0;
	}
}

void Speaker::PrintID()
{
	std::cout << this->m_number << " ";
}

void Speaker::PrintName()
{
	std::cout << this->m_name << " ";
}

//选手设置，打印，读取成绩函数
void Speaker::PrintGrade(const Manager& man)
{
	std::cout << this->GeadeArray[man.Round-1] << std::endl;
}

double Speaker::GetGrade(const Manager& man)
{
	return this->GeadeArray[man.Round - 1];
}

void Speaker::SetGrade(double Score,const Manager& man)
{
	if (man.Round == 1)
	{
		this->GeadeArray[0] = Score;
	}
	else if (man.Round == 2)
	{
		this->GeadeArray[1] = Score;
	}
}

//选手析构函数
Speaker::~Speaker()
{
	;
}

//Speaker::Speaker()
//{
//	for (int i = 0; i < 12; i++)
//	{
//		this->m_name = "选手" + this->NameSeed[i];
//		this->m_number = 10001 + i;
//		for (int j = 0; j < 2; j++)
//		{
//			this->GradeArray[j] = 0;
//		}
//	}
//	
//}
//

//std::string Speaker::PrintID()
//{
//	//std::cout << this->m_id << " ";
//	return this->m_name;
//}
//
//double Speaker::PrintGrade(const Manager& man)
//{
//	//std::cout << this->m_grade << " ";
//	return (this->GradeArray[man.Round]);
//}
//
//
