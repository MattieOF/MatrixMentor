#pragma once

#define BIT(x) (1 << (x))

// MSVC compiler intrinsics
#ifdef MM_PLATFORM_WINDOWS
	#define UNALIGNED __unaligned
	#define FORCEINLINE __forceinline
#else
	#define UNALIGNED
	#define FORCEINLINE inline
#endif

// -----------------------------------------------------------------------------------------------
// Array size macro
// From winnt.h:
//
// RtlpNumberOf is a function that takes a reference to an array of N Ts.
//
// typedef T array_of_T[N];
// typedef array_of_T &reference_to_array_of_T;
//
// RtlpNumberOf returns a pointer to an array of N chars.
// We could return a reference instead of a pointer but older compilers do not accept that.
//
// typedef char array_of_char[N];
// typedef array_of_char *pointer_to_array_of_char;
//
// sizeof(array_of_char) == N
// sizeof(*pointer_to_array_of_char) == N
//
// pointer_to_array_of_char RtlpNumberOf(reference_to_array_of_T);
//
// We never even call RtlpNumberOf, we just take the size of dereferencing its return type.
// We do not even implement RtlpNumberOf, we just declare it.
//
// Attempts to pass pointers instead of arrays to this macro result in compile time errors.
// That is the point.
//
extern "C++" // templates cannot be declared to have 'C' linkage
template <typename T, size_t N>
char(*RtlpNumberOf(UNALIGNED T(&)[N]))[N];
#define MM_ARRAY_SIZE(A) (sizeof(*RtlpNumberOf(A)))
// -----------------------------------------------------------------------------------------------

// Basic swap macro
#define MM_SWAP(IntermediateType, a, b) do { IntermediateType t = a; (a) = b; (b) = t; } while (0)

// Assertion macros
#ifdef MM_ENABLE_ASSERTS
	#define MM_ASSERT                PPK_ASSERT
	#define MM_ASSERT_WARNING        PPK_ASSERT_WARNING
	#define MM_ASSERT_DEBUG          PPK_ASSERT_DEBUG
	#define MM_ASSERT_ERROR          PPK_ASSERT_ERROR
	#define MM_ASSERT_FATAL          PPK_ASSERT_FATAL
	#define MM_ASSERT_CUSTOM         PPK_ASSERT_CUSTOM
	#define MM_ASSERT_USED           PPK_ASSERT_USED
	#define MM_ASSERT_USED_WARNING   PPK_ASSERT_USED_WARNING
	#define MM_ASSERT_USED_DEBUG     PPK_ASSERT_USED_DEBUG
	#define MM_ASSERT_USED_ERROR     PPK_ASSERT_USED_ERROR
	#define MM_ASSERT_USED_FATAL     PPK_ASSERT_USED_FATAL
	#define MM_ASSERT_USED_CUSTOM    PPK_ASSERT_USED_CUSTOM
#else
	#define MM_ASSERT                
	#define MM_ASSERT_WARNING        
	#define MM_ASSERT_DEBUG          
	#define MM_ASSERT_ERROR          
	#define MM_ASSERT_FATAL          
	#define MM_ASSERT_CUSTOM         
	#define MM_ASSERT_USED           
	#define MM_ASSERT_USED_WARNING   
	#define MM_ASSERT_USED_DEBUG     
	#define MM_ASSERT_USED_ERROR     
	#define MM_ASSERT_USED_FATAL     
	#define MM_ASSERT_USED_CUSTOM
#endif
