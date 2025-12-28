#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LEVELNAME "stack-three"
#define BANNER \
  "Welcome to " LEVELNAME ", brought to you by https://exploit.education"

char *gets(char *);

void complete_level() {
  printf("Congratulations, you've finished " LEVELNAME " :-) Well done!\n");
  exit(0);
}

int main(int argc, char **argv) {
  struct {
    char buffer[64];
    volatile int (*fp)();
  } locals;  

  ///////////////////////// 
  // int (*fp)();について//
  /////////////////////////

  /* 例えば、関数プロトタイプ int function(int, int);は以下のように一般化出来る
   *
   * int function(int, int);
   * 型指定子 関数名(パラメータ, パラメータ);  //パラメータ == 仮引数 
   *
   * このとき、関数名functionは変数の様に表せる。つまり、
   * 
   * A	== 変数
   * *p	== 変数
   *
   * であるから
   *
   * function	== 関数名
   * (*fp)	== 関数名		//fpという名前はFunctionPointerのイニシャル
   *
   * よって
   *
   * int function(int, int);	という形があったように、
   * int (*fp)(int, int);	という形も可能である。
   *
   * このような形にすることによって、fpの値を変えるだけで様々な関数にアクセス出来る
   * fp = &関数A ならば *fp == 関数A
   * fp = &関数B ならば *fp == 関数B
   * fp = &関数C ならば *fp == 関数C
   * のように、様々な関数へアクセス出来る(ポインタのいいところだね！)
   * このとき、
   *
   * fp == 関数ポインタ
   * と呼ぶ。
   *
   * int (*fp)(int, int);	これのパラメータ、すなわち仮引数のない形が
   * int (*fp)();		これである。
   *
   * int (*fp)(ここが空欄);
   * の場合について。
   *
   * 好きな引数を取れる古いの書き方である。
   */

  printf("%s\n", BANNER);

  locals.fp = NULL;
  gets(locals.buffer);

  if (locals.fp) {
    printf("calling function pointer @ %p\n", locals.fp);
    fflush(stdout);
    locals.fp();
  } else {
    printf("function pointer remains unmodified :~( better luck next time!\n");
  }

  exit(0);
}
  //////////////////////////////////////////////
  //locals.fp()ってlocal.(*fp)()の間違えじゃ？//
  //////////////////////////////////////////////

  /* fp() == (*fp)() の シンタックスシュガー
   * 
   * 「関数ポインタを実行」なんて意味不明だが、
   * 「関数Aポインタを実行」なんて「関数Aを実行」するとしか意味しえないため、
   * 
   * fp() == (*fp)() 
   *
   * になった。
   * 
   *               // (正直この機能は好きじゃない...)
   *
   * 実をいうと、
   *
   * fp == &関数名
   * fp == 関数名
   *
   * でも良い
   *
   * 
   */
