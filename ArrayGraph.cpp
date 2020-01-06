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
	cout << "��ѧ�ƻ�����ϵͳ������" << endl;
	cout << "������ѧ��ѧ������: " << endl;
	cin >> all_terms;
	cout << "������ÿѧ�ڵ�ѧ������ֵ: " << endl;
	cin >> t_max_xf;
	cout << "�������ܿγ���: " << endl;
	cin >> t_V;
	cout << "����������γ̵����޿γ̵��ܺ�: " << endl;//�ܱ���
	cin >> t_E;
	cout << "����������γ̵Ŀγ̺�" << endl;
	node data;
	for (i = 1; i <= t_V; i++)
	{
		cout << "�������" << i << "���γ̺�: ";
		cin >> data.name;
		G[i].push_back(data);
		mp[G[i][0].name] = i;
	}
	cout << "������" << t_V << "���γ̵�ѧ��ֵ:" << endl;
	for (i = 1; i <= t_V; i++) cin >> G[i][0].xf;
	cout << "��������ѡ�γ̵����޿γ�(��û��������#)" << endl;
	char s[33];
	for (i = 1; i <= t_V; i++)
	{
		cout << G[i][0].name << "�����޿γ�:";
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
	cout << "����������ͼ" << endl;
	cout << "������" << t_V << "������:" << endl;
	for (i = 1; i <= t_V; ++i)
		cout << G[i][0].name << endl;
	cout << "������" << t_E << "������:" << endl;
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
		cout << "�ڵ�" << q << "��ѧ��Ӧѡ����޿γ�: ";
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
		cout << "�ڵ�" << q << "��ѧ��Ӧѡ����޿γ�: ";
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
			cout << "��ѡ��ϵͳ����:" << endl;
			cout << "1.ƽ������" << endl;
			cout << "2.��ǰ����" << endl;
			cout << "3.�˳�" << endl;
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


