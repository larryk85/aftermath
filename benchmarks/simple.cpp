#ifdef USE_EXCEPTIONS
#include <stdexcept>
#else
#include <bluegrass/error/error.hpp>
using namespace bluegrass;
#endif

#include <functional>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

#ifdef USE_EXCEPTIONS
struct simple_ex_cat_1_error_1 : public std::runtime_error {
   simple_ex_cat_1_error_1()
      : std::runtime_error("simple exception 1 : error 1") {}
};
struct simple_ex_cat_1_error_2 : public std::runtime_error {
   simple_ex_cat_1_error_2()
      : std::runtime_error("simple exception 1 : error 2") {}
};
struct simple_ex_cat_1_error_3 : public std::runtime_error {
   simple_ex_cat_1_error_3()
      : std::runtime_error("simple exception 1 : error 3") {}
};
struct simple_ex_cat_2_error_1 : public std::runtime_error {
   simple_ex_cat_2_error_1()
      : std::runtime_error("simple exception 2 : error 1") {}
};
struct simple_ex_cat_2_error_2 : public std::runtime_error {
   simple_ex_cat_2_error_2()
      : std::runtime_error("simple exception 2 : error 2") {}
};
struct simple_ex_cat_2_error_3 : public std::runtime_error {
   simple_ex_cat_2_error_3()
      : std::runtime_error("simple exception 2 : error 3") {}
};
#else
enum class simple_errors_1 : uint8_t {
   error_1,
   error_2,
   error_3
};

using simple_errors_1_category = error_category<simple_errors_1>;

enum class simple_errors_2 : uint8_t {
   error_1,
   error_2,
   error_3
};

using simple_errors_2_category = error_category<simple_errors_2>;

template <typename ErrorType>
std::string_view get_info( uint16_t ec ) {
   if constexpr (std::is_same_v<ErrorType, simple_errors_1>) {
      switch ( static_cast<simple_errors_1>(ec) ) {
         case simple_errors_1::error_1: return "simple errors 1 : error 1";
         case simple_errors_1::error_2: return "simple errors 1 : error 2";
         case simple_errors_1::error_3: return "simple errors 1 : error 3";
      };
   } else {
      switch ( static_cast<simple_errors_2>(ec) ) {
         case simple_errors_2::error_1: return "simple errors 2 : error 1";
         case simple_errors_2::error_2: return "simple errors 2 : error 2";
         case simple_errors_2::error_3: return "simple errors 2 : error 3";
      };
   }
   return "internal error";
}
#endif

std::vector<char> file_buffer;
uint32_t it;

bool should_fail_random() {
   it = rand() % file_buffer.size();
   static uint32_t bp = 0;
   bool b = (file_buffer[it] >> bp) & 0x1;
   ++bp %= 8;
   return b;
}

std::function<bool()> should_fail;

#ifdef USE_EXCEPTIONS
int test_func1( int v ) {
   if (should_fail() && should_fail())
      throw simple_ex_cat_2_error_2{};
   else if (should_fail() && (v % 7) == 4)
      throw simple_ex_cat_2_error_3{};
   return v + 131;
}

int test_func2( int v ) {
   if (should_fail())
      throw simple_ex_cat_1_error_3{};
   if (should_fail())
      throw simple_ex_cat_2_error_1{};
   return v + 13 - test_func1(v);
}

int test_func3( int v ) {
   if (should_fail())
      throw simple_ex_cat_1_error_1{};
   else if (should_fail())
      throw simple_ex_cat_1_error_2{};
   try {
      return v + test_func2(v);
   } catch ( simple_ex_cat_1_error_3 e ) {
      std::cerr << "Failed " << e.what() << std::endl;
   } catch ( simple_ex_cat_2_error_1 e ) {
      std::cerr << "Failed " << e.what() << std::endl;
   } catch (...) {
      std::cerr << "Failed ?" << std::endl;
      throw;
   }
   return v + 101;
}

std::vector<int> test_funcv1( int v ) {
   if (should_fail() && should_fail())
      throw simple_ex_cat_2_error_2{};
   else if (should_fail() && (v % 7) == 4)
      throw simple_ex_cat_2_error_3{};
   return {v, 13, 134, v+23};
}

std::vector<int> test_funcv2( int v ) {
   if (should_fail())
      throw simple_ex_cat_1_error_3{};
   if (should_fail())
      throw simple_ex_cat_2_error_1{};
   auto vec = test_funcv1(v);
   vec.push_back(v+13);
   return vec;
}

std::vector<int> test_funcv3( int v ) {
   if (should_fail())
      throw simple_ex_cat_1_error_1{};
   else if (should_fail())
      throw simple_ex_cat_1_error_2{};
   std::vector<int> vec;
   try {
      vec = test_funcv2(v);
   } catch ( simple_ex_cat_1_error_3 e ) {
      std::cerr << "Failed " << e.what() << std::endl;
   } catch ( simple_ex_cat_2_error_1 e ) {
      std::cerr << "Failed " << e.what() << std::endl;
   } catch (...) {
      std::cerr << "Failed ?" << std::endl;
      throw;
   }
   vec.push_back(101);
   vec.push_back(v + 101);
   return vec;
}

