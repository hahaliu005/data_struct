//二叉树的二叉链表存储表示
#include "include/header.h"
typedef char TElemType;
#define CHAR
#define Nil ' '
#define max(a,b) (a>=b?a:b)
#define __MAIN__
#define __REDEFINE__

typedef struct BiTNode{
  TElemType data;
  struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

Status InitBiTree(BiTree *T){
  *T = NULL;
  return OK;
}

Status DestroyBiTree(BiTree *T){
  if(*T){
    if((*T)->lchild){
      DestroyBiTree(&(*T)->lchild);
    }
    if((*T)->rchild){
      DestroyBiTree(&(*T)->rchild);
    }
    free(*T);
    *T = NULL;
  }
}

Status CreateBiTree(BiTree *T){
  TElemType ch;
  scanf("%c", &ch);
  if(ch == Nil){
    (*T) = NULL;
  }else{
    *T = (BiTree)malloc(sizeof(BiTNode));
    if(!(*T)){
      exit(OVERFLOW);
    }
    (*T)->data = ch;
    CreateBiTree(&(*T)->lchild);
    CreateBiTree(&(*T)->rchild);
  }
}

Status BiTreeEmpty(BiTree T){
  if(T){
    return FALSE;
  }else{
    return TRUE;
  }
}

#define ClearBiTree DestroyBiTree

int BiTreeDepth(BiTree T){
  int d1,d2;
  if(! T){
    return 0;
  }else{
    d1 = BiTreeDepth(T->lchild);
    d2 = BiTreeDepth(T->rchild);
    return 1 + max(d1, d2);
  }
}

TElemType Root(BiTree T){
  if(BiTreeEmpty(T)){
    return Nil;
  }else{
    return T->data;
  }
}

TElemType Value(BiTree p){
  return p->data;
}

void Assign(BiTree p, TElemType value){
  p->data = value;
}
#include "3.2.c"

TElemType Parent(BiTree T, TElemType e){
  LinkQueue q;
  QElemType a;
  if(T){
    InitQueue(&q);
    EnQueue(&q, T);
    while(!QueueEmpty(q)){
      DeQueue(&q, &a);
      if(a->lchild->data&&a->lchild->data==e || a->rchild->data&&a->rchild->data == e){
        return a->data;
      }else{
        if(a->lchild){
          EnQueue(&q, a->lchild);
        }
        if(a->rchild){
          EnQueue(&q, a->rchild);
        }
      }
    }
  }
  return Nil;
}

BiTree Point(BiTree T, TElemType s){
  LinkQueue q;
  QElemType a;
  if(T){
    InitQueue(&q);
    EnQueue(&q, T);
    while(!QueueEmpty(q)){
      DeQueue(&q, &a);
      if(a->data == s){
        return a;
      }
      if(a->lchild){
        EnQueue(&q,a->lchild);
      }
      if(a->rchild){
        EnQueue(&q, a->rchild);
      }
    }
  }
  return NULL;
}

TElemType LeftChild(BiTree T, TElemType e){
  LinkQueue q;
  QElemType a;
  if(T){
    InitQueue(&q);
    EnQueue(&q, T);
    while(! QueueEmpty(q)){
      DeQueue(&q, &a);
      if(a->data == e && a->lchild){
        return a->lchild->data;
      }
      if(a->lchild){
        EnQueue(&q, a->lchild);
      }
      if(a->rchild){
        EnQueue(&q, a->rchild);
      }
    }
  }
  return Nil;
}

TElemType RightChild(BiTree T, TElemType e){
  BiTree a;
  if(T){
    a = Point(T, e);
    if(a&&a->rchild){
      return a->rchild->data;
    }
  }
  return Nil;
}

TElemType LeftSibling(BiTree T, TElemType e){
  TElemType a;
  BiTree p;
  if(T){
    a = Parent(T, e);
    p = Point(T, a);
    if(p->lchild&&p->rchild&&p->rchild->data==e){
      return p->lchild->data;
    }
  }
  return Nil;
}

TElemType RightSibling(BiTree T, TElemType e){
  TElemType a;
  BiTree p;
  if(T){
    a = Parent(T, e);
    p = Point(T, a);
    if(p->lchild&&p->rchild&&p->lchild->data==e){
      return p->rchild->data;
    }
  }
  return Nil;
}

Status InsertChild(BiTree p, int LR, BiTree c){
  if(p){
    if(LR == 0){
      c->rchild = p->lchild;
      p->lchild = c;
    }else{
      c->lchild = p->rchild;
      p->rchild = c;
    }
  }
  return OK;
}

Status DeleteChild(BiTree p, int LR){
  if(p){
    if(LR==0){
      ClearBiTree(&p->lchild);
    }else{
      ClearBiTree(&p->rchild);
    }
    return OK;
  }
  return ERROR;
}

void PreOrderTraverse(BiTree T, Status(*visit)(TElemType)){
  if(T){
    visit(T->data);
    PreOrderTraverse(T->lchild, visit);
    PreOrderTraverse(T->rchild, visit);
  }
}

void InOrderTraverse(BiTree T, Status(*visit)(TElemType)){
  if(T){
    InOrderTraverse(T->lchild, visit);
    visit(T->data);
    InOrderTraverse(T->rchild, visit);
  }
}

#include"./3.1.c"
Status InOrderTraverse1(BiTree T, Status(*visit)(TElemType)){
  SqStack S;
  InitStack(&S);
  while(T || ! StackEmpty(S)){
    if(T){
      Push(&S, T);
      T = T->lchild;
    }else{
      Pop(&S, &T);
      if(! visit(T->data)){
        return ERROR;
      }
      T = T->rchild;
    }
  }
  printf("\n");
  return OK;
}

Status InOrderTraverse2(BiTree T, Status(*visit)(TElemType)){
  SqStack S;
  BiTree p;
  InitStack(&S);
  Push(&S, T);
  while(! StackEmpty(S)){
    while(GetTop(S, &p) && p){
      Push(&S, p->lchild);
    }
    Pop(&S, &p);
    if(! StackEmpty(S)){
      Pop(&S, &p);
      if(!visit(p->data)){
        return ERROR;
      }
      Push(&S, p->rchild);
    }
  }
  printf("\n");
  return OK;
}

void PostOrderTraverse(BiTree T, Status(*visit)(TElemType)){
  if(T){
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T->data);
  }
}

