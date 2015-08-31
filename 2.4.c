// 多项式的链式表示
#include "include/header.h"

typedef struct{
  float coef;
  int expn;
}term, ElemType;

typedef struct LNode{
  ElemType data;
  struct LNode * next;
} * Link, * Position, LNode;

typedef struct{
  Link head, tail;
  int len;
} LinkList;


typedef LinkList polynomial;

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
    return OK;
  }else{
    return FALSE;
  }
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

int cmp(ElemType a,ElemType b)
{ /* 根据a<、=或>b,分别返回-1、0或1 */
  if(a.expn==b.expn)
    return 0;
  else
    return (a.expn-b.expn)/abs(a.expn-b.expn);
}

Status visit(ElemType c)
{
  printf("%d ",c);
  return OK;
}

#define DestroyPolyn DestroyList
#define PolynLength ListLength

/* Status OrderInsertMerge(LinkList *L,ElemType e,int(* compare)(term,term)) */
/* { /1* 按有序判定函数compare()的约定，将值为e的结点插入或合并到升序链表L的适当位置 *1/ */
/*   Position q,s; */
/*   if(LocateElemP(*L, e, &q, compare)){ */
/*     q->data.coef += e.coef; */
/*     if(! q->data.coef){ */
/*       s = PriorPos(*L, q); */
/*       if(!s){ */
/*         s = (*L).head; */
/*       } */
/*       DelFirst(L, s, &q); */
/*       FreeNode(&q); */
/*     } */
/*     return OK; */
/*   }else{ */
/*     if(MakeNode(&s, e)){ */
/*       InsFirst(L, q, s); */
/*       return OK; */
/*     }else{ */
/*       return ERROR; */
/*     } */
/*   } */
/* } */

Status OrderInsertMerge(LinkList *L,ElemType e,int(* compare)(term,term))
{ /* 按有序判定函数compare()的约定，将值为e的结点插入或合并到升序链表L的适当位置 */
  Position q,s;
  if(LocateElemP(*L,e,&q,compare)) /* L中存在该指数项 */
  {
    q->data.coef+=e.coef; /* 改变当前结点系数的值 */
    if(!q->data.coef) /* 系数为0 */
    { /* 删除多项式L中当前结点 */
      s=PriorPos(*L,q); /* s为当前结点的前驱 */
      if(!s) /* q无前驱 */
        s=(*L).head;
      DelFirst(L,s,&q);
      FreeNode(&q);
    }
    return OK;
  }
  else /* 生成该指数项并插入链表 */
    if(MakeNode(&s,e)) /* 生成结点成功 */
    {
      InsFirst(L,q,s);
      return OK;
    }
    else /* 生成结点失败 */
      return ERROR;
}


void CreatPolyn(polynomial *P, int m){
  int i;
  Link q,s;
  ElemType e;
  InitList(P);
  printf("请依次输入%d个系数,指数:\n", m);
  for(i=0;i<m;i++){
    scanf("%f %d", &e.coef, &e.expn);
    if(!LocateElemP(*P, e, &q, cmp)){
      if(MakeNode(&s,e)){
        InsFirst(P,q,s);
      }
    }
  }
}

void PrintPolyn(polynomial P){
  printf("系数\t指数\n");
  Link q;
  q = P.head->next;
  while(q){
    printf("%f\t%d\n", q->data.coef, q->data.expn);
    q = q->next;
  }
}

void AddPolyn(polynomial *Pa, polynomial *Pb){
  Position qb;
  term b;
  qb = Pb->head->next;
  while(qb){
    printf("merge %f %d\n", qb->data.coef, qb->data.expn);
    b = qb->data;
    printf("before insert\n");
    PrintPolyn(*Pa);
    OrderInsertMerge(Pa, b, cmp);
    printf("after insert:\n");
    PrintPolyn(*Pa);
    qb = qb->next;
  }
  DestroyPolyn(Pb);
}

void AddPolyn1(polynomial *Pa,polynomial *Pb)
{ /* 另一种多项式加法的算法:Pa=Pa+Pb,并销毁一元多项式Pb */
  Position qb;
  term b;
  qb=GetHead(*Pb); /* qb指向Pb的头结点 */
  qb=qb->next; /* qb指向Pb的第一个结点 */
  while(qb)
  {
    b=GetCurElem(qb);
    OrderInsertMerge(Pa,b,cmp);
    qb=qb->next;
  }
  DestroyPolyn(Pb); /* 销毁Pb */
}


void SubtractPolyn(polynomial *Pa, polynomial *Pb){
  Link p, q;
  p = Pb->head->next;
  while(p){
    if(LocateElemP(*Pa, p->data, &q, cmp)){
      q->data.coef -= p->data.coef;
    }else{
      InsAfter(Pa, &q, p);
    }
    p = p->next;
  }
}


void MultiplyPolyn(polynomial *Pa, polynomial *Pb){
  polynomial Pc;
  InitList(&Pc);
  Link qa, qb, qc;
  term c;
  qa = Pa->head->next;
  qb = Pb->head->next;
  while(qa){
    qb = Pb->head->next;
    while(qb){
      printf("qa:%f %d qb:%f %d\n", qa->data.coef, qa->data.expn, qb->data.coef, qb->data.expn);
      c.coef = qa->data.coef * qb->data.coef;
      c.expn = qa->data.expn + qb->data.expn;
      printf("c:%f %d\n", c.coef, c.expn);
      OrderInsertMerge(&Pc, c, cmp);
      printf("after insert Pc:\n");
      PrintPolyn(Pc);
      qb = qb->next;
    }
    qa = qa->next;
  }
  DestroyPolyn(Pb);
  ClearList(Pa);
  Pa->head = Pc.head;
  Pa->tail = Pc.tail;
  Pa->len = Pc.len;
}

void main()
{
  polynomial p,q;
  int m;
  printf("请输入第一个一元多项式的非零项的个数：");
  scanf("%d",&m);
  CreatPolyn(&p,m);
  PrintPolyn(p);
  printf("请输入第二个一元多项式的非零项的个数：");
  scanf("%d",&m);
  CreatPolyn(&q,m);
  PrintPolyn(q);
  MultiplyPolyn(&p,&q);
  printf("两个一元多项式相乘的结果：\n");
  PrintPolyn(p);
  return;

  AddPolyn(&p,&q);
  printf("两个一元多项式相加的结果：\n");
  PrintPolyn(p);
  printf("请输入第三个一元多项式的非零项的个数：");
  scanf("%d",&m);
  CreatPolyn(&q,m);
  AddPolyn1(&p,&q);
  printf("两个一元多项式相加的结果(另一种方法)：\n");
  PrintPolyn(p);
  printf("请输入第四个一元多项式的非零项的个数：");
  scanf("%d",&m);
  CreatPolyn(&q,m);
  SubtractPolyn(&p,&q);
  printf("两个一元多项式相减的结果：\n");
  PrintPolyn(p);
  printf("请输入第五个一元多项式的非零项的个数：");
  scanf("%d",&m);
  CreatPolyn(&q,m);
  MultiplyPolyn(&p,&q);
  printf("两个一元多项式相乘的结果：\n");
  PrintPolyn(p);
  DestroyPolyn(&p);
}
