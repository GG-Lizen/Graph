//�ӿ�ʵ��
#include"Lqueue.h"
#include"Graphhead.h"



//�Ӻ�������
//��������ͼ�ڽӱ�洢�ṹ
Status CreatUDG_AL(ALGraph& G, VexType* vexs, int n, ArcInfo* arcs, int e);
//��������ͼ�ڽӱ�洢�ṹ
Status CreatDG_AL(ALGraph& G, VexType* vexs, int n, ArcInfo* arcs, int e);
//����ͨͼG �Ķ���k��������������ȱ���
Status DFS_AL(ALGraph G, int k, Status(*visit)(VexType));
//�Ӻ�������end


//����n�������e���ߵ�kind���ͼG,vexsΪ������Ϣ,arcsΪ����Ϣ
Status CreateGraph_AL(ALGraph& G, GraphKind kind, VexType* vexs, int n, ArcInfo* arcs, int e)
{
    G.kind = kind;
    if (G.kind == UDG)CreatUDG_AL(G, vexs, n, arcs, e);
    else if (G.kind == DG)CreatDG_AL(G, vexs, n, arcs, e);
    else return ERROR;
}
// ����ͼG
Status DestroyGraph_AL(ALGraph& G)
{
    int i;
    AdjVexNodeP p,q;
    //���ٶ�����ڽ�����
    if (G.vexs == NULL||G.tags==NULL) return ERROR;//ͼΪ��
    for (i = 0; i < G.n; i++) {
        p = G.vexs[i].firstArc;
        while (p != NULL) {
            q = p->nextArc;
            free(p);
            p = q;
        }
    }
    //���ٶ�������
    free(G.vexs);
    //���ٱ�־����
    free(G.tags);
    G.n = 0;
    G.e = 0;
    return OK;




}
//���Ҷ���v��ͼG�е�λ��
int LocateVex_AL(ALGraph G, VexType v) {
    int i;
    for (i = 0; i < G.n; i++)
        if (v == G.vexs[i].data) return i;
    return -1;
} 
Status GetVex_AL(ALGraph G, int k, VexType& w) // ȡͼG��k�����ֵ��w 
{
    if (k<0 || k>G.n)return ERROR;
    w = G.vexs[k].data;
    return OK;
}
Status PutVex_AL(ALGraph G, int k, VexType w)//��ͼG��k���㸳ֵw
{
    if (k<0 || k>G.n)return ERROR;
    G.vexs[k].data=w;
    return OK;
}

/*��ͼG��k������ڽ�����ǿ�, ����ָ��pָ���һ�����, ��������洢���ڽӶ���λ��, ������ָ��pΪNULL, ������ - 1 */
int FirstAdjVex_AL(ALGraph G, int k, AdjVexNodeP& p) {
    if (k < 0 || k >= G.n)return -1;//k���㲻����
    p = G.vexs[k].firstArc;
    if (p != NULL)return p->adjvex;//���ص�һ�����洢��λ��
    else return -1;//k�޶���
}

// ��k������ڽ�������, ��pָ����һ�����
//��p�ǿ�, ���ش洢��p����е���һ���ڽӶ����λ��, ���򷵻� - 1
int NextAdjvex_AL(ALGraph G, int k, AdjVexNodeP& p) {
    if (k<0 || k>G.n) return ERROR;
    if (NULL == p) return -1;
    p = p->nextArc;
    if (p != NULL)return p->adjvex;
    else return -1;
}


//��ͼG������k���㵽m����ı߻�,��Ϊ��Ȩͼ,infoΪȨֵ,����Ϊ1
Status AddArc_AL(ALGraph& G, int k, int m, int info) {
    AdjVexNodeP p;
    if (k<0 || k>G.n || m<0 || m>G.n)return ERROR;
    if ((UDG == G.kind || DG == G.kind )&& info != 1)return ERROR;///info��ͼ���Ͳ�ƥ��
    p = G.vexs[k].firstArc;
    while (p!=NULL)
    {
        if (m == p->adjvex)return ERROR;
        p = p->nextArc;
    }
    p = (AdjVexNode*)malloc(sizeof(AdjVexNode));//Ϊm����p���
    if (NULL == p)return OVERFLOW;
    p->adjvex = m; p->info = info;
    p->nextArc = G.vexs[k].firstArc;//��k������ڽ������ͷ����p���
    G.vexs[k].firstArc = p;
    if (UDG == G.kind || UDN == G.kind) {
    p = (AdjVexNode*)malloc(sizeof(AdjVexNode));//Ϊm����p���
    if (NULL == p)return OVERFLOW;
    p->adjvex = k; p->info = info;
    p->nextArc = G.vexs[m].firstArc;//��m������ڽ������ͷ����p���
    G.vexs[m].firstArc = p;
    }
    G.e++;
    return OK;
      
}
        
//��ͼG��ɾ��k���㵽m����ı߻�
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
                return ERROR; //�Ҳ���<m,k>   
            }
            G.e--;
            return OK;
        }
        q = p;
        p = p->nextArc;
    }
    return ERROR;//�Ҳ���<k,m>
}

// ������ȱ���ͼG
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




