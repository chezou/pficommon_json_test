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
  stringstream ss("{\"name\":null,\"famouse\":true}");

  Souvenir sv2;
  ss >> via_json_with_default(sv2);
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
