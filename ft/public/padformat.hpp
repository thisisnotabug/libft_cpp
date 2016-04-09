// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   padformat.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/07 15:41:51 by jaguillo          #+#    #+#             //
//   Updated: 2016/04/09 15:29:42 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PADFORMAT_HPP
# define PADFORMAT_HPP

# include <iostream>

# include "ft/utils.hpp"

namespace ft
{

/*
** FT::pad printing
*/

std::string truncmid(std::string const &str, int w = 11);


namespace detail // ~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


std::string	padformat_openlvl(
	int line, std::string const &file, std::string const &function);
void padformat_closelvl();
std::string	padformat_singlelvl(
	int line, std::string const &file, std::string const &function);

// FT PAD Begin, without details
inline void	padformat_begin(
	int line, std::string const &file, std::string const &function)
{
	std::string const	header = padformat_openlvl(line, file, function);

	std::cout << header << '\n';
	return ;
}

// FT PAD Begin, with details
template <typename ...ARGS>
void		padformat_begin(
	int line, std::string const &file, std::string const &function,
	const char *fmt , ARGS ...args)
{
	std::string const	header = padformat_openlvl(line, file, function);

	std::cout << header << "-> " << ft::f(fmt, args...) << '\n';
	return ;
}

// FT PAD End
inline void	padformat_end(void)
{
	padformat_closelvl();
	return ;
}

// FT PAD single, without details
inline void	padformat_single(
	int line, std::string const &file, std::string const &function)
{
	std::string const header = padformat_singlelvl(line, file, function);

	std::cout << header << '\n';
	return ;
}

// FT PAD single, with details
template <typename ...ARGS>
void		padformat_single(
	int line, std::string const &file, std::string const &function,
	const char *fmt, ARGS ...args)
{
	std::string const header = padformat_singlelvl(line, file, function);

	std::cout << header << "-> " << ft::f(fmt, args...) << '\n';
	return ;
}

class PadScope
{
	int _line;
	std::string _file, _function;

public:
	inline PadScope(int line, char const *file, char const *function,
					std::string &&info) :
		_line(line), _file(file), _function(function) {

		ft::detail::padformat_begin(line, file, function, "Begin %", info);
	}
	inline ~PadScope() {

		ft::detail::padformat_single(_line, _file, _function, "End");
		ft::detail::padformat_end();
	}
};

}; // ~~~~~~~~~~~~~~~~~ END OF NAMESPACE DETAIL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

# define FTPADE() ft::detail::padformat_end()
#  ifdef __clang__
# define FTPADB(...) ft::detail::padformat_begin(			\
		__LINE__, __FILE__, __FUNCTION__, ##__VA_ARGS__)
# define FTPAD(...) ft::detail::padformat_single(			\
		__LINE__, __FILE__, __FUNCTION__, ##__VA_ARGS__)
# define FTPADSCOPE(...) ft::detail::PadScope __PADSCOPE{		\
		__LINE__, __FILE__, __FUNCTION__, ft::f(__VA_ARGS__)}

#  else
// Small fix
# define FTPADB(...) ft::detail::padformat_begin(					\
		__LINE__, __FILE__, __FUNCTION__, "%", ft::f(__VA_ARGS__))
# define FTPAD(...) ft::detail::padformat_single(					\
		__LINE__, __FILE__, __FUNCTION__, "%", ft::f(__VA_ARGS__))
#  endif

};

#endif
