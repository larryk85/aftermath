#include <bluegrass/error/error.hpp>

#include <catch2/catch.hpp>

using namespace bluegrass;

enum class test_errors_a : uint16_t {
   error_1,
   error_2,
   error_3,
   error_4
};

enum class test_errors_b : uint16_t {
   error_1,
   error_2,
   error_3,
   error_4
};

using test_category_a = error_category<test_errors_a>;
using test_category_b = error_category<test_errors_b>;

TEST_CASE("Testing error_type", "[error_type_tests]") {
   auto test_func = [&](auto er, auto ec, auto& cat) {
      REQUIRE( er.is_valid() );
      REQUIRE( er );
      REQUIRE( static_cast<uint16_t>(ec) == er.code() );
      REQUIRE( er.template is_owned_by<std::decay_t<decltype(cat)>>() );
   };

   test_func( test_category_a::create_error( test_errors_a::error_1 ),
              test_errors_a::error_1,
              test_category_a::get() );

   test_func( test_category_a::create_error( test_errors_a::error_2 ),
              test_errors_a::error_2,
              test_category_a::get() );

   test_func( test_category_a::create_error( test_errors_a::error_3 ),
              test_errors_a::error_3,
              test_category_a::get() );

   test_func( test_category_a::create_error( test_errors_a::error_4 ),
              test_errors_a::error_4,
              test_category_a::get() );

   test_func( test_category_b::create_error( test_errors_b::error_1 ),
              test_errors_b::error_1,
              test_category_b::get() );

   test_func( test_category_b::create_error( test_errors_b::error_2 ),
              test_errors_b::error_2,
              test_category_b::get() );

   test_func( test_category_b::create_error( test_errors_b::error_3 ),
              test_errors_b::error_3,
              test_category_b::get() );

   test_func( test_category_b::create_error( test_errors_b::error_4 ),
              test_errors_b::error_4,
              test_category_b::get() );
}
