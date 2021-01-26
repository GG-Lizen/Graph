//接口实现
#include"Lqueue.h"
#include"Graphhead.h"



//子函数声明
//创建无向图邻接表存储结构
Status CreatUDG_AL(ALGraph& G, VexType* vexs, int n, ArcInfo* arcs, int e);
//创建有向图邻接表存储结构
Status CreatDG_AL(ALGraph& G, VexType* vexs, int n, ArcInfo* arcs, int e);
//从连通图G 的顶点k出发进行深度优先遍历
Status DFS_AL(ALGraph G, int k, Status(*visit)(VexType));
//子函数声明end


//创建n个顶点和e条边的kind类的图G,vexs为顶点信息,arcs为边信息
Status CreateGraph_AL(ALGraph& G, GraphKind kind, VexType* vexs, int n, ArcInfo* arcs, int e)
{
    G.kind = kind;
    if (G.kind == UDG)CreatUDG_AL(G, vexs, n, arcs, e);
    else if (G.kind == DG)CreatDG_AL(G, vexs, n, arcs, e);
    else return ERROR;
}
// 销毁图G
Status DestroyGraph_AL(ALGraph& G)
{
    int i;
    AdjVexNodeP p,q;
    //销毁顶点的邻接链表
    if (G.vexs == NULL||G.tags==NULL) return ERROR;//图为空
    for (i = 0; i < G.n; i++) {
        p = G.vexs[i].firstArc;
        while (p != NULL) {
            q = p->nextArc;
            free(p);
            p = q;
        }
    }
    //销毁顶点数组
    free(G.vexs);
    //销毁标志数组
    free(G.tags);
    G.n = 0;
    G.e = 0;
    return OK;




}
//查找顶点v在图G中的位序
int LocateVex_AL(ALGraph G, VexType v) {
    int i;
    for (i = 0; i < G.n; i++)
        if (v == G.vexs[i].data) return i;
    return -1;
} 
Status GetVex_AL(ALGraph G, int k, VexType& w) // 取图G的k顶点的值到w 
{
    if (k<0 || k>G.n)return ERROR;
    w = G.vexs[k].data;
    return OK;
}
Status PutVex_AL(ALGraph G, int k, VexType w)//对图G的k顶点赋值w
{
    if (k<0 || k>G.n)return ERROR;
    G.vexs[k].data=w;
    return OK;
}

/*若图G中k顶点的邻接链表非空, 则令指针p指向第一个结点, 并返回其存储的邻接顶点位序, 否则令指针p为NULL, 并返回 - 1 */
int FirstAdjVex_AL(ALGraph G, int k, AdjVexNodeP& p) {
    if (k < 0 || k >= G.n)return -1;//k顶点不存在
    p = G.vexs[k].firstArc;
    if (p != NULL)return p->adjvex;//返回第一个结点存储的位序
    else return -1;//k无顶点
}

// 在k顶点的邻接链表中, 令p指向下一个结点
//若p非空, 返回存储在p结点中的下一个邻接顶点的位序, 否则返回 - 1
int NextAdjvex_AL(ALGraph G, int k, AdjVexNodeP& p) {
    if (k<0 || k>G.n) return ERROR;
    if (NULL == p) return -1;
    p = p->nextArc;
    if (p != NULL)return p->adjvex;
    else return -1;
}


//在图G中增加k顶点到m顶点的边或弧,若为带权图,info为权值,否则为1
Status AddArc_AL(ALGraph& G, int k, int m, int info) {
    AdjVexNodeP p;
    if (k<0 || k>G.n || m<0 || m>G.n)return ERROR;
    if ((UDG == G.kind || DG == G.kind )&& info != 1)return ERROR;///info和图类型不匹配
    p = G.vexs[k].firstArc;
    while (p!=NULL)
    {
        if (m == p->adjvex)return ERROR;
        p = p->nextArc;
    }
    p = (AdjVexNode*)malloc(sizeof(AdjVexNode));//为m分配p结点
    if (NULL == p)return OVERFLOW;
    p->adjvex = m; p->info = info;
    p->nextArc = G.vexs[k].firstArc;//在k顶点的邻接链表表头插入p结点
    G.vexs[k].firstArc = p;
    if (UDG == G.kind || UDN == G.kind) {
    p = (AdjVexNode*)malloc(sizeof(AdjVexNode));//为m分配p结点
    if (NULL == p)return OVERFLOW;
    p->adjvex = k; p->info = info;
    p->nextArc = G.vexs[m].firstArc;//在m顶点的邻接链表表头插入p结点
    G.vexs[m].firstArc = p;
    }
    G.e++;
    return OK;
      
}
        
