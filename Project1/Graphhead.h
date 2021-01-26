#pragma once
#include"Base.h"

//邻接表储存结构定义
#define UNVISITED 0
#define VISITED 1
#define INFINITY MAX_INT  
#define SELECTED 1
#define UNSELECTED 0 
typedef enum{DG,DN,UDG,UDN}GraphKind;//有向图，有向带权图，无向图，无向带权图
//
typedef struct {
	int prev;//当前最短路径上该顶点的前驱顶点位序
	int lowcost;//当前最短路径长度
}DistInfo;
DistInfo* Dist;
typedef struct AdjVexNode {
	int adjvex;// 邻接顶点在顶点数组中的位序
	struct AdjVexNode* nextArc; // 指向下一个邻接顶点(下一条边或弧)
	int info; // 存储边(弧)相关信息(如带权图的权值)
} AdjVexNode, * AdjVexNodeP; // 邻接链表的结点类型
								
typedef struct vexNode {
	VexType data;//顶点值, VexType是顶点类型,由用户定义
	struct AdjVexNode* firstArc; // 邻接链表的头指针
}VexNode;//顶点数组的元素类型
typedef struct {
	VexNode* vexs; // 顶点数组, 用于存储顶点信息
	int n, e;//顶点数和边(弧)数
	GraphKind kind;//图的类型
	int* tags; // 标志数组, 可用于在图的遍历中标记顶点访间与否
}ALGraph;//邻接表类型
								
typedef struct {
	VexType v, w;//边端点
	int info;//带权图为权图
}ArcInfo;
								
								
//接口

//Status visit(VexType v);//访问结点
Status CreateGraph_AL(ALGraph& G, GraphKind kind, VexType* vexs, int n, ArcInfo* arcs, int e);//创建n个顶点和e条边的kind类的图G,vexs为顶点信息,arcs为边信息
Status DestroyGraph_AL(ALGraph& G); // 销毁图G
int LocateVex_AL(ALGraph G, VexType v); //查找顶点v在图G中的位序
Status GetVex_AL(ALGraph G, int k, VexType& w); // 取图G的k顶点的值到w
Status PutVex_AL(ALGraph G, int k, VexType w);//对图G的k顶点赋值w

int FirstAdjVex_AL(ALGraph G, int k,AdjVexNode &p);
/*若图G中k顶点的邻接链表非空, 则令指针p指向第一个结点, 开返凹具仔储的邻接$点位序, 否则令指针p为NULL, 并返回 - 1 */
int NextAdjvex_AL(ALGraph G, int k,AdjVexNodeP &p);
// 在k顶点的邻接链表中, 令p指向下一个结点
//若p非空, 返回存储在p结点中的下一个邻接顶点的位序, 否则返回 - 1
Status AddArc_AL(ALGraph& G, int k, int m, int info);//在图G中增加k顶点到m顶点的边或弧,若为带权图,info为权值,否则为1
Status RemoveArc_AL(ALGraph& G, int k, int m);//在图G中删除k顶点到m顶点的边或弧
Status DFSTraverse_AL(ALGraph G, Status(*visit)(VexType));  // 深度优先遍历图G
Status BFSTraverse_AL (ALGraph G, Status(*visit)(VexType));//广度优先遍历图G
Status ADDVexNode_AL(ALGraph &G, VexNode w);//增加顶点w
Status RemoveVexNode_AL(ALGraph& G, int k, VexNode &w);//移除图G的k顶点到w//移除节点不释放内存
Status Dijkstra(ALGraph G, int i, DistInfo* Dist);//求图G中从顶点i到其他所有顶点的最少消耗路径，并由Dist返回
void Outputpath(ALGraph G, DistInfo* Dist, int k);//输出最短路径
