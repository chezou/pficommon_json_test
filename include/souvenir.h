#ifndef __SOUVENIR_H__
#define __SOUVENIR_H__

#include <pficommon/text/json.h>
#include <pficommon/data/optional.h>
#include <string>
#include <vector>
#include <map>

class Souvenir
{
 public:
  std::string name;
  int price;
  pfi::data::optional<int> max_price;
  bool famous;
  bool funny;

  template <class Archive>
    void serialize(Archive &ar){
    ar & MEMBER(price) & MEMBER(famous) & MEMBER(name) & MEMBER(funny);
  }
};

class SouvenirDef
{
 public:
  pfi::data::optional<std::string> name;
  pfi::data::optional<int> price;
  pfi::data::optional<bool> famous;
  pfi::data::optional<bool> funny;

  template <class Archive>
    void serialize(Archive &ar){
    ar & MEMBER(price) & MEMBER(famous) & MEMBER(name) & MEMBER(funny);
  }
};

class Bag
{
 public:
  std::vector<SouvenirDef> souvenirs;
  std::map<std::string, int> hash;
  std::vector< std::map< std::string, int > > array;

  //以下の型はserializeできない
  std::map<int, int> map_int;
  std::pair<std::string, int> bad_hash;
  
  template <class Archive>
    void serialize(Archive &ar){
    ar & MEMBER(souvenirs) 
      & MEMBER(hash) 
      //& MEMBER(map_int)
      //& MEMBER(bad_hash)
      & MEMBER(array);
  }
};

#endif //__SOUVENIR_H__
