// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   padformat.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/10 14:57:32 by ngoguey           #+#    #+#             //
//   Updated: 2016/04/09 15:22:03 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ft/assert.hpp"
#include "ft/utils.hpp"
#include <stack>
#include <array>
#include <tuple>
#include <iostream>
#include <vector>
#include <algorithm>
// #include <iostream>

// v2 of this file

namespace ft // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
namespace detail // ~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


using lineinfo_t = std::tuple<int, std::string, std::string>;
static std::vector<lineinfo_t>  padstack{};
static std::array<std::string, 6> const colors{
	"\033[42m", "\033[43m", "\033[44m", "\033[45m", "\033[46m", "\033[47m",
		};

std::string truncmid(std::string const &str, int w /*= 11*/)
{
	int const sz = str.size();
	int right;

	if (sz <= w)
	{
		right = w - sz;
		return str + std::string(right, ' ');
	}
	right = (w - 1) / 2;
	return str.substr(0, w - 1 - right)
		+ "."
		+ str.substr(str.size() - right, right);
}

static void truncate_mid(std::string &str)
{
	str = truncmid(str, 13);
	// str = str.substr(0, 7) + "." + str.substr(str.size() - 7, 7);
	return ;
}

static void applywidth(
	std::string &str, unsigned int curwidth, unsigned int width)
{
	if (curwidth < width)
		str += std::string(std::max(0u, width - curwidth), ' ');
	return ;
}

static std::string  build_header(void)
{
	std::string     str("");
	unsigned int    i;
	int             line;
	std::string     file;
	std::string     fun;
	std::size_t     pos;
	std::string     linestr;

	for (i = 0; i < padstack.size(); i++)
		str += colors[i % colors.size()] + "  ";
	str += "\033[0m";
	applywidth(str, padstack.size() * 2, 2 * 9);

	std::tie(line, file, fun) = padstack.back();
	pos = file.find_last_of('/');
	file = file.substr(pos + 1, file.find_last_of('.') - pos - 1);
	truncate_mid(file);
	applywidth(file, file.size(), 11);

	truncate_mid(fun);
	applywidth(fun, fun.size(), 11);

	linestr = ft::f("%", line);
	applywidth(linestr, linestr.size(), 3);

	str += ft::f("\033[4m%\033[0m:\033[4m%\033[0m:\033[4m%\033[0m"
				 , file, fun, linestr);
	return str;
}

std::string padformat_openlvl(
	int line, std::string const &file, std::string const &function)
{
	padstack.emplace_back(line, file, function);
	return build_header();
}

void padformat_closelvl(void)
{
	if (padstack.size() == 0)
	{
		std::cout << "EXTRANEOUS FTPADE()" << std::endl;
		return ;
	}
	(void)padstack.pop_back();
	if (padstack.size() == 0)
		std::cout << "...done" << std::endl;
	return ;
}

std::string padformat_singlelvl(
	int line, std::string const &file, std::string const &function)
{
	std::string str;
	lineinfo_t backLine;

	if (padstack.size() > 0)
	{
		backLine = padstack.back();
		if (file == std::get<1>(backLine)
			&& function == std::get<2>(backLine)
			&& line >= std::get<0>(backLine))
		{
			padstack.pop_back();
			padstack.emplace_back(line, file, function);
			str = build_header();
			padstack.pop_back();
			padstack.push_back(backLine);
			return str;
		}
	}
	padstack.emplace_back(line, file, function);
	str = build_header();
	padstack.pop_back();
	return str;
}


}; // ~~~~~~~~~~~~~~~~~ END OF NAMESPACE DETAIL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

}; // ~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FT //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
