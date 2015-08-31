// 线性表的链式存储结构
#include "include/header.h"
typedef int ElemType;
typedef struct LNode{
  ElemType data;
  struct LNode * next;
} * Link, * Position, LNode;

typedef struct{
  Link head, tail;
  int len;
} LinkList;

Status MakeNode(Link *p, ElemType e){
  *p = (Link)malloc(sizeof(LNode));
  if(!*p){
    return ERROR;
  }
  (*p)->data = e;
  return OK;
}

void FreeNode(Link *p){
  free(*p);
  *p = NULL;
}

Status InitList(LinkList *L){
  Link p;
  p = (Link)malloc(sizeof(LNode));
  if(p){
    p ->next = NULL;
    L->head = L->tail = p;
    L->len = 0;
    return OK;
  }else{
    return ERROR;
  }
}

Status ClearList(LinkList *L){
  Link p, q;
  if(L->head != L->tail){
    p = q = L->head->next;
    while(p != L->tail){
      p = q->next;
      free(q);
      q = p;
    }
    free(q);
    L->tail = L->head;
    L->len = 0;
  }
  return OK;
}

Status DestroyList(LinkList *L){
  free(L->head);
  L->tail = NULL;
  L->len = 0;
  return OK;
}

Status InsFirst(LinkList *L, Link h, Link s){
  s->next = h->next;
  h->next = s;
  if(h == L->tail){
    L->tail = h->next;
  }
  L->len++;
  return OK;
}

Status DelFirst(LinkList *L, Link h, Link *q){
  *q = h->next;
  if(*q){
    h->next = (*q)->next;
    if(!h->next){
      L->tail = h;
    }
    L->len--;
  }
  return OK;
}

Status Append(LinkList *L, Link s){
  int i = 1;
  L->tail->next = s;
  while(s->next){
    s = s->next;
    i++;
  }
  L->tail = s;
  L->len += i;
}

Status Remove(LinkList *L, Link *q){
  *q = L->tail;
  Link p;
  p = L->head;
  while(p->next != L->tail){
    p = p->next;
  }
  p->next = NULL;
  L->tail = p;
  L->len--;
  return OK;
}

Status InsBefore(LinkList *L, Link *p, Link s){
  /* 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前， */
  /* 并修改指针p指向新插入的结点 */
  Link q;
  q = L->head;
  while(q->next != *p){
    q = q->next;
  }
  q->next = s;
  s->next = *p;
  *p = s;
  L->len++;
  return OK;
}

Status InsAfter(LinkList *L, Link *p, Link s){
  (*p)->next = s;
  while(s->next){
    s = s->next;
  }
  L->tail = s;
  return OK;
}

Status SetCurElem(Link p, ElemType e){
  p->data = e;
  return OK;
}

ElemType GetCurElem(Link p){
  return p->data;
}

Status ListEmpty(LinkList L){
  return L.head == L.tail;
}

int ListLength(LinkList L){
  return L.len;
}

Position GetHead(LinkList L){
  return L.head;
}

Position GetLast(LinkList L){
  return L.tail;
}

Position PriorPos(LinkList L, Link p){
  Link q;
  q = L.head->next;
  if(q==p){
    return NULL;
  }else{
    while(q->next != p){
      q = q->next;
    }
    return q;
  }
}

Position NextPos(Link p){
  return p->next;
}

Status LocatePos(LinkList L, int i, Link *p){
  if(i<0 || i>L.len){
    return ERROR;
  }
  int j = 0;
  Link q;
  q = L.head;
  while(j < i){
    q = q->next;
    j++;
  }
  *p = q;
  return OK;
}

Position LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType,ElemType)){
  Link p;
  p = L.head;
  while(p->next){
    if(compare(p->data, e)){
      return p;
    }else{
      p = p->next;
    }
  }
  return NULL;
}

Status ListTraverse(LinkList L, Status(*visit)(ElemType)){
  Link p;
  p = L.head->next;
  while(p){
    if(! visit(p->data)){
      return ERROR;
    }
    p = p->next;
  }
  return OK;
}

Status OrderInsert(LinkList *L,ElemType e,int (*comp)(ElemType,ElemType))
{ /* 已知L为有序线性链表，将元素e按非降序插入在L中。（用于一元多项式） */
  Link o,p,q;
  q=(*L).head;
  p=q->next;
  while(p!=NULL&&comp(p->data,e)<0) /* p不是表尾且元素值小于e */
  {
    q=p;
    p=p->next;
  }
  o=(Link)malloc(sizeof(LNode)); /* 生成结点 */
  o->data=e; /* 赋值 */
  q->next=o; /* 插入 */
  o->next=p;
  (*L).len++; /* 表长加1 */
  if(!p) /* 插在表尾 */
    (*L).tail=o; /* 修改尾结点 */
  return OK;
}

