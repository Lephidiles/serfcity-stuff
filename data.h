#pragma once

#include <vector>

class Data {
  public:
    void Load();
    void Print(unsigned int);
    unsigned int GetSize(unsigned int);
  private:
    void GetData();
    unsigned int fileHeader;
    unsigned int totEntries;
    struct Entry {
      unsigned int entry;
      unsigned int size;
      unsigned int offset;
      uint8_t type=0; // 0: Unk, 1: Sprite, 2: Animation, 3: Sound, 4: Music
      uint8_t unk1=0;
      uint8_t unk2=0;
      uint8_t unk3=0;
      std::vector<uint8_t> data;
    };
    std::vector<Entry> vEntry;
};