//������ȱ���ͼG
Status BFSTraverse_AL(ALGraph G, Status(*visit)(VexType)) {
    int i, j, k;
    AdjVexNodeP p;
    LQueue Q; InitQueue_LQ(Q);//��ʼ������Q
    for (i = 0; i < G.n; i++) G.tags[i] = UNVISITED;//��ʼ����־����
    for (i = 0; i < G.n; i++) 
        if(UNVISITED==G.tags[i]){
        if (ERROR == visit(G.vexs[i].data)) return ERROR;
        G.tags[i] = VISITED; EnQueue_LQ(Q, i);//���ʶ���i�����
        while (OK==DeQueue_LQ(Q,k))//����Ԫ�ص�k
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


Status ADDVexNode_AL(ALGraph& G, VexNode w) {//���Ӷ���w
    int i;
    VexNode *vptr;
    int* iptr;
    if (G.vexs == NULL || G.tags == NULL)return ERROR;
    i = LocateVex_AL(G, w.data);
    if (i == -1) {
        if (sizeof(G.vexs) / sizeof(VexNode) <= G.n)//�ڴ治�����¿���
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
 
Status RemoveVexNode_AL(ALGraph& G, int k, VexNode& w) {//�Ƴ�ͼG��k���㵽w//k��λ��
    if (G.vexs == NULL || G.tags == NULL)return ERROR;
    if (k<0 || k>G.n) return ERROR;
    int i,j;
    AdjVexNodeP p;
   // int* index = (int*)malloc(sizeof(int) * (G.n - k - 1));//���汻�޸Ľ������±�
        w = G.vexs[k];
        for (i = 0; i < G.n; i++) {
            if (i ==k)continue;
            RemoveArc_AL(G, i, k);
        }

        //������Ҫ�޸ĵĽ��
        for (i = 0; i < G.n; i++) {
            if (i == k) continue;
            p = G.vexs[i].firstArc;
            while (p!=NULL)
            {
                if (p->adjvex > k)p->adjvex--;
                NextAdjvex_AL(G, i, p);
            }
        }


        for (i = k; i < G.n-1; i++) {//����ǰ��
            G.vexs[i] = G.vexs[i+1];
        }
        for (i = k; i < G.n - 1; i++) {//����ǰ��
            G.tags[i] = G.tags[i+1];
        }
       
        G.n--;
        return OK;
}

//��ͼG�дӶ���i���������ж������������·��������Dist����
Status Dijkstra(ALGraph G, int i, DistInfo* Dist) {
    int j, m, k, min;
    AdjVexNodeP p;
    Dist = (DistInfo*)malloc(G.n * sizeof(DistInfo));
    for (j = 0; j < G.n; j++) {// ��ʼ��
        Dist[j].lowcost = INFINITY;
        G.tags[j] = UNSELECTED;//���ж�������ڼ���U��
    }
    for (p = G.vexs[i].firstArc; p != NULL; p = p->nextArc) {
        // Դ��i���������л�����Ϣ����Dist
        Dist[p->adjvex].prev = i;
            Dist[p->adjvex].lowcost = p->info;

    }
    Dist[i].prev = -1; Dist[i].lowcost = 0; // Դ��i��Ϣ���� Dist
    G.tags[i] = SELECTED;//��ʼ����U����Դ��i
    for (m = 1; m < G.n; m++) {//��·����������,����ˮԴ�㵽�����ӵ�����·��
        min = INFINITY; k = 0;
        for (j = 0; j < G.n; j++)
            if (0 == G.tags[j] && Dist[j].lowcost < min) {
                k = j; min = Dist[k].lowcost;
            }
        G.tags[k] = SELECTED; // ��k������˼���U
        for (p = G.vexs[k].firstArc; p != NULL; p = p->nextArc) {//����Dist ����
            j = p->adjvex;
                if (UNSELECTED == G.tags[j] && Dist[k].lowcost + p->info < Dist[i].lowcost) {
                    Dist[j].lowcost = Dist[k].lowcost + p->info;
                    Dist[j].prev = k;
                }
    
        }


    }
}

void Outputpath(ALGraph G, DistInfo* Dist, int k) {
    // �� Dist �����prev��, �ɵݹ���Դ�㵽k��������·��
    if (-1 == k) return;
    Outputpath(G, Dist, Dist[k].prev); // ����ݹ��ȡ·���ϵĶ���
    printf("%c", G.vexs[k].data); // ���������ǰ·���ϵĶ���
}















//�Ӻ���
//��������ͼ�ڽӱ�洢�ṹ
Status CreatUDG_AL(ALGraph& G, VexType* vexs, int n, ArcInfo* arcs, int e) {
    int i, j, k;
    VexType v, w;
    AdjVexNodeP p;
    G.n = n;//���붥����
    G.e = e;//���뻡��
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
        i = LocateVex_AL(G, v); j = LocateVex_AL(G, w);//ȷ��v,w
        if (i < 0 || j < 0) return ERROR;//v,w������
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
//��������ͼ�ڽӱ�洢�ṹ
Status CreatDG_AL(ALGraph& G,  VexType* vexs, int n, ArcInfo* arcs, int e) {
    int i, j, k;
    VexType v, w;
    AdjVexNodeP p;
    G.n = n;//���붥����
    G.e = e;//���뻡��
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
        i = LocateVex_AL(G, v); j = LocateVex_AL(G, w);//ȷ��v,w
        if (i < 0 || j < 0) return ERROR;//v,w������
        p = (AdjVexNode*)malloc(sizeof(AdjVexNode));
        if (NULL == p)return OVERFLOW;
        p->adjvex = j;
        p->nextArc = G.vexs[i].firstArc;
        G.vexs[i].firstArc = p;
      
    }

}
//����ͨͼG �Ķ���k��������������ȱ���
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
