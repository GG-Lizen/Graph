#include"Graphhead.h"
#include"Lqueue.h"




Status visit_char(VexType v) {
	printf("%c ", v);
	return  OK;
}

Status isExist(VexType vexs[],VexType v ,int n,int &index){//插入的数组 插入的数据，已插入结点数 存在返回位序，不存在返回-1
	if (vexs == NULL || n < 0) return ERROR;
	for (int i = 0; i < n; i++) {
		if (vexs[i] == v) {
			index = i;
			return OK;
		}
	}
	index= -1;
	return OK;
}

//-------------------UI-------------------//

int main() {
	int i, k, j, flag = 1;
	ALGraph G;
	G.tags = NULL;
	G.vexs = NULL;
	int n=0, e=0;//边数 弧数
	VexType vexs[MAXSIZE];
	ArcInfo infos[MAXSIZE];
	char in, in2;
	AdjVexNodeP p;
	VexNode v;
	int** array;//用于构造邻接矩阵
	////-----TEST
	//ALGraph TEST_G;
	//VexType TEST_vexs[] = {'A','B','C','D'};
	//CreateGraph_AL(TEST_G, UDG, TEST_vexs, 4, infos, 0);
	////-----TEST-END
	while (flag)
	{
		printf("                           | --------------------------------- |\n");
		printf("                           | ----------    菜单选择    ------- |\n");
		printf("                           | --------------------------------- |\n");
		printf("                           | -------1--创建无边的无向图------- |\n");
		printf("                           | -------2--  广度优先遍历  ------- |\n");
		printf("                           | -------3--  深度优先遍历  ------- |\n");
		printf("                           | -------4--  添加边        ------- |\n");
		printf("                           | -------5--  删除边        ------- |\n");
		printf("                           | -------6--  销毁图        ------- |\n");
		printf("                           | -------7--  增加结点      ------- |\n");
		printf("                           | -------8--  删除结点      ------- |\n");
		printf("                           | -------9--  图的邻接矩阵  ------- |\n");
		printf("                           | -------0--  退出程序      ------- |\n");
		printf("                           | --------------------------------- |\n");
		printf("\n");
		printf("                            请输入你的选择：");
		scanf(" %c", &in);//加空格过滤回车
		getchar();
		switch (in) {
		case '0':flag = 0;
			break;
		case '1':
			//创建无向图
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------创建无边的无向图-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			while (true)//输入错误可重新输入
			{
				printf("                            请输入结点数：");
				n = 0;//重置n
				scanf(" %d", &n);
				getchar();
				//判断输入
				if (n <= 0) {
					printf("请输入大于0的整数\n");
					continue;
				}
				if (n > MAXSIZE) {
					printf("生而为程序，我很抱歉！结点数过大！\n");
					continue;
				}
				//判断输入end
				k = 0;
				for (i = 0; i < n; i++)
				{
					while (true)
					{
						printf("                            请输入第%d个结点：", i + 1);
						scanf(" %c", &in);
						getchar();
						if (isExist(vexs, in, k, j) == ERROR)
						{
							printf("ERROR!");//出错程序终止
							return 0;
						}
						else if (-1 == j) {//判断结点是否已经存在
							vexs[k] = in;
							k++;
						}
						else
						{
							printf("                            %c 结点已存在\n", in);
							continue;
						}

						break;
					}
				}
					CreateGraph_AL(G, UDG, vexs, n, infos, 0);
					printf("                            创建成功！\n");
					break;
				}

				//
				break;
		case '2':
			//广度优先遍历
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------**广度优先遍历**-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			printf("                            ");
			BFSTraverse_AL(G, visit_char);
			printf("\n");
			system("pause");
			//
			break;
		case '3':
			//深度优先遍历
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------**深度优先遍历**-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			printf("                            ");
			DFSTraverse_AL(G, visit_char);
			printf("\n");
			system("pause");

			//
			break;
		case '4':
			//添加边
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------*****添加边*****-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			while (true)
			{
				if ( n<= 0) {
					printf("                            顶点不存在，请先构建图\n");
					break;
				}

				printf(" 请输入边 逗号隔开(输入 -,- 退出)：");
				scanf(" %c,%c", &in, &in2);
				getchar();

				
				if (in == '-' && in2 == '-')break;
				j = LocateVex_AL(G, in);
				if (-1 == j) {//判断结点是否已经存在
					printf("                            第一个结点 %c 不存在，请重新输入\n", in);
					continue;
				}

				j = LocateVex_AL(G,in2);
				 if (-1 == j) {//判断结点是否已经存在
					printf("                            第二个结点 %c 不存在，请重新输入\n", in2);
					continue;
				}
				if (AddArc_AL(G, LocateVex_AL(G, in), LocateVex_AL(G, in2), 1))
					printf("                            插入成功\n");
				else printf("                            插入失败\n");
			}
			//
			break;
		case '5':
			//删除边
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------*****删除边*****-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			while (true)
			{
				printf(" 请输入边  逗号隔开 (输入 -,- 退出)：");
				scanf(" %c,%c", &in,&in2);
				getchar();
				if (in == '-' && in2 == '-')break;

				j = LocateVex_AL(G, in);
				if (-1 == j) {//判断结点是否已经存在
					printf("                            第一个结点 %c 不存在，请重新输入\n", in);
					continue;

				}

				j = LocateVex_AL(G, in2);
				if (-1 == j) {//判断结点是否已经存在
					printf("                            第二个结点 %c 不存在，请重新输入\n", in2);
					continue;
				}
				if (RemoveArc_AL(G, LocateVex_AL(G, in), LocateVex_AL(G, in2)))
					printf("                            删除成功\n");
				else printf("                            删除失败\n");
			
			}

			break;
		case '6':
			//销毁图
			if (n <= 0) {
				printf("\n");
				printf("                            图已销毁\n");
				break;
			}
			if (DestroyGraph_AL(G)) printf("                            销毁成功\n");
			else printf("                            图不存在\n");
			n = 0;
			//
			break;
	
		case'7':
			//增加顶点
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------****增加顶点****-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			while (true)
			{
				printf("请输入要增加的顶点(输入 - 退出)：");
				scanf(" %c", &in);
				getchar();
				if (in == '-')break;
				j = LocateVex_AL(G, in);
				if (-1 != j) {//判断结点是否已经存在
					printf("                            结点 %c 已存在，请重新输入\n", in);
					continue;
				}
				else
				{
					v.data = in;
					v.firstArc = NULL;
					if(!ADDVexNode_AL(G, v))printf("                            添加失败\n");
					else printf("                            添加成功\n");
				}

			}
			//
			break;
		case'8':
			//删除顶点
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------****删除顶点****-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			while (true)
			{
				printf("请输入要删除的顶点(输入 - 退出)：");
				scanf(" %c", &in);
				getchar();
				if (in == '-')break;
				j = LocateVex_AL(G, in);
				if (-1 == j) {//判断结点是否存在
					printf("                            结点 %c 不存在，请重新输入\n", in);
					continue;
				}
				else {
					if (!RemoveVexNode_AL(G, j, v)) printf("                            删除失败\n");
					else printf("                            删除成功\n");
				}

			}
			//
			break;
		case '9':
			//查看图的邻接矩阵
			if (n <= 0) {
				printf("\n");
				printf("                            无顶点请先创建图\n");
				break;
			}
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------**图的邻接矩阵**-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			
			if (NULL == (array = (int**)malloc(G.n * sizeof(int*)))) return OVERFLOW;
			for (i = 0; i < G.n; i++) {
				if (NULL == (array[i] = (int*)malloc(G.n * sizeof(int)))) return OVERFLOW;
			}
			for (i = 0; i < G.n; i++) {
				for (j = 0; j < G.n; j++)
					array[i][j] = 0;
			}
			for (i = 0; i < G.n; i++) {
				 p= G.vexs[i].firstArc;
				 while (p != NULL) {
					 array[i][p->adjvex] = p->info;
					 NextAdjvex_AL(G, i, p);
				}

			}
			printf("                           \\ ");
			for (i = 0; i < G.n; i++) {
				printf("%c ", G.vexs[i].data);
			}
			printf("\n");
			for (i = 0; i < G.n; i++) {
				printf("                           %c ", G.vexs[i].data);
				for (j = 0; j < G.n; j++)
					printf("%d ", array[i][j]);
				printf("\n");
			}
			break;
			//
			//
		case 'a'://隐藏功能[狗头]
			if (n <= 0) {
				printf("\n");
				printf("                            无顶点请先创建图\n");
				break;
			}
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-------------**最短路径**-------------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			while (true)
			{
				printf("请输入起点:\n");
				scanf(" %c", &in);
				i=LocateVex_AL(G, in);
				if (-1 == i) {//判断结点是否存在
					printf("                            结点 %c 不存在，请重新输入\n", in);
					continue;
				}
				break;
			}
			Dijkstra(G,i,Dist);
			while (true)
			{
				printf("请输入起点:\n");
				scanf(" %c", &in);
				j = LocateVex_AL(G, in);
				if (-1 == j) {//判断结点是否存在
					printf("                            结点 %c 不存在，请重新输入\n", in);
					continue;
				}
				break;
			}
			printf("最短路径如下\n");
			Outputpath(G,Dist,j);
			break;
			//
		default: printf("                            输入错误\n");
	
			}

		}

	}



