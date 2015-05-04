#pragma once
#include "stdint.h"
#include "intsafe.h"
#include <wtypes.h>
#include "windef.h"
namespace DUI_V0_1{
	namespace DUI_BASE{
#ifndef _In_
#define _In_
#define _Out_
#endif

	// size 的基类，尺寸自定义类型，以适应不同需求
	template<typename T>
	struct SIZE{
		typedef T value;
		value cx;
		value cy;
	};

	template<typename T>
	struct POINT
	{
		typedef T value_type;
		value_type x;
		value_type y;
	};

	template<typename T>
	struct RECT
	{
		typedef T value_type;
		value_type left;
		value_type top;
		value_type right;
		value_type buttom;
	};

	template<typename T>
	struct type_traits
	{
		typedef SIZE<T>  SIZE;
		typedef POINT<T> POINT;
		typedef RECT<T>  RECT;
	};


	template<typename T, typename basetype_traits, typename Point>
	class CPointT;//前向声明
	template<typename T, typename basetype_traits, typename Rect>
	class CRectT;

	template
		< class T,
	class TypeTraits = type_traits<T>,
	class Size = typename TypeTraits::SIZE
		>
	class CSizeT :public Size
	{
	public:
		typedef CSizeT<T, TypeTraits, Size > _Myt;
		typedef Size _MyBase;
		typedef T value_type;
		typename typedef TypeTraits::POINT POINT;
		typedef CPointT<T, TypeTraits, POINT> CPoint;
		typedef typename TypeTraits::RECT RECT;
		typedef CRectT<T, TypeTraits, RECT> CRect;
		CSizeT() throw( )
		{
			cx = cy = 0;
		}

		// create from two integers
		CSizeT(
			_In_ value_type CX,
			_In_ value_type CY ) throw( )
		{
			cx = CX;
			cy = CY;
		}

		// create from another size
		CSizeT( _In_ _MyBase size ) throw( )
		{
			cx = size.cx;
			cy = size.cy;
		}

		// create from a point
		CSizeT( _In_ POINT Pt ) throw( )
		{
			cx = Pt.x;
			cy = Pt.y;
		}

		CSizeT( _In_ DWORD dwSize ) throw( )
		{
			cx = (short)LOWORD( dwSize );
			cy = (short)HIWORD( dwSize );
		}

		// Operations
		bool operator==( _In_ _MyBase size ) const throw( )
		{
			return this->cx == size.cx && this->cy == size.cy;
		}

		bool operator!=( _In_ const _MyBase& size ) const throw( )
		{
			return !( *this == size );
		}

		void operator+=( _In_ _MyBase size ) throw( )
		{
			this->cx += size.cx;
			this->cy += size.cy;
		}

		void operator-=( _In_ _MyBase size ) throw( )
		{
			this->cx -= size.cx;
			this->cy -= size.cy;
		}

		void SetSize( _In_ value_type CX, _In_ value_type CY ) throw( )
		{
			cx = CX;
			cy = CY;
		}

		// Operators returning CSize values
		_Myt operator+( _In_ _MyBase size ) const throw( )
		{
			return CSizeT( cx + size.cx, cy + size.cy );
		}
		_Myt operator-( _In_ _MyBase size ) const throw( )
		{
			return CSizeT( cx - size.cx, cy - size.cy );
		}
		_Myt operator-( ) const throw( )
		{
			return _Myt( 0 - cx, 0 - cy );
		}

		// Operators returning CPoint values
		CPoint operator+( _In_ POINT point ) const throw( )
		{
			return CPoint( cx + point.x, cy + point.y );
		}
		CPoint operator-( _In_ POINT point ) const throw( )
		{
			return CPoint( cx - point.x, cy - point.y );
		}

		template<typename TypeDest>
		TypeDest To()const throw( )
		{
			TypeDest out;
			out.cx = static_cast<TypeDest::value_type>( cx );
			out.cy = static_cast<TypeDest::value_type>( cy );
			return out;
		}

