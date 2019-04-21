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
	int i, j;
	Schedule **shift = new Schedule*[10];
	for (i = 0; i < 10; i++)
	{
		shift[i] = new Schedule[10];
	}
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			shift[i][j].path_number = 0;
		}
	}
	ifstream in;
	in.open("C://Users/84101/Desktop/tabledata.txt");
	if (in.is_open())
	{
		while (!in.eof())
		{
			string from, to;
			in >> from >> to;
			if (from == "北京") i = 0;
			else if (from == "上海") i = 1;
			else if (from == "广州") i = 2;
			else if (from == "厦门") i = 3;
			else if (from == "重庆") i = 4;
			else if (from == "拉萨") i = 5;
			else if (from == "乌鲁木齐") i = 6;
			else if (from == "武汉") i = 7;
			else if (from == "南京") i = 8;
			else if (from == "哈尔滨") i = 9;
			if (to == "北京") j = 0;
			else if (to == "上海") j = 1;
			else if (from == "广州") j = 2;
			else if (from == "厦门") j = 3;
			else if (from == "重庆") j = 4;
			else if (from == "拉萨") j = 5;
			else if (from == "乌鲁木齐") j = 6;
			else if (from == "武汉") j = 7;
			else if (from == "南京") j = 8;
			else if (from == "哈尔滨") j = 9;
			in >> shift[i][j].path[shift[i][j].path_number].traffic >> shift[i][j].path[shift[i][j].path_number].begin_time >> shift[i][j].path[shift[i][j].path_number].end_time >> shift[i][j].path[shift[i][j].path_number].cost >> shift[i][j].path[shift[i][j].path_number].time_used;
			shift[i][j].path_number++;
		}
	}
	else
	{
		cout << "Erroer:open txt failed" << endl;
	}
	in.close();
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			cout << " " << i << " " << j << " " << shift[i][j].path_number;
		}
		cout << endl;
	}
}
