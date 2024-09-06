/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:06:13 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/03 20:06:16 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cat.hpp"

Cat::Cat(): Animal::Animal("Cat")
{
  std::cout << "Cat : Default Constructor" << std::endl;
}

Cat::~Cat()
{
  std::cout << "Cat : Destructor" << std::endl;
}

Cat::Cat(Cat const &cpy)
{
  std::cout << "Cat : Copy Constructor" << std::endl;
  if (this != &cpy)
    *this = cpy;
}

void Cat::makeSound() const
{
  std::cout << "Cat Sound:\n\t>>>Meow<<<\n" << std::endl;
}
