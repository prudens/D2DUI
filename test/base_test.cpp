#define BOOST_TEST_MODULE base_test
#include <boost/test/included/unit_test.hpp>
#include "../base/basetypes.h"
using namespace DUI_V0_1;
using namespace DUI_BASE;

BOOST_AUTO_TEST_CASE(csize_test)
{
	DUI_V0_1::CSize sz(1, 2);
	BOOST_CHECK( sz.cx == 1 );
	BOOST_CHECK(sz.cy == 2);
	DUI_V0_1::POINT pt;
	pt.x = 1;
	pt.y = 2;
	DUI_V0_1::CSize size(pt);	
	BOOST_CHECK(sz==size);
	size =size+pt;
	BOOST_CHECK(size.cx == 2);
	size = size - pt;
	BOOST_CHECK(size.cx == 1);
}

BOOST_AUTO_TEST_CASE(cpoint_test)
{
	DUI_V0_1::CPoint pt(1, 2);
	BOOST_CHECK(pt.x == 1);
	BOOST_CHECK(pt.y == 2);
	DUI_V0_1::SIZE sz;
	sz.cx = 3;
	sz.cy = 4;
	DUI_V0_1::CPoint point(sz);
	BOOST_CHECK(point.x == 3);
//	DUI_V0_1::CSize size = point + sz;
//	BOOST_CHECK(size.cx == 6);
}

BOOST_AUTO_TEST_CASE(crect_test)
{
	DUI_V0_1::CRect rc(1, 2, 3, 4);
	BOOST_CHECK(rc.left == 1);
}