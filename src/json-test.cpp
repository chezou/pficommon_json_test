/*
 Copyright (c) 2012 chezou

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <pficommon/text/json.h>
#include <sstream>
#include "souvenir.h"

using namespace pfi::text::json;
using namespace std;

namespace util{
  json string_to_json(string str){
    json js;
    stringstream ss(str);
    ss >> js;
    return js;
  }

  string json_to_string(json js){
    stringstream oss;
    oss << js;
    return oss.str();
  }
}

int main(){

  //通常のシリアライズ
  Souvenir sv;
  sv.name = "kishimen";
  sv.price = 1000;
  sv.famous = true;
  sv.funny = false;

  json js = to_json(sv);
  cout << js << endl;

  string str = util::json_to_string(js);
  cout << str << endl;
  

  json ks = util::string_to_json(str);
  // jsonはoperator==は未定義
  // string b = (js == ks) ? "true " : "false";
  // cout << b << endl;

  //nullを含む値をデシリアライズする場合
  //初期化していない値はまちまち
  stringstream ss("{\"name\":null,\"famous\":true,\"max_price\":1200}");

  Souvenir sv2;
  ss >> via_json_with_default(sv2);
  //max_priceは型をpfi::data::optional<int>にしているため、1/0の値で格納される
  cout << "name:" << sv2.name << " price:" << sv2.price 
       << " max_price:"  << sv2.max_price <<  " famous:" << (sv2.famous ? "true" : "false")
       << " funny:" << (sv2.funny ? "true" : "false") << endl;
  //max_priceをjsonにする場合は問題ない
  cout << to_json(sv2) << endl;

  //格納するクラスの変数をpficommon::data::optionalで定義
  //値がない場合はnullになる
  stringstream ss2("{\"name\":null,\"famouse\":true}");
  SouvenirDef svd;
  //以前使ったstringstreamをそのまま使うとeos
  //ss >> via_json_with_default(svd);
  ss2 >> via_json_with_default(svd);
  cout << to_json(svd) << endl;

  //各種変数のシリアライズテスト
  //pairとmap<int,int>はserializeできない
  SouvenirDef svd2;
  svd2.name = "doara no koibito";
  svd2.price = 600;
  svd2.funny = true;

  Bag shisyo;
  shisyo.souvenirs.push_back(svd);
  shisyo.souvenirs.push_back(svd2);
  map<string, int> nokori;
  shisyo.hash.insert(map<string, int>::value_type("nokori" , 2));
  nokori = shisyo.hash;
  shisyo.array.push_back( nokori );

  map<string, int> space;
  nokori.insert(map<string, int>::value_type("jakkan" , 1));
  shisyo.array.push_back( space );

  map<int, int> mapii;
  mapii.insert(map<int, int>::value_type(758, 884));
  
  cout << pretty( to_json(shisyo) ) << endl;
  
}
