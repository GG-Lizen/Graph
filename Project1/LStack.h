#pragma once
#include"Graphhead.h"
typedef AdjVexNodeP  ElemType;



typedef struct LSNode {
	ElemType data;// ������
	struct LSNode* next;//ָ����

} LSNode , * LStack; // ������ջ����

void InitStack_LS(LStack& s);//��ʼ����ջS

void DestroyStack_LS(LStack& s);//������ջs

Status stackEmpty_LS(LStack s);/*�жϿ�ջ,��ջ/���򷵻�TRUE�����򷵻�FALSE*/

Status Push_Ls(LStack& S, ElemType e);//Ԫ��eѹ��ջS

Status Pop_LS(LStack& S, ElemType& e); // ջs��ջ��Ԫ�س�ջ, ����e����

Status GetTop_LS(LStack S,ElemType& e);//ȡջS��ջ��Ԫ��,����e����













