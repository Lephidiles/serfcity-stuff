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
        << std::endl;
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
            switch (byte) {
            case 0:
              itr->data.push_back(0x00); // r
              itr->data.push_back(0x00); // g
              itr->data.push_back(0x00); // b
              itr->data.push_back(0xff); // a
		          break;
            case 1:
              itr->data.push_back(0x80); 
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff); 
              break;
            case 2:
              itr->data.push_back(0x00);
              itr->data.push_back(0x80);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 3:
              itr->data.push_back(0x80);
              itr->data.push_back(0x80);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 4:
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0x80);
              itr->data.push_back(0xff);
              break;
            case 5:
              itr->data.push_back(0x80);
              itr->data.push_back(0x00);
              itr->data.push_back(0x80);
              itr->data.push_back(0xff);
              break;
            case 6:
              itr->data.push_back(0x00);
              itr->data.push_back(0x80);
              itr->data.push_back(0x80);
              itr->data.push_back(0xff);
              break;
            case 7:
              itr->data.push_back(0xc0);
              itr->data.push_back(0xc0);
              itr->data.push_back(0xc0);
              itr->data.push_back(0xff);
              break;
            case 8:
              itr->data.push_back(0x80);
              itr->data.push_back(0x80);
              itr->data.push_back(0x80);
              itr->data.push_back(0xff);
              break;
            case 9:
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 10:
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 11:
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 12:
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;
            case 13:
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;
            case 14:
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;
            case 15:
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 16:
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 17:
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 18:
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 19:
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 20:
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 21:
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 22:
              itr->data.push_back(0x00);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 23:
              itr->data.push_back(0x00);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 24:
              itr->data.push_back(0x00);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 25:
              itr->data.push_back(0x00);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 26:
              itr->data.push_back(0x00);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 27:
              itr->data.push_back(0x00);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 28:
              itr->data.push_back(0x00);
              itr->data.push_back(0x87);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 29:
              itr->data.push_back(0x00);
              itr->data.push_back(0x87);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 30:
              itr->data.push_back(0x00);
              itr->data.push_back(0x87);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 31:
              itr->data.push_back(0x00);
              itr->data.push_back(0x87);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 32:
              itr->data.push_back(0x00);
              itr->data.push_back(0x87);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 33:
              itr->data.push_back(0x00);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 34:
              itr->data.push_back(0x00);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 35:
              itr->data.push_back(0x00);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 36:
              itr->data.push_back(0x00);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 37:
              itr->data.push_back(0x00);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 38:
              itr->data.push_back(0x00);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 39:
              itr->data.push_back(0x00);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 40:
              itr->data.push_back(0x00);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 41:
              itr->data.push_back(0x00);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 42:
              itr->data.push_back(0x00);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 43:
              itr->data.push_back(0x00);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 44:
              itr->data.push_back(0x00);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 45:
              itr->data.push_back(0x00);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 46:
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 47:
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 48:
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 49:
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 50:
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 51:
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 52:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 53:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x00);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 54:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x00);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 55:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x00);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 56:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x00);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 57:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 58:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 59:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 60:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 61:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 62:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 63:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 64:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x87);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 65:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x87);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 66:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x87);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 67:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x87);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 68:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x87);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 69:
              itr->data.push_back(0x5f);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 70:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 71:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 72:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 73:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 74:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 75:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 76:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 77:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 78:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 79:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 80:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 81:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 82:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 83:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 84:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 85:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 86:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 87:
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 88:
              itr->data.push_back(0x87);
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 89:
              itr->data.push_back(0x87);
              itr->data.push_back(0x00);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 90:
              itr->data.push_back(0x87);
              itr->data.push_back(0x00);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 91:
              itr->data.push_back(0x87);
              itr->data.push_back(0x00);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 92:
              itr->data.push_back(0x87);
              itr->data.push_back(0x00);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 93:
              itr->data.push_back(0x87);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 94:
              itr->data.push_back(0x87);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 95:
              itr->data.push_back(0x87);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 96:
              itr->data.push_back(0x87);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 97:
              itr->data.push_back(0x87);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 98:
              itr->data.push_back(0x87);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 99:
              itr->data.push_back(0x87);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 100:
              itr->data.push_back(0x87);
              itr->data.push_back(0x87);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 101:
              itr->data.push_back(0x87);
              itr->data.push_back(0x87);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 102:
              itr->data.push_back(0x87);
              itr->data.push_back(0x87);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 103:
              itr->data.push_back(0x87);
              itr->data.push_back(0x87);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 104:
              itr->data.push_back(0x87);
              itr->data.push_back(0x87);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 105:
              itr->data.push_back(0x87);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 106:
              itr->data.push_back(0x87);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 107:
              itr->data.push_back(0x87);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 108:
              itr->data.push_back(0x87);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 109:
              itr->data.push_back(0x87);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 110:
              itr->data.push_back(0x87);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 111:
              itr->data.push_back(0x87);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 112:
              itr->data.push_back(0x87);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 113:
              itr->data.push_back(0x87);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 114:
              itr->data.push_back(0x87);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 115:
              itr->data.push_back(0x87);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 116:
              itr->data.push_back(0x87);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 117:
              itr->data.push_back(0x87);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 118:
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 119:
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 120:
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 121:
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 122:
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 123:
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 124:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 125:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x00);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 126:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x00);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 127:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 128:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 129:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 130:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 131:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 132:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 133:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 134:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 135:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 136:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x87);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 137:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x87);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 138:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x87);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 139:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 140:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 141:
              itr->data.push_back(0xaf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 142:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 143:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 144:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 145:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 146:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 147:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 148:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 149:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 150:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 151:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 152:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 153:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 154:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 155:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 156:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 157:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 158:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 159:
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 160:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 161:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x00);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 162:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x00);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 163:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x00);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 164:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x00);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 165:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 166:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 167:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 168:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 169:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 170:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 171:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 172:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x87);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 173:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x87);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 174:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x87);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 175:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x87);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 176:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x87);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 177:
              itr->data.push_back(0xd7);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 178:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 179:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 180:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 181:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 182:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 183:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 184:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 185:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 186:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 187:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 188:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 189:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 190:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 191:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xff);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 192:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xff);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 193:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xff);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 194:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xff);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 195:
              itr->data.push_back(0xd7);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 196:
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 197:
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 198:
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 199:
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 200:
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 201:
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 202:
              itr->data.push_back(0xff);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 203:
              itr->data.push_back(0xff);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 204:
              itr->data.push_back(0xff);
              itr->data.push_back(0x5f);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 205:
              itr->data.push_back(0xff);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 206:
              itr->data.push_back(0xff);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 207:
              itr->data.push_back(0xff);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 208:
              itr->data.push_back(0xff);
              itr->data.push_back(0x87);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 209:
              itr->data.push_back(0xff);
              itr->data.push_back(0x87);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 210:
              itr->data.push_back(0xff);
              itr->data.push_back(0x87);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 211:
              itr->data.push_back(0xff);
              itr->data.push_back(0x87);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 212:
              itr->data.push_back(0xff);
              itr->data.push_back(0x87);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 213:
              itr->data.push_back(0xff);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 214:
              itr->data.push_back(0xff);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 215:
              itr->data.push_back(0xff);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 216:
              itr->data.push_back(0xff);
              itr->data.push_back(0xaf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 217:
              itr->data.push_back(0xff);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 218:
              itr->data.push_back(0xff);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 219:
              itr->data.push_back(0xff);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 220:
              itr->data.push_back(0xff);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 221:
              itr->data.push_back(0xff);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 222:
              itr->data.push_back(0xff);
              itr->data.push_back(0xdf);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 223:
              itr->data.push_back(0xff);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 224:
              itr->data.push_back(0xff);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 225:
              itr->data.push_back(0xff);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 226:
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0x00);
              itr->data.push_back(0xff);
              break;
            case 227:
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0x5f);
              itr->data.push_back(0xff);
              break;
            case 228:
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0x87);
              itr->data.push_back(0xff);
              break;
            case 229:
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0xaf);
              itr->data.push_back(0xff);
              break;
            case 230:
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0xdf);
              itr->data.push_back(0xff);
              break;
            case 231:
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              itr->data.push_back(0xff);
              break;

            case 232:
              itr->data.push_back(0x08);
              itr->data.push_back(0x08);
              itr->data.push_back(0x08);
              itr->data.push_back(0xff);
              break;
            case 233:
              itr->data.push_back(0x12);
              itr->data.push_back(0x12);
              itr->data.push_back(0x12);
              itr->data.push_back(0xff);
              break;
            case 234:
              itr->data.push_back(0x1c);
              itr->data.push_back(0x1c);
              itr->data.push_back(0x1c);
              itr->data.push_back(0xff);
              break;
            case 235:
              itr->data.push_back(0x26);
              itr->data.push_back(0x26);
              itr->data.push_back(0x26);
              itr->data.push_back(0xff);
              break;
            case 236:
              itr->data.push_back(0x30);
              itr->data.push_back(0x30);
              itr->data.push_back(0x30);
              itr->data.push_back(0xff);
              break;
            case 237:
              itr->data.push_back(0x3a);
              itr->data.push_back(0x3a);
              itr->data.push_back(0x3a);
              itr->data.push_back(0xff);
              break;

            case 238:
              itr->data.push_back(0x44);
              itr->data.push_back(0x44);
              itr->data.push_back(0x44);
              itr->data.push_back(0x44);
              break;
            case 239:
              itr->data.push_back(0x4e);
              itr->data.push_back(0x4e);
              itr->data.push_back(0x4e);
              itr->data.push_back(0xff);
              break;
            case 240:
              itr->data.push_back(0x58);
              itr->data.push_back(0x58);
              itr->data.push_back(0x58);
              itr->data.push_back(0xff);
              break;
            case 241:
              itr->data.push_back(0x60);
              itr->data.push_back(0x60);
              itr->data.push_back(0x60);
              itr->data.push_back(0xff);
              break;
            case 242:
              itr->data.push_back(0x66);
              itr->data.push_back(0x66);
              itr->data.push_back(0x66);
              itr->data.push_back(0xff);
              break;
            case 243:
              itr->data.push_back(0x76);
              itr->data.push_back(0x76);
              itr->data.push_back(0x76);
              itr->data.push_back(0xff);
              break;

            case 244:
              itr->data.push_back(0x80);
              itr->data.push_back(0x80);
              itr->data.push_back(0x80);
              itr->data.push_back(0x44);
              break;
            case 245:
              itr->data.push_back(0x8a);
              itr->data.push_back(0x8a);
              itr->data.push_back(0x8a);
              itr->data.push_back(0xff);
              break;
            case 246:
              itr->data.push_back(0x94);
              itr->data.push_back(0x94);
              itr->data.push_back(0x94);
              itr->data.push_back(0xff);
              break;
            case 247:
              itr->data.push_back(0x9e);
              itr->data.push_back(0x9e);
              itr->data.push_back(0x9e);
              itr->data.push_back(0xff);
              break;
            case 248:
              itr->data.push_back(0xa8);
              itr->data.push_back(0xa8);
              itr->data.push_back(0xa8);
              itr->data.push_back(0xff);
              break;
            case 249:
              itr->data.push_back(0xb2);
              itr->data.push_back(0xb2);
              itr->data.push_back(0xb2);
              itr->data.push_back(0xff);
              break;

            case 250:
              itr->data.push_back(0xbc);
              itr->data.push_back(0xbc);
              itr->data.push_back(0xbc);
              itr->data.push_back(0x44);
              break;
            case 251:
              itr->data.push_back(0xc6);
              itr->data.push_back(0xc6);
              itr->data.push_back(0xc6);
              itr->data.push_back(0xff);
              break;
            case 252:
              itr->data.push_back(0xd0);
              itr->data.push_back(0xd0);
              itr->data.push_back(0xd0);
              itr->data.push_back(0xff);
              break;
            case 253:
              itr->data.push_back(0xda);
              itr->data.push_back(0xda);
              itr->data.push_back(0xda);
              itr->data.push_back(0xff);
              break;
            case 254:
              itr->data.push_back(0xe4);
              itr->data.push_back(0xe4);
              itr->data.push_back(0xe4);
              itr->data.push_back(0xff);
              break;
            case 255:
              itr->data.push_back(0xee);
              itr->data.push_back(0xee);
              itr->data.push_back(0xee);
              itr->data.push_back(0xee);
              break;
            }
          }
        } else {
          for (unsigned int i=0; i<itr->size-10; ++i) {
              file >> byte;
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