//在图G中删除k顶点到m顶点的边或弧
Status RemoveArc_AL(ALGraph& G, int k, int m) {
    AdjVexNodeP p, q=NULL;
    if (k<0 || k>G.n || m<0 || m>G.n) return ERROR;
    p = G.vexs[k].firstArc;
    while (p != NULL) {
       
        if (m == p->adjvex) {
            if (p == G.vexs[k].firstArc) {
                G.vexs[k].firstArc = p->nextArc;
                free(p);
            }
            else {
                q->nextArc = p->nextArc;
                free(p);
            }
            if (G.kind == UDG || G.kind == G.kind) {
                p = G.vexs[m].firstArc;
                while (p != NULL) {
             
                    if (k == p->adjvex) {
                        if (p == G.vexs[m].firstArc) {
                            G.vexs[m].firstArc = p->nextArc;
                            free(p);
                        }
                        else {
                            q->nextArc = p->nextArc;
                            free(p);
                        }
                        G.e--;
                        return OK;
                    }
                    q = p;
                    p = p->nextArc;
                }
                return ERROR; //找不到<m,k>   
            }
            G.e--;
            return OK;
        }
        q = p;
        p = p->nextArc;
    }
    return ERROR;//找不到<k,m>
}

// 深度优先遍历图G
Status DFSTraverse_AL(ALGraph G, Status(*visit)(VexType))
{
    int i;
    for (i = 0; i < G.n; i++) G.tags[i] = UNVISITED;
    for(i = 0; i < G.n; i++)
    if(UNVISITED == G.tags[i])
        if (ERROR == DFS_AL(G, i, visit)) return ERROR;
    return OK;
}





//
//int i, j;
//AdjVexNodeP p;
//LStack S; InitStack_LS(S);
//for (i = 0; i < G.n; i++)G.tags[i] = UNVISITED;
//for (i = 0; i < G.n; i++) {
//    if (UNVISITED == G.tags[i]) {
//        if (ERROR == visit(i)) return ERROR;
//        G.tags[i] = VISITED; Push_Ls(S, i);
//        while (!stackEmpty_LS(S))
//        {
//            j = FirstAdjVex_AL(G, i, p);
//            if (j < 0) return ERROR;
//            if (UNVISITED == G.tags[j]) {
//                if (ERROR == visit(j)) return ERROR;
//                G.tags[j] = VISITED; Push_Ls(S, j);
//            }
//            else {
//                j = NextAdjvex_AL(G, j, p);
//                if (j < 0) {
//                    Pop_LS(S, j);
//                    j = NextAdjvex_AL(G, j, p);
//                }
//                if (UNVISITED == G.tags[j]) {
//                    if (ERROR == visit(j)) return ERROR;
//                    G.tags[j] = VISITED;
//                }
//
//
//            }
//        }
//    }
//}
//




//广度优先遍历图G
Status BFSTraverse_AL(ALGraph G, Status(*visit)(VexType)) {
    int i, j, k;
    AdjVexNodeP p;
    LQueue Q; InitQueue_LQ(Q);//初始化队列Q
    for (i = 0; i < G.n; i++) G.tags[i] = UNVISITED;//初始化标志数组
    for (i = 0; i < G.n; i++) 
        if(UNVISITED==G.tags[i]){
        if (ERROR == visit(G.vexs[i].data)) return ERROR;
        G.tags[i] = VISITED; EnQueue_LQ(Q, i);//访问顶点i并入队
        while (OK==DeQueue_LQ(Q,k))//出队元素到k
        {
            for (j = FirstAdjVex_AL(G, k, p); j >= 0; j = NextAdjvex_AL(G, k, p))
                if (UNVISITED == G.tags[j]) {
                    if (ERROR == visit(G.vexs[j].data)) return ERROR;
                    G.tags[j] = VISITED; EnQueue_LQ(Q, j);
                }
            
        }
    }
    return OK;
}


