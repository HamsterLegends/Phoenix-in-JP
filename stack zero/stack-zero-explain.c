#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LEVELNAME "Stack Zero"
#define BANNER \
  "Welcome to LEVELNAME , brought to you by https://exploit.education"
//getsを宣言
char *gets(char *);

int main(int argc, char **argv) {

    /*
    struct something{
    メンバ1
    メンバ2
    }name;
    のようなsomethingという「タグ」がない場合、(以下の場合)
    無名構造体と呼ばれ、他の関数やファイルから参照ができない
    なお、nameは「構造体変数」もしくは「インスタンス」と呼ばれる
    */
////////////////////////////////////////////////////
//struct内のメンバは連続しているため、メモリも連続する//
////////////////////////////////////////////////////
  struct {
    char buffer[64];
    volatile int changeme;
  } locals;

  printf("%s\n", BANNER);

  locals.changeme = 0;
  gets(locals.buffer);

  if (locals.changeme != 0) {
    puts("Well done, the 'changeme' variable has been changed!");
  } else {
    puts(
        "Uh oh, 'changeme' has not yet been changed. Would you like to try "
        "again?");
  }

  exit(0);
}