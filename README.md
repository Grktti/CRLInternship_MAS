# Multi-Agent-System課題（インターン向け）

このリポジトリは、C++ の基礎からオブジェクト指向、そしてマルチエージェントシステムまでを学ぶための課題集です。  
各課題ファイルには **TODO コメントでブランク** があり、そこを埋める形で進めます。

---

## 0. GitHub フォークの手順
1. このリポジトリの GitHub ページを開く
2. 右上の **Fork** ボタンを押して、自分のアカウントにコピーを作成
3. 自分のフォークを **ローカルに clone**
   ```powershell
   git clone https://github.com/<あなたのユーザー名>/<リポジトリ名>.git
   cd <リポジトリ名>
   ```
4. 各課題のファイルを編集してコミット・プッシュ
   ```powershell
   git add kadai_1A.cpp
   git commit -m "課題1Aの解答を実装"
   git push origin main
   ```

---

## 1. 課題の進め方
- 課題は `kadai_1A.cpp` から `kadai_2C.cpp` まで段階的に用意されています。
- **Step1**：C++ 基礎（文字列操作・配列・ファイルI/O）
- **Step2**：クラス設計（オブジェクト指向・描画・シミュレーション）

各ファイルは単体でコンパイル・実行できます。  
`TODO` 部分を自分で書き換えて完成させてください。

---

## 2. 課題一覧

### Step1
- **kadai_1A.cpp**  
  2D グリッドを文字で描画する関数 `renderGrid` を完成させる  
  （外周を `#`、内部を `?` にして改行付きで表示）

- **kadai_1B.cpp**  
  与えられた整数ベクトルの **最大値・平均・中央値** を返す関数を実装する  

- **kadai_1C.cpp**  
  `step,value` 形式でログを `log.csv` に書き出すプログラムを完成させる  

---

### Step2
- **kadai_2A.cpp**  
  `Ball` クラスを作り、`update` で座標を更新、`print` で出力する  

- **kadai_2B.cpp**  
  OpenGL (GLFW) を使ってボールを画面上に描画し、壁で反射させる  

- **kadai_2C.cpp**  
  Boids モデルの簡易版を実装（分離・整列・凝集 + 壁反発 + 円描画）  

---

## 3. ビルドと実行

### Visual Studio
1. **ソリューションを新規作成**
   - 「空のプロジェクト」を作る
   - 各 `kadai_xx.cpp` を追加する
2. **ビルド構成を Release x64 に設定**
3. F5 で実行（コンソールアプリの場合は黒い画面に出力）

### CLion (CMake)
1. `File > Open...` でリポジトリを開く
2. `kadai_xx.cpp` を `CMakeLists.txt` に追加（課題は追加済）
   ```cmake
   add_executable(kadai_1A kadai_1A.cpp)
   ```
3. 右上の実行ボタンから Run

### OpenGL を使う課題 (2B, 2C)
- **GLFW のインストールは不要**  
  vcpkg を使う場合の例:
  ```powershell
  vcpkg install glfw3
  ```
- Visual Studio のプロパティでリンク設定を行うか、CMake の場合は
  ```cmake
  find_package(glfw3 CONFIG REQUIRED)
  target_link_libraries(kadai_2B PRIVATE glfw)
  ```

### macOS
#### Homebrew と GLFW のインストール
1. Homebrew をインストール
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```
2. インストール後に表示されるコマンドを実行  
   （例：`xxxx` の部分は自分のユーザー名）
   ```bash
   echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> /Users/xxxx/.zprofile
   eval "$(/opt/homebrew/bin/brew shellenv)"
   ```
3. GLFW をインストール
   ```bash
   brew install glfw3
   ```

---

## 4. 提出方法
- 完成したプログラムとファイルをSLACKや直接担当者に見せる。
