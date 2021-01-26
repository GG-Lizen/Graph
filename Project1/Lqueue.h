#pragma once
#include"Base.h"

typedef int  ElemType;

typedef struct LQNode {
    ElemType  data;
    struct LQNode* next;
} LQNode, * QueuePtr; // ���ͽ��ָ������
typedef struct {
    QueuePtr  front;  // ��ͷָ��
    QueuePtr  rear;   // ��βָ��
} LQueue;  // ����������

Status InitQueue_LQ(LQueue& Q);//��������
Status EnQueue_LQ(LQueue& Q, ElemType e);//���
Status DeQueue_LQ(LQueue& Q, ElemType& e);//����
Status QueueEmpty_LQ(LQueue Q);
/* �ж�������Q�Ƿ�Ϊ�ն��С�           */
/* ��Q�ǿն��У��򷵻�TRUE������FALSE��*/
int QueueLength_LQ(LQueue Q);
/* ��������Q�ĳ��Ȳ�������ֵ */


