#include "pch.h"
#include"../TList.h"

TEST(TPolynom, create_empty_polynom) {
	ASSERT_NO_THROW(TPolynom a);
	TPolynom b;
	EXPECT_TRUE(b.empty());
}
TEST(TPolynom, add_monom) {
	TPolynom a;
	TMonom b(1, 1, 1, 1);
	ASSERT_NO_THROW(a.addMonom(b));
	a.reset();
	EXPECT_EQ(b, a.getCurr());
}
TEST(TPolynom, can_add_polynom) {
	TPolynom a,c;
	TMonom b(1, 1, 1, 1);
	TMonom e(1, 1, 1, 2);
	a.addMonom(b);
	c.addMonom(e);
	TPolynom res;
	res.addMonom(b);
	res.addMonom(e);
	ASSERT_NO_THROW(a+c);
	EXPECT_EQ(res, a + c);
}
TEST(TPolynom, can_sub_polynom) {
	TPolynom a,c;
	TMonom b(1, 1, 1, 1);
	a.addMonom(b);
	c.addMonom(b*2);
	TPolynom res;
	res.addMonom(b*(-1));
	ASSERT_NO_THROW(a-c);
	EXPECT_EQ(res, a - c);
}
TEST(TPolynom, can_prod_polynom_by_int) {
	TPolynom a,c;
	TMonom b(1, 1, 1, 1);
	a.addMonom(b);
	TPolynom res;
	res.addMonom(b * 4);
	res == a * 4;
	ASSERT_NO_THROW(a*4);
	EXPECT_EQ(res, a*4);
}
TEST(TPolynom, can_copy_polynom) {
	TPolynom a,e;
	TMonom b(1, 1, 1, 1);
	a.addMonom(b);
	
	ASSERT_NO_THROW(TPolynom c(a));
	TPolynom q;
	ASSERT_NO_THROW(q=a);
	TPolynom c(a);
	EXPECT_EQ(a,c);
	EXPECT_EQ(a,q);
}
TEST(TPolynom, copied_polynom_has_own_memory) {
	TPolynom a,e;
	TMonom b(1, 1, 1, 1);
	TMonom r(2, 2, 1, 4);
	a.addMonom(b);
	
	ASSERT_NO_THROW(TPolynom c(a));
	TPolynom q;
	ASSERT_NO_THROW(q=a);
	TPolynom c(a);
	a.addMonom(r);
	EXPECT_NE(a,c);
	EXPECT_NE(a,q);
}
TEST(TPolynom, add_empty_polynom) {
	TPolynom a,c;
	TMonom b(1, 1, 1, 1);
	a.addMonom(b);
	ASSERT_NO_THROW(a + c);
	TPolynom q = a;
	a = a + c;
	EXPECT_EQ(q,a);
}
TEST(TPolynom, merge_monoms_with_equal_degrees) {
	TPolynom a,c;
	TMonom b(1, 1, 1, 1);
	a.addMonom(b);
	a.addMonom(b);
	TMonom e(1, 1, 1, 2);
	c.addMonom(e);
	EXPECT_EQ(c,a);
}
TEST(TPolynom, delete_monom_with_zero_coeff) {
	TPolynom a,c;
	TMonom b(1, 1, 1, 1);
	TMonom bb(1, 1, 1, -1);
	a.addMonom(b);
	a.addMonom(bb);
	EXPECT_EQ(c,a);
}
TEST(TPolynom, addition_long_polynoms) {
	TPolynom a,b,c;
	a.addMonom(TMonom(1,1,1,  4));
	a.addMonom(TMonom(1,2,1, -3));
	a.addMonom(TMonom(1,1,3,  1.2));
	b.addMonom(TMonom(5,2,1,  -3.9));
	b.addMonom(TMonom(1,2,3,  5.52));

	c.addMonom(TMonom(1,1,1,  4));
	c.addMonom(TMonom(1,2,1, -3));
	c.addMonom(TMonom(1,1,3,  1.2));
	c.addMonom(TMonom(5,2,1,  -3.9));
	c.addMonom(TMonom(1,2,3,  5.52));
	EXPECT_EQ(c, a + b);
}
TEST(TPolynom, addition_long_polynoms_with_del_monom_1) {
	TPolynom a,b,c;
	a.addMonom(TMonom(1,1,1,  4));
	a.addMonom(TMonom(1,2,1, -3));
	a.addMonom(TMonom(1,1,3,  1.2));////a
	b.addMonom(TMonom(5,2,1,  -3.9));
	b.addMonom(TMonom(1,1,3,  -1.2));/////b

	c.addMonom(TMonom(1,1,1,  4));
	c.addMonom(TMonom(1,2,1, -3));
	c.addMonom(TMonom(5,2,1,  -3.9));
	EXPECT_EQ(c, a + b);
}
TEST(TPolynom, addition_long_polynoms_with_del_monom_in_the_begin) {
	TPolynom a,b,c;

	a.addMonom(TMonom(5,2,1,  3.9));
	a.addMonom(TMonom(1,1,1,  4));
	a.addMonom(TMonom(1,2,1, -3));
	a.addMonom(TMonom(1,1,3,  1.2));

	b.addMonom(TMonom(5,2,1,  -3.9));
	b.addMonom(TMonom(1,1,3,  1.2));


	c.addMonom(TMonom(1,1,1,  4));
	c.addMonom(TMonom(1,2,1, -3));
	c.addMonom(TMonom(1,1,3,  2.4));

	EXPECT_EQ(c, a + b);
}
TEST(TPolynom, addition_long_polynoms_with_del_monom_in_the_end) {
	TPolynom a,b,c;

	a.addMonom(TMonom(0,2,1,  3.9));
	a.addMonom(TMonom(1,1,1,  4));
	a.addMonom(TMonom(1,2,1, -3));
	a.addMonom(TMonom(1,1,3,  1.2));

	b.addMonom(TMonom(0,2,1,  -3.9));
	b.addMonom(TMonom(1,1,3,  1.2));


	c.addMonom(TMonom(1,1,1,  4));
	c.addMonom(TMonom(1,2,1, -3));
	c.addMonom(TMonom(1,1,3,  2.4));

	EXPECT_EQ(c, a + b);
}
TEST(TPolynom, addition_long_polynoms_with_del_monom_in_the_middle) {
	TPolynom a,b,c;

	a.addMonom(TMonom(5,1,1,  4));
	a.addMonom(TMonom(1,2,1,  3.9));/////a
	a.addMonom(TMonom(0,2,1, -3));
	a.addMonom(TMonom(0,0,3,  1.2));

	b.addMonom(TMonom(1,2,1,  -3.9));////b
	b.addMonom(TMonom(0,0,3,  1.2));


	c.addMonom(TMonom(5,1,1,  4));
	c.addMonom(TMonom(0,2,1, -3));
	c.addMonom(TMonom(0,0,3,  2.4));
	c == a + b;
	EXPECT_EQ(c, a + b);
}
TEST(TPolynom, addition_long_polynoms_with_del_all_monoms) {
	TPolynom a,b,c;
	a.addMonom(TMonom(1,1,3,  1.2));
	a.addMonom(TMonom(1,1,1,  4));
	a.addMonom(TMonom(1,2,1, -3));
	//
	b.addMonom(TMonom(1,2,1,  3));
	b.addMonom(TMonom(1,1,3,  -1.2));
	b.addMonom(TMonom(1,1,1,  -4));

	EXPECT_EQ(c, a + b);
}
