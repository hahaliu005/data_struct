// 队列的链式存储
#include"include/header.h"
typedef int QElemType;

typedef struct QNode{
  QElemType data;
  struct QNode * next;
}QNode, * QueuePtr;

typedef struct{
  QueuePtr front;
  QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue *Q){
  Q->front = (QueuePtr)malloc(sizeof(QNode));
  if(! Q->front){
    exit(OVERFLOW);
  }
  Q->front->next = NULL;
  Q->rear = Q->front;
  return OK;
}

Status DestroyQueue(LinkQueue *Q){
  while(Q->front){
    Q->rear = Q->front->next;
    free(Q->front);
    Q->front = Q->rear;
  }
  return OK;
}

Status ClearQueue(LinkQueue *Q){
  QNode *p;
  p = Q->front->next;
  while(p){
    free(p);
    p = p->next;
  }
  Q->rear = Q->front;
  return OK;
}

Status QueueEmpty(LinkQueue Q){
  return Q.front == Q.rear;
}

int QueueLength(LinkQueue Q){
  int i = 0;
  QNode *p;
  p = Q.front->next;
  while(p){
    i++;
    p = p->next;
  }
  return i;
}

Status GetHead(LinkQueue Q, QElemType *e){
  if(Q.front->next){
    *e = Q.front->next->data;
    return OK;
  }else{
    return ERROR;
  }
}

Status EnQueue(LinkQueue *Q, QElemType e){
  QNode *p;
  p = (QNode *)malloc(sizeof(QNode));
  p->data = e;
  p->next = NULL;
  Q->rear->next = p;
  Q->rear = p;
  return OK;
}

Status DeQueue(LinkQueue *Q, QElemType *e){
  if(! QueueEmpty(*Q)){
    *e = Q->front->next->data;
    Q->front->next = Q->front->next->next;
    return OK;
  }else{
    return ERROR;
  }
}

Status QueueTraverse(LinkQueue Q, void visit(QElemType)){
  QNode *p;
  p = Q.front->next;
  while(p){
    visit(p->data);
    p = p->next;
  }
  return OK;
}

Status GetHead_Q(LinkQueue Q,QElemType *e) /* 避免与bo2-6.c重名 */
{ /* 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR */
  QueuePtr p;
  if(Q.front==Q.rear)
    return ERROR;
  p=Q.front->next;
  *e=p->data;
  return OK;
}


void visit(QElemType i)
{
  printf("%d ",i);
}

void main()
{
  int i;
  QElemType d;
  LinkQueue q;
  i=InitQueue(&q);
  if(i)
    printf("成功地构造了一个空队列!\n");
  printf("是否空队列？%d(1:空 0:否)  ",QueueEmpty(q));
  printf("队列的长度为%d\n",QueueLength(q));
  EnQueue(&q,-5);
  EnQueue(&q,5);
  EnQueue(&q,10);
  printf("插入3个元素(-5,5,10)后,队列的长度为%d\n",QueueLength(q));
  printf("是否空队列？%d(1:空 0:否)  ",QueueEmpty(q));
  printf("队列的元素依次为：");
  QueueTraverse(q,visit);
  i=GetHead_Q(q,&d);
  if(i==OK)
    printf("队头元素是：%d\n",d);
  DeQueue(&q,&d);
  printf("删除了队头元素%d\n",d);
  i=GetHead_Q(q,&d);
  if(i==OK)
    printf("新的队头元素是：%d\n",d);
  ClearQueue(&q);
  printf("清空队列后,q.front=%u q.rear=%u q.front->next=%u\n",q.front,q.rear,q.front->next);
  DestroyQueue(&q);
  printf("销毁队列后,q.front=%u q.rear=%u\n",q.front, q.rear);
}