		// 		// Operators returning CRect values
		CRect operator+( _In_ const RECT* lpRect ) const throw( )
		{
			return CRect( lpRect ) + *this;
		}

		CRect operator-( _In_ const RECT* lpRect ) const throw( )
		{
			return CRect( lpRect ) - *this;
		}

	};

	template
		< class T,
	class TypeTraits = type_traits<T>,
	class Point = typename TypeTraits::POINT
		>
	class CPointT :public Point
	{
	public:
		typedef CPointT<T, TypeTraits, Point> _Myt;
		typedef Point _MyBase;
		typedef T value_type;
		typename typedef TypeTraits::SIZE SIZE;
		typedef CSizeT<T, TypeTraits, SIZE> CSize;
		typename typedef TypeTraits::RECT RECT;
		typedef CRectT<T, TypeTraits, RECT> CRect;
		// create an uninitialized point
		CPointT() throw( )
		{
			x = y = 0;
		}
		// create from two integers
		CPointT(
			_In_ value_type X,
			_In_ value_type Y ) throw( )
		{
			x = X;
			y = Y;
		}
		// create from another point
		CPointT( _In_ _MyBase Pt ) throw( )
		{
			x = Pt.x;
			y = Pt.y;
		}
		// create from a size
		CPointT( _In_ SIZE sz ) throw( )
		{
			x = sz.cx;
			y = sz.cy;
		}
		// create from an LPARAM: x = LOWORD(dw) y = HIWORD(dw)
		CPointT( _In_ LPARAM dwPoint ) throw( )
		{
			x = (short)LOWORD( dwPoint );
			y = (short)HIWORD( dwPoint );
		}


		// Operations

		// translate the point
		void Offset(
			_In_ value_type xOffset,
			_In_ value_type yOffset ) throw( )
		{
			x += xOffset;
			y += yOffset;
		}

		void Offset( _In_ _MyBase point ) throw( )
		{
			x += xOffset;
			y += yOffset;
		}

		void Offset( _In_ SIZE size ) throw( )
		{
			x += size.cx;
			y += size.cy;
		}

		void SetPoint(
			_In_ int X,
			_In_ int Y ) throw( )
		{
			x = X;
			y = Y;
		}

		BOOL operator==( _In_ _MyBase point ) const throw( )
		{
			return ( x == point.x && y == point.y );
		}

		BOOL operator!=( _In_ _MyBase point ) const throw( )
		{
			return ( x != point.x || y != point.y );
		}

		void operator+=( _In_ SIZE size ) throw( )
		{
			x += size.cx;
			y += size.cy;
		}

		void operator-=( _In_ SIZE size ) throw( )
		{
			x -= size.cx;
			y -= size.cy;
		}

		void operator+=( _In_ _MyBase point ) throw( )
		{
			x += point.x;
			y += point.y;
		}

		void operator-=( _In_ _MyBase point ) throw( )
		{
			x -= point.x;
			y -= point.y;
		}

		// Operators returning CPoint values
		_Myt operator+( _In_ SIZE size ) const throw( )
		{
			return _Myt( x + size.cx, y + size.cy );
		}

		_Myt operator-( _In_ SIZE size ) const throw( )
		{
			return _Myt( x - size.cx, y - size.cy );
		}

		_Myt operator-( ) const throw( )
		{
			return _Myt( -x, -y );
		}

		_Myt operator+( _In_ _MyBase point ) const throw( )
		{
			return _Myt( x + point.x, y + point.y );
		}

		// Operators returning CSize values
		CSize operator-( _In_ _MyBase point ) const throw( )
		{
			return CSize( x - point.x, y - point.y );
		}

		template<typename T> T To()const throw( )
		{
			T out;
			out.x = static_cast<T::value_type>( x );
			out.y = static_cast<T::value_type>( y );
			return out;
		}

