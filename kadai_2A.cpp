//
// Created by rikuo on 25/08/17.
//
#include <iostream>
class Ball {
public:
    float x, y;   // 座標
    float vx, vy; // 速度


    Ball(float _x, float _y, float _vx, float _vy) {
        // TODO: メンバ初期化（x,y,vx,vy を引数から代入）
    }

    void update() {
        // TODO: 1ステップの更新
    }

    void print() {
        // TODO: 現在位置を "(x,y)" 形式で出力
    }
};

int main() {
    Ball b(0, 0, 1, 1); // (0,0)から速度(1,1)で動く
    for (int i=0; i<5; i++) {
        b.update();
        b.print();
    }
}
