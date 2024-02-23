#include "CircularBuffer.h"
#include <iostream>
#include <string.h>

#define DATA_LEN 64
#define BUFFER_SIZE 32

struct DataPoint {
   int m_value;
   int m_parity;
   char m_name[32];
   int m_data[DATA_LEN];

   DataPoint() : m_value(0), m_parity(0) {
      m_name[0] = '\0';
   }
   DataPoint(const char *name) : m_value(0), m_parity(0) {
      strncpy(m_name, name, sizeof(m_name) / sizeof(m_name[0]));
   }
};

void FillStream(int *data, size_t len, int value) {
   for (unsigned i = 0; i < len; ++i) {
      data[i] = value;
   }
}

void PrintDataPoint(const DataPoint &dp) {
   std::cout << "value=" << dp.m_value << " parity=" << dp.m_parity << " data: ";
   for (unsigned i = 0; i < sizeof(dp.m_data) / sizeof(dp.m_data[0]); ++i) {
      std::cout << dp.m_data[i];
   }
}


int main() {
   DataPoint dpw;
   DataPoint dpr;
   buffer::CircularBuffer<DataPoint, 32, uint8_t> *pBuffer;

   pBuffer = new buffer::CircularBuffer<DataPoint, 32, uint8_t>();

   for (unsigned int i = 1; i < 100; ++i) {
      dpw.m_value = i;
      dpw.m_parity = i % 2;
      FillStream(dpw.m_data, DATA_LEN, i);

      if (pBuffer->isFull()) {
         bool res = pBuffer->remove(&dpr);
         std::cout << std::endl;
         std::cout << "<== Remove element with result: " << res;
         if (res) {
            std::cout << " data: ";
            PrintDataPoint(dpr);
         }
         std::cout << std::endl;
      }


      bool res = pBuffer->insert(&dpw);
      std::cout << std::endl;
      std::cout << "--> Insert element nummer " << i << " with result: " << res;
      if (res) {
         std::cout << " data: ";
         PrintDataPoint(dpw);
      }
      std::cout << std::endl;
   }

   while (pBuffer->readAvailable()) {
      bool res = pBuffer->remove(&dpr);
      std::cout << std::endl;
      std::cout << "<-- Remove element with result: " << res;
      if (res) {
         std::cout << " data: ";
         PrintDataPoint(dpr);
      }
      std::cout << std::endl;
   }


   delete pBuffer;

   return 0;
}
