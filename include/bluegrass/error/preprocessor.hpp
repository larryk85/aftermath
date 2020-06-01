#pragma once

#define BGT_GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, NAME, ...) NAME

#define BGT1( FUNC ) \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) return bluegrass_func_value;

#define BGT2( VAR, FUNC ) \
   decltype(FUNC)::expected_t VAR; \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) return bluegrass_func_value; \
   else VAR = bluegrass_func_value;

#define BGT3( VAR, FUNC, CATCH )                            \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      CATCH                                                 \
   } else VAR = bluegrass_func_value;

#define BGT4( VAR, FUNC, C1, C2 )                           \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1                                                    \
      else C2                                               \
   } else VAR = bluegrass_func_value;

#define BGT5( VAR, FUNC, C1, C2, C3 )                       \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1 \
      else C2 \
      else C3 \
   } else VAR = bluegrass_func_value;

#define BGT6( VAR, FUNC, C1, C2, C3, C4 )                   \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1 \
      else C2 \
      else C3 \
      else C4 \
   } else VAR = bluegrass_func_value;

#define BGT7( VAR, FUNC, C1, C2, C3, C4, C5 )                   \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1 \
      else C2 \
      else C3 \
      else C4 \
      else C5 \
   } else VAR = bluegrass_func_value;

#define BGT8( VAR, FUNC, C1, C2, C3, C4, C5, C6 )                   \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1 \
      else C2 \
      else C3 \
      else C4 \
      else C5 \
      else C6 \
   } else VAR = bluegrass_func_value;

#define BGT9( VAR, FUNC, C1, C2, C3, C4, C5, C6, C7 )                   \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1 \
      else C2 \
      else C3 \
      else C4 \
      else C5 \
      else C6 \
      else C7 \
   } else VAR = bluegrass_func_value;

#define BGT10( VAR, FUNC, C1, C2, C3, C4, C5, C6, C7, C8 )                   \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1 \
      else C2 \
      else C3 \
      else C4 \
      else C5 \
      else C6 \
      else C7 \
      else C8 \
   } else VAR = bluegrass_func_value;

#define BGT11( VAR, FUNC, C1, C2, C3, C4, C5, C6, C7, C8, C9 ) \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1 \
      else C2 \
      else C3 \
      else C4 \
      else C5 \
      else C6 \
      else C7 \
      else C8 \
      else C9 \
   } else VAR = bluegrass_func_value;

#define BGT12( VAR, FUNC, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10 ) \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1 \
      else C2 \
      else C3 \
      else C4 \
      else C5 \
      else C6 \
      else C7 \
      else C8 \
      else C9 \
      else C10 \
   } else VAR = bluegrass_func_value;

#define BGT13( VAR, FUNC, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11 ) \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1 \
      else C2 \
      else C3 \
      else C4 \
      else C5 \
      else C6 \
      else C7 \
      else C8 \
      else C9 \
      else C10 \
      else C11 \
   } else VAR = bluegrass_func_value;

#define BGT14( VAR, FUNC, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12 ) \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1 \
      else C2 \
      else C3 \
      else C4 \
      else C5 \
      else C6 \
      else C7 \
      else C8 \
      else C9 \
      else C10 \
      else C11 \
      else C12 \
   } else VAR = bluegrass_func_value;

#define BGT15( VAR, FUNC, C1, C2, C3, C4, C5, C6, C7, C8, C10, C11, C12, C13 ) \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1 \
      else C2 \
      else C3 \
      else C4 \
      else C5 \
      else C6 \
      else C7 \
      else C8 \
      else C9 \
      else C10 \
      else C11 \
      else C12 \
      else C13 \
   } else VAR = bluegrass_func_value;

#define BGT16( VAR, FUNC, C1, C2, C3, C4, C5, C6, C7, C8, C10, C11, C12, C13, C14 ) \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1 \
      else C2 \
      else C3 \
      else C4 \
      else C5 \
      else C6 \
      else C7 \
      else C8 \
      else C9 \
      else C10 \
      else C11 \
      else C12 \
      else C13 \
      else C14 \
   } else VAR = bluegrass_func_value;

#define BGT17( VAR, FUNC, C1, C2, C3, C4, C5, C6, C7, C8, C10, C11, C12, C13, C14, C15 ) \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1 \
      else C2 \
      else C3 \
      else C4 \
      else C5 \
      else C6 \
      else C7 \
      else C8 \
      else C9 \
      else C10 \
      else C11 \
      else C12 \
      else C13 \
      else C14 \
      else C15 \
   } else VAR = bluegrass_func_value;

#define BGT18( VAR, FUNC, C1, C2, C3, C4, C5, C6, C7, C8, C10, C11, C12, C13, C14, C15, C16 ) \
   std::decay_t<decltype(FUNC)::expected_t> VAR;            \
   if ( auto bluegrass_func_value = FUNC; !bluegrass_func_value.has_value() ) { \
      C1 \
      else C2 \
      else C3 \
      else C4 \
      else C5 \
      else C6 \
      else C7 \
      else C8 \
      else C9 \
      else C10 \
      else C11 \
      else C12 \
      else C13 \
      else C14 \
      else C15 \
      else C16 \
   } else VAR = bluegrass_func_value;

#define BLUEGRASS_TRY(...) \
  BGT_GET_MACRO(__VA_ARGS__, BGT18, BGT17, BGT16, BGT15, BGT14, BGT13, BGT12, BGT11, BGT10, BGT9, BGT8, BGT7, BGT6, BGT5, BGT4, BGT3, BGT2, BGT1)(__VA_ARGS__)

#define BGCATCH_GET_MACRO(_1, _2, NAME, ...) NAME

#define BLUEGRASS_CATCH_1( CFUNC ) CFUNC();

#define BLUEGRASS_CATCH_2( ERR, CFUNC ) \
   if ( auto bluegrass_func_error = bluegrass_func_value.get_error(); bluegrass_func_error.is_owned_by<bluegrass::error_category<decltype(detail::to_enum_class(ERR))>>() && (static_cast<bluegrass::error_category<decltype(detail::to_enum_class(ERR))>::error_code_t>(bluegrass_func_error.code()) == ERR) && bluegrass::detail::pass_type(bluegrass::catch_type<ERR>(bluegrass_func_error, CFUNC)) );

#define BLUEGRASS_RETHROW_1( CFUNC ) CFUNC(); return bluegrass_func_value;

#define BLUEGRASS_RETHROW_2( ERR, CFUNC ) \
   if ( auto bluegrass_func_error = bluegrass_func_value.get_error(); bluegrass_func_error.is_owned_by<bluegrass::error_category<decltype(detail::to_enum_class(ERR))>>() && (static_cast<bluegrass::error_category<decltype(detail::to_enum_class(ERR))>::error_code_t>(bluegrass_func_error.code()) == ERR) && bluegrass::detail::pass_type(bluegrass::catch_type<ERR>(bluegrass_func_error, CFUNC)) ) return bluegrass_func_value;

#define BLUEGRASS_CATCH(...) BGCATCH_GET_MACRO( __VA_ARGS__, BLUEGRASS_CATCH_2, BLUEGRASS_CATCH_1)(__VA_ARGS__)
#define BLUEGRASS_RETHROW(...) BGCATCH_GET_MACRO( __VA_ARGS__, BLUEGRASS_RETHROW_2, BLUEGRASS_RETHROW_1)(__VA_ARGS__)
