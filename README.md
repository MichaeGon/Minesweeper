Minesweeper
===========

ノーマルなマインスイーパー

オブジェクト化不能なところを無理やり組み込んだせいでオブジェクト指向の根幹が揺らいでるが気にしない。

visual studioでいじるとき、実行ファイルを開くときのために
=========================================================

+ http://www.xmission.com/~nate/glut.html より最新版xxxx-bin.zip をダウンロード
+ 解凍後、glut.h はC:\Program Files(x86) \Microsoft Visual Studio 1x.0\VCnincludeにGL フォルダを作成し、その中に入れる
+ glut32.libはC:\Program Files(x86) \Microsoft Visual Studio 1x.0 \libに入れる
+ glut32.dll はwindowsが64bit ならC:\Windows \SysWOW64 へ、32bit ならC:\Windows\System32 へ入れる

