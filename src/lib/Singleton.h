/*
 * Singleton.h
 *
 *  Created on: 14-may-2009
 *      Author: Carlos Agüero
 *
 *  Copyright 2014 Francisco Martín
 *
 *  This file is part of ATCSim.
 *
 *  ATCSim is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ATCSim is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ATCSim.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SRC_LIB_SINGLETON_H_
#define SRC_LIB_SINGLETON_H_

#include <string>

template< class C >
class Singleton {
 public:
static C* getInstance() {
  if ( Singleton<C>::uniqueInstance_ == nullptr )
    Singleton<C>::uniqueInstance_ = new C();
  return Singleton<C>::uniqueInstance_;
}

static void removeInstance() {
  if ( Singleton<C>::uniqueInstance_ != nullptr ) {
    delete Singleton<C>::uniqueInstance_;
    Singleton<C>::uniqueInstance_ = nullptr;
  }
}

 private:
  static C *uniqueInstance_;
};

// Initialize the static member CurrentInstance
template< class C >
C* Singleton<C>::uniqueInstance_ = nullptr;

#endif  // SRC_LIB_SINGLETON_H_
