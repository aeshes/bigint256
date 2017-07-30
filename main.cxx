#include <iostream>
#include <cstdint>

#define BIGNUM_CHUNK int8_t

typedef struct
{
	BIGNUM_CHUNK a[5];
} bigint256;


void make_bigint256(
	bigint256* x,
	BIGNUM_CHUNK a0,
	BIGNUM_CHUNK a1,
	BIGNUM_CHUNK a2,
	BIGNUM_CHUNK a3,
	BIGNUM_CHUNK a4)
{
	x->a[0] = a0;
	x->a[1] = a1;
	x->a[2] = a2;
	x->a[3] = a3;
	x->a[4] = a4;
}

void bigint256_print(const bigint256* x)
{
	for (int i = 4; i >= 0; --i)
		std::cout << +x->a[i] << " ";
	std::cout << std::endl;
}

void bigint256_add(bigint256* r,
                   const bigint256* x,
                   const bigint256* y)
{
	for (int i = 0; i < 5; ++i)
	{
		r->a[i] = x->a[i] + y->a[i];
	}

	BIGNUM_CHUNK carry = r->a[0] >> 6;
	r->a[1] += carry;
	r->a[0] &= 0x3F; /*Zero carries */

	carry = r->a[1] >> 6;
	r->a[2] += carry;
	r->a[1] &= 0x3F;

	carry = r->a[2] >> 6;
	r->a[3] += carry;
	r->a[2] &= 0x3F;

	carry = r->a[3] >> 6;
	r->a[4] += carry;
	r->a[3] &= 0x3F;

	r->a[5] &= 0x3F;
}

void bigint256_sub(bigint256* r,
                   const bigint256* x,
                   const bigint256* y)
{
	r->a[0] = x->a[0] - y->a[0];
	r->a[1] = x->a[1] - y->a[1];
	r->a[2] = x->a[2] - y->a[2];
	r->a[3] = x->a[3] - y->a[3];
	r->a[4] = x->a[4] - y->a[4];

	int8_t carry = r->a[0] >> 6;
	r->a[1] -= carry;
	r->a[0] &= 0x3F;

	carry = r->a[1] >> 6;
	r->a[2] -= carry;
	r->a[1] &= 0x3F;

	carry = r->a[2] >> 6;
	r->a[3] -= carry;
	r->a[2] &= 0x3F;

	carry = r->a[3] >> 6;
	r->a[4] -= carry;
	r->a[3] &= 0x3F;

	r->a[4] &= 0x3F;
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

	bigint256_sub(&r, &x, &y);
	bigint256_print(&r);
}
