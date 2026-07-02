/*
 *  myenv.c : env コマンドのクローン
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __linux__
#include "myputenv.h"
#endif
extern char **environ;

int main(int argc, char* argv[], char *envp[]) {
    int i = 1;
    int out = 0;
    while(out == 0 && i < argc) {
        out = putenv(argv[i]);
        putenv(argv[i]);
        i++;
    }
    if (out == -1) {
        execvp(argv[i-1], &argv[i-1]);
        if (execvp(argv[i-1], &argv[i-1])== -1) {
            fprintf(stderr,
            "Usage: %s [name=value ...] command [argument ...]]\n", argv[0]);
            return 1;
        }        
    }   else {
        for (int i = 0; environ[i] != NULL; i++) {
            printf ("%s\n", environ[i]);
        }
    }
    return 1;
}


/* 実行例
コンパイル
% make
cc -D_GNU_SOURCE -Wall -std=c99 -o myenv myenv.c myputenv.c

環境変数の変更
% date
2026年 7月 2日 木曜日 14時37分57秒 JST
% ./myenv TZ=Cuba date
2026年 7月 2日 木曜日 01時38分27秒 CDT
% date
2026年 7月 2日 木曜日 14時38分36秒 JST

複数の環境変数の変更
% date
2026年 7月 2日 木曜日 14時39分35秒 JST
% ./myenv TZ=Cuba LC_TIME=c date
Thu Jul  2 01:40:15 CDT 2026
% date
2026年 7月 2日 木曜日 14時40分22秒 JST

引数付きのコマンドの場合
% date
2026年 7月 2日 木曜日 14時41分29秒 JST
% ./myenv TZ=Cuba LC_TIME=c date -I     
2026-07-02
% date
2026年 7月 2日 木曜日 14時42分07秒 JST

エラー発生時
./myenv TZ                       
Usage: ./myenv [name=value ...] command [argument ...]]

引数を指定する場合
./myenv TZ=Cuba                  
__CFBundleIdentifier=com.apple.Terminal
TMPDIR=/var/folders/yb/mz28h38d3113xns5pqd_br380000gn/T/
XPC_FLAGS=0x0
TERM=xterm-256color
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.ExE3QZAewu/Listeners
XPC_SERVICE_NAME=0
TERM_PROGRAM=Apple_Terminal
TERM_PROGRAM_VERSION=455.1
TERM_SESSION_ID=5EE396F3-008D-4245-BCD7-428250849ECA
SHELL=/bin/zsh
HOME=/Users/sakamotoyuto
LOGNAME=sakamotoyuto
USER=sakamotoyuto
PATH=/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/
usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/code
x.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.sys
tem/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstr
ap/usr/appleinternal/bin
SHLVL=1
PWD=/Users/sakamotoyuto/Syspro/kadai09-i23sakamoto
OLDPWD=/Users/sakamotoyuto/Syspro
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew
FPATH=/opt/homebrew/share/zsh/site-functions:/usr/local/share/zsh/site-function
s:/usr/share/zsh/site-functions:/usr/share/zsh/5.9/functions
INFOPATH=/opt/homebrew/share/info:
LANG=ja_JP.UTF-8
_=/Users/sakamotoyuto/Syspro/kadai09-i23sakamoto/./myenv
TZ=Cuba

引数を指定しない場合
 % env         
__CFBundleIdentifier=com.apple.Terminal
TMPDIR=/var/folders/yb/mz28h38d3113xns5pqd_br380000gn/T/
XPC_FLAGS=0x0
TERM=xterm-256color
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.ExE3QZAewu/Listeners
XPC_SERVICE_NAME=0
TERM_PROGRAM=Apple_Terminal
TERM_PROGRAM_VERSION=455.1
TERM_SESSION_ID=5EE396F3-008D-4245-BCD7-428250849ECA
SHELL=/bin/zsh
HOME=/Users/sakamotoyuto
LOGNAME=sakamotoyuto
USER=sakamotoyuto
PATH=/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/
usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/code
x.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.sys
tem/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstr
ap/usr/appleinternal/bin
SHLVL=1
PWD=/Users/sakamotoyuto/Syspro/kadai09-i23sakamoto
OLDPWD=/Users/sakamotoyuto/Syspro
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew
FPATH=/opt/homebrew/share/zsh/site-functions:/usr/local/share/zsh/site-function
s:/usr/share/zsh/site-functions:/usr/share/zsh/5.9/functions
INFOPATH=/opt/homebrew/share/info:
LANG=ja_JP.UTF-8
_=/usr/bin/env

ここに実行例を書く

*/