		// Operators returning CRect values
		CRect operator+( _In_ const RECT* lpRect ) const throw( )
		{
			return CRect( lpRect ) + *this;
		}
		CRect operator-( _In_ const RECT* lpRect ) const throw( )
		{
			return CRect( lpRect ) - *this;
		}

	};

	template
		<
			class T,
			class TypeTraits = type_traits<T>,
			class Rect = typename TypeTraits::RECT
		>
	class CRectT :public Rect
	{
	public:
		typedef T value_type;
		typedef CRectT<T, TypeTraits, Rect> _Myt;
		typedef Rect _MyBase;
		typedef _Myt* LPRECT;
		typedef const _Myt* LPCRECT;
		typename typedef TypeTraits::POINT POINT;
		typedef CPointT<T, TypeTraits, POINT> CPoint;
		typename typedef TypeTraits::SIZE SIZE;
		typedef CSizeT<T, TypeTraits, SIZE> CSize;
		// uninitialized rectangle
		CRectT() throw( )
		{
			left = right = top = bottom = 0;
		}
		// from left, top, right, and bottom
		CRectT(
			_In_ value_type l,
			_In_ value_type t,
			_In_ value_type r,
			_In_ value_type b ) throw( )
		{
			left = l;
			top = t;
			right = r;
			bottom = b;
		}
		// copy constructor
		CRectT( _In_ const _MyBase& srcRect ) throw( )
		{
			memcpy( this, &srcRect, sizeof( srcRect ) );
		}

		// from a pointer to another rect
		CRectT( _In_ const _MyBase* lpSrcRect ) throw( )
		{
			memcpy( this, lpSrcRect, sizeof( RECT ) );
		}
		// from a point and size
		CRectT(
			_In_ POINT point,
			_In_ SIZE size ) throw( )
		{
			right = ( left = point.x ) + size.cx;
			bottom = ( top = point.y ) + size.cy;
		}
		// from two points
		CRectT(
			_In_ POINT topLeft,
			_In_ POINT bottomRight ) throw( )
		{
			left = topLeft.x;
			top = topLeft.y;
			right = bottomRight.x;
			bottom = bottomRight.y;
		}

		// Attributes (in addition to RECT members)

		// retrieves the width
		int Width() const throw( )
		{
			return right - left;
		}
		// returns the height
		int Height() const throw( )
		{
			return bottom - top;
		}
		// returns the size
		CSize Size() const throw( )
		{
			return CSize( right - left, bottom - top );
		}
		// reference to the top-left point
		CPoint& TopLeft() throw( )
		{
			return *( ( CPoint* )this );
		}
		// reference to the bottom-right point
		CPoint& BottomRight() throw( )
		{
			return *( ( CPoint* )this + 1 );
		}
		// const reference to the top-left point
		const CPoint& TopLeft() const throw( )
		{
			return *( ( CPoint* )this );
		}
		// const reference to the bottom-right point
		const CPoint& BottomRight() const throw( )
		{
			return *( ( CPoint* )this + 1 );
		}
		// the geometric center point of the rectangle
		CPoint CenterPoint() const throw( )
		{
			return CPoint( ( left + right ) / 2, ( top + bottom ) / 2 );
		}
		// swap the left and right
		void SwapLeftRight() throw( )
		{
			SwapLeftRight( LPRECT( this ) );
		}
		static void WINAPI SwapLeftRight( _Inout_ LPRECT lpRect ) throw( )
		{
			value_type temp = lpRect->left;
			lpRect->left = lpRect->right;
			lpRect->right = temp;
		}

		// convert between CRect and LPRECT/LPCRECT (no need for &)
		operator LPRECT() throw( )
		{
			return this;
		}
		operator LPCRECT() const throw( )
		{
			return this;
		}

