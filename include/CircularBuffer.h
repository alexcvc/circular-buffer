
#ifndef CYCLIC_BUFFER_T_H
#define CYCLIC_BUFFER_T_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

//----------------------------------------------------------------------------
// Public defines and macros
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Public typedefs, structs, enums, unions and variables
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Public Function Prototypes
//----------------------------------------------------------------------------

namespace buffer {

/**
 * @brief A template class representing a cyclic buffer.
 *
 * @tparam T The type of elements stored in the buffer.
 * @tparam buffer_size The maximum number of elements the buffer can hold.
 * @tparam index_t The type of index used to access elements in the buffer.
 */
template<typename T, size_t buffer_size = 16, typename index_t = size_t>
class CircularBuffer {
public:
   /**
    * @brief Default constructor for CircularBuffer class.
    *
    * Initializes the m_head and m_tail variables to 0.
    * It also includes an assert statement to check whether the buffer_size is a power of 2.
    *
    * @tparam T The type of elements stored in the buffer.
    * @tparam buffer_size The maximum number of elements the buffer can hold.
    * @tparam index_t The type of index used to access elements in the buffer.
    */
   CircularBuffer() : m_head(0), m_tail(0) {
      // "buffer size is not a power of 2"
      assert((buffer_size & buffer_mask) == 0);
   }

   /**
    * \brief Special case constructor to premature out unnecessary initialization code when object is
    * instantiated in .bss section
    * \warning If object is instantiated on stack, heap or inside no-init section then the contents have to be
    * explicitly cleared before use
    * \param dummy ignored
    */
   CircularBuffer(int dummy) {
      (void) (dummy);
   }

   /**
      * @brief Clears the buffer by setting the tail index equal to the head index.
      *
      * This function is used to reset the buffer, effectively clearing all elements in it.
      * It sets the tail index equal to the head index, indicating that the buffer is empty.
      */
   void clear(void) {
      m_tail = m_head;
   }

   /**
      * @brief Checks the number of elements available to read in the buffer.
      *
      * The readAvailable function calculates the number of elements that can be read from the buffer.
      * It subtracts the tail index from the head index to get the count of available elements.
      *
      * @return The number of elements available to read in the buffer.
      */
   bool isEmpty(void) const {
      return readAvailable() == 0;
   }

   /**
    * @brief Check if the cyclic buffer is full.
    *
    * This function checks if the cyclic buffer is full by comparing the amount of available space for writing with 0.
    * If the available space for writing is 0, it means that the buffer is full.
    *
    * @return True if the cyclic buffer is full, false otherwise.
    */
   bool isFull(void) const {
      return writeAvailable() == 0;
   }

   /**
    * @brief Returns the number of elements available to be read from the buffer.
    *
    * The readAvailable() function calculates the number of elements available to be read
    * by subtracting the tail index from the head index. This represents the number of
    * elements that have been written to the buffer but have not yet been read.
    * @return The number of elements available to be read.
    */
   index_t readAvailable(void) const {
      return m_head - m_tail;
   }

   /**
    * \brief Check how many elements can be written into the buffer
    * \return Number of free slots that can be be written
    */
   index_t writeAvailable(void) const {
      return buffer_size - (m_head - m_tail);
   }

   /**
    * @brief Inserts an element into the cyclic buffer.
    *
    * This function inserts an element into the cyclic buffer. If the buffer is full, the function returns false.
    *
    * @tparam T The type of elements stored in the buffer.
    * @param data The element to be inserted into the buffer.
    * @return True if the element was inserted successfully, false if the buffer is full.
    */
   bool insert(T data) {
      if ((m_head - m_tail) == buffer_size) {
         return false;
      } else {
         m_dataBuff[m_head++ & buffer_mask] = data;
      }
      return true;
   }

