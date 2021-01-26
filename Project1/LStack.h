#pragma once
#include"Graphhead.h"
typedef AdjVexNodeP  ElemType;



typedef struct LSNode {
	ElemType data;// 数据域
	struct LSNode* next;//指针域

} LSNode , * LStack; // 结点和链栈类型

void InitStack_LS(LStack& s);//初始化链栈S

void DestroyStack_LS(LStack& s);//销毁链栈s

Status stackEmpty_LS(LStack s);/*判断空栈,若栈/空则返回TRUE，否则返回FALSE*/

Status Push_Ls(LStack& S, ElemType e);//元素e压入栈S

Status Pop_LS(LStack& S, ElemType& e); // 栈s的栈顶元素出栈, 并用e返回

Status GetTop_LS(LStack S,ElemType& e);//取栈S的栈顶元素,并用e返回













