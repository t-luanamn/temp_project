/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:08:20 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/04 21:08:21 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WrongAnimal_HPP_
# define _WrongAnimal_HPP_

# include "Animal.hpp"

class	WrongAnimal
{
  public:
    WrongAnimal(void);
    WrongAnimal(const WrongAnimal &obj);
    ~WrongAnimal(void);
    WrongAnimal &operator = (const WrongAnimal &obj);

  private:
    // DataType	attributes.
};

#endif
