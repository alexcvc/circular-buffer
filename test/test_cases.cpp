//
// Copyright (c) 2015 Alexander Sacharov <a.sacharov@gmx.de>
//               All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
//

//-----------------------------------------------------------------------------
// includes <...>
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

//-----------------------------------------------------------------------------
// includes "..."
//-----------------------------------------------------------------------------

#include "catch2/catch.hpp"

//----------------------------------------------------------------------------
// Defines and macros
//----------------------------------------------------------------------------

TEST_CASE("TestCase", "[what]")
{
   SECTION("Test1") {
      REQUIRE(true);
   }

   SECTION("Test2") {
      REQUIRE(false);
   }

}

