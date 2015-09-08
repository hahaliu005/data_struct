#ifndef __HEADER__
#define __HEADER__
/* c1.h (程序名) */
#include<string.h>
#include<ctype.h>
#include<limits.h> /* INT_MAX等 */
#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<stdlib.h> /* atoi() */
#include<stdarg.h>
#ifdef __APPLE__
  #include<malloc/malloc.h> /* malloc()等 */
  #include <sys/uio.h>
#else
  #include<malloc.h> /* malloc()等 */
  #include <sys/io.h>
#endif
#include<math.h> /* floor(),ceil(),abs() */
// #include<process.h> /* exit() */
/* 函数结果状态代码 */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
/* #define OVERFLOW -2 因为在math.h中已定义OVERFLOW的值为3,故去掉此行 */
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */
#endif

