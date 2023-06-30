#include "nkcs.hpp"

namespace ahn
{
	nkcs::nkcs()
	{
		unsigned char initialization_table[32] =
		{
			0x11, 0x9F, 0x30, 0x01, 0x82, 0xE7, 0xE3, 0x89,
			0x38, 0xF4, 0x55, 0xA4, 0xE5, 0x6D, 0xE8, 0x37,
			0x7A, 0xCB, 0x79, 0xBE, 0x7B, 0x56, 0x8A, 0xCC,
			0xFC, 0x52, 0x9D, 0xE6, 0x4E, 0x73, 0xEF, 0x00
		};

		memset(this->input, 0, 32);
		memcpy(this->table, initialization_table, 32);

		this->nkcs_key = 0;
		this->nkcs_product = 0x81750E16;
	}

	nkcs::~nkcs()
	{
		memset(this->input, 0, 32);
		memset(this->table, 0, 32);
	}

	void nkcs::pack(unsigned char* source)
	{
		this->seed(source);

		unsigned int verification = 0x00123456;

		for (int i = 0; i < 0x20; i++)
		{
			if ((1 << i) & 0x11707E)
			{
				if (this->nkcs_product & (1 << (this->table[i] % 32)))
				{
					verification |= (1 << (this->input[i] % 32));
				}
				else
				{
					verification &= ~(1 << (this->input[i] % 32));
				}
			}
		}

		memcpy(this->table, this->input, 32);
		this->nkcs_product = verification;
	}

	void nkcs::set_key(unsigned int key)
	{
		this->nkcs_key = key;
	}

	unsigned int nkcs::get_product() const
	{
		return this->nkcs_product;
	}

	unsigned int nkcs::get_key() const
	{
		return this->nkcs_key;
	}

	void nkcs::seed(unsigned char* source)
	{
		memset(this->input, 0, 32);

		unsigned char value = source[0];

		for (unsigned int i = 0; i < 31; i++)
		{
			if (this->verify(i, value) != false)
			{
				value++;
				i--;
			}
			else
			{
				this->input[i] = value;
				value = source[i + 1];
			}
		}
	}

	bool nkcs::verify(unsigned int count, unsigned char end)
	{
		if (count <= 0)
		{
			return false;
		}

		for (unsigned int i = 0; ((this->input[i] % 32) != (end % 32) && (end % 32) != 0); i++)
		{
			if (i >= count)
			{
				return false;
			}
		}

		return true;
	}
}