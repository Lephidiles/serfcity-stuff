#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

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
        << " X: " << +itr->X << " Y: " << itr->Y << " Unk1: " << +itr->unk1
        << " Unk2: " << +itr->unk2 << " Data: " << std::endl;
        uint16_t i=0;
        for (auto itr2=itr->umData.begin(); itr2!=itr->umData.end(); ++itr2) {
          std::cout << std::hex << std::setfill('0') << std::setw(2) << +*itr2 << " " << std::dec;
          ++i;
          if (i==itr->X) {
            std::cout << std::endl;
            i=0;
          }
        } 
        std::cout << std::endl;
      break;
    }
  }
}

void Data::InternalGetData() {
  std::ifstream file("SPAE.PA", std::ios::binary);

  if (file.good()) {
    union {
      char* Bytes = new char[2];
      uint16_t* Word;
    } c;
    
    for (auto itr=vEntry.begin(); itr !=vEntry.end(); ++itr) {
      if (itr->size) {
        if (itr->entry==2) {
          file.seekg(itr->offset);
          char* byte = new char[1];
          for (unsigned int i=0; i<itr->size; ++i) {
            file.read(byte, 1);
            palette.push_back(*byte);
          }
          delete[] byte;
        } else {
          
          file.seekg(itr->offset);
          file.read(c.Bytes, 2);
          itr->type=*c.Word;

          file.read(c.Bytes, 2);
          itr->X=*c.Word;
          
          file.read(c.Bytes, 2);
          itr->Y=*c.Word;
        
          file.read(c.Bytes, 2);
          itr->unk1=*c.Word;
        
          file.read(c.Bytes, 2);
          itr->unk2=*c.Word;
        
          // -10 for the read to variables above
          // Fix and move this to actual display of Sprite
          if (itr->type==1) {
            char* byte = new char[1];
            for (unsigned int i=0; i<itr->size-10; ++i) {
              file.read(byte, 1);
              itr->umData.push_back(*byte);
              
              uint8_t red;
              uint8_t green;
              uint8_t blue;
             
              if (palette.size()) {
                red = palette[*byte * 3 + 0];
                green = palette[*byte * 3 + 1];
                blue = palette[*byte * 3 + 2];
              }
                            
              itr->data.push_back(red);
              itr->data.push_back(green);
              itr->data.push_back(blue);
              if (*byte==0x99) {
                itr->data.push_back(0xFF);
              } else {
                itr->data.push_back(0xFF);
              }
            }
            delete[]byte;
          } else {
            char* byte = new char[1];
            for (unsigned int i=0; i<itr->size-10; ++i) {
              file.read(byte, 1);
              itr->umData.push_back(*byte);
              itr->data.push_back(*byte);
            }
            delete[]byte;
          }
        }
      }
    }
    delete[] c.Bytes;
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

