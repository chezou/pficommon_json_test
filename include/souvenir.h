/*
 Copyright (c) 2012 chezou

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


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
    ar & MEMBER(price) & MEMBER(famous) & MEMBER(name) & MEMBER(funny) & MEMBER(max_price);
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
