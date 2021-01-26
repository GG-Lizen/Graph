#include"Lqueue.h"
//��������
Status InitQueue_LQ(LQueue& Q) {
    Q.front = NULL;
    Q.rear = NULL;
    return OK;
}
//���
Status EnQueue_LQ(LQueue& Q, ElemType e){
    LQNode* p;
    p=(LQNode*)malloc(sizeof(LQNode));
    if (NULL == p) return OVERFLOW;
    p->data = e; p->next = NULL;
    if (NULL == Q.front)Q.front = p;
    else Q.rear->next = p;
    Q.rear = p;
    return OK;
}

//����
Status DeQueue_LQ(LQueue& Q, ElemType& e) {
    LQNode* p;
    if (NULL == Q.front) return ERROR;
    p = Q.front;
    e = p->data;
    Q.front = p->next;
    if (Q.rear == p) Q.rear == NULL;
    free(p);
    return OK;
}
Status QueueEmpty_LQ(LQueue Q)
/* �ж�������Q�Ƿ�Ϊ�ն��С�           */
/* ��Q�ǿն��У��򷵻�TRUE������FALSE��*/
{

    if (Q.front == NULL || NULL == Q.rear)
        return TRUE;
    return FALSE;
}

int QueueLength_LQ(LQueue Q)
/* ��������Q�ĳ��Ȳ�������ֵ */
{
    if (Q.front == NULL || Q.rear == NULL) return 0;
    int count = 0;
    QueuePtr p = Q.front;
    while (p != Q.rear->next)
    {
        p = p->next;
        count++;
    }
    return count;
}
