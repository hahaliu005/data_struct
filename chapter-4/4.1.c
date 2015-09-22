// 串的堆分配存储表示
#include"include/header.h"

typedef struct{
  char * ch;
  int length;
}HString;

Status StrAssign(HString *T, char *chars){
  if(T->ch){
    free(T->ch);
  }
  int len, i;
  len = strlen(chars);
  if(len){
    T->ch = (char *)malloc(len * sizeof(char));
    for(i=0; i<len; i++){
      T->ch[i] = chars[i];
    }
    T->length = len;
  }else{
    T->ch = NULL;
    T->length = 0;
  }
  return OK;
}

int StrLength(HString S){
  return S.length;
}

int StrCompare(HString S,HString T)
{ /* 若S>T,则返回值>0;若S=T,则返回值=0;若S<T,则返回值<0 */
  int i;
  for(i=0;i<S.length&&i<T.length;++i)
    if(S.ch[i]!=T.ch[i])
      return S.ch[i]-T.ch[i];
  return S.length-T.length;
}

Status StrCopy(HString *S, HString H){
  if(S->ch){
    free(S->ch);
  }
  int i;
  S->ch = (char *)malloc(H.length * sizeof(char));
  for(i = 0; i < H.length; i++){
    S->ch[i] = H.ch[i];
  }
  S->length = H.length;
  return OK;
}

Status StrEmpty(HString S){
  if(S.length == 0){
    return TRUE;
  }else{
    return FALSE;
  }
}

Status ClearString(HString *S){
  if(S->ch){
    free(S->ch);
    S->ch = NULL;
    S->length = 0;
  }
  return OK;
}

Status Concat(HString *T, HString S1, HString S2){
  if(T->ch){
    free(T->ch);
  }
  int len_s1, len_s2, i;
  len_s1 = StrLength(S1);
  len_s2 = StrLength(S2);
  T->ch = (char *)malloc((len_s1 + len_s2) * sizeof(char));
  for(i = 0; i < len_s1; i++){
    (T->ch)[i] = S1.ch[i];
  }
  for(i = len_s1; i < len_s1 + len_s2; i++){
    T->ch[i] = S2.ch[i - len_s1];
  }
  T->length = len_s1 + len_s2;
  return OK;
}

Status SubString(HString *P, HString S, int pos, int len){
  if(pos < 1 || pos > StrLength(S) || len < 0 || len > StrLength(S) - pos + 1){
    return ERROR;
  }
  P->ch = (char *)malloc(len * sizeof(char));
  int i;
  for(i=0;i<len;i++){
    P->ch[i] = S.ch[pos + i - 1];
  }
  P->length = len;
  return OK;
}

Status InitString(HString *S){
  S->ch = NULL;
  S->length = 0;
  return OK;
}

Status Index(HString S, HString T, int pos){
  int len_s, len_t, i;
  HString Sub;
  len_s = StrLength(S);
  len_t = StrLength(T);
  InitString(&Sub);
  if(pos > 0){
    i = pos;
    while(i <= len_s - len_t + 1){
      SubString(&Sub, S, i, len_t);
      if(StrCompare(Sub, T) != 0){
        i++;
      }else{
        return i;
      }
    }
  }
  return 0;
}

Status StrInsert(HString *S, int pos, HString T){
  int len_t, len_s, new_len_s, i, j;
  len_t = StrLength(T);
  len_s = StrLength(*S);
  if(pos < 1 || pos > len_s + 1){
    return ERROR;
  }
  if(T.length){
    new_len_s = len_s + len_t;
    S->ch = (char *)realloc(S->ch, new_len_s * sizeof(char));
    if(!S->ch){
      exit(OVERFLOW);
    }
    for(i=len_s - 1; i >= pos - 1; i--){
      S->ch[i + len_t] = S->ch[i];
    }
    for(i=0;i<len_t;i++){
      (*S).ch[pos-1+i]=T.ch[i];
    }
    S->length = new_len_s;
  }
  return OK;
}

Status StrDelete(HString *S, int pos, int len){
  int i, len_s, new_len;
  len_s = StrLength(*S);
  if(pos < 1 || pos > len_s || len < 0 || len > len_s - pos + 1){
    return ERROR;
  }
  new_len = len_s - len;
  for(i = pos - 1; i < new_len; i++){
    S->ch[i] = S->ch[i+len];
  }
  S->length = new_len;
  return OK;
}

Status Replace(HString *S, HString T, HString V){
  int i = 1, len_t, len_v;
  if(StrEmpty(*S)){
    return ERROR;
  }
  len_t = StrLength(T);
  len_v = StrLength(V);
  do{
    i = Index(*S, T, i);
    if(i){
      StrDelete(S, i, len_t);
      StrInsert(S, i, V);
      i += len_v;
    }
  }while(i);
  return OK;
}

void DestroyString(HString *S){
  //堆分配类型无法销毁
}

void StrPrint(HString S){
  int i;
  for(i=0;i<S.length;i++){
    printf("%c", S.ch[i]);
  }
  printf("\n");
}

#ifndef __MAIN__
void main()
{
  int i;
  char c,*p="God bye!",*q="God luck!";
  HString t,s,r;
  InitString(&t); /* HString类型必需初始化 */
  InitString(&s);
  InitString(&r);
  StrAssign(&t,p);
  printf("串t为: ");
  StrPrint(t);
  printf("串长为%d 串空否？%d(1:空 0:否)\n",StrLength(t),StrEmpty(t));
  StrAssign(&s,q);
  printf("串s为: ");
  StrPrint(s);
  i=StrCompare(s,t);
  if(i<0)
    c='<';
  else if(i==0)
    c='=';
  else
    c='>';
  printf("串s%c串t\n",c);
  Concat(&r,t,s);
  printf("串t联接串s产生的串r为: ");
  StrPrint(r);
  StrAssign(&s,"oo");
  printf("串s为: ");
  StrPrint(s);
  StrAssign(&t,"o");
  printf("串t为: ");
  StrPrint(t);
  Replace(&r,t,s);
  printf("把串r中和串t相同的子串用串s代替后，串r为:\n");
  StrPrint(r);
  ClearString(&s);
  printf("串s清空后，串长为%d 空否？%d(1:空 0:否)\n",StrLength(s),StrEmpty(s));
  SubString(&s,r,6,4);
  printf("串s为从串r的第6个字符起的4个字符，长度为%d 串s为: ",s.length);
  StrPrint(s);
  StrCopy(&t,r);
  printf("复制串t为串r,串t为: ");
  StrPrint(t);
  StrInsert(&t,6,s);
  printf("在串t的第6个字符前插入串s后，串t为: ");
  StrPrint(t);
  StrDelete(&t,1,5);
  printf("从串t的第1个字符起删除5个字符后,串t为: ");
  StrPrint(t);
  printf("%d是从串t的第1个字符起，和串s相同的第1个子串的位置\n",Index(t,s,1));
  printf("%d是从串t的第2个字符起，和串s相同的第1个子串的位置\n",Index(t,s,2));
}
#endif
