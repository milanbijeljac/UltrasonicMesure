#pragma once

#include <memory>
#include "types.h"

namespace DataStructure
{
	/** Class ring buffer. Data can be both on stack and heap */
	template <typename T>
	class RingBuffer
	{
	public:
		/** Result of a write/read operation */
		enum class Status : uint8
		{
			Ok = 0,
			Overwrite,           /* write would clobber not-yet-read data */
			WriteLimitExceeded,  /* requested write larger than free space  */
			ReadSizeExceeded,    /* requested read larger than available    */
			Empty                /* nothing to read                         */
		};

		[[nodiscard]] static bool createObj(uint8 size, T* elementStorage, void* objectStorage, RingBuffer*& out)
		{
			/* Check if size exceeds uint8 and if memory location is nullptr */
			if (size == 0 || size > 255 || elementStorage == nullptr)
			{
				out = nullptr;
				return false;
			}

			out = new (objectStorage) RingBuffer(size, elementStorage); /* Placement new - construct only object at give memory address (objectStorage) */
																		/* With this user determines if object is on heap or stack */
			return true;
		}

		void destroyObj()
		{
			this->~RingBuffer();
		}
		/** Getter for available bytes to read */
		[[nodiscard]] uint8 RingBuffer_u_GetMaxReadSize() const noexcept { return m_size - m_MaxBytesToWrite; }

		/** Getter for read index */
		[[nodiscard]] uint8 RingBuffer_u_GetReadIndex() const noexcept { return m_readIndex; }

		/** Getter for write index */
		[[nodiscard]] uint8 RingBuffer_u_GetWriteIndex() const noexcept { return m_writeIndex; }

		/**
		 *
		 * \brief      - Method used to push elements to ring buffer.
		 * \param[in]  - const T* data - pointer to data that needs to be pushed to buffer
		 * \param[in]  - uint8 size - size of data
		 * \return     - NONE
		 *
		 */
		[[nodiscard]] Status RingBuffer_v_WriteElement(const T* data, uint8 size)
		{
			uint8 i;

			if ((RingBuffer::m_fullCircle == 1u) && (RingBuffer::m_writeIndex == RingBuffer::m_readIndex))
			{
				return Status::Overwrite;
			}
			else if ((size > RingBuffer::m_MaxBytesToWrite) || (size > RingBuffer::m_size))
			{
				return Status::WriteLimitExceeded;
			}

			for (i = 0; i < size; i++)
			{
				if (RingBuffer::m_writeIndex == RingBuffer::m_size)
				{
					RingBuffer::m_writeIndex = 0u;
					RingBuffer::m_fullCircle = 1u;
				}

				RingBuffer::buffer[RingBuffer::m_writeIndex] = *data;
				data++;
				RingBuffer::m_writeIndex++;
				RingBuffer::m_MaxBytesToWrite--;
			}

			return Status::Ok;
		}

		/**
		 *
		 * \brief      - Method used to pop elements from ring buffer.
		 * \param[in]  - const T* data - pointer to data in which data from read buffer is stored
		 * \param[in]  - uint8 size - size to read
		 * \return     - NONE
		 *
		 */
		[[nodiscard]] Status RingBuffer_v_ReadElement(T* data, uint8 size)
		{
			uint8 i;
			uint8 u_readLength = 0u;

			u_readLength = RingBuffer::RingBuffer_u_GetMaxReadSize();

			if (size > u_readLength)
			{
				if ((m_writeIndex == m_readIndex) && m_fullCircle != 1)
				{
					return Status::Empty;
				}
				return Status::ReadSizeExceeded;
			}

			for (i = 0; i < size; i++)
			{
				if (RingBuffer::m_readIndex == RingBuffer::m_size)
				{
					RingBuffer::m_readIndex = 0u;
					RingBuffer::m_fullCircle = 0u;
				}

				*data = RingBuffer::buffer[RingBuffer::m_readIndex];
				data++;
				RingBuffer::m_readIndex++;
				RingBuffer::m_MaxBytesToWrite++;
			}

			return Status::Ok;
		}

	private:

		RingBuffer(uint8 size, T* storage) : buffer(storage), m_MaxBytesToWrite(size), m_size(size) {}

		~RingBuffer() = default;

	private:
		uint8 m_writeIndex{ 0 };
		uint8 m_readIndex{ 0 };
		uint8 m_fullCircle{ 0 };
		uint8 m_MaxBytesToWrite;
		uint8 m_size;
		T* buffer;
	};
}
