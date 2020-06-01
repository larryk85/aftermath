#pragma once

#include "utility.hpp"
#include "error_type.hpp"

#include <utility>

namespace bluegrass {

   template <typename Expected>
   class result {
      public:
         using expected_t = Expected;
         inline result(const Expected& v)
            : _value(v), _has_value(true) {}
         inline result(Expected&& v)
            : _value(std::move(v)), _has_value(true) {}
         inline result(error_type e)
            : _err(e), _has_value(false) {}
         inline result(const result& other) {
            if (_has_value) {
               _value = other._value;
            } else {
               _err = other._err;
            }
            _has_value = other._has_value;
         }
         inline result(result&& other) {
            if (_has_value) {
               _value = std::move(other._value);
            } else {
               _err = other._err;
            }
            _has_value = other._has_value;
         }
         template <typename... Args>
         inline result(std::in_place_t, Args&&... args)
            : _value(std::forward<Args>(args)...), _has_value(true) {}

         inline ~result() {
            if (_has_value)
               _value.~Expected();
         }

         inline result& operator=(const Expected& v) {
            _value = v;
            _has_value = true;
            return *this;
         }

         inline result& operator=(Expected&& v) {
            _value = std::move(v);
            _has_value = true;
            return *this;
         }

         inline result& operator=(error_type e) {
            _err = e;
            _has_value = false;
            return *this;
         }

         inline bool operator==(result other) {
            if (has_value())
               return other.has_value() && _value == other._value;
            else
               return _err == other._err;
         }

         template <typename... Args>
         inline void emplace_value( Args&&... args ) {
            _value = {std::forward<Args>(args)...};
            _has_value = true;
         }

         inline void reset_value( const Expected& v ) {
            _value = v;
            _has_value = true;
         }

         inline void reset_value( Expected&& v ) {
            _value = std::move(v);
            _has_value = true;
         }

         inline bool has_value() const { return _has_value; }
         inline bool has_error() const { return !has_value(); }
         inline operator Expected() const { return _value; }
         inline operator error_type() const { return _err; }

         inline Expected& operator*() { return _value; }
         inline const Expected& operator*() const { return _value; }

         inline Expected& operator->() { return _value; }
         inline const Expected& operator->() const { return _value; }

         inline auto& get_error() { return _err; }
         inline auto get_error() const { return _err; }

         inline auto& get_value() { return _value; }
         inline const auto& get_value() const { return _value; }

         template <typename F>
         inline auto& and_then( F func ) {
            if (has_value())
               func( _value );
            return *this;
         }

         template <typename Category, auto EC, typename F>
         inline auto& or_else( F&& func ) {
            if (!has_value()) {
               if ( _err.is_owned_by<Category>() && (to_underlying_type(EC) == _err.code()) )
                  func( _err );
            }
            return *this;
         }

         template <typename F>
         inline auto& or_else( F&& func ) {
            if (!has_value())
               func( _err );
            return *this;
         }

      private:
         union {
            Expected   _value;
            error_type _err;
         };
         bool _has_value = false;
   };

} // ns bluegrass
