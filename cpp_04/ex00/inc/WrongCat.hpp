/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:08:44 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/04 21:08:45 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WrongCat_HPP_
# define _WrongCat_HPP_

# include "Animal.hpp"

class	WrongCat
{
  public:
    WrongCat(void);
    WrongCat(const WrongCat &obj);
    ~WrongCat(void);
    WrongCat &operator = (const WrongCat &obj);

  private:
    // DataType	attributes.
};

#endif
