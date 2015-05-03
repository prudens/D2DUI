#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>  
namespace DUI_V0_1{
namespace DUI_BASE
{
	// 基础类，扩充一些字符串处理算法

	template<typename _Elem,typename _Traits,typename _Alloc>
	class CStringT : public std::basic_string<_Elem, _Traits, _Alloc>
	{
	public:
 		typedef CStringT<_Elem, _Traits, _Alloc> _Myt;
 		typedef std::basic_string<_Elem, _Traits, _Alloc> _MyBase;

		CStringT() throw()
		{
		}
		
		void to_lower( const std::locale & Loc = std::locale() )
		{
			boost::to_lower( *this, Loc );
		}
		void to_upper( const std::locale & Loc = std::locale() )
		{
			boost::to_upper( *this,Loc );
		}
		void trim( const std::locale &Loc = std::locale() )
		{
			boost::trim( *this, Loc );
		}
		template<typename PredicateT>
		void trim( PredicateT  Pred )
		{
			boost::trim_if( *this, Pred);
		}
		void trim_left( const std::locale &Loc = std::locale() )
		{
			boost::trim_left( *this, Loc );
		}
		template<typename PredicateT>
		void trim_left( PredicateT Pred )
		{
			boost::trim_left_if( *this, Pred );
		}
		void trim_right( const std::locale &Loc = std::locale() )
		{
			boost::trim_right( *this, Loc);
		}
		template<typename PredicateT>
		void trim_right( PredicateT Pred )
		{
			boost::trim_right_if(Pred);
		}
		void trim_all( const std::locale &Loc = std::locale() )
		{
			boost::trim_all( *this, Loc );;
		}
		template<typename PredicateT>
		void trim_all( PredicateT Pred)
		{
			boost::trim_all( *this, Pred );
		}
		// regex swrap function
		template< typename CharT, typename RegexTraitsT>
		boost::iterator_range< typename boost::range_iterator< _Myt >::type >
			find_regex( const boost::basic_regex< CharT, RegexTraitsT > &regex,
			boost::match_flag_type = match_default )
		{
			return boost::find_regex( *this, regex, match_flag_type );
		}
		template< typename CharT, typename RegexTraitsT,
			typename FormatStringTraitsT, typename FormatStringAllocatorT>
	    void replace_regex(const boost::basic_regex< CharT, RegexTraitsT > &regex,
			const std::basic_string< CharT, FormatStringTraitsT, FormatStringAllocatorT > &format,
			boost::match_flag_type = match_default | format_default )
		{
			boost::replace_regex( *this, regex, format,match_flag_type );
		}
		template< typename CharT, typename RegexTraitsT>
		void erase_regex( const boost::basic_regex< CharT, RegexTraitsT > &regex,
						 boost:: match_flag_type = match_default )
		{
			boost::erase_regex( *this, regex, match_flag_type );
		}

		template<typename SequenceSequenceT, typename PredicateT>
		void split( SequenceSequenceT & Result, PredicateT Pred,
					boost::algorithm::token_compress_mode_type eCompress = token_compress_off )
		{
			boost::split( Result, *this, Pred, eCompress );
		}
		bool iends_with( _Myt tail, const std::locale &Loc = std::locale() )
		{
			return boost::iends_with( *this, tail, Loc );
		}
		double to_double()
		{
			return stod(*this);
		}
		float to_float()
		{
			return stof(*this);
		}
		int to_int(int base = 10)
		{
			return stoi(*this,0,base);
		}
		long to_long(int base = 10)
		{
			return stol(*this,0,base);
		}
		long double to_longdouble()
		{
			return std::stold( *this );
		}
		long long to_longlong(int base = 10)
		{
			return std::stoll( *this, base);
		}
		unsigned long to_ulong( int base = 10 )
		{
			return std::stoul( *this, 0, base );
		}
		unsigned long long to_ulonglong(int base = 10)
		{
			return std::stoull( *this, 0,base);
		}
	private:
		template<typename _CharT>
		struct to_tstring{};
		template<>struct to_tstring<char>
		{
		public:
			template<typename Value>
			std::string operator ()( Value val )
			{
				return std::to_string( val );
			}
		};

		template<>struct to_tstring < wchar_t >
		{
		public:
			template<typename Value>
			std::wstring operator ()( Value val )
			{
				return std::to_wstring( val );
			}
		};
	public:
		template<typename Digit>
		void to_string(Digit val)
		{
			_Tidy();
			assign( std::move(to_tstring<_Elem>()( val )));
		}
		
	};

}//DUI_BASE

typedef DUI_BASE::CStringT<char, std::char_traits<char>, std::allocator<char> > CStringA;
typedef DUI_BASE::CStringT<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > CStringW;
#ifdef UNICODE
typedef CStringW CString;
#else
typedef CStringA CString;
#endif
}//DUI_V0_1