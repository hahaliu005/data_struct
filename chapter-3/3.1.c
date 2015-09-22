// 栈的顺序存储结构
#include"include/header.h"
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int ElemType;
#ifdef __REDEFINE__
typedef BiTree SElemType;
#else
typedef ElemType SElemType;
#endif

typedef struct{
  SElemType *base;
  SElemType *top;
  int stacksize;
}SqStack;

Status InitStack(SqStack *S){
  S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
  if(! S->base){
    exit(OVERFLOW);
  }
  S->top = S->base;
  S->stacksize = STACK_INIT_SIZE;
  return OK;
}

Status DestroyStack(SqStack *S){
  free(S->base);
  S->base = NULL;
  S->top = NULL;
  S->stacksize = 0;
  return OK;
}

Status ClearStack(SqStack *S){
  S->top = S->base;
  return OK;
}

Status StackEmpty(SqStack S){
  return S.top == S.base;
}

int StackLength(SqStack S){
  return S.top - S.base;
}

Status GetTop(SqStack S, SElemType *e){
  if(S.top <= S.base){
    return ERROR;
  }
  *e = *(S.top - 1);
  return OK;
}

Status Push(SqStack *S, SElemType e){
  if(StackLength(*S) >= S->stacksize){
    int new_len = S->stacksize + STACKINCREMENT;
    S->base = (SElemType *)realloc(S->base, new_len * sizeof(SElemType));
    S->stacksize = new_len;
  }
  *(S->top) = e;
  S->top ++;
  return OK;
}

Status Pop(SqStack *S, SElemType *e){
  if(StackEmpty(*S)){
    return ERROR;
  }
  S->top--;
  *e = *(S->top);
  return OK;
}

Status StackTraverse(SqStack S, Status(*visit)(SElemType)){
  SElemType *p;
  p = S.base;
  while(p != S.top){
    if(! visit(*p)){
      return FALSE;
    }
    p++;
  }
  return OK;
}

#ifndef __MAIN__
Status visit(SElemType c)
{
  printf("%d ",c);
  return OK;
}

void conversion(){
  printf("Enter a decimal\n");
  SElemType n;
  SElemType e;
  SqStack S;
  InitStack(&S);
  scanf("%d", &n);
  while(n){
    Push(&S, n % 8);
    n = n / 8;
  }
  while(!StackEmpty(S)){
    Pop(&S, &e);
    printf("%d", e);
  }
}
#endif

#ifndef __MAIN__
void main()
{
  int j;
  SqStack s;
  SElemType e;
  if(InitStack(&s)==OK)
    for(j=1;j<=12;j++)
      Push(&s,j);
  printf("栈中元素依次为：");
  StackTraverse(s,visit);
  Pop(&s,&e);
  printf("弹出的栈顶元素 e=%d\n",e);
  printf("栈空否：%d(1:空 0:否)\n",StackEmpty(s));
  GetTop(s,&e);
  printf("栈顶元素 e=%d 栈的长度为%d\n",e,StackLength(s));
  Push(&s, 13);
  printf("after push 13:\n");
  StackTraverse(s,visit);
  ClearStack(&s);
  printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(s));
  DestroyStack(&s);
  printf("销毁栈后，s.top=%u s.base=%u s.stacksize=%d\n",s.top,s.base, s.stacksize);
  conversion();
}
#endif