   /**
      * @brief Inserts an element into the cyclic buffer.
      *
      * This function inserts an element into the cyclic buffer. If the buffer is full, the function returns false.
      *
      * @tparam T The type of elements stored in the buffer.
      * @param data The element to be inserted into the buffer.
      * @return True if the element was inserted successfully, false if the buffer is full.
      */
   bool insert(const T *data) {
      if ((m_head - m_tail) == buffer_size) {
         return false;
      } else {
         m_dataBuff[m_head++ & buffer_mask] = *data;
      }
      return true;
   }

   /**
      * @brief Removes an element from the cyclic buffer.
      *
      * This function removes an element from the cyclic buffer by incrementing the tail index.
      * If the buffer is empty, the function returns false.
      *
      * @return True if an element was successfully removed, false if the buffer is empty.
      */
   bool remove() {
      if (m_tail == m_head) {
         return false;
      } else {
         m_tail++;
         return true;
      }
   }

   /**
      * @brief Removes a specified number of elements from the buffer.
      *
      * This function removes a specified number of elements from the buffer. It first calculates the number of
      * elements available in the buffer by subtracting the tail index from the head index. It then ensures that
      * the count of elements to be removed does not exceed the available number of elements. Finally, it updates
      * the tail index by adding the count of elements to be removed. It returns the actual count of elements removed.
      *
      * @param cnt The number of elements to be removed from the buffer.
      * @return The actual count of elements removed from the buffer.
      */
   size_t remove(size_t cnt) {
      index_t avail = m_head - m_tail;

      cnt = (cnt > avail) ? avail : cnt;

      m_tail += cnt;
      return cnt;
   }

   /**
    * @brief Removes an element from the cyclic buffer.
    *
    * This function removes an element from the cyclic buffer by incrementing the tail index.
    * If the buffer is empty, the function returns false.
    *
    * @tparam T The type of elements stored in the buffer.
    * @param data The element to be removed from the buffer.
    * @return True if an element was successfully removed, false if the buffer is empty.
    */
   bool remove(T &data) {
      return remove(&data);// references are anyway implemented as pointers
   }

   /**
    * @brief Removes an element from the buffer.
    *
    * This function removes an element from the buffer by incrementing the tail index and storing the removed value
    * in the provided data pointer. If the buffer is empty, the function returns false.
    *
    * @tparam T The type of elements stored in the buffer.
    * @param data Pointer to store the removed element.
    * @return True if an element was successfully removed, false if the buffer is empty.
    */
   bool remove(T *data) {
      if (m_tail == m_head) {
         return false;
      } else {
         *data = m_dataBuff[m_tail++ & buffer_mask];
      }
      return true;
   }

   /**
      * @brief Returns a pointer to the next element in the cyclic buffer without removing it.
      *
      * This function returns a pointer to the next element in the cyclic buffer without removing it. If the buffer is empty, it returns NULL.
      *
      * @tparam T The type of elements stored in the buffer.
      * @return A pointer to the next element in the buffer, or NULL if the buffer is empty.
      */
   T *peek() {
      if (m_tail == m_head) {
         return NULL;
      } else {
         return &m_dataBuff[m_tail & buffer_mask];
      }
   }

   /**
    * @brief Returns a pointer to the element at the specified index in the cyclic buffer.
    *
    * This function returns a pointer to the element at the specified index in the cyclic buffer.
    * If the index is invalid or the buffer is empty, it returns NULL.
    *
    * @tparam T The type of elements stored in the buffer.
    * @param index The index of the element to retrieve.
    * @return A pointer to the element at the specified index, or NULL if the index is invalid or the buffer is empty.
    */
   T *at(size_t index) {
      if ((m_head - m_tail) <= index) {
         return NULL;
      } else {
         return &m_dataBuff[(m_tail + index) & buffer_mask];
      }
   }

