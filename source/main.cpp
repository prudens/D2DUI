// 测试非UI功能
#include <iostream>
#include "GuiWindow.h"
#include <memory>
#include "../base/basetypes.h"
#include "../base/cstring.h"
int main( char**, int )
{
	using std::cout;
	using std::endl;
	using std::shared_ptr;
	std::cout << "Hello,World!" << std::endl;
	std::shared_ptr<DemoApp> app( new DemoApp );
	cout << "the shared_ptr size is: " << sizeof( app ) << endl;// 应该说有12字节
	shared_ptr<int> int_ptr( new int );
	//vector
	//CSize
	//CSize 
//	Gdiplus::RectF
	using DUI_V0_1::CSize;
	CSize size = {1,2};
	size = CSize( 2, 1 );
	size += CSize( 1, 1 );
	size -= CSize( 2, 2 );
	size.SetSize( 3, 3 );
	//size = (-size);
	cout << "cx:" << size.cx << "cy:" << size.cy << endl;
 
 	using DUI_V0_1::CPoint;
 	CPoint pt;
 	typedef DUI_V0_1::DUI_BASE::CSizeT<CPoint::value_type> CSize2;
 	CSize sz2(1,2),sz3(2,1);
 	//pt.Offset( size.To<CSize2>() );// 类型检查，显然不安全，所以直接用编译不通过
 	cout << "pt.x:" << pt.x << "pt.y" << pt.y << endl;
 	DUI_V0_1::CPoint ptf( 2, 3 );
 	cout << ptf.x << "  "<< ptf.y << endl;
	CSize sz = { 1, 2 };
	if ( CSize( 1, 2 ) == sz2 )
	{
		cout << "same" << endl;
	}
	POINT pt1 = { 1, 2 };
	CSize sz5( pt1 );
	using DUI_V0_1::CString;
	CString str;

	str.assign( L"123" );
    if (str == L"123")
    {
		cout << "可以用重载运算符" << endl;
    }
	str.to_string(1.1f);
	CString str2( L"1234",4 );
	CString str3( L"111" );
	CString str4 = str3;
	str4 += str;
    CString str5 = str4 + str3;
	std::wcout << str5.c_str() << endl;
	std::wcout << str.c_str() << endl;

// 	A a(1);
// 	B b(1);

	system( "pause" );
	return 0;
}
