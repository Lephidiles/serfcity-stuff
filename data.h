#pragma once

#include <vector>

struct Entry {
  unsigned int entry;
  unsigned int size;
  unsigned int offset;
  uint8_t type=0; // 0: Unk, 1: Sprite, 2: Animation, 3: Sound, 4: Music
  uint8_t unk1=0;
  uint8_t unk2=0; // X res ??
  uint8_t unk3=0;
  uint8_t unk4=0; // Y res ??
  uint8_t unk5=0;
  uint8_t unk6=0;
  uint8_t unk7=0;
  uint8_t unk8=0;
  uint8_t unk9=0;
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
    std::vector<Entry> vEntry;
};
