# どうぶつしょうぎ

このリポジトリは、シンプルで奥深いボードゲーム「どうぶつしょうぎ」をC言語で実装したものです。「どうぶつしょうぎ」は、3×4の盤面と4種類の駒を使用し、子供から大人まで楽しめるゲームです。

## ゲームの概要

「どうぶつしょうぎ」は、女流棋士の北尾まどか氏が考案し、藤田麻衣子氏がデザインしたゲームで、2008年に日本女子プロ将棋協会（LPSA）から発表されました。3×4の盤面と「ライオン」「ぞう」「きりん」「ひよこ」の4種類の駒を使用し、相手のライオンを捕まえるか、自分のライオンを相手陣地の最前列に進めることで勝利となります。

## ルール

1. **駒の動き**:
   - **ライオン**: 上下左右および斜めの全方向に1マス移動できます。
   - **ぞう**: 斜め4方向に1マス移動できます。
   - **きりん**: 上下左右の4方向に1マス移動できます。
   - **ひよこ**: 前方に1マス移動できます。相手陣地の最前列に進むと「にわとり」に成り、斜め後ろ以外の6方向に1マス移動できます。

2. **勝利条件**:
   - **キャッチ**: 相手のライオンを捕まえる。
   - **トライ**: 自分のライオンを相手陣地の最前列に安全に進める。

詳細なルールや遊び方については、[日本将棋連盟のコラム](https://www.shogi.or.jp/column/2016/11/post_43.html)をご参照ください。

## このリポジトリについて

本リポジトリでは、C言語を用いて「どうぶつしょうぎ」のゲームロジックを実装しています。以下のファイルが含まれています。

- `main.c`: ゲームのエントリーポイント。
- `shogi.c` / `shogi.h`: ゲームの主要なロジックとデータ構造。
- `move.c`: 駒の移動に関する関数。
- `capture.c`: 駒の捕獲に関する関数。
- `evaluate.c`: ゲームの評価関数。
- `io.c`: 入出力処理。
- `judge.c`: 勝敗の判定に関する関数。
- `attack.c`: 攻撃に関する関数。
- `tree.c`: ゲームツリーの管理。
- `param.h`: 各種定数やパラメータの定義。
- `Makefile`: ビルド構成。

## ビルドと実行

以下の手順でビルドおよび実行が可能です。

1. リポジトリをクローンします。

   ```bash
   git clone https://github.com/IsseiNAKASONE/dobutsushogi.git
   ```

2. ディレクトリに移動します。

   ```bash
   cd dobutsushogi
   ```

3. ビルドします。

   ```bash
   make
   ```

4. 実行します。

   ```bash
   ./dobutsushogi
   ```

詳細な使用方法やコントリビューションに関する情報は、`README.md`およびソースコード内のコメントをご参照ください。

「どうぶつしょうぎ」の公式ルールや詳細な情報については、[日本将棋連盟の公式サイト](https://www.shogi.or.jp/column/2016/11/post_43.html)をご覧ください。

ゲームの遊び方に関するビジュアルな説明は、以下の動画も参考になります。

[「みんなのどうぶつしょうぎ」遊び方①どうぶつしょうぎ](https://www.youtube.com/watch?v=Z-kRQ_xcw9s)