int test_func( int v ) {
   try {
      test_func3(v);
   } catch(...) {
      std::cerr << "Failed ??" << std::endl;
   }

   try {
      test_funcv3(v);
   } catch(...) {
      std::cerr << "Failed Vec ??" << std::endl;
   }

   return static_cast<int>(it);
}
#else
result<int> test_func1( int v ) {
   if (should_fail() && should_fail())
      return simple_errors_2_category::create_error(simple_errors_2::error_2);
   else if (should_fail() && (v % 7) == 4)
      return simple_errors_2_category::create_error(simple_errors_2::error_3);
   return v + 131;
}

result<int> test_func2( int v ) {
   if (should_fail())
      return simple_errors_1_category::create_error(simple_errors_1::error_3);
   if (should_fail())
      return simple_errors_2_category::create_error(simple_errors_2::error_1);
   BLUEGRASS_TRY(ret, test_func1(v));
   return v + 13 - ret;
}
result<int> test_func3( int v ) {
   if (should_fail())
      return simple_errors_1_category::create_error(simple_errors_1::error_1);
   else if (should_fail())
      return simple_errors_1_category::create_error(simple_errors_1::error_2);
   BLUEGRASS_TRY(ret,
                 test_func2(v),
                 BLUEGRASS_CATCH(simple_errors_1::error_3,
                    [&](auto& e) { std::cerr << "Failed " << get_info<simple_errors_1>(e.code()) << std::endl; } ),
                 BLUEGRASS_CATCH(simple_errors_2::error_1,
                    [&](auto& e) { std::cerr << "Failed " << get_info<simple_errors_2>(e.code()) << std::endl; } ),
                 BLUEGRASS_RETHROW([&]() { std::cerr << "Failed ?" << std::endl; }));
   return ret + 101;
}

result<std::vector<int>> test_funcv1( int v ) {
   if (should_fail() && should_fail())
      return simple_errors_2_category::create_error(simple_errors_2::error_2);
   else if (should_fail() && (v % 7) == 4)
      return simple_errors_2_category::create_error(simple_errors_2::error_3);
   return std::vector<int>{v, 13, 134, v+23};
}

result<std::vector<int>> test_funcv2( int v ) {
   if (should_fail())
      return simple_errors_1_category::create_error(simple_errors_1::error_3);
   if (should_fail())
      return simple_errors_2_category::create_error(simple_errors_2::error_1);
   BLUEGRASS_TRY(ret, test_funcv1(v));
   ret.push_back(v+13);
   return ret;
}
result<std::vector<int>> test_funcv3( int v ) {
   if (should_fail())
      return simple_errors_1_category::create_error(simple_errors_1::error_1);
   else if (should_fail())
      return simple_errors_1_category::create_error(simple_errors_1::error_2);
   BLUEGRASS_TRY(ret,
                 test_funcv2(v),
                 BLUEGRASS_CATCH(simple_errors_1::error_3,
                    [&](auto& e) { std::cerr << "Failed " << get_info<simple_errors_1>(e.code()) << std::endl; } ),
                 BLUEGRASS_CATCH(simple_errors_2::error_1,
                    [&](auto& e) { std::cerr << "Failed " << get_info<simple_errors_2>(e.code()) << std::endl; } ),
                 BLUEGRASS_RETHROW([&]() { std::cerr << "Failed ?" << std::endl; }));
   ret.push_back(101);
   ret.push_back(v + 101);
   return ret;
}
int test_func( int v ) {
   auto ret = test_func3(v);
   ret.or_else([&](auto&) { std::cerr << "Failed ??" << std::endl; });

   auto retv = test_funcv3(v);
   retv.or_else([&](auto&) { std::cerr << "Failed Vec ??" << std::endl; });

   return static_cast<int>(it);
}
#endif

int main(int argc, char** argv) {
   if (argc < 2) {
      std::cerr << "Please run with a number of iterations\n";
      return -1;
   }

   // cheesy random but it doesn't really matter
   srand(time(nullptr));

   int iterations = std::atoi(argv[1]);

   std::ifstream infile(argv[0]);
   infile.seekg(0, infile.end);
   file_buffer.resize(infile.tellg());
   infile.seekg(0, infile.beg);
   infile.read(file_buffer.data(), file_buffer.size());

   int ii = 0;
   should_fail = []() { return should_fail_random(); };
   auto t1 = std::chrono::high_resolution_clock::now();
   for (int i=0; i < iterations; ++i) {
      ii = test_func(ii);
   }
   auto t2 = std::chrono::high_resolution_clock::now();

   std::cout << "(Random) Time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << std::endl;

   should_fail = []() {
         it = rand() % file_buffer.size();
         return false;
      };
   auto t3 = std::chrono::high_resolution_clock::now();
   for (int i=0; i < iterations; ++i) {
      ii = test_func(ii);
   }
   auto t4 = std::chrono::high_resolution_clock::now();
   std::cout << "(No Fail) Time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(t4-t3).count() << std::endl;
}
