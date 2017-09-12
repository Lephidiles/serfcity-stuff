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
  std::ifstream file("SPAE.PA", std::ios::binary | std::ios::ate);

  if (file.good()) {
    union {
      char Byte[4];
      uint16_t Word;
      unsigned int Int;
    } c;
    
    unsigned int fileSize=file.tellg();
    char* byte = new char[fileSize];
    
    file.seekg(file.beg);
    file.read(byte, fileSize);
    file.close();
    
    for (int i=0; i!=4; ++i) {
      c.Byte[i]=byte[i];
    }
    fileHeader=c.Int;

   for (int i=0; i!=4; ++i) {
      c.Byte[i]=byte[i+4];
    }
    totEntries=c.Int;
   
    Entry ent;
    vEntry.reserve(totEntries);        
    
    // Satan has returned from the moons of endor and says that
    // f=2 ??? I thought it should be 8
    for (unsigned int i=0, f=2; i<totEntries*2; ++i, ++f) {
      if (i%2==0) {
        for (int b=0; b!=4; ++b) {
          c.Byte[b]=byte[f*4+b];
        }
        ent.size=c.Int;
      } else {
        for (int b=0; b!=4; ++b) {
          c.Byte[b]=byte[f*4+b];
        }
        ent.entry=i/2;
        ent.offset=c.Int;
        vEntry.push_back(ent);        
      }
    }
    
    c.Int=0;
    
    for (auto itr=vEntry.begin(); itr !=vEntry.end(); ++itr) {
      if (itr->size) {
        
        itr->data.reserve(itr->size);
        
        if (itr->entry==2) {
          for (unsigned int i=0; i<itr->size-1; ++i) {
            uint8_t dt=byte[itr->offset+i];
            palette[i]=dt;
          }
        } else {
          
          c.Byte[0]=byte[itr->offset+0];
          c.Byte[1]=byte[itr->offset+1];
          itr->type=c.Word;

          if (itr->type==1) {
            c.Byte[0]=byte[itr->offset+2];
            c.Byte[1]=byte[itr->offset+3];
            itr->X=c.Word;

            c.Byte[0]=byte[itr->offset+4];
            c.Byte[1]=byte[itr->offset+5];
            itr->Y=c.Word;
          
            c.Byte[0]=byte[itr->offset+6];
            c.Byte[1]=byte[itr->offset+7];
            itr->unk1=c.Word;
          
            c.Byte[0]=byte[itr->offset+8];
            c.Byte[1]=byte[itr->offset+9];
            itr->unk2=c.Word;
            
            for (unsigned int i=10; i<itr->size; ++i) {
              uint8_t color=byte[itr->offset+i];
              itr->umData.push_back(color);
              itr->data.push_back(palette[color * 3 + 0]);
              itr->data.push_back(palette[color * 3 + 1]);
              itr->data.push_back(palette[color * 3 + 2]);
              itr->data.push_back(0xFF);
            }
          } else {
            for (unsigned int i=3; i<itr->size; ++i) {            
              itr->data.push_back(byte[itr->offset+i]);
            }
          }
        }
      }
    }
    delete[] byte;
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

