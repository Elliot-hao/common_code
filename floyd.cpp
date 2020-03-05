#include <iostream>
#include<cstring>
#include<windows.h>
using namespace std;

#define MaxVnum 100  //���������ֵ
const int INF=1e7; // �����10000000

typedef string VexType;  //������������ͣ�������Ҫ����
typedef int EdgeType;  //����Ȩֵ���������ͣ�������Ȩֵ��ͼ����Ϊ0��1
typedef struct{
  VexType Vex[MaxVnum];
  EdgeType Edge[MaxVnum][MaxVnum];
  int vexnum,edgenum; //������������
}AMGragh;

int dist[MaxVnum][MaxVnum],p[MaxVnum][MaxVnum];

int locatevex(AMGragh G,VexType x)
{
    for(int i=0;i<G.vexnum;i++)//���Ҷ�����Ϣ���±�
       if(x==G.Vex[i])
        return i;
    return -1;//û�ҵ�
}

void CreateAMGraph(AMGragh &G)//��������ͼ���ڽӾ���
{
    int i,j,w;
    VexType u,v;
    cout << "�����붥������"<<endl;
    cin>>G.vexnum;
    cout << "���������:"<<endl;
    cin>>G.edgenum;
    cout << "�����붥����Ϣ:"<<endl;
    for(int i=0;i<G.vexnum;i++)//���붥����Ϣ�����붥����Ϣ����
        cin>>G.Vex[i];
    for(int i=0;i<G.vexnum;i++)//��ʼ���ڽӾ�������ֵΪ0�������������ʼ��Ϊ�����
      for(int j=0;j<G.vexnum;j++)
        if(i!=j)
            G.Edge[i][j]=INF;
        else
            G.Edge[i][j]=0; //ע��i==jʱ������Ϊ0
    cout << "������ÿ�����������������㼰Ȩֵ��"<<endl;
    while(G.edgenum--)
    {
       cin>>u>>v>>w;
       i=locatevex(G,u);//���Ҷ���u�Ĵ洢�±�
       j=locatevex(G,v);//���Ҷ���v�Ĵ洢�±�
       if(i!=-1&&j!=-1)
         G.Edge[i][j]=w; //����ͼ�ڽӾ���洢Ȩֵ
    }
}

void Floyd(AMGragh G) //��Floyd�㷨��������G�и��Զ���i��j֮������·��
{
   	int i,j,k;
    for(i=0;i<G.vexnum;i++)          		//���Խ��֮���ʼ��֪·��������
      for(j=0;j<G.vexnum;j++)
      {
          dist[i][j]=G.Edge[i][j];
          if(dist[i][j]<INF && i!=j)
             p[i][j]=i;  	//���i��j֮���л�����j��ǰ����Ϊi
          else p[i][j]=-1;  //���i��j֮���޻�����j��ǰ����Ϊ-1
      }
	for(k=0;k<G.vexnum; k++)
		for(i=0;i<G.vexnum; i++)
			for(j=0;j<G.vexnum; j++)
				if(dist[i][k]+dist[k][j]<dist[i][j])//��i��k��j��һ��·������
                {
					dist[i][j]=dist[i][k]+dist[k][j]; //����dist[i][j]
					p[i][j]=p[k][j];       //����j��ǰ��Ϊk
				}
}

void print(AMGragh G)
{
    int i,j;
    for(i=0;i<G.vexnum;i++)//�����̾�������
    {
        for(j=0;j<G.vexnum;j++)
            cout<<dist[i][j]<<"\t";
        cout<<endl;
    }
    cout<<endl;
    for(i=0;i<G.vexnum;i++)//���ǰ������
    {
        for(j=0;j<G.vexnum;j++)
            cout<<p[i][j]<<"\t";
        cout<<endl;
    }
}

void DisplayPath(AMGragh G,int s,int t )//��ʾ���·��
{
	if(p[s][t]!=-1)
    {
		DisplayPath(G,s,p[s][t]);
		cout<<G.Vex[p[s][t]]<<"-->";
	}
}

int main()
{
    VexType start,destination;
    int u,v;
    system("color 0d");
    AMGragh G;
    CreateAMGraph(G);
    Floyd(G);
    print(G);
	cout<<"����������·����������յ�����ƣ�";
	cin>>start>>destination;
	u=locatevex(G,start);
	v=locatevex(G,destination);
	DisplayPath(G,u,v);
	cout<<G.Vex[v]<<endl;
	cout<<"���·���ĳ���Ϊ��"<<dist[u][v]<<endl;
	cout<<endl;
    return 0;
}