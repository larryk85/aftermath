#pragma once

#include <cstdint>
#include <type_traits>

namespace bluegrass {
   template <typename EC>
   constexpr static inline auto to_underlying_type( EC ec ) {
      return static_cast<std::underlying_type_t<EC>>(ec);
   }
   // helpers for std::visit
   template <class... Ts>
   struct overloaded : Ts... {
      using Ts::operator()...;
   };
   template <class... Ts>
   overloaded(Ts...)->overloaded<Ts...>;

   namespace detail {
      template <typename T>
      constexpr bool pass_type(T&& t) { (void)t; return true; }

      template <typename T>
      constexpr auto to_enum_class(T) -> std::decay_t<T>;
   } // ns bluegrass::detail
} // ns bluegrass
