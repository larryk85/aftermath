#pragma once

#include "utility.hpp"

namespace bluegrass {
   class error_type {
      public:
         inline error_type() : _all(0) {}
         inline explicit error_type( uint64_t ec ) : _all(ec) {}

         template <typename EC>
         inline error_type( uint64_t addr, EC ec )
            : _address(addr), _code(to_underlying_type(ec)) {}

         uint64_t to_uint64_t() const { return _all; }

         uint16_t code() const { return _code; }

         bool is_valid() const { return _all != 0; }

         operator bool() const { return is_valid(); }

         template <typename Category>
         inline bool is_owned_by() const {
            return Category::get().get_address_as_uint64_t() == _address;
         }

      private:
         union {
            struct {
               uint64_t _address : 48;
               uint64_t _code    : 16;
            };
            uint64_t _all;
         };
   };

   template <typename ErrorCodeEnum>
   struct error_category {
      static_assert(std::is_same_v<uint16_t, std::underlying_type_t<ErrorCodeEnum>> ||
                    std::is_same_v<uint8_t,  std::underlying_type_t<ErrorCodeEnum>>,
                    "ErrorCodeEnum can not be an unsigned type greater than 16 bits");

      using error_code_t = ErrorCodeEnum;

      static auto& get() {
         static error_category<ErrorCodeEnum> inst;
         return inst;
      }

      inline uint64_t get_address_as_uint64_t() const {
         return reinterpret_cast<uintptr_t>(this);
      }

      static auto create_error( ErrorCodeEnum ec ) {
         return error_type{ get().get_address_as_uint64_t(), ec };
      }
   };
} // ns bluegrass