Status ADDVexNode_AL(ALGraph& G, VexNode w) {//增加顶点w
    int i;
    VexNode *vptr;
    int* iptr;
    if (G.vexs == NULL || G.tags == NULL)return ERROR;
    i = LocateVex_AL(G, w.data);
    if (i == -1) {
        if (sizeof(G.vexs) / sizeof(VexNode) <= G.n)//内存不足重新开辟
        {
            vptr = (VexNode*)realloc(G.vexs, sizeof(VexNode) * (G.n + 1));
            if (vptr == NULL)return OVERFLOW;
            else G.vexs = vptr;
        }
        if (sizeof(G.tags) / sizeof(int) <= G.n)
        {
            iptr = (int*)realloc(G.tags, sizeof(int) * (G.n + 1));
            if (iptr == NULL)return OVERFLOW;
            else G.tags = iptr;
        }
        G.vexs[G.n] = w;
        G.tags[G.n] = UNVISITED;
        G.n++;
        
        return OK;
    }
    else {
        return ERROR;
    }
}
 
Status RemoveVexNode_AL(ALGraph& G, int k, VexNode& w) {//移除图G的k顶点到w//k是位序
    if (G.vexs == NULL || G.tags == NULL)return ERROR;
    if (k<0 || k>G.n) return ERROR;
    int i,j;
    AdjVexNodeP p;
   // int* index = (int*)malloc(sizeof(int) * (G.n - k - 1));//储存被修改结点的新下标
        w = G.vexs[k];
        for (i = 0; i < G.n; i++) {
            if (i ==k)continue;
            RemoveArc_AL(G, i, k);
        }

        //查找需要修改的结点
        for (i = 0; i < G.n; i++) {
            if (i == k) continue;
            p = G.vexs[i].firstArc;
            while (p!=NULL)
            {
                if (p->adjvex > k)p->adjvex--;
                NextAdjvex_AL(G, i, p);
            }
        }


        for (i = k; i < G.n-1; i++) {//数组前移
            G.vexs[i] = G.vexs[i+1];
        }
        for (i = k; i < G.n - 1; i++) {//数组前移
            G.tags[i] = G.tags[i+1];
        }
       
        G.n--;
        return OK;
}

//求图G中从顶点i到其他所有顶点的最少消耗路径，并由Dist返回
Status Dijkstra(ALGraph G, int i, DistInfo* Dist) {
    int j, m, k, min;
    AdjVexNodeP p;
    Dist = (DistInfo*)malloc(G.n * sizeof(DistInfo));
    for (j = 0; j < G.n; j++) {// 初始化
        Dist[j].lowcost = INFINITY;
        G.tags[j] = UNSELECTED;//所有顶点均不在集合U中
    }
    for (p = G.vexs[i].firstArc; p != NULL; p = p->nextArc) {
        // 源点i引出的所有弧的信息存入Dist
        Dist[p->adjvex].prev = i;
            Dist[p->adjvex].lowcost = p->info;

    }
    Dist[i].prev = -1; Dist[i].lowcost = 0; // 源点i信息存人 Dist
    G.tags[i] = SELECTED;//初始集合U仅含源点i
    for (m = 1; m < G.n; m++) {//按路径长度升序,依次水源点到具他坝点的最短路径
        min = INFINITY; k = 0;
        for (j = 0; j < G.n; j++)
            if (0 == G.tags[j] && Dist[j].lowcost < min) {
                k = j; min = Dist[k].lowcost;
            }
        G.tags[k] = SELECTED; // 将k顶点加人集合U
        for (p = G.vexs[k].firstArc; p != NULL; p = p->nextArc) {//更新Dist 数组
            j = p->adjvex;
                if (UNSELECTED == G.tags[j] && Dist[k].lowcost + p->info < Dist[i].lowcost) {
                    Dist[j].lowcost = Dist[k].lowcost + p->info;
                    Dist[j].prev = k;
                }
    
        }


    }
}

