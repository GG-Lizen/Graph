#pragma once
#include"Base.h"

typedef int  ElemType;

typedef struct LQNode {
    ElemType  data;
    struct LQNode* next;
} LQNode, * QueuePtr; // 结点和结点指针类型
typedef struct {
    QueuePtr  front;  // 队头指针
    QueuePtr  rear;   // 队尾指针
} LQueue;  // 链队列类型

Status InitQueue_LQ(LQueue& Q);//创建队列
Status EnQueue_LQ(LQueue& Q, ElemType e);//入队
Status DeQueue_LQ(LQueue& Q, ElemType& e);//出队
Status QueueEmpty_LQ(LQueue Q);
/* 判定链队列Q是否为空队列。           */
/* 若Q是空队列，则返回TRUE，否则FALSE。*/
int QueueLength_LQ(LQueue Q);
/* 求链队列Q的长度并返回其值 */


