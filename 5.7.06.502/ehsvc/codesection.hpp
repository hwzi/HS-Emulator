#pragma once
#include "standards.hpp"
#include "buffer.hpp"
#include <vector>

#pragma warning(disable:4018)

namespace ahn
{
	typedef struct
	{
		unsigned int start_address;
		unsigned int end_address;
		unsigned int size;
	} codesection_info;

	class codesection
	{
	public:
		codesection();
		~codesection();

		bool initialize(buffer::request* request);

		bool codesections_exists();

	private:
		bool already_initialized();

		void initialize_allocation(unsigned int key, unsigned char* allocation);
		unsigned int bitcheck(unsigned int data, unsigned int size);

		unsigned char codesection_count;
		unsigned char codesection_byte;

		unsigned int codesection_data_1;
		unsigned int codesection_data_2;

		unsigned char* crc_allocation;
		unsigned char* codesections;

		std::vector<codesection_info> codesection_infos;

		unsigned char minimum_size_check;
		unsigned char average_size_check;

		unsigned short maximum_size_check;
		unsigned short current_size_check;
	};
}