		// returns TRUE if rectangle has no area
		BOOL IsRectEmpty() const throw( )
		{
			return left >= right || top >= bottom;
		}
		// returns TRUE if rectangle is at (0,0) and has no area
		BOOL IsRectNull() const throw( )
		{
			return ( left == 0 && right == 0 && top == 0 && bottom == 0 );
		}
		// returns TRUE if point is within rectangle
		BOOL PtInRect( _In_ POINT point ) const throw( )
		{
			return point.x >= left &&
				point.x < right &&
				point.y >= top  &&
				point.y < bottom &&
				!IsRectEmpty();
		}

		// Operations

		// set rectangle from left, top, right, and bottom
		void SetRect(
			_In_ value_type x1,
			_In_ value_type y1,
			_In_ value_type x2,
			_In_ value_type y2 ) throw( )
		{
			left = x1;
			top = y1;
			right = x2;
			bottom = y2;
		}
		void SetRect(
			_In_ POINT topLeft,
			_In_ POINT bottomRight ) throw( )
		{
			left = topLeft.x;
			top = topLeft.y;
			right = bottomRight.x;
			bottom = bottomRight.y;
		}
		// empty the rectangle
		void SetRectEmpty() throw( )
		{
			memset( this, 0, sizeof( _Myt ) );
		}
		// copy from another rectangle
		void CopyRect( _In_ LPCRECT lpSrcRect ) throw( )
		{
			if ( lpSrcRect )
			{
				lpSrcRect->left = left;
				lpSrcRect->top = top;
				lpSrcRect->right = right;
				lpSrcRect->bottom = bottom;
			}
		}
		// TRUE if exactly the same as another rectangle
		BOOL EqualRect( _In_ LPCRECT lpRect ) const throw( )
		{
			if ( !lpRect )
			{
				return FALSE;
			}
			return left == lpRect->left &&
				top == lpRect->top &&
				right == lpRect->right &&
				bottom == lpRect->bottom;
		}

		// Inflate rectangle's width and height by
		// x units to the left and right ends of the rectangle
		// and y units to the top and bottom.
		void InflateRect(
			_In_ value_type x,
			_In_ value_type y ) throw( )
		{
			left -= x;
			right += x;
			top -= y;
			bottom += y;
		}
		// Inflate rectangle's width and height by
		// size.cx units to the left and right ends of the rectangle
		// and size.cy units to the top and bottom.
		void InflateRect( _In_ SIZE size ) throw( )
		{
			InflateRect( size.cx, size.cy );
		}
		// Inflate rectangle's width and height by moving individual sides.
		// Left side is moved to the left, right side is moved to the right,
		// top is moved up and bottom is moved down.
		void InflateRect( _In_ LPCRECT lpRect ) throw( )
		{
			left -= lpRect->left;
			top -= lpRect->top;
			right += lpRect->right;
			bottom += lpRect->bottom;
		}
		void InflateRect(
			_In_ value_type l,
			_In_ value_type t,
			_In_ value_type r,
			_In_ value_type b ) throw( )
		{
			left -= l;
			top -= t;
			right += r;
			bottom += b;
		}

		// deflate the rectangle's width and height without
		// moving its top or left
		void DeflateRect(
			_In_ value_type x,
			_In_ value_type y ) throw( )
		{
			InflateRect( 0 - x, 0 - y );
		}
		void DeflateRect( _In_ SIZE size ) throw( )
		{
			InflateRect( size );
		}
		void DeflateRect( _In_ LPCRECT lpRect ) throw( )
		{
			left += lpRect->left;
			top += lpRect->top;
			right -= lpRect->right;
			bottom -= lpRect->bottom;
		}
		void DeflateRect(
			_In_ value_type l,
			_In_ value_type t,
			_In_ value_type r,
			_In_ value_type b ) throw( )
		{
			left += l;
			top += t;
			right -= r;
			bottom -= b;
		}

		// translate the rectangle by moving its top and left
		void OffsetRect(
			_In_ value_type x,
			_In_ value_type y ) throw( )
		{
			left += x;
			top += y;
			right += x;
			bottom += y;
		}

