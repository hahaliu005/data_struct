// 这是一个三元组
#include "include/header.h"

typedef int ElemType;
typedef ElemType * Triplet;

Status InitTriplet(Triplet *T, ElemType v1, ElemType v2, ElemType v3){
  *T = (ElemType *)malloc(3 * sizeof(ElemType));
  if(!*T){
    exit(OVERFLOW);
  }
  (*T)[0] = v1;
  (*T)[1] = v2;
  (*T)[2] = v3;
  return OK;
}

Status DestroyTriplet(Triplet *T){
  free(*T);
  *T = NULL;
  return OK;
}

Status Get(Triplet T, int i, ElemType *e){
  if(i<1 || i >3){
    return ERROR;
  }
  *e = T[i-1];
  return OK;
}

Status Put(Triplet T, int i, ElemType e){
  if(i<1 || i >3){
    return ERROR;
  }
  T[i-1] = e;
  return OK;
}

Status IsAscending(Triplet T){
  T[0] <= T[1] && T[1] <= T[2];
}

Status IsDescending(Triplet T){
  T[0] >= T[1] && T[1] >= T[2];
}

Status Max(Triplet T, ElemType *e){
  if(T[0] >= T[1]){
    if(T[0] >= T[2]){
      *e = T[0];
    }else{
      *e = T[2];
    }
  }else{
    if(T[1] >= T[2]){
      *e = T[1];
    }else{
      *e = T[2];
    }
  }
}

Status Min(Triplet T, ElemType *e){
  if(T[0] <= T[1]){
    if(T[0] <= T[2]){
      *e = T[0];
    }else{
      *e = T[2];
    }
  }else{
    if(T[1] <= T[2]){
      *e = T[1];
    }else{
      *e = T[2];
    }
  }
}


int main(){
  Triplet T;
  ElemType m;
  Status i;
  i=InitTriplet(&T,5,7,9);
  /*i=InitTriplet(&T,5.0,7.1,9.3); /* 当ElemType为双精度型时,可取代上句 */
  printf("调用初始化函数后，i=%d(1:成功) T的三个值为：%d %d %d\n",i,T[0],T[1],T[2]); /* 当ElemType的类型变化时，要相应改变printf()的格式符。 */
  i=Get(T,2,&m);
  if(i==OK)
    printf("T的第2个值为：%d\n",m);
  i=Put(T,2,6);
  if(i==OK)
    printf("将T的第2个值改为6后，T的三个值为：%d %d %d\n",T[0],T[1],T[2]);
  i=IsAscending(T); /* 此类函数实参与ElemType的类型无关,当ElemType的类型变化时,实参不需改变 */
  printf("调用测试升序的函数后，i=%d(0:否 1:是)\n",i);
  i=IsDescending(T);
  printf("调用测试降序的函数后，i=%d(0:否 1:是)\n",i);
  if((i=Max(T,&m))==OK) /* 先赋值再比较 */
    printf("T中的最大值为：%d\n",m);
  if((i=Min(T,&m))==OK)
    printf("T中的最小值为：%d\n",m);
  DestroyTriplet(&T); /* 函数也可以不带回返回值 */
  printf("销毁T后，T=%u(NULL)\n",T);
  return 0;
}
