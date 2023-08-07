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



//����ϵͳ���캯��
Manager::Manager()
{
	this->Init();

	//this->CheckRecord();//���������¼
}
//����ϵͳ��������
Manager::~Manager()
{
	;
}
//չʾ�˵�����
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
//�˳�����
void Manager::Quit()
{
	std::cout << "��лʹ��,��ӭ�´�ʹ��" << std::endl;
}
//��ʼ������
void Manager::Init()
{
	this->Round1.clear();
	this->Round2.clear();
	this->Final.clear();
	this->Round = 1;

}

void Manager::ContestBegin()
{
	//��һ����ǩ
	this->Draw();
	//����
	this->RoundOneBegin();
	//��ʾ�������

	//�ڶ��ֱ���
	this->Round++;
	//��ǩ
	this->Draw();
	//����
	this->RoundOneBegin();
	//��ʾ���ս�����Ǽ�

	//��������
	this->SaveRecord();
	std::cout << "�������Բ��������" << std::endl;
	system("pause");
	system("cls");
	this->Round--;
	this->Round2.clear();
	this->Final.clear();
}
//��ǩ����
void Manager::Draw()
{
	if (this->Round == 1)
	{
		std::cout << "��" << this->Round << "�ֱ���ѡ�����ڳ�ǩ" << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
		std::cout << "��ǩ������£�" << std::endl;
	}

	if (this->Round == 1)
	{
		std::random_shuffle(Round1.begin(), Round1.end());//�������
		for (std::vector<Speaker>::iterator iter = Round1.begin(); iter != Round1.end(); iter++)
		{
			(*iter).PrintID();
		}
		std::cout << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
	}
	else if (this->Round == 2)
	{
		std::random_shuffle(Round2.begin(), Round2.end());//�������
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


//������������Speaker��m_Grade��С��ѡ�ֽ��з�������
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


//��������
void Manager::RoundOneBegin()
{
	std::cout << "----------------��" << this->Round << "�ֱ�����ʼ-----------------" << std::endl;
	
	//ͳ������һ��,������ʱ����
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

	//��������ѡ�ֿ�ʼ����
	for (std::vector<Speaker>::iterator iter = v_Src.begin(); iter != v_Src.end(); iter++)
	{
		num++;
		double score;

		//��ί���
		std::deque<double>d;//�洢����������
		for (int i = 0; i < 10; i++)
		{
		    score = (rand() % 401 + 600) / 10.0f;	//600~1000
			//printf("%.1f ", score);//��ӡ����
			d.push_back(score);

		}
		sort(d.begin(),d.end(),std::greater<double>());//����
		d.pop_front();//ȥ����߷֣���ͷ�
		d.pop_back();
		double sum = std::accumulate(d.begin(), d.end(),0.0f);//�ܷ�
		double avg = sum / (double)d.size();//ƽ����
		
		//���ɼ����ݱ�������¼��
		(*iter).SetGrade(avg,*this);
		if (this->Round == 1)
		{
			Round1 = v_Src;
		}
		else if (this->Round == 2)
		{
			Round2 = v_Src;
		}
		if (this->Round == 1)//��һ�ֵĴ���
		{
			//ÿ����ȡǰ����
			if (num % 6 == 0)
			{
				std::cout << std::endl;
				std::cout << std::endl;
				std::cout << "��" << num / 6 << "С�������������:" << std::endl;
				if (num / 6 == 1)//�����һ��
				{
					VectorBubble(*this);

					//Test Code,�����Ƿ���ȷ����
					for (size_t u = 0; u < this->Round1.size()/2; u++)
					{
						this->Round1[u].PrintName();
						std::cout << "�ĳɼ���:";
						this->Round1[u].PrintGrade(*this);

					}
					//ȡ�ߵ�һ���ǰ���������ݵ�ǰ�����ִν�������µ�������
					for (size_t q = 0; q < 3; q++)
					{
						this->Round2.push_back(this->Round1[q]);
					}
				}

				else if (num / 6 == 2)//����ڶ���
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
						std::cout << "�ĳɼ���:";
						this->Round1[u].PrintGrade(*this);

					}
					//ȡ�ߵ�һ���ǰ���������ݵ�ǰ�����ִν�������µ�������
					for (size_t q = 6; q < 9; q++)
					{
						this->Round2.push_back(this->Round1[q]);
					}

				}
			}
			//	std::cout << std::endl;
		}
		else if (this->Round == 2)//�ڶ��ִ���
		{
			if (num % 6 == 0)
			{
				std::cout << std::endl;
				std::cout << std::endl;
				std::cout << "�ڶ��ֱ����������£�" << std::endl;
				if (num / 6 == 1)
				{
					VectorBubble(*this);
					for (size_t u = 0; u < this->Round2.size(); u++)
					{
						this->Round2[u].PrintName();
						std::cout << "�ĳɼ���";
						this->Round2[u].PrintGrade(*this);
					}
					//ȡ��ǰ�������������Ǽ���
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
		std::cout << "��" << this->Round << "�ֱ�����ϣ�����ѡ�ֽ�������һ�ֱ�����"<<std::endl;
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
		std::cout << "��" << this->Round << "���ֱ�������ϣ����������Ǽ���" << std::endl;
	}

}

//�ϴ�ѡ����Ϣ
void Manager::UpLoadContestors(const Speaker& spkr)
{
	this->Round1.push_back(spkr);
}

void Manager::SaveRecord()
{
	std::ofstream Out;
	Out.open("FormerRecord.csv",std::ios::out|std::ios::app);//��׷�ӵķ�ʽд�ļ�

	//��ÿ��ѡ�ֵ�����д���ļ���
	for (std::vector<Speaker>::iterator iter = this->Final.begin(); iter != this->Final.end(); iter++)
	{
		Out << iter->m_name << "," << iter->GeadeArray[1] << ", ";
	}
	Out << std::endl;
	Out.close();
	std::cout << "�ļ���¼���" << std::endl;
}

void Manager::CheckRecord()
{
	std::ifstream In("FormerRecord.csv", std::ios::in);
	if (!In.is_open())
	{
		std::cout << "�ļ�������" << std::endl;
		//this->FileEmpty() = true;
		In.close();
		return;
	}
	
	//�ļ����
	char ch;
	In >> ch;
	if (In.eof())
	{
		//this->FileEmpty() = true;
		std::cout << "�ļ���" << std::endl;		
		In.close();
		return;
	}
	//�ļ�����
	//this->FileEmpty() = false;
	In.putback(ch);//���ղŶ�ȡ�ĵ����ַ��ջ�

	std::string data;
	int index = 0;
	while (In >> data)
	{
		std::vector<std::string> v;//�������string�ַ���
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
		std::cout << (iter->first)/3+1 << "���ױ�ţ� " << iter->second[0] << " ���� " << iter->second[1] << std::endl;
	}
	std::cout << std::endl;
}

void Manager::ShowRecord()
{
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		std::cout << "��" << i + 1 << "��Ĺھ�Ϊ:" << this->m_Record[i][0] << " �÷� " << this->m_Record[i][1] << " "
			<< "�Ǿ�Ϊ:" << this->m_Record[i][2] << " �÷� " << this->m_Record[i][3] << " "
			<< "����Ϊ:" << this->m_Record[i][4] << " �÷� " << this->m_Record[i][5] << " "
			<< std::endl;
	}
	system("pause");
	system("cls");
}

void Manager::ClearRecord()
{
	std::cout << "ȷ��Ҫ�����ʷ��¼��" << std::endl;
	std::cout << "Press 1 to confirm" << std::endl;
	std::cout << "Press 2 to cancal" << std::endl;
	int Select = 0;
	std::cin >> Select;
	if (Select == 1)
	{
		std::ofstream ofs("FormerRecord.csv", std::ios::trunc);
		ofs.close();
		std::cout << "��ճɹ�" << std::endl;
	}
		system("pause");
		system("cls");
}
/**************************************************************************************************************/


//ѡ�ֹ��캯��

Speaker::Speaker(int i)
{
	this->m_name = "ѡ��" + this->NameSeed[i];
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

//ѡ�����ã���ӡ����ȡ�ɼ�����
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

//ѡ����������
Speaker::~Speaker()
{
	;
}

//Speaker::Speaker()
//{
//	for (int i = 0; i < 12; i++)
//	{
//		this->m_name = "ѡ��" + this->NameSeed[i];
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