void LevelOrderTraverse(BiTree T, Status(*visit)(TElemType)){
  LinkQueue q;
  QElemType a;
  if(T){
    InitQueue(&q);
    EnQueue(&q, T);
    while(! QueueEmpty(q)){
      DeQueue(&q, &a);
      visit(a->data);
      if(a->lchild){
        EnQueue(&q, a->lchild);
      }
      if(a->rchild){
        EnQueue(&q, a->rchild);
      }
    }
    printf("\n");
  }
}

Status visitT(TElemType e)
{
#ifdef CHAR
  printf("%c ",e);
#endif
#ifdef INT
  printf("%d ",e);
#endif
  return OK;
}


void main()
{
  int i;
  BiTree T,p,c;
  TElemType e1,e2;
  InitBiTree(&T);
  printf("构造空二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
  e1=Root(T);
  if(e1!=Nil)
#ifdef CHAR
    printf("二叉树的根为: %c\n",e1);
#endif
#ifdef INT
  printf("二叉树的根为: %d\n",e1);
#endif
  else
    printf("树空，无根\n");
#ifdef CHAR
  printf("请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
#endif
#ifdef INT
  printf("请先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
#endif
  CreateBiTree(&T);
  printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
  e1=Root(T);
  if(e1!=Nil)
#ifdef CHAR
    printf("二叉树的根为: %c\n",e1);
#endif
#ifdef INT
  printf("二叉树的根为: %d\n",e1);
#endif
  else
    printf("树空，无根\n");
  printf("中序递归遍历二叉树:\n");
  InOrderTraverse(T,visitT);
  printf("\n中序非递归遍历二叉树:\n");
  InOrderTraverse1(T,visitT);
  printf("中序非递归遍历二叉树(另一种方法):\n");
  InOrderTraverse2(T,visitT);
  printf("后序递归遍历二叉树:\n");
  PostOrderTraverse(T,visitT);
  printf("\n层序遍历二叉树:\n");
  LevelOrderTraverse(T,visitT);
  printf("请输入一个结点的值: ");
#ifdef CHAR
  scanf("%*c%c",&e1);
#endif
#ifdef INT
  scanf("%d",&e1);
#endif
  p=Point(T,e1); /* p为e1的指针 */
#ifdef CHAR
  printf("结点的值为%c\n",Value(p));
#endif
#ifdef INT
  printf("结点的值为%d\n",Value(p));
#endif
  printf("欲改变此结点的值，请输入新值: ");
#ifdef CHAR
  scanf("%*c%c%*c",&e2);
#endif
#ifdef INT
  scanf("%d",&e2);
#endif
  Assign(p,e2);
  printf("层序遍历二叉树:\n");
  LevelOrderTraverse(T,visitT);
  e1=Parent(T,e2);
  if(e1!=Nil)
#ifdef CHAR
    printf("%c的双亲是%c\n",e2,e1);
#endif
#ifdef INT
  printf("%d的双亲是%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%c没有双亲\n",e2);
#endif
#ifdef INT
  printf("%d没有双亲\n",e2);
#endif
  e1=LeftChild(T,e2);
  if(e1!=Nil)
#ifdef CHAR
    printf("%c的左孩子是%c\n",e2,e1);
#endif
#ifdef INT
  printf("%d的左孩子是%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%c没有左孩子\n",e2);
#endif
#ifdef INT
  printf("%d没有左孩子\n",e2);
#endif
  e1=RightChild(T,e2);
  if(e1!=Nil)
#ifdef CHAR
    printf("%c的右孩子是%c\n",e2,e1);
#endif
#ifdef INT
  printf("%d的右孩子是%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%c没有右孩子\n",e2);
#endif
#ifdef INT
  printf("%d没有右孩子\n",e2);
#endif
  e1=LeftSibling(T,e2);
  if(e1!=Nil)
#ifdef CHAR
    printf("%c的左兄弟是%c\n",e2,e1);
#endif
#ifdef INT
  printf("%d的左兄弟是%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%c没有左兄弟\n",e2);
#endif
#ifdef INT
  printf("%d没有左兄弟\n",e2);
#endif
  e1=RightSibling(T,e2);
  if(e1!=Nil)
#ifdef CHAR
    printf("%c的右兄弟是%c\n",e2,e1);
#endif
#ifdef INT
  printf("%d的右兄弟是%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%c没有右兄弟\n",e2);
#endif
#ifdef INT
  printf("%d没有右兄弟\n",e2);
#endif
  InitBiTree(&c);
  printf("构造一个右子树为空的二叉树c:\n");
#ifdef CHAR
  printf("请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
#endif
#ifdef INT
  printf("请先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
#endif
  CreateBiTree(&c);
  printf("先序递归遍历二叉树c:\n");
  PreOrderTraverse(c,visitT);
  printf("\n树c插到树T中,请输入树T中树c的双亲结点 c为左(0)或右(1)子树: ");
#ifdef CHAR
  scanf("%*c%c%d",&e1,&i);
#endif
#ifdef INT
  scanf("%d%d",&e1,&i);
#endif
  p=Point(T,e1); /* p是T中树c的双亲结点指针 */
  InsertChild(p,i,c);
  printf("先序递归遍历二叉树:\n");
  PreOrderTraverse(T,visitT);
  printf("\n删除子树,请输入待删除子树的双亲结点  左(0)或右(1)子树: ");
#ifdef CHAR
  scanf("%*c%c%d",&e1,&i);
#endif
#ifdef INT
  scanf("%d%d",&e1,&i);
#endif
  p=Point(T,e1);
  DeleteChild(p,i);
  printf("先序递归遍历二叉树:\n");
  PreOrderTraverse(T,visitT);
  printf("\n");
  DestroyBiTree(&T);
}
