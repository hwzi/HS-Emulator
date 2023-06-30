#pragma once

#include "standards.hpp"

namespace ahn
{
	class nkcs
	{
	public:
		nkcs();
		~nkcs();

		void pack(unsigned char* source);

		void set_key(unsigned int key);

		unsigned int get_product() const;
		unsigned int get_key() const;

	private:
		void seed(unsigned char* source);
		bool verify(unsigned int count, unsigned char end);

		unsigned int nkcs_key;
		unsigned int nkcs_product;

		unsigned char input[0x20];
		unsigned char table[0x20];
	};
}