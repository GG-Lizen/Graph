#include"Graphhead.h"
#include"Lqueue.h"




Status visit_char(VexType v) {
	printf("%c ", v);
	return  OK;
}

Status isExist(VexType vexs[],VexType v ,int n,int &index){//��������� ��������ݣ��Ѳ������� ���ڷ���λ�򣬲����ڷ���-1
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
	int n=0, e=0;//���� ����
	VexType vexs[MAXSIZE];
	ArcInfo infos[MAXSIZE];
	char in, in2;
	AdjVexNodeP p;
	VexNode v;
	int** array;//���ڹ����ڽӾ���
	////-----TEST
	//ALGraph TEST_G;
	//VexType TEST_vexs[] = {'A','B','C','D'};
	//CreateGraph_AL(TEST_G, UDG, TEST_vexs, 4, infos, 0);
	////-----TEST-END
	while (flag)
	{
		printf("                           | --------------------------------- |\n");
		printf("                           | ----------    �˵�ѡ��    ------- |\n");
		printf("                           | --------------------------------- |\n");
		printf("                           | -------1--�����ޱߵ�����ͼ------- |\n");
		printf("                           | -------2--  ������ȱ���  ------- |\n");
		printf("                           | -------3--  ������ȱ���  ------- |\n");
		printf("                           | -------4--  ��ӱ�        ------- |\n");
		printf("                           | -------5--  ɾ����        ------- |\n");
		printf("                           | -------6--  ����ͼ        ------- |\n");
		printf("                           | -------7--  ���ӽ��      ------- |\n");
		printf("                           | -------8--  ɾ�����      ------- |\n");
		printf("                           | -------9--  ͼ���ڽӾ���  ------- |\n");
		printf("                           | -------0--  �˳�����      ------- |\n");
		printf("                           | --------------------------------- |\n");
		printf("\n");
		printf("                            ���������ѡ��");
		scanf(" %c", &in);//�ӿո���˻س�
		getchar();
		switch (in) {
		case '0':flag = 0;
			break;
		case '1':
			//��������ͼ
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------�����ޱߵ�����ͼ-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			while (true)//����������������
			{
				printf("                            ������������");
				n = 0;//����n
				scanf(" %d", &n);
				getchar();
				//�ж�����
				if (n <= 0) {
					printf("���������0������\n");
					continue;
				}
				if (n > MAXSIZE) {
					printf("����Ϊ�����Һܱ�Ǹ�����������\n");
					continue;
				}
				//�ж�����end
				k = 0;
				for (i = 0; i < n; i++)
				{
					while (true)
					{
						printf("                            �������%d����㣺", i + 1);
						scanf(" %c", &in);
						getchar();
						if (isExist(vexs, in, k, j) == ERROR)
						{
							printf("ERROR!");//���������ֹ
							return 0;
						}
						else if (-1 == j) {//�жϽ���Ƿ��Ѿ�����
							vexs[k] = in;
							k++;
						}
						else
						{
							printf("                            %c ����Ѵ���\n", in);
							continue;
						}

						break;
					}
				}
					CreateGraph_AL(G, UDG, vexs, n, infos, 0);
					printf("                            �����ɹ���\n");
					break;
				}

				//
				break;
		case '2':
			//������ȱ���
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------**������ȱ���**-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			printf("                            ");
			BFSTraverse_AL(G, visit_char);
			printf("\n");
			system("pause");
			//
			break;
		case '3':
			//������ȱ���
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------**������ȱ���**-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			printf("                            ");
			DFSTraverse_AL(G, visit_char);
			printf("\n");
			system("pause");

			//
			break;
		case '4':
			//��ӱ�
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------*****��ӱ�*****-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			while (true)
			{
				if ( n<= 0) {
					printf("                            ���㲻���ڣ����ȹ���ͼ\n");
					break;
				}

				printf(" ������� ���Ÿ���(���� -,- �˳�)��");
				scanf(" %c,%c", &in, &in2);
				getchar();

				
				if (in == '-' && in2 == '-')break;
				j = LocateVex_AL(G, in);
				if (-1 == j) {//�жϽ���Ƿ��Ѿ�����
					printf("                            ��һ����� %c �����ڣ�����������\n", in);
					continue;
				}

				j = LocateVex_AL(G,in2);
				 if (-1 == j) {//�жϽ���Ƿ��Ѿ�����
					printf("                            �ڶ������ %c �����ڣ�����������\n", in2);
					continue;
				}
				if (AddArc_AL(G, LocateVex_AL(G, in), LocateVex_AL(G, in2), 1))
					printf("                            ����ɹ�\n");
				else printf("                            ����ʧ��\n");
			}
			//
			break;
		case '5':
			//ɾ����
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------*****ɾ����*****-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			while (true)
			{
				printf(" �������  ���Ÿ��� (���� -,- �˳�)��");
				scanf(" %c,%c", &in,&in2);
				getchar();
				if (in == '-' && in2 == '-')break;

				j = LocateVex_AL(G, in);
				if (-1 == j) {//�жϽ���Ƿ��Ѿ�����
					printf("                            ��һ����� %c �����ڣ�����������\n", in);
					continue;

				}

				j = LocateVex_AL(G, in2);
				if (-1 == j) {//�жϽ���Ƿ��Ѿ�����
					printf("                            �ڶ������ %c �����ڣ�����������\n", in2);
					continue;
				}
				if (RemoveArc_AL(G, LocateVex_AL(G, in), LocateVex_AL(G, in2)))
					printf("                            ɾ���ɹ�\n");
				else printf("                            ɾ��ʧ��\n");
			
			}

			break;
		case '6':
			//����ͼ
			if (n <= 0) {
				printf("\n");
				printf("                            ͼ������\n");
				break;
			}
			if (DestroyGraph_AL(G)) printf("                            ���ٳɹ�\n");
			else printf("                            ͼ������\n");
			n = 0;
			//
			break;
	
		case'7':
			//���Ӷ���
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------****���Ӷ���****-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			while (true)
			{
				printf("������Ҫ���ӵĶ���(���� - �˳�)��");
				scanf(" %c", &in);
				getchar();
				if (in == '-')break;
				j = LocateVex_AL(G, in);
				if (-1 != j) {//�жϽ���Ƿ��Ѿ�����
					printf("                            ��� %c �Ѵ��ڣ�����������\n", in);
					continue;
				}
				else
				{
					v.data = in;
					v.firstArc = NULL;
					if(!ADDVexNode_AL(G, v))printf("                            ���ʧ��\n");
					else printf("                            ��ӳɹ�\n");
				}

			}
			//
			break;
		case'8':
			//ɾ������
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------****ɾ������****-----------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			while (true)
			{
				printf("������Ҫɾ���Ķ���(���� - �˳�)��");
				scanf(" %c", &in);
				getchar();
				if (in == '-')break;
				j = LocateVex_AL(G, in);
				if (-1 == j) {//�жϽ���Ƿ����
					printf("                            ��� %c �����ڣ�����������\n", in);
					continue;
				}
				else {
					if (!RemoveVexNode_AL(G, j, v)) printf("                            ɾ��ʧ��\n");
					else printf("                            ɾ���ɹ�\n");
				}

			}
			//
			break;
		case '9':
			//�鿴ͼ���ڽӾ���
			if (n <= 0) {
				printf("\n");
				printf("                            �޶������ȴ���ͼ\n");
				break;
			}
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-----------**ͼ���ڽӾ���**-----------|\n");
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
		case 'a'://���ع���[��ͷ]
			if (n <= 0) {
				printf("\n");
				printf("                            �޶������ȴ���ͼ\n");
				break;
			}
			system("cls");
			printf("                           |--------------------------------------|\n");
			printf("                           |-------------**���·��**-------------|\n");
			printf("                           |--------------------------------------|\n");
			printf("\n");
			while (true)
			{
				printf("���������:\n");
				scanf(" %c", &in);
				i=LocateVex_AL(G, in);
				if (-1 == i) {//�жϽ���Ƿ����
					printf("                            ��� %c �����ڣ�����������\n", in);
					continue;
				}
				break;
			}
			Dijkstra(G,i,Dist);
			while (true)
			{
				printf("���������:\n");
				scanf(" %c", &in);
				j = LocateVex_AL(G, in);
				if (-1 == j) {//�жϽ���Ƿ����
					printf("                            ��� %c �����ڣ�����������\n", in);
					continue;
				}
				break;
			}
			printf("���·������\n");
			Outputpath(G,Dist,j);
			break;
			//
		default: printf("                            �������\n");
	
			}

		}

	}



//------------------END-------------------//



//__________________________________����ͼ����__________________________________//
//int main() {
//	int i;
//	ALGraph G;
//	int n = 4, e = 4;//���� ����
//	VexType vexs[] = { 'A','B','C','D' };
//	ArcInfo* info;
//	info = (ArcInfo*)malloc(n*sizeof(ArcInfo));
//	//��ʼ�� info����
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
//	printf("������ߣ�");
//	scanf("%c%c", &in, &in2);
//	getchar();
//	if (isExist(vexs, in, k, j) == ERROR)
//	{
//		printf("ERROR!");//���������ֹ
//		return 0;
//	}
//	else if (-1 == j) {//�жϽ���Ƿ��Ѿ�����
//		vexs[k] = in;
//		k++;
//	}
//
//	if (isExist(vexs, in2, k, j) == ERROR)
//	{
//		printf("ERROR!");//���������ֹ
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