//------------------END-------------------//



//__________________________________无向图测试__________________________________//
//int main() {
//	int i;
//	ALGraph G;
//	int n = 4, e = 4;//边数 弧数
//	VexType vexs[] = { 'A','B','C','D' };
//	ArcInfo* info;
//	info = (ArcInfo*)malloc(n*sizeof(ArcInfo));
//	//初始化 info数组
//	for (i = 0; i < n; i++)
//	{
//		ArcInfo a;
//		a.v = 'A' + i;
//		a.w = 'A' + i + 1;
//		if (a.w == 'A' + n)a.w = 'A';
//		info[i] = a;
//	}
//
//
//	CreateGraph_AL(G, UDG, vexs, n, info, e);
//	for (i = 0; i < G.n; i++) visit_char(G.vexs[i].data);
//	printf("%d\t%d\t%d\t%d\t", LocateVex_AL(G, 'A'), LocateVex_AL(G, 'B'), LocateVex_AL(G, 'C'), LocateVex_AL(G, 'D'));
//	printf("\n");
//	DFSTraverse_AL(G, visit_char);
//	printf("\n");
//	BFSTraverse_AL(G, visit_char);
//
//	RemoveArc_AL(G, LocateVex_AL(G, 'A'), LocateVex_AL(G, 'D'));
//	printf("\n");
//	DFSTraverse_AL(G, visit_char);
//	printf("\n");
//	BFSTraverse_AL(G, visit_char);
//
//	AddArc_AL(G, LocateVex_AL(G, 'A'), LocateVex_AL(G, 'C'),1);
//	printf("\n");
//	DFSTraverse_AL(G, visit_char);
//	printf("\n");
//	BFSTraverse_AL(G, visit_char);
//}

//for (i = 0; i < n; i++)
//{
//
//	printf("请输入边：");
//	scanf("%c%c", &in, &in2);
//	getchar();
//	if (isExist(vexs, in, k, j) == ERROR)
//	{
//		printf("ERROR!");//出错程序终止
//		return 0;
//	}
//	else if (-1 == j) {//判断结点是否已经存在
//		vexs[k] = in;
//		k++;
//	}
//
//	if (isExist(vexs, in2, k, j) == ERROR)
//	{
//		printf("ERROR!");//出错程序终止
//		return 0;
//	}
//	else if (-1 == j) {
//		vexs[k] = in2;
//		k++;
//	}
//
//
//	infos[i].info = 1;
//	infos[i].v = in;
//	infos[i].w = in2;
//
//}


