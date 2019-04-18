#include"struct.hpp"
/****************************************************
0 北京
1 上海
2 广州
3 哈尔滨
4 沈阳
5 重庆
6 西安
7 昆明
8 拉萨
9 乌鲁木齐
*****************************************************/

void PutSchedule()
{
	Schedule **shift;
	int i, j;
	Schedule shift = new Schedule*[10];
	for (i=0; i<10 ; i++)
	{
		shift[i] = new Schedule[10];
	}
	ifstream fin("pathdata.txt");
	if (!fin.is_open())
	{
		cout<<"Error: opening file fail"<<endl;
		exit(1);
	}
	else
	{
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				fin >> shift[i][j].path_number;
			}
		}
	}
	fin.close();
	int n = 0;
	ifstream fins("tabledata.txt");
	if (!fins.is_open())
	{
		cout << "Error: opening file fail" << endl;
		exit(1);
	}
	else
	{
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				for (int x = 0; x < shift[i][j].path_number; x++)
				{
					in >> shift[i][j].path[n].traffic >> shift[i][j].path[n].from >> shift[i][j].path[n].begin_time >> shift[i][j].path[n].to >> shift[i][j].path[n].end_time >> shift[i][j].path[n].cost >> shift[i][j].path[n].time_used;
					n++;
				}
			}
		}
	}
	fins.close();
}
