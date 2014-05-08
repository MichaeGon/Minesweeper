// 共通ヘッダ
#ifndef ___COMMONHEADER___
#define ___COMMONHEADER___

const int SENTINEL = -2; // 番兵ちゃん
extern int sqrNum; // 一辺のマス目の数
extern int width; // ウィンドウの横幅
extern int height; // ウィンドウの縦幅
extern char* title; // アプリタイトル

// 色の列挙体 配列colorsを指定するのに使用するのを想定(2とついているもののほうが暗い色)
enum color { Gray, Blue, Green, Red, Blue2, Brown, Green2, Red2, Purple, Yellow };
extern double colors[][3]; // 色配列

// 以下OpenGL関連

void display(); // 描画の際呼び出される関数。描画したいときはこの中に書き込むこと
void displayBoard(); // ボードの基盤を描画する
void displayPiece(int x, int y, double color[]); //x,yで指定したマス目をcolor[]={R,G,B}でRGB指定した色で塗りつぶす(各値は0~1)
void displayPushedPiece(int x, int y, int num); // x,yで指定したマス目にnumを描画する
void displayFlagPiece(int x, int y); // x,yで指定したマス目にフラグを描画する
void displayTime(time_t elapsed); // 経過時間を描画する
void displayGrayBand(); // 画面中央を横断するGrayの帯を表示する(この上に文字を描画することを想定している)
void displaySentenceOnBand(char* str, double color[]); // Grayの帯の上に文字列を表示する
void displaySentenceOnBandRandom(char* str); // 色が１文字ずつランダムで決まるバージョン
void displayBombNum(int bomb, int flag); // 爆弾数として引数の数値を表示する

void idle(); // アニメーション用
void resize(int w, int h); // 再描画前の処理に呼び出される
void mouse(int button, int state, int x, int y); // マウス
void keyboard(unsigned char key, int x, int y); // キーボード

void left(int x, int y);
void right(int x, int y);

#endif