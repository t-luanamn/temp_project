/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:05:59 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/03 20:06:02 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>

class Animal
{
  public:
    Animal(void);
    Animal(std::string type);
    Animal(const Animal &cpy);
    virtual ~Animal();
    Animal &operator=(const Animal &cpy);

    std::string getType() const;
    virtual void makeSound() const;

  protected:
    std::string _type;
};

#endif