Status LocateElemP(LinkList L,ElemType e,Position *q,int(*compare)(ElemType,ElemType))
{ /* 若升序链表L中存在与e满足判定函数compare()取值为0的元素，则q指示L中 */
  /* 第一个值为e的结点的位置，并返回TRUE；否则q指示第一个与e满足判定函数 */
  /* compare()取值>0的元素的前驱的位置。并返回FALSE。（用于一元多项式） */
  Link p=L.head,pp;
  do
  {
    pp=p;
    p=p->next;
  }while(p&&(compare(p->data,e)<0)); /* 没到表尾且p->data.expn<e.expn */
  if(!p||compare(p->data,e)>0) /* 到表尾或compare(p->data,e)>0 */
  {
    *q=pp;
    return FALSE;
  }
  else /* 找到 */
  {
    *q=p;
    return TRUE;
  }
}

Status compare(ElemType c1,ElemType c2) /* c1等于c2 */
{
  if(c1==c2)
    return TRUE;
  else
    return FALSE;
}

int cmp(ElemType a,ElemType b)
{ /* 根据a<、=或>b,分别返回-1、0或1 */
  if(a==b)
    return 0;
  else
    return (a-b)/abs(a-b);
}

Status visit(ElemType c)
{
  printf("%d ",c);
  return OK;
}

void main()
{
  Link p,h;
  LinkList L;
  Status i;
  int j,k;
  i=InitList(&L);
  if(!i) /* 初始化空的线性表L不成功 */
    exit(FALSE); /* 退出程序运行 */
  for(j=1;j<=2;j++)
  {
    MakeNode(&p,j); /* 生成由p指向、值为j的结点 */
    InsFirst(&L,L.tail,p); /* 插在表尾 */
  }
  OrderInsert(&L,0,cmp); /* 按升序插在有序表头 */
  for(j=0;j<=3;j++)
  {
    i=LocateElemP(L,j,&p,cmp);
    if(i)
      printf("链表中有值为%d的元素。\n",p->data);
    else
      printf("链表中没有值为%d的元素。\n",j);
  }
  printf("输出链表：");
  ListTraverse(L,visit); /* 输出L */
  for(j=1;j<=4;j++)
  {
    printf("删除表头结点：");
    DelFirst(&L,L.head,&p); /* 删除L的首结点，并以p返回 */
    if(p)
      printf("%d\n",GetCurElem(p));
    else
      printf("表空，无法删除 p=%u\n",p);
  }
  printf("L中结点个数=%d L是否空 %d(1:空 0:否)\n",ListLength(L),ListEmpty(L));
  MakeNode(&p,10);
  p->next=NULL; /* 尾结点 */
  for(j=4;j>=1;j--)
  {
    MakeNode(&h,j*2);
    h->next=p;
    p=h;
  } /* h指向一串5个结点，其值依次是2 4 6 8 10 */
  Append(&L,h); /* 把结点h链接在线性链表L的最后一个结点之后 */
  OrderInsert(&L,12,cmp); /* 按升序插在有序表尾头 */
  OrderInsert(&L,7,cmp); /* 按升序插在有序表中间 */
  printf("输出链表：");
  ListTraverse(L,visit); /* 输出L */
  for(j=1;j<=2;j++)
  {
    p=LocateElem(L,j*5,compare);
    if(p)
      printf("L中存在值为%d的结点。\n",j*5);
    else
      printf("L中不存在值为%d的结点。\n",j*5);
  }
  for(j=1;j<=2;j++)
  {
    LocatePos(L,j,&p); /* p指向L的第j个结点 */
    h=PriorPos(L,p); /* h指向p的前驱 */
    if(h)
      printf("%d的前驱是%d。\n",p->data,h->data);
    else
      printf("%d没前驱。\n",p->data);
  }
  k=ListLength(L);

  for(j=k-1;j<=k;j++)
  {
    LocatePos(L,j,&p); /* p指向L的第j个结点 */
    h=NextPos(p); /* h指向p的后继 */
    if(h)
      printf("%d的后继是%d。\n",p->data,h->data);
    else
      printf("%d没后继。\n",p->data);
  }
  printf("L中结点个数=%d L是否空 %d(1:空 0:否)\n",ListLength(L),ListEmpty(L));
  p=GetLast(L); /* p指向最后一个结点 */
  SetCurElem(p,15); /* 将最后一个结点的值变为15 */
  printf("第1个元素为%d 最后1个元素为%d\n",GetCurElem(GetHead(L)->next),GetCurElem(p));
  MakeNode(&h,10);
  InsBefore(&L,&p,h); /* 将10插到尾结点之前，p指向新结点 */
  p = p->next;
  MakeNode(&h,20);
  InsAfter(&L,&p,h); /* 将20插到尾结点之后 */
  k=ListLength(L);
  printf("依次删除表尾结点并输出其值：");
  for(j=0;j<=k;j++)
  {
    i=Remove(&L,&p);
    if(!i) /* 删除不成功 */
      printf("删除不成功 p=%u\n",p);
    else
      printf("%d ",p->data);
  }
  MakeNode(&p,29); /* 重建具有1个结点(29)的链表 */
  InsFirst(&L,L.head,p);
  DestroyList(&L); /* 销毁线性链表L */
  printf("销毁线性链表L之后: L.head=%u L.tail=%u L.len=%d\n",L.head,L.tail,L.len);
}

