/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluanamn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:07:28 by tluanamn          #+#    #+#             */
/*   Updated: 2024/09/03 20:07:31 by tluanamn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/Animal.hpp"

int main()
{
  const Animal* j = new Dog();
  const Animal* i = new Cat();

  delete j;
  delete i;
  // ... create more animals here ...
  
  return 0;
}
