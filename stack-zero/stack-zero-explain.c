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

//////////////////////////////////////////////////////////////
//構造体メンバは連続しているため、構造体メンバのアドレスも連続する//
//////////////////////////////////////////////////////////////
  struct /*A*/ {            //構造体キーワード
  char buffer[64];        //構造体メンバ
    volatile int changeme;  //構造体メンバ
  } locals;                 //識別子

//(ここはあまり重要でない)............................................//
// /*A*/に入るはずの「構造体タグ」がないものを無名構造体という。
// 無名構造体のスコープはその関数内に限られる。 
//volatileはコンパイルをするとき、省略されたコンパイルをするのを防ぐために、
//つまりコードと完全に等価な機械語が欲しいときに使う。
//..................................................................// 
  printf("%s\n", BANNER);

  locals.changeme = 0;
  gets(locals.buffer);
//bufferは64バイトの配列である。故に64バイトを超える入力があると
//アドレスが連続しているchangemeへ入力を上書きしてしまう。
//なお、ASCIIの文字は1バイトであるため、Aを64回入力すれば、その先に
//入力するものを丸ごとchangemeに上書きできる。
  if (locals.changeme != 0) {
    puts("Well done, the 'changeme' variable has been changed!");
  } else {
    puts(
        "Uh oh, 'changeme' has not yet been changed. Would you like to try "
        "again?");
  }

  exit(0);
}