#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <boost/endian/conversion.hpp>

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

    InternalGetData();
  }
}

void Data::Print(unsigned int ent) {
  for (auto itr=vEntry.begin(); itr!=vEntry.end(); ++itr) {
    if (itr->entry==ent) {
      std::cout << "Entry: " << itr->entry << " Size: " << itr->size << " Offset: "
        << std::hex << itr->offset << std::dec << " Type: " << +itr->type 
        << " Unk1: " << +itr->unk1 << " Unk2: " << +itr->unk2 << " Unk3: " << +itr->unk3
        << " Unk4: " << +itr->unk4 << " Unk5: " << +itr->unk5 << " Unk6: " << +itr->unk6
        << " Unk7: " << +itr->unk7 << " Unk8: " << +itr->unk8 << " Unk9: " << +itr->unk9
        << " Data: ";
        for (auto itr2=itr->umData.begin(); itr2!=itr->umData.end(); ++itr2) {
          std::cout << +*itr2 << " ";
        } 
        std::cout << std::endl;
      break;
    }
  }
}

void Data::InternalGetData() {
  std::ifstream file("SPAE.PA", std::ios::binary);

  if (file.good()) {
    for (auto itr=vEntry.begin(); itr !=vEntry.end(); ++itr) {
      if (itr->size) {
        uint8_t byte;
        file.seekg(itr->offset);
        file >> itr->type >> itr->unk1 >> itr->unk2 >> itr->unk3
          >> itr->unk4 >> itr->unk5 >> itr->unk6 >> itr->unk7
          >> itr->unk8 >> itr->unk9;
        // -10 for the read to variables above
        if (itr->type==1) {
          for (unsigned int i=0; i<itr->size-10; ++i) {
            file >> byte;
            itr->umData.push_back(byte);
            uint8_t b=boost::endian::endian_reverse(byte);
            uint8_t red = round(((b & 0xE0) >> 5) / 7.0 * 0xFF);
            uint8_t green = round(((b & 0x1C) >> 2) / 7.0 * 0xFF);
            uint8_t blue = round((b & 0x03) / 3.0 * 0xFF);
            itr->data.push_back(red);
            itr->data.push_back(green);
            itr->data.push_back(blue);
            itr->data.push_back(0xFF);
          }
        } else {
          for (unsigned int i=0; i<itr->size-10; ++i) {
              file >> byte;
              itr->umData.push_back(byte);
              itr->data.push_back(byte);
            }
          }
        }
      }
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

Entry Data::GetData(unsigned int ent) {
  Entry ret;
  for (auto itr=vEntry.begin(); itr!=vEntry.end(); ++itr) {
    if (itr->entry==ent) {
      ret=*itr;
      break;
    }
  }
  return ret;
}