		void OffsetRect( _In_ SIZE size ) throw( )
		{
			OffsetRect( size.cx, size.cy );
		}
		void OffsetRect( _In_ POINT point ) throw( )
		{
			OffsetRect( point.x, point.y );
		}
		void NormalizeRect() throw( )
		{
			if ( left > right )
			{
				swap( left, right );
			}
			if ( top > bottom )
			{
				swap( top, bottom );
			}
		}

		// absolute position of rectangle
		void MoveToY( _In_ value_type y ) throw( )
		{
			bottom = Height() + y;
			top = y;
		}
		void MoveToX( _In_ value_type x ) throw( )
		{
			right = Width() + x;
			left = x;
		}
		void MoveToXY(
			_In_ value_type x,
			_In_ value_type y ) throw( )
		{
			MoveToX( x );
			MoveToY( y );
		}
		void MoveToXY( _In_ POINT point ) throw( )
		{
			MoveToXY( point.x, point.y );
		}

		// set this rectangle to intersection of two others
		BOOL IntersectRect(
			_In_ LPCRECT lpRect1,
			_In_ LPCRECT lpRect2 ) throw( )
		{
			right = min( lpRect2->right, lpRect1->right );
			bottom = min( lpRect1->bottom, lpRect2->bottom );
			left = max( lpRect2->left, lpRect1->left );
			top = max( lpRect1->top, lpRect2->top );
			return !IsRectEmpty();
		}

		// set this rectangle to bounding union of two others
		BOOL UnionRect(
			_In_ LPCRECT lpRect1,
			_In_ LPCRECT lpRect2 ) throw( )
		{
			left = min( lpRect1->left, lpRect2->left );
			top = min( lpRect1->top, lpRect2->top );
			right = max( lpRect1->right, lpRect2->right );
			bottom = max( lpRect1->bottom, lpRect2->bottom );
			return !IsRectEmpty();
		}

		// set this rectangle to minimum of two others
		BOOL SubtractRect(
			_In_ LPCRECT lpRectSrc1,
			_In_ LPCRECT lpRectSrc2 ) throw( )
		{
			if ( IntersectRect( lpRectSrc1, lpRectSrc2 ) )
			{
				if ( lpRectSrc1->Height() == Height() )
				{
					if ( left >= lpRectSrc1->left &&right == lpRectSrc1->right )
					{
						right = left;
						left = lpRectSrc1->left;
					}
					else if ( lpRectSrc1->left == left && right < lpRectSrc1->right )
					{
						left = right;
						right = lpRectSrc1->right;
					}
					else
					{
						CopyRect( lpRectSrc1 );
					}
				}
				else if ( lpRectSrc1->Width() == Width() )
				{
					if ( top >= lpRectSrc1->top &&bottom == lpRectSrc1->bottom )
					{
						bottom = top;
						top = lpRectSrc1->top;
					}
					else if ( lpRectSrc1->top == top && bottom < lpRectSrc1->bottom )
					{
						top = bottom;
						bottom = lpRectSrc1->bottom;
					}
					else
					{
						CopyRect( lpRectSrc1 );
					}
				}
				else
				{
					CopyRect( lpRectSrc1 );
				}
			}
			else
			{
				CopyRect( lpRectSrc1 );
			}
			return !IsRectEmpty();
		}

