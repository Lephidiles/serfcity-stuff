#pragma once

#include <vector>

struct Entry {
  unsigned int entry;
  unsigned int size;
  unsigned int offset;
  uint16_t type=0; // 0: Unk, 1: Sprite, 2: Animation, 3: Sound, 4: Music
  uint16_t X=0;
  uint16_t Y=0;
  uint16_t unk1=0;
  uint16_t unk2=0;
  std::vector<uint8_t> data;
  std::vector<uint8_t> umData;
};
    
class Data {
public:
  void Load();
  void Print(unsigned int);
  unsigned int GetSize(unsigned int);
  Entry GetData(unsigned int);
private:
  void InternalGetData();
  unsigned int fileHeader;
  unsigned int totEntries;
  std::vector<uint8_t> palette;
  std::vector<Entry> vEntry;
};
