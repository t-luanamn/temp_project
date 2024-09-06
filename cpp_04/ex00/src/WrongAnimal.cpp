/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:09:17 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/04 21:09:19 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
  std::cout << "WrongAnimal : Default Constructor" << std::endl;
}

WrongAnimal::~WrongAnimal()
{
  std::cout << "WrongAnimal : Destructor" << std::endl;
}

WrongAnimal::WrongAnimal(WrongAnimal const &obj)
{
  std::cout << "Copy Constructor" << std::endl;
  if (this != &obj)
    *this = obj;
}

WrongAnimal &WrongAnimal::operator = (const WrongAnimal &obj)
{
  std::cout << "Copy Assignment Operator" << std::endl;
  if (this != &obj)
  {
    //	this->attributes = obj.attributes;
    //	...
  }
  return (*this);
}
