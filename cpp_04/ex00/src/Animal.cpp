/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:05:22 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/03 20:05:40 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Animal.hpp"

Animal::Animal(void): _type("Unknown Animal")
{
  std::cout << "Animal Default Constructor" << std::endl;
}

Animal::Animal(std::string type): _type(type)
{
  std::cout << "Animal Parameter Constructor" << std::endl;
}

Animal::Animal(const Animal &cpy)
{
  std::cout << "Animal Copy Constructor" << std::endl;
  if (this != &cpy)
    *this = cpy;
}

Animal::~Animal()
{
  std::cout << "Animal Destructor" << std::endl;
}

Animal &Animal::operator=(const Animal &cpy)
{
  std::cout << "Animal Assignation Operator" << std::endl;
  if (this != &cpy)
    this->_type = cpy._type;
  return (*this);
}

std::string Animal::getType() const
{
  return (this->_type);
}

void Animal::makeSound() const
{
  std::cout << "Animal Sound:\n\t>>>...<<<\n" << std::endl;
}
