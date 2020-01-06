#include<iostream>
#include<map>
#include<vector>
#include<stack>
using namespace std;

struct node
{
	char name[33];
	int xf;
};

int all_terms, t_max_xf, t_V, t_E;
vector<node> G[1009];
map<string, int> mp;

void create_graph()
{
	int i;
	cout << "教学计划编制系统已载入" << endl;
	cout << "请输入学生学期总数: " << endl;
	cin >> all_terms;
	cout << "请输入每学期的学分上限值: " << endl;
	cin >> t_max_xf;
	cout << "请输入总课程数: " << endl;
	cin >> t_V;
	cout << "请输入各个课程的先修课程的总和: " << endl;//总边数
	cin >> t_E;
	cout << "请输入各个课程的课程号" << endl;
	node data;
	for (i = 1; i <= t_V; i++)
	{
		cout << "请输入第" << i << "个课程号: ";
		cin >> data.name;
		G[i].push_back(data);
		mp[G[i][0].name] = i;
	}
	cout << "请输入" << t_V << "个课程的学分值:" << endl;
	for (i = 1; i <= t_V; i++) cin >> G[i][0].xf;
	cout << "请输入所选课程的先修课程(如没有请输入#)" << endl;
	char s[33];
	for (i = 1; i <= t_V; i++)
	{
		cout << G[i][0].name << "的先修课程:";
		while (true)
		{
			cin >> s;
			if (s[0] == '#') break;
			G[i].push_back(G[mp[s]][0]);
		}
	}
}

void display()
{
	int i, j;
	cout << "已生成有向图" << endl;
	cout << "共生成" << t_V << "个顶点:" << endl;
	for (i = 1; i <= t_V; ++i)
		cout << G[i][0].name << endl;
	cout << "共生成" << t_E << "条连接:" << endl;
	for (i = 1; i <= t_V; i++)
	{
		int k = G[i].size();
		for (j = 0; j < k; j++)
			cout << G[i][0].name << "-->" << G[i][j].name << endl;
	}
}

void solve1(int ans[])
{
	int q = 1, cnt = 0;
	while (q <= all_terms)
	{
		int num = t_V / all_terms;
		cout << "在第" << q << "个学期应选择进修课程: ";
		while (num--)
		{
			cout << G[ans[cnt++]][0].name << "  ";
		}
		if (q == all_terms) printf("OK Over!\n");
		q++;
	}
}

void solve2(int ans[])
{
	int q = 1, cnt = 0;
	while (q <= all_terms)
	{
		int C = G[ans[cnt]][0].xf;
		cout << "在第" << q << "个学期应选择进修课程: ";
		while (cnt < t_V && C <= t_max_xf)
		{
			cout << G[ans[cnt]][0].name<<"  ";
			if (cnt + 1 < t_V) C = C + G[ans[cnt + 1]][0].xf;
			cnt++;
		}
		if (cnt >= t_V || q == all_terms)
		{
			cout << endl;
			break;
		}
		q++;
	}
}

void topo_sort()
{
	int i, j, vis[1009];
	memset(vis, 0, sizeof(vis));
	for (i = 1; i <= t_V; i++)
	{
		int k = G[i].size();
		for (j = 1; j < k; j++)
			vis[mp[G[i][j].name]]++;
	}
	int ans[1009], cnt = 0;
	memset(ans, 0, sizeof(ans));
	stack<int> s;
	for (i = 1; i <= t_V; i++)
	{
		if (!vis[i]) s.push(i);
	}
	while (!s.empty())
	{
		int cur = s.top(); s.pop();
		ans[cnt++] = cur;
		int k = G[cur].size();
		for (j = 1; j < k; j++)
		{
			int num = mp[G[cur][j].name];
			vis[num]--;
			if (!vis[num]) s.push(num);
		}
	}
	if (cnt != t_V) cout << "Error!";
	else
	{
		while (true)
		{
			cout << "请选择系统功能:" << endl;
			cout << "1.平均分配" << endl;
			cout << "2.靠前分配" << endl;
			cout << "3.退出" << endl;
			int sel;
			cin >> sel;
			switch (sel)
			{
			case 1: solve1(ans); break;
			case 2: solve2(ans); break;
			}
			if (sel == 3) break;
		}
	}
}

int main()
{
	create_graph();
	display();
	topo_sort();
	return 0;
}


