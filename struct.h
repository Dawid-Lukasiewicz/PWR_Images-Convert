#ifndef STRUCT_H
#define STRUCT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


struct Obraz
{
  char znak;
  int wymx;
  int wymy;
  int szarosci;
  int **obraz_pgm;
  int **R;
  int **G;
  int **B;
};

typedef struct Obraz Obraz;

#endif
