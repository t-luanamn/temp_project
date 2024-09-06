/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:06:21 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/03 20:06:23 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _Cat_HPP_
# define _Cat_HPP_

# include "Animal.hpp"

class	Cat: public Animal
{
  public:
    Cat(void);
    Cat(const Cat &cpy);
    ~Cat(void);
    
    using Animal::operator=;

    void makeSound() const;
};

#endif
