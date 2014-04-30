// 共通ヘッダ
#ifndef ___COMMONHEADER___
#define ___COMMONHEADER___

const int SENTINEL = -2; // 番兵ちゃん
extern int sqrNum; // 一辺のマス目の数
extern int sqrX; // 盤面のマス目の位置。左から何列目か。
extern int sqrY; // 盤面のマス目の位置。上から何行目か。
extern bool mvSwitch; // 処理切り替え用フラグ trueで内部データ処理優先、falseで描画優先
extern int width; // ウィンドウの横幅
extern int height; // ウィンドウの縦幅

void mouse(int, int, int, int); // マウス
void keyboard(unsigned char, int, int); // キーボード

#endif