# sample_motion_model_velocity
速度動作モデルのサンプリングアルゴリズム

2020年３月13日のzoomオンラインレクチャー資料
2020年３月24日のzoomオンラインレクチャー資料

### 2020.3.14
途中経過も含めて画面描画するように修正

### 2020.3.23
- 直線経路（方向転換含む）にともなう誤差の分散シミュレーション
- オドメトリの説明プログラムを追加
- 共分散行列・固有値固有ベクトルの計算を追加

お気づきの点は k.inoue@oyama-ct.ac.jp まで

# コンパイル
```
mkdir build
cd build
cmake ..
make
```

# 実行結果
![result.png (17.2 kB)](https://img.esa.io/uploads/production/attachments/14617/2020/03/14/12742/84f7f256-a508-4859-80b8-c239631bc6e8.png)

![prog2](https://img.esa.io/uploads/production/attachments/14617/2020/03/23/12742/3d63942c-1e85-4c11-8351-6f72f6b8539f.png)


