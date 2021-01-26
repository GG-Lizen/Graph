#pragma once
#include"Base.h"

//�ڽӱ���ṹ����
#define UNVISITED 0
#define VISITED 1
#define INFINITY MAX_INT  
#define SELECTED 1
#define UNSELECTED 0 
typedef enum{DG,DN,UDG,UDN}GraphKind;//����ͼ�������Ȩͼ������ͼ�������Ȩͼ
//
typedef struct {
	int prev;//��ǰ���·���ϸö����ǰ������λ��
	int lowcost;//��ǰ���·������
}DistInfo;
DistInfo* Dist;
typedef struct AdjVexNode {
	int adjvex;// �ڽӶ����ڶ��������е�λ��
	struct AdjVexNode* nextArc; // ָ����һ���ڽӶ���(��һ���߻�)
	int info; // �洢��(��)�����Ϣ(���Ȩͼ��Ȩֵ)
} AdjVexNode, * AdjVexNodeP; // �ڽ�����Ľ������
								
typedef struct vexNode {
	VexType data;//����ֵ, VexType�Ƕ�������,���û�����
	struct AdjVexNode* firstArc; // �ڽ������ͷָ��
}VexNode;//���������Ԫ������
typedef struct {
	VexNode* vexs; // ��������, ���ڴ洢������Ϣ
	int n, e;//�������ͱ�(��)��
	GraphKind kind;//ͼ������
	int* tags; // ��־����, ��������ͼ�ı����б�Ƕ���ü����
}ALGraph;//�ڽӱ�����
								
typedef struct {
	VexType v, w;//�߶˵�
	int info;//��ȨͼΪȨͼ
}ArcInfo;
								
								
//�ӿ�

//Status visit(VexType v);//���ʽ��
Status CreateGraph_AL(ALGraph& G, GraphKind kind, VexType* vexs, int n, ArcInfo* arcs, int e);//����n�������e���ߵ�kind���ͼG,vexsΪ������Ϣ,arcsΪ����Ϣ
Status DestroyGraph_AL(ALGraph& G); // ����ͼG
int LocateVex_AL(ALGraph G, VexType v); //���Ҷ���v��ͼG�е�λ��
Status GetVex_AL(ALGraph G, int k, VexType& w); // ȡͼG��k�����ֵ��w
Status PutVex_AL(ALGraph G, int k, VexType w);//��ͼG��k���㸳ֵw

int FirstAdjVex_AL(ALGraph G, int k,AdjVexNode &p);
/*��ͼG��k������ڽ�����ǿ�, ����ָ��pָ���һ�����, ���������д����ڽ�$��λ��, ������ָ��pΪNULL, ������ - 1 */
int NextAdjvex_AL(ALGraph G, int k,AdjVexNodeP &p);
// ��k������ڽ�������, ��pָ����һ�����
//��p�ǿ�, ���ش洢��p����е���һ���ڽӶ����λ��, ���򷵻� - 1
Status AddArc_AL(ALGraph& G, int k, int m, int info);//��ͼG������k���㵽m����ı߻�,��Ϊ��Ȩͼ,infoΪȨֵ,����Ϊ1
Status RemoveArc_AL(ALGraph& G, int k, int m);//��ͼG��ɾ��k���㵽m����ı߻�
Status DFSTraverse_AL(ALGraph G, Status(*visit)(VexType));  // ������ȱ���ͼG
Status BFSTraverse_AL (ALGraph G, Status(*visit)(VexType));//������ȱ���ͼG
Status ADDVexNode_AL(ALGraph &G, VexNode w);//���Ӷ���w
Status RemoveVexNode_AL(ALGraph& G, int k, VexNode &w);//�Ƴ�ͼG��k���㵽w//�Ƴ��ڵ㲻�ͷ��ڴ�
Status Dijkstra(ALGraph G, int i, DistInfo* Dist);//��ͼG�дӶ���i���������ж������������·��������Dist����
void Outputpath(ALGraph G, DistInfo* Dist, int k);//������·��
