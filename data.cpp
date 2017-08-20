#include <iostream>
#include <fstream>
#include <vector>

#include "data.h"

/*
 * File Header: 2x32Bit Word
 *                1=Bytesize of datafile
 *                2=Number of entries in dataobject index table
 *
 * Each entry: 2x32Bit Word
 *                1=Bytesize of dataobject
 *                2=Byteoffset of dataobject from begining of file
*/

void Data::Load() {
  std::ifstream file("SPAE.PA", std::ios::binary);

  if (file.good()) {
    union {
      char* Bytes = new char[4];
      unsigned int* Int;
    } c;

    file.read(c.Bytes, 4);
    fileHeader=*c.Int;

    file.read(c.Bytes, 4);
    totEntries=*c.Int;

    Entry ent;
    for (unsigned int i=0;i<=totEntries;++i) {
      ent.entry=i;
      file.read(c.Bytes, 4);
      ent.size=*c.Int;

      file.read(c.Bytes, 4);
      ent.offset=*c.Int;
      vEntry.push_back(ent);
    }
    delete[] c.Bytes;
    file.close();

    GetData();
  }
}

void Data::Print(unsigned int ent) {
  for (auto itr=vEntry.begin(); itr!=vEntry.end(); ++itr) {
    if (itr->entry==ent) {
      std::cout << "Entry: " << itr->entry << " Size: " << itr->size << " Offset: " << itr->offset
        << " Type: " << +itr->type << " Unk1: " << +itr->unk1 << " Unk2: " << +itr->unk2
        << " Unk3: " << +itr->unk3 << " Data: ";
      for (auto itr2=itr->data.begin(); itr2!=itr->data.end(); ++itr2) {
        std::cout << +*itr2 << " ";
      }
      std::cout << std::endl;
      break;
    }
  }
}

void Data::GetData() {
  std::ifstream file("SPAE.PA", std::ios::binary);

  if (file.good()) {
    for (auto itr=vEntry.begin(); itr !=vEntry.end(); ++itr) {
      if (itr->size) {
        uint8_t byte;
        file.seekg(itr->offset);
        file >> itr->type >> itr->unk1 >> itr->unk2 >> itr->unk3;
        // -4 for the read to variables above
        for (unsigned int i=0; i<itr->size-4; ++i) {
          file >> byte;
          itr->data.push_back(byte);
        }
      }
    }
  file.close();
  } else {
    file.close();
  }
}


unsigned int Data::GetSize(unsigned int ent) {
  for (auto itr=vEntry.begin(); itr!=vEntry.end(); ++itr) {
    if (itr->entry==ent) {
      return itr->size;
    }
  }
  return 0;
}