void Outputpath(ALGraph G, DistInfo* Dist, int k) {
    // 沿 Dist 数组的prev域, 可递归获得源点到k顶点的最短路径
    if (-1 == k) return;
    Outputpath(G, Dist, Dist[k].prev); // 逆向递归获取路径上的顶点
    printf("%c", G.vexs[k].data); // 正向输出当前路径上的顶点
}















//子函数
//创建无向图邻接表存储结构
Status CreatUDG_AL(ALGraph& G, VexType* vexs, int n, ArcInfo* arcs, int e) {
    int i, j, k;
    VexType v, w;
    AdjVexNodeP p;
    G.n = n;//读入顶点数
    G.e = e;//读入弧数
    G.vexs = (VexNode*)malloc(n * sizeof(VexNode));
    G.tags = (int*)malloc(n * sizeof(int));
    for (i = 0; i < G.n; i++)
    {
        G.tags[i] = UNVISITED;
        G.vexs[i].data = vexs[i];
        G.vexs[i].firstArc = NULL;
    }
    for (k = 0; k < G.e; k++)
    {
        v = arcs[k].v; w = arcs[k].w;
        i = LocateVex_AL(G, v); j = LocateVex_AL(G, w);//确定v,w
        if (i < 0 || j < 0) return ERROR;//v,w不存在
        //i->j
        p = (AdjVexNode*)malloc(sizeof(AdjVexNode));
        if (NULL == p)return OVERFLOW;
        p->adjvex = j;
        p->nextArc = G.vexs[i].firstArc;
        G.vexs[i].firstArc = p;
        //j->i
        p = (AdjVexNode*)malloc(sizeof(AdjVexNode));
        if (NULL == p)return OVERFLOW;
        p->adjvex = i;
        p->nextArc = G.vexs[j].firstArc;
        G.vexs[j].firstArc = p;
    }
}
//创建有向图邻接表存储结构
Status CreatDG_AL(ALGraph& G,  VexType* vexs, int n, ArcInfo* arcs, int e) {
    int i, j, k;
    VexType v, w;
    AdjVexNodeP p;
    G.n = n;//读入顶点数
    G.e = e;//读入弧数
    G.vexs = (VexNode*)malloc(n * sizeof(VexNode));
    G.tags = (int*)malloc(n * sizeof(int));
    for (i = 0; i < G.n; i++)
    {
        G.tags[i] = UNVISITED;
        G.vexs[i].data = vexs[i];
        G.vexs[i].firstArc = NULL;
    }
    for (k = 0; k < G.e; k++)
    {
        v = arcs[k].v; w = arcs[k].w;
        i = LocateVex_AL(G, v); j = LocateVex_AL(G, w);//确定v,w
        if (i < 0 || j < 0) return ERROR;//v,w不存在
        p = (AdjVexNode*)malloc(sizeof(AdjVexNode));
        if (NULL == p)return OVERFLOW;
        p->adjvex = j;
        p->nextArc = G.vexs[i].firstArc;
        G.vexs[i].firstArc = p;
      
    }

}
//从连通图G 的顶点k出发进行深度优先遍历
Status DFS_AL(ALGraph G,int k,Status(*visit)(VexType)) {

    int i;
    AdjVexNodeP p;
    if (ERROR == visit(G.vexs[k].data))return ERROR;
    G.tags[k] = VISITED;
    for (i = FirstAdjVex_AL(G,k,p); i >= 0; i = NextAdjvex_AL(G, k, p)) {
        
        if (UNVISITED == G.tags[i])
            if (ERROR == DFS_AL(G,i,visit)) return ERROR;
    }
    return OK;
}