		// Additional Operations
		void operator=( _In_ const _MyBase& srcRect ) throw( )
		{
			::CopyRect( this, &srcRect );
		}
		BOOL operator==( _In_ const _MyBase& rect ) const throw( )
		{
			return EqualRect( this, &rect );
		}
		BOOL operator!=( _In_ const _MyBase& rect ) const throw( )
		{
			return !EqualRect( this, &rect );
		}
		void operator+=( _In_ POINT point ) throw( )
		{
			OffsetRect( point.x, point.y );
		}
		void operator+=( _In_ SIZE size ) throw( )
		{
			OffsetRect( size.cx, size.cy );
		}
		void operator+=( _In_ LPCRECT lpRect ) throw( )
		{
			InflateRect( lpRect );
		}
		void operator-=( _In_ POINT point ) throw( )
		{
			OffsetRect( -point.x, -point.y );
		}
		void operator-=( _In_ SIZE size ) throw( )
		{
			OffsetRect( -size.cx, -size.cy );
		}
		void operator-=( _In_ LPCRECT lpRect ) throw( )
		{
			DeflateRect( lpRect );
		}
		void operator&=( _In_ const _MyBase& rect ) throw( )
		{
			IntersectRect( this, &rect );
		}
		void operator|=( _In_ const _MyBase& rect ) throw( )
		{
			UnionRect( this, &rect );
		}

		// Operators returning CRect values
		_Myt operator+( _In_ POINT point ) const throw( )
		{
			_Myt rect( *this );
			rect.OffsetRect( pt.x, pt.y );
			return rect;
		}
		_Myt operator-( _In_ POINT point ) const throw( )
		{
			_Myt rect( *this );
			rect.OffsetRect( -pt.x, -pt.y );
			return rect;
		}
		_Myt operator+( _In_ LPCRECT lpRect ) const throw( )
		{
			_Myt rect( this );
			rect.InflateRect( lpRect );
			return rect;
		}
		_Myt operator+( _In_ SIZE size ) const throw( )
		{
			_Myt rect( *this );
			rect.OffsetRect( size.cx, size.cy );
			return rect;
		}
		_Myt operator-( _In_ SIZE size ) const throw( )
		{
			_Myt rect( *this );
			rect.OffsetRect( -size.cx, -size.cy );
			return rect;
		}
		_Myt operator-( _In_ LPCRECT lpRect ) const throw( )
		{
			_Myt rect( this );
			rect.DeflateRect( lpRect );
			return rect;
		}
		_Myt operator&( _In_ const _MyBase& rect2 ) const throw( )
		{
			_Myt rect( *this );
			rect.IntersectRect( this, rect2 );
			return rect;
		}
		_Myt operator|( _In_ const _MyBase& rect2 ) const throw( )
		{
			_Myt rect( *this );
			rect.UnionRect( this, rect2 );
			return rect;
		}
		_Myt MulDiv(
			_In_ int nMultiplier,
			_In_ int nDivisor ) const throw( )
		{
			return _Myt(
				::MulDiv( left, nMultiplier, nDivisor ),
				::MulDiv( top, nMultiplier, nDivisor ),
				::MulDiv( right, nMultiplier, nDivisor ),
				::MulDiv( bottom, nMultiplier, nDivisor ) );
		}
		template<typename _Ty>
		_Ty To()
		{
			_Ty rect;
			rect.left = static_cast<_Ty::value_type>( left );
			rect.top = static_cast<_Ty::value_type>( top );
			rect.right = static_cast<_Ty::value_type>( right );
			rect.bottom = static_cast<_Ty::value_type>( bottom );
			return rect;
		}
	};
}// namsespace DUI_BASE 
struct type_traits_sys
{
	typedef tagSIZE SIZE;
	typedef tagPOINT POINT;
	typedef tagRECT RECT;
};
typedef DUI_BASE::SIZE<LONG> SIZE;// 兼容标准size基类。
typedef DUI_BASE::CSizeT<LONG,type_traits_sys,tagSIZE> CSize;// 标准Size
typedef DUI_BASE::POINT<LONG> POINT; // 兼容标准POINT基类
typedef DUI_BASE::CPointT<LONG, type_traits_sys, tagPOINT> CPoint;// 标准Point
typedef DUI_BASE::RECT<LONG> RECT;// 兼容标准RECT基类
typedef DUI_BASE::CRectT<LONG, type_traits_sys, tagRECT> CRect; // 默认，兼容系统的类型

}// nasmespace DUI_V0_1