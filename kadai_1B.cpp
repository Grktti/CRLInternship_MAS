//
// Created by rikuo on 25/08/17.
//
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <iostream>

// 平均: 読み取り専用の参照で無駄なコピーを避ける
double meanOf(const std::vector<int>& v){
    // TODO: 平均を計算する関数を作成

}

// 最大: イテレータから値を取り出す
int maxOf(const std::vector<int>& v){
    // TODO: 最大値を計算する関数を作成

}

// 中央値: 呼び出し側のデータを壊さないよう値渡しでコピー
double medianOf(std::vector<int> v){
    // TODO: 中央値を計算する関数を作成

}

int main(){
    {
        std::vector<int> a{2,9,4,1,7};
        std::cout << "max=" << maxOf(a)
                  << ", mean=" << meanOf(a)
                  << ", median=" << medianOf(a) << "\n";
    }
    {
        std::vector<int> b{1,2,3,4};
        std::cout << "median(b)=" << medianOf(b) << "\n";
    }
}