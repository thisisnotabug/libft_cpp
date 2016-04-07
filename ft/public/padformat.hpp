// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   padformat.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/07 15:41:51 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/07 15:44:36 by jaguillo         ###   ########.fr       //
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

std::string		truncmid(std::string const &str, int w = 11);

std::string	padformat_openlvl(
	int line, std::string const &file, std::string const &function);
void		padformat_closelvl();
std::string	padformat_singlelvl(
	int line, std::string const &file, std::string const &function);

inline void	padformat_begin(
	int line, std::string const &file, std::string const &function)
{
	std::string const	header = padformat_openlvl(line, file, function);

	std::cout << header << '\n';
	return ;
}

template <typename ...ARGS>
void		padformat_begin(
	int line, std::string const &file, std::string const &function,
	const char *fmt , ARGS ...args)
{
	std::string const	header = padformat_openlvl(line, file, function);

	std::cout << header << "-> " << ft::f(fmt, args...) << '\n';
	return ;
}

inline void	padformat_end(void)
{
	padformat_closelvl();
	return ;
}

inline void	padformat_single(
	int line, std::string const &file, std::string const &function)
{
	std::string const	header = padformat_singlelvl(line, file, function);

	std::cout << header << '\n';
	return ;
}

template <typename ...ARGS>
void		padformat_single(
	int line, std::string const &file, std::string const &function,
	const char *fmt , ARGS ...args)
{
	std::string const	header = padformat_singlelvl(line, file, function);

	std::cout << header << "-> " << ft::f(fmt, args...) << '\n';
	return ;
}

# define FTPADE() ft::padformat_end()

#  ifdef __clang__
# define FTPADB(...) ft::padformat_begin(__LINE__, __FILE__, __FUNCTION__, ##__VA_ARGS__)
# define FTPAD(...) ft::padformat_single(__LINE__, __FILE__, __FUNCTION__, ##__VA_ARGS__)
#  else
// Small fix
# define FTPADB(...) ft::padformat_begin(__LINE__, __FILE__, __FUNCTION__, "%", ft::f(__VA_ARGS__))
# define FTPAD(...) ft::padformat_single(__LINE__, __FILE__, __FUNCTION__, "%", ft::f(__VA_ARGS__))
#  endif

};

#endif
