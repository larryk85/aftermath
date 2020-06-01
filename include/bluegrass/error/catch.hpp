#pragma once

#include "result.hpp"

namespace bluegrass {
   struct catch_rethrow{};
   struct catch_no_rethrow{};

   template <auto EC, typename Policy = catch_no_rethrow>
   struct catch_type {
      using category_t = error_category<decltype(detail::to_enum_class(EC))>;
      using policy_t   = Policy;

      template <typename CatchFunc>
      constexpr inline catch_type( error_type e, CatchFunc&& cfunc ) {
         if constexpr (std::is_same_v<policy_t, catch_rethrow>)
            err = cfunc(e);
         else
            cfunc(e);
      }

      operator bool() const { return err; }
      auto error() const { return err; }

      error_type err = {};
   };
} // ns bluegrass