   /**
    * @brief Overloaded subscript operator to access elements in the cyclic buffer.
    *
    * This function allows accessing elements in the cyclic buffer using the subscript operator ([]).
    * It takes an index as input and returns a reference to the element at that index.
    * The index is calculated by adding the current tail index to the provided index and then performing a bitwise AND with the buffer mask.
    *
    * @tparam T The type of elements stored in the buffer.
    * @param index The index of the element to access.
    * @return A reference to the element at the specified index.
    */
   T &operator[](size_t index) {
      return m_dataBuff[(m_tail + index) & buffer_mask];
   }

   /**
    * @brief Writes elements from a buffer to the cyclic buffer.
    *
    * This function writes elements from a buffer to the cyclic buffer. If there is not enough space
    * in the cyclic buffer to write all the elements, it writes as many elements as there is space for.
    *
    * @tparam T The type of elements stored in the cyclic buffer.
    * @param buff Pointer to the buffer containing the elements to write.
    * @param count Number of elements to write.
    * @return The number of elements actually written to the cyclic buffer.
    */
   size_t writeBuff(const T *buff, size_t count);

   /**
    * @brief Reads elements from the cyclic buffer into a buffer.
    *
    * The readBuff function reads elements from the cyclic buffer into the provided buffer. It takes a pointer to the buffer and the number of elements to read as input. If the number of
   * available elements in the buffer is less than the requested count, it only reads the available elements. The read operation is performed by copying the elements from the cyclic buffer
   * to the provided buffer using a for loop.
    *
    * @tparam T The type of elements stored in the buffer.
    * @param buff Pointer to the buffer where the elements will be stored.
    * @param count The number of elements to read.
    * @return The actual number of elements read from the cyclic buffer.
    */
   size_t readBuff(T *buff, size_t count);

private:
   const static index_t buffer_mask = buffer_size - 1;///< bitwise mask for a given buffer size

   index_t m_head;///< head index
   index_t m_tail;///< tail index

   // // put buffer after variables so everything can be reached with short offsets
   T m_dataBuff[buffer_size];///< actual buffer
};

/**
 * @brief Writes the given buffer into the cyclic buffer.
 *
 * @tparam T The type of the elements in the buffer.
 * @tparam buffer_size The size of the cyclic buffer.
 * @tparam index_t The type of the indices used in the buffer.
 * @param buff Pointer to the buffer to be written.
 * @param count The number of elements in the buffer.
 * @return The number of elements actually written to the cyclic buffer.
 */
template<typename T, size_t buffer_size, typename index_t>
size_t CircularBuffer<T, buffer_size, index_t>::writeBuff(const T *buff, size_t count) {
   index_t available = 0;
   size_t to_write = count;

   available = buffer_size - (m_head - m_tail);

   if (available < count)// do not write more than we can
      to_write = available;

   // maybe divide it into 2 separate writes
   for (size_t i = 0; i < to_write; i++)
      m_dataBuff[m_head++ & buffer_mask] = buff[i];

   return to_write;
}

/**
 * @brief Reads data from the circular buffer.
 *
 * This function reads a specified number of elements from the circular buffer into the provided buffer.
 *
 * @tparam T The type of data stored in the buffer.
 * @tparam buffer_size The maximum number of elements that can be stored in the buffer.
 * @tparam index_t The type of the index used to track the buffer position.
 *
 * @param buff Pointer to the buffer where the read data will be stored.
 * @param count The number of elements to read from the buffer.
 *
 * @return The actual number of elements read from the buffer.
 */
template<typename T, size_t buffer_size, typename index_t>
size_t CircularBuffer<T, buffer_size, index_t>::readBuff(T *buff, size_t count) {
   index_t available = 0;
   size_t to_read = count;

   available = m_head - m_tail;

   if (available < count) {
      // do not read more than we can
      to_read = available;
   }

   // maybe divide it into 2 separate reads
   for (size_t i = 0; i < to_read; i++) {
      buff[i] = m_dataBuff[m_tail++ & buffer_mask];
   }
   return to_read;
}
} // namespace buffer

#endif /* CYCLIC_BUFFER_T_H */
