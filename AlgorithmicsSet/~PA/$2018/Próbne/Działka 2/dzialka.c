#include "dzialka.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>

static char IsInitialized = 0;
static int FieldH, FieldW;
static char **IsUsable;

static void Initialize() {
  scanf("%d%d", &FieldH, &FieldW);
  char *str = (char *)malloc(FieldW + 1);
  IsUsable = (char **)malloc(FieldH * sizeof(char *));
  for (int i = 0; i < FieldH; ++i) {
    IsUsable[i] = (char *)malloc(FieldW);
    scanf("%s", str);
    for (int j = 0; j < FieldW; ++j)
      IsUsable[i][j] = (str[j] == '1');
  }
  free(str);
  IsInitialized = true;
}

int GetFieldHeight() {
  if (!IsInitialized) { Initialize(); }
  return FieldH;
}

int GetFieldWidth() {
  if (!IsInitialized) { Initialize(); }
  return FieldW;
}

int IsUsableCell(int Row, int Col) {
  if (!IsInitialized) { Initialize(); }
  assert(0 <= Row && Row < FieldH && "Nieprawidlowy numer wiersza!");
  assert(0 <= Col && Col < FieldW && "Nieprawidlowy numer kolumny!");

  return IsUsable[Row][Col];
}

