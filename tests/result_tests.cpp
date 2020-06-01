#include <bluegrass/error/error.hpp>

#include <catch2/catch.hpp>

using namespace bluegrass;

enum class errors : uint16_t {
   error_1,
   error_2,
   error_3
};

using error_cat = error_category<errors>;

template <typename T>
inline void test_construction( T v ) {
   result<T> r(v);
   result<T> r2 = {v};
   REQUIRE( r == r2 );

   result<T> r3 = r;
   result<T> r4(r3);

   REQUIRE( r3 == r );
   REQUIRE( r4 == r3 );

   result<T> r5 = std::move(r3);
   result<T> r6(std::move(r4));

}

template <typename T>
inline void test_value( result<T>& r, T v ) {
   r = v;
   REQUIRE( r.has_value() );
   REQUIRE( r.get_value() == v );
}

template <typename T>
inline void test_resets_impl(result<T>&) {}

template <typename T, typename Arg, typename... Args>
inline void test_resets_impl( result<T>& r, Arg&& arg, Args&&... args ) {
   test_value(r, arg);
   if constexpr (sizeof...(Args) > 0)
      test_resets_impl<T>(r, std::forward<Args>(args)...);
}

template <typename T, typename... Args>
inline void test_resets( T v, Args&&... args ) {
   result<T> r = v; // needed for non
   test_value( r, v );
   if constexpr (sizeof...(Args) > 0)
      test_resets_impl<T>(r, std::forward<Args>(args)...);
}

TEST_CASE("Testing result simple types", "[result_simple_tests]") {
   test_construction( (int)33 );
   test_construction( (float)33 );
   float f;
   test_construction( (float*)&f );
   test_construction( (bool)true );
   test_construction( (bool)false );

   test_resets<int>( 33, 42, 13 );
   test_resets<float>( 33.3f, 42.21f, 13.133f );
}
