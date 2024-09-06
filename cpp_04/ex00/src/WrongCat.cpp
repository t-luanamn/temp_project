/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:09:32 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/04 21:09:34 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/WrongCat.hpp"

WrongCat::WrongCat()
{
  std::cout << "WrongCat : Default Constructor" << std::endl;
}

WrongCat::~WrongCat()
{
  std::cout << "WrongCat : Destructor" << std::endl;
}

WrongCat::WrongCat(WrongCat const &obj)
{
  std::cout << "Copy Constructor" << std::endl;
  if (this != &obj)
    *this = obj;
}

WrongCat &WrongCat::operator = (const WrongCat &obj)
{
  std::cout << "Copy Assignment Operator" << std::endl;
  if (this != &obj)
  {
    //	this->attributes = obj.attributes;
    //	...
  }
  return (*this);
}
