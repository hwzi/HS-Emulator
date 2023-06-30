#include "codesection.hpp"

typedef struct
{
	unsigned short offset_00;
	unsigned short offset_02;
	Padding(0x04);
	unsigned int offset_08;
	unsigned int offset_0C;
	unsigned int offset_10;
	unsigned int offset_14;
	unsigned int offset_18;
	Padding(0x04);
} codesection_t;

namespace ahn
{
	codesection::codesection()
	{

	}

	codesection::~codesection()
	{
		if (this->crc_allocation != nullptr)
		{
			free(this->crc_allocation);
		}

		if (this->codesections != nullptr)
		{
			free(this->codesections);
		}
	}

	bool codesection::initialize(buffer::request* request)
	{
		this->codesection_count = request->get<unsigned char>();		/* request + 0x00 */
		this->codesection_byte = request->get<unsigned char>();			/* request + 0x01 */

		request->indent(6);												/* request + 0x02 -> not used */

		this->codesection_data_1 = request->get<unsigned int>();		/* request + 0x08 */
		this->codesection_data_2 = request->get<unsigned int>();		/* request + 0x0C */

		for (unsigned int i = 0; i < codesection_count; i++)
		{
			unsigned int start_address = request->get<unsigned int>();	/* request + (0x10 + (0x08 * i)) */
			unsigned int size = request->get<unsigned int>();			/* request + (0x14 + (0x08 * i)) */

			this->codesection_infos.push_back({ start_address, start_address + size - 1, size });
		}

		if (this->already_initialized())
		{
			return true;
		}

		this->crc_allocation = reinterpret_cast<unsigned char*>(malloc(1024));

		if (!this->crc_allocation)
		{
			return false;
		}

		this->initialize_allocation(0x037ABE17, this->crc_allocation);

		if (this->codesection_count <= 0 || this->codesection_count > 40)
		{
			memset(this->crc_allocation, 0, 1024);
			free(this->crc_allocation);
			this->crc_allocation = nullptr;
			return false;
		}

		this->codesections = reinterpret_cast<unsigned char*>(malloc(32 * this->codesection_count));

		if (this->codesections == nullptr)
		{
			memset(this->crc_allocation, 0, 1024);
			free(this->crc_allocation);
			this->crc_allocation = nullptr;
			return false;
		}

		codesection_t* codesection = reinterpret_cast<codesection_t*>(this->codesections);
		unsigned int total_bitsum = 0;

		for (auto info : this->codesection_infos)
		{
			codesection->offset_08 = (this->codesection_data_1 + info.start_address) & 0xFFFFF000;
			codesection->offset_0C = this->codesection_data_2 + (info.start_address >= -static_cast<int>(this->codesection_data_1));
			codesection->offset_10 = (this->codesection_data_1 + info.end_address) & 0xFFFFF000;
			codesection->offset_14 = this->codesection_data_2 + (info.end_address >= -static_cast<int>(this->codesection_data_1));
			codesection->offset_18 = (info.size % 0x1000);

			unsigned int bitsum = codesection->offset_10 - codesection->offset_08 + 1;

			bitsum >>= 12;
			bitsum++;

			codesection->offset_00 = total_bitsum;
			codesection->offset_02 = bitsum;

			total_bitsum += bitsum;
			codesection += 32;
		}

		this->maximum_size_check = total_bitsum / this->codesection_byte;
		this->average_size_check = total_bitsum % this->codesection_byte;

		if (this->average_size_check == 0)
		{
			this->maximum_size_check--;
			this->average_size_check = this->codesection_byte;
		}

		srand(GetTickCount());

		this->current_size_check = rand() % (this->maximum_size_check + 1);
		this->minimum_size_check = this->codesection_byte;
		return true;
	}

	bool codesection::codesections_exists()
	{
		return (this->codesections != nullptr);
	}
	
	bool codesection::already_initialized()
	{
		return (this->codesections_exists() && this->minimum_size_check != 0x00);
	}

	void codesection::initialize_allocation(unsigned int key, unsigned char* allocation)
	{
		for (int i = 0; i <= 0xFF; i++)
		{
			*reinterpret_cast<unsigned int*>(allocation + (4 * i)) = (this->bitcheck(i, 8) << 24);

			for (int j = 0; j < 8; j++)
			{
				*reinterpret_cast<unsigned int*>(allocation + (4 * i)) = ((*reinterpret_cast<unsigned int*>(allocation + (4 * i)) & 0x80000000) != 0 ? key : 0) ^ (2 * *reinterpret_cast<unsigned int*>(allocation + (4 * i)));
			}

			*reinterpret_cast<unsigned int*>(allocation + (4 * i)) = this->bitcheck(*reinterpret_cast<unsigned int*>(allocation + (4 * i)), 32);
		}
	}

	unsigned int codesection::bitcheck(unsigned int data, unsigned int size)
	{
		int bit_check = 0;

		for (unsigned int i = 1; i < (size + 1); i++)
		{
			if (data & 1)
			{
				bit_check |= (1 << (size - i));
			}

			data >>= 1;
		}

		return bit_check;
	}
}