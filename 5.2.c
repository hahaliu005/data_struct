// 广义表的头尾链表存储
#include"include/header.h"
#define __MAIN__ 1
#define max(a,b) (a>=b ? a : b)
#include "./4.1.c"
typedef int AtomType;

typedef enum{
  ATOM, LIST
} ElemTag;

typedef struct GLNode{
  ElemTag tag;
  union{
    AtomType atom;
    struct {
      struct GLNode *hp, *tp;
    }ptr;
  } a;
} * GList, GLNode;

Status sever(HString *str,HString *hstr)
{
  int n,i=1,k=0;
  HString ch,c1,c2,c3;
  InitString(&ch);
  InitString(&c1);
  InitString(&c2);
  InitString(&c3);
  StrAssign(&c1,",");
  StrAssign(&c2,"(");
  StrAssign(&c3,")");
  n=StrLength(*str);
  do
  {
    SubString(&ch,*str,i,1);
    if(!StrCompare(ch,c2))
      ++k;
    else if(!StrCompare(ch,c3))
      --k;
    ++i;
  }while(i<=n&&StrCompare(ch,c1)||k!=0);
  if(i<=n)
  {
    StrCopy(&ch,*str);
    SubString(hstr,ch,1,i-2);
    SubString(str,ch,i,n-i+1);
  }
  else
  {
    StrCopy(hstr,*str);
    ClearString(str);
  }
  return OK;
}

Status CreateGList(GList *L,HString S)
{
  HString emp,sub,hsub;
  GList p,q;
  InitString(&emp);
  InitString(&sub);
  InitString(&hsub);
  StrAssign(&emp,"()");
  if(!StrCompare(S,emp))
    *L=NULL;
  else
  {
    *L=(GList)malloc(sizeof(GLNode));
    if(!*L)
      exit(OVERFLOW);
    if(StrLength(S)==1)
    {
      (*L)->tag=ATOM;
      (*L)->a.atom=S.ch[0];
    }
    else
    {
      (*L)->tag=LIST;
      p=*L;
      SubString(&sub,S,2,StrLength(S)-2);
      do
      {
        sever(&sub,&hsub);
        CreateGList(&p->a.ptr.hp,hsub);
        q=p;
        if(!StrEmpty(sub))
        {
          p=(GList)malloc(sizeof(GLNode));
          if(!p)
            exit(OVERFLOW);
          p->tag=LIST;
          q->a.ptr.tp=p;
        }
      }while(!StrEmpty(sub));
      q->a.ptr.tp=NULL;
    }
  }
  return OK;
}

Status InitGList(GList *L){
  *L = NULL;
  return OK;
}

void DestroyGList(GList *L){
  GList q1, q2;
  if(! *L){
    if((*L)->tag == ATOM){
      free(*L);
      *L = NULL;
    }else{
      q1 = (*L)->a.ptr.hp;
      q2 = (*L)->a.ptr.tp;
      free(*L);
      *L = NULL;
      DestroyGList(&q1);
      DestroyGList(&q2);
    }
  }
}

Status CopyGList(GList *T, GList L){
  if(!L){
    *T = NULL;
  }else{
    (*T) = (GList)malloc(sizeof(GLNode));
    if(*T){
      exit(OVERFLOW);
    }
    (*T)->tag = L->tag;
    if(L->tag == ATOM){
      (*T)->a.atom = L->a.atom;
    }else{
      CopyGList(&((*T)->a.ptr.hp), L->a.ptr.hp);
      CopyGList(&((*T)->a.ptr.tp), L->a.ptr.tp);
    }
  }
}

int GListLength(GList L){
  int len;
  if(! L){
    return 0;
  }
  if(L->tag == ATOM){
    return 1;
  }
  len = 0;
  while(L){
    L = L->a.ptr.tp;
    len++;
  }
  return len;
}

int GListDepth(GList L){
  if(!L){
    return 1;
  }
  if(L->tag == ATOM){
    return 0;
  }
  int max=0, dep;
  GList pp;
  for(pp=L;pp;pp=pp->a.ptr.tp){
    dep = GListDepth(pp->a.ptr.hp);
    if(dep > max){
      max = dep;
    }
  }
  return 1 + max;
}



Status GListEmpty(GList L){
  if(!L){
    return TRUE;
  }else{
    return FALSE;
  }
}

GList GetHead(GList L){
  if(!L){
    exit(0);
  }
  GList p, h;
  p = L->a.ptr.tp;
  L->a.ptr.tp = NULL;
  CopyGList(&h, L);
  L->a.ptr.tp = p;
  return h;
}

GList GetTail(GList L){
  if(!L){
    exit(0);
  }
  GList h;
  CopyGList(&h, L->a.ptr.tp);
  return h;
}

Status InsertFirst_GL(GList *L, GList e){
  GList p;
  p = (GList)malloc(sizeof(GLNode));
  if(!p){
    exit(OVERFLOW);
  }
  p->tag = LIST;
  p->a.ptr.hp = e;
  p->a.ptr.tp = *L;
  (*L) = p;
  return OK;
}

Status DeleteFirst_GL(GList *L, GList *e){
  GList p;
  *e = (*L)->a.ptr.hp;
  p = *L;
  *L = (*L)->a.ptr.tp;
  free(p);
  return OK;
}

void Traverse_GL(GList L, void(*v)(AtomType)){
  if(L){
    if(L->tag == ATOM){
      v(L->a.atom);
    }else{
      Traverse_GL(L->a.ptr.hp, v);
      Traverse_GL(L->a.ptr.tp, v);
    }
  }
}

void visit(AtomType e)
{
  printf("%c ", e);
}

void main()
{
  int size = 80;
  char p[size];
  GList l,m;
  HString t; /* 与main5-51.c不同 */
  InitString(&t); /* 增加此句 */
  InitGList(&l);
  InitGList(&m);
  printf("空广义表l的深度=%d l是否空？%d(1:是 0:否)\n",GListDepth(l),GListEmpty(l));
  printf("请输入广义表l(书写形式：空表:(),单原子:a,其它:(a,(b),b)):\n");
  fgets(p, size, stdin);
  printf("hahahah ;%s %d\n", p, strlen(p));

  int len = strlen(p);
  if (len > 0 && p[len-1] == '\n'){
    p[len-1] = '\0';
  }
  printf("hahaha: %s len:%d\n", p, strlen(p));

  StrAssign(&t,p);

  CreateGList(&l,t);
  printf("广义表l的长度=%d\n",GListLength(l));
  printf("广义表l的深度=%d l是否空？%d(1:是 0:否)\n",GListDepth(l),GListEmpty(l));
  printf("遍历广义表l：\n");
  Traverse_GL(l,visit);
  printf("\n复制广义表m=l\n");
  CopyGList(&m,l);
  printf("广义表m的长度=%d\n",GListLength(m));
  printf("广义表m的深度=%d\n",GListDepth(m));
  printf("遍历广义表m：\n");
  Traverse_GL(m,visit);
  DestroyGList(&m);
  m=GetHead(l);
  printf("\nm是l的表头，遍历广义表m：\n");
  Traverse_GL(m,visit);
  DestroyGList(&m);
  m=GetTail(l);
  printf("\nm是l的表尾，遍历广义表m：\n");
  Traverse_GL(m,visit);
  InsertFirst_GL(&m,l);
  printf("\n插入l为m的表头，遍历广义表m：\n");
  Traverse_GL(m,visit);
  printf("\n删除m的表头，遍历广义表m：\n");
  DestroyGList(&l);
  DeleteFirst_GL(&m,&l);
  Traverse_GL(m,visit);
  printf("\n");
  DestroyGList(&m);
}


