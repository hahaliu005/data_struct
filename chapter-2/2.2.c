// 线性表的顺序存储结构
#include "include/header.h"
#define LIST_INIT_SIZE 10
#define LISTINCREMENT 10
typedef struct{
  ElemType *elem;
  int length;
  int listsize;
} SqList;

Status InitList(SqList *L){
  (*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
  if(!(*L).elem){
    exit(OVERFLOW);
  }
  (*L).length = 0;
  (*L).listsize = LIST_INIT_SIZE;
  return OK;
}

Status DestroyList(SqList *L){
  free((*L).elem);
  (*L).length = 0;
  (*L).listsize = 0;
  return OK;
}

Status ClearList(SqList *L){
  (*L).length = 0;
  return OK;
}

Boolean ListEmpty(SqList L){
  return (L).length == 0;
}

int ListLength(SqList L){
  return L.length;
}

Status GetElem(SqList L, int i, ElemType *e){
  if(i<1 || i>ListLength(L)){
    exit(ERROR);
  }
  *e = *(L.elem + i-1);
  return OK;
}

int LocateElem(SqList L, ElemType e, Status (* compare)(ElemType, ElemType)){
  ElemType *p;
  int i = 1;
  p = L.elem;
  while (i <= L.length && !compare(*p, e)){
    ++i;
    ++p;
  }
  if(i<=L.length){
    return i;
  }else{
    return 0;
  }
}

Status PriorElem(SqList L, ElemType cur_e, ElemType *pre_e){
  ElemType *p;
  int i = 2;
  p = L.elem + 1;
  while(i <= L.length && *p != cur_e){
    p++;
    i++;
  }
  if(i<=L.length){
    *pre_e = *(--p);
    return OK;
  }else{
    return INFEASIBLE;
  }
}

Status NextElem(SqList L, ElemType cur_e, ElemType *next_e){
  ElemType *p;
  int i = 1;
  p = L.elem;
  while(i < L.length && *p != cur_e){
    p++;
    i++;
  }
  if(i < L.length){
    *next_e = *(++p);
    return OK;
  }else{
    return INFEASIBLE;
  }
}

Status ListInsert(SqList *L, int i, ElemType e){
  ElemType *newbase, *q, *p;
  if(i<1 && i>(*L).length + 1){
    return ERROR;
  }
  if((*L).length >= (*L).listsize){
    newbase = (ElemType *)realloc((*L).elem, ((*L).listsize + LISTINCREMENT) * sizeof(ElemType));
    if(!newbase){
      exit(OVERFLOW);
    }
    (*L).elem = newbase;
    (*L).listsize += LISTINCREMENT;
  }
  q = (*L).elem + i - 1;
  p = (*L).elem + (*L).length - 1;
  while(p >= q){
    *(p+1) = *p;
    --p;
  }
  *q = e;
  ++(*L).length;
  return OK;
}

Status ListDelete(SqList *L, int i, ElemType *e){
  if(i<1 || i>(*L).length){
    return ERROR;
  }
  ElemType *p, *q;
  p = (*L).elem + i - 1;
  q = (*L).elem + (*L).length - 1;
  *e = *p;
  while(p < q){
    *p = *(p+1);
    ++p;
  }
  --(*L).length;
  return OK;
}

Status ListTraverse(SqList L, void(*vi)(ElemType *)){
  int i;
  ElemType *p;
  p = L.elem;
  for(i=1;i<=L.length;++i,++p){
    vi(p);
  }
  return OK;
}

Boolean equal(ElemType a, ElemType b){
  return a == b;
}

//将Lb联接到La中
Status Union(SqList *La, SqList Lb){
  int i, La_len, Lb_len;
  La_len = ListLength(*La);
  Lb_len = ListLength(Lb);
  ElemType e;
  for(i=1;i<=Lb_len; i++){
    GetElem(Lb, i, &e);
    if(!LocateElem(*La, e, equal)){
      ListInsert(La, ++La_len, e);
    }
  }
}

// 将la和Lb组合成Lc, 需要是非递减排列
Status MergeList(SqList La, SqList Lb, SqList *Lc){
  InitList(Lc);
  int i=1,j=1,k=0,La_len,Lb_len;
  ElemType ai,bj;
  La_len=ListLength(La);
  Lb_len=ListLength(Lb);
  while((i <= La_len) && (j <= Lb_len)){
    GetElem(La, i, &ai);
    GetElem(Lb, j, &bj);
    if(ai<bj){
      ListInsert(Lc, ++k, ai); ++i;
    }else{
      ListInsert(Lc, ++k, bj); ++j;
    }
  }
  while(i <= La_len){
    GetElem(La, i++, &ai);
    ListInsert(Lc, ++k, ai);
  }
  while(j <= Lb_len){
    GetElem(Lb, j++, &bj);
    ListInsert(Lc, ++k, bj);
  }
}

// 辅助函数

Status comp(ElemType c1,ElemType c2) /* 数据元素判定函数(平方关系) */
{
  if(c1==c2*c2)
    return TRUE;
  else
    return FALSE;
}

void visit(ElemType *c) /* ListTraverse()调用的函数(类型要一致) */
{
  printf("%d \n",*c);
}

void dbl(ElemType *c) /* ListTraverse()调用的另一函数(元素值加倍) */
{
  *c*=2;
}

void main()
{
  SqList L;
  ElemType e,e0;
  Status i;
  int j,k;
  i=InitList(&L);
  printf("初始化L后：L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
  for(j=1;j<=5;j++)
    i=ListInsert(&L,1,j);
  printf("在L的表头依次插入1～5后：*L.elem=");
  for(j=1;j<=5;j++)
    printf("%d ",*(L.elem+j-1));
  printf("\n");
  printf("L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
  i=ListEmpty(L);
  printf("L是否空：i=%d(1:是 0:否)\n",i);
  i=ClearList(&L);
  printf("清空L后：L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
  i=ListEmpty(L);
  printf("L是否空：i=%d(1:是 0:否)\n",i);
  for(j=1;j<=10;j++)
    ListInsert(&L,j,j);
  printf("在L的表尾依次插入1～10后：*L.elem=");
  for(j=1;j<=10;j++)
    printf("%d ",*(L.elem+j-1));
  printf("\n");
  printf("L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
  ListInsert(&L,1,0);
  printf("在L的表头插入0后：*L.elem=");
  for(j=1;j<=ListLength(L);j++) /* ListLength(L)为元素个数 */
    printf("%d ",*(L.elem+j-1));
  printf("\n");
  printf("L.elem=%u(有可能改变) L.length=%d(改变) L.listsize=%d(改变)\n",L.elem,L.length,L.listsize);
  GetElem(L,5,&e);
  printf("第5个元素的值为：%d\n",e);
  for(j=3;j<=4;j++)
  {
    k=LocateElem(L,j,comp);
    if(k)
      printf("第%d个元素的值为%d的平方\n",k,j);
    else
      printf("没有值为%d的平方的元素\n",j);
  }
  for(j=1;j<=2;j++) /* 测试头两个数据 */
  {
    GetElem(L,j,&e0); /* 把第j个数据赋给e0 */
    i=PriorElem(L,e0,&e); /* 求e0的前驱 */
    if(i==INFEASIBLE)
      printf("元素%d无前驱\n",e0);
    else
      printf("元素%d的前驱为：%d\n",e0,e);
  }
  for(j=ListLength(L)-1;j<=ListLength(L);j++) /* 最后两个数据 */
  {
    GetElem(L,j,&e0); /* 把第j个数据赋给e0 */
    i=NextElem(L,e0,&e); /* 求e0的后继 */
    if(i==INFEASIBLE)
      printf("元素%d无后继\n",e0);
    else
      printf("元素%d的后继为：%d\n",e0,e);
  }
  k=ListLength(L); /* k为表长 */
  for(j=k+1;j>=k;j--)
  {
    i=ListDelete(&L,j,&e); /* 删除第j个数据 */
    if(i==ERROR)
      printf("删除第%d个数据失败\n",j);
    else
      printf("删除的元素值为：%d\n",e);
  }
  printf("依次输出L的元素：");
  ListTraverse(L,visit); /* 依次对元素调用visit()，输出元素的值 */
  printf("L的元素值加倍后：");
  ListTraverse(L,dbl); /* 依次对元素调用dbl()，元素值乘2 */
  ListTraverse(L,visit);
  DestroyList(&L);
  printf("销毁L后：L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);

  SqList La,Lb;
  InitList(&La);
  InitList(&Lb);
  for(j=1;j<=5;j++)
    i=ListInsert(&La,1,j);
  for(j=6;j<=10;j++)
    i=ListInsert(&Lb,1,j);
  printf("init La and Lb\n");
  printf("La:\n");
  ListTraverse(La, visit);
  printf("Lb\n");
  ListTraverse(Lb, visit);
  printf("union La and Lb\n");
  Union(&La, Lb);
  printf("New La:\n");
  ListTraverse(La, visit);

  SqList Lc;
  printf("clear list La, Lb\n");
  ClearList(&La);
  ClearList(&Lb);
  for(j=1;j<=5;j++){
    i=ListInsert(&La,j,j);
  }
  for(j=1;j<=5;j++){
    i=ListInsert(&Lb,j,j);
  }
  printf("MergeList La and Lb\n");
  MergeList(La, Lb, &Lc);
  printf("Lc:\n");
  ListTraverse(Lc, visit);
}

