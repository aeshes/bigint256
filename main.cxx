#include <iostream>
#include <cstring>

#define BIGNUM_CHUNK uint8_t

typedef struct
{
	BIGNUM_CHUNK chunks[5];
} bigint256;


void make_bigint256(
	bigint256* x,
	BIGNUM_CHUNK a0,
	BIGNUM_CHUNK a1,
	BIGNUM_CHUNK a2,
	BIGNUM_CHUNK a3,
	BIGNUM_CHUNK a4)
{
	x->chunks[0] = a0;
	x->chunks[1] = a1;
	x->chunks[2] = a2;
	x->chunks[3] = a3;
	x->chunks[4] = a4;
}

void bigint256_print(const bigint256* x)
{
	for (int i = 4; i >= 0; --i)
		std::cout << +x->chunks[i] << " ";
	std::cout << std::endl;
}

void bigint256_add(bigint256* result,
                   const bigint256* x,
                   const bigint256* y)
{
	unsigned long long carry = 0;
	for (int i = 0; i < 5; ++i)
	{
		result->chunks[i] = x->chunks[i] + y->chunks[i];
	}

	BIGNUM_CHUNK tmp = result->chunks[0];
	tmp >>= 6;	/*Get carry */
	result->chunks[1] += tmp;
	result->chunks[0] &= 0x3F; /*Zero carries */

	tmp = result->chunks[1];
	tmp >>= 6;
	result->chunks[2] += tmp;
	result->chunks[1] &= 0x3F;

	tmp = result->chunks[2];
	tmp >>= 6;
	result->chunks[3] += tmp;
	result->chunks[2] &= 0x3F;

	tmp = result->chunks[3];
	tmp >>= 6;
	result->chunks[4] += tmp;
	result->chunks[3] &= 0x3F;

	result->chunks[5] &= 0x3F;
}

void bigint256_sub(bigint256* result,
                   const bigint256* x,
                   const bigint256* y)
{
	unsigned carry = 0;
	for (int i = 0; i < 5; ++i)
	{
		result->chunks[i] = x->chunks[i] - y->chunks[i] - carry;
		carry = x->chunks[i] < y->chunks[i];
	}
}


int main()
{
	bigint256 x, y, r;

	//make_bigint256(&x, 0xE5, 0x2A, 0xCD, 0x51);
	//make_bigint256(&y, 0xFF, 0xD0, 0x19, 0xCC);
	make_bigint256(&x, 0, 40, 44, 38, 59);
	make_bigint256(&y, 23, 57, 15, 0, 0);

	bigint256_print(&x);
	bigint256_print(&y);

	bigint256_add(&r, &x, &y);
	bigint256_print(&r);
}
