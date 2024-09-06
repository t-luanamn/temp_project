/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:06:33 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/03 20:06:34 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Dog.hpp"

Dog::Dog()
{
  std::cout << "Dog : Default Constructor" << std::endl;
}

Dog::~Dog()
{
  std::cout << "Dog : Destructor" << std::endl;
}

Dog::Dog(Dog const &obj)
{
  std::cout << "Copy Constructor" << std::endl;
  if (this != &obj)
    *this = obj;
}

Dog &Dog::operator = (const Dog &obj)
{
  std::cout << "Copy Assignment Operator" << std::endl;
  if (this != &obj)
  {
    //	this->attributes = obj.attributes;
    //	...
  }
  return (*this);
}
