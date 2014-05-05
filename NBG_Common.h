#pragma once

//RGB color macro
#define UIColorFromRGB(rgbValue) [UIColor \
colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 \
green:((float)((rgbValue & 0xFF00) >> 8))/255.0 \
blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]

//RGB color macro with alpha
#define UIColorFromRGBWithAlpha(rgbValue,a) [UIColor \
colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 \
green:((float)((rgbValue & 0xFF00) >> 8))/255.0 \
blue:((float)(rgbValue & 0xFF))/255.0 alpha:a]

/// BOX(expr)
///
/// Macro. Box simple things like `CGPoint` or `CGRect` into an `NSValue`.
///
/// (Compare with the use of `@` in `@YES`, @123, @"abc" or `@(1 + 2)`.)

#define BOX(expr) ({ __typeof__(expr) _box_expr = (expr); \
[NSValue valueWithBytes:&_box_expr objCType:@encode(__typeof__(expr))]; })

//based off of http://www.dribin.org/dave/blog/archives/2008/09/22/convert_to_nsstring/
NSString * VTPG_DDToStringFromTypeAndValue(const char * typeCode, void * value);

#ifdef DEBUG
#import "LoggerClient.h"
#import "LoggerCommon.h"
#if !defined(NDEBUG)
#undef assert
#if __DARWIN_UNIX03
#define assert(e) \
(__builtin_expect(!(e), 0) ? (CFShow(CFSTR("assert going to fail, connect NSLogger NOW\n")), LoggerFlush(NULL,YES), __assert_rtn(__func__, __FILE__, __LINE__, #e)) : (void)0)
#else
#define assert(e)  \
(__builtin_expect(!(e), 0) ? (CFShow(CFSTR("assert going to fail, connect NSLogger NOW\n")), LoggerFlush(NULL,YES), __assert(#e, __FILE__, __LINE__)) : (void)0)
#endif
#endif

#include <libgen.h>

// LEVEL
// use 0 for close to production so only very important message or error should be there
// use 1 
// use 2 warning
// use 3 info
// use 4 for everything = full debug
// use 5 for in progress debug, you should never commit a 1 in git (my ass) !

#define DLOG_DATA(level, tag, data)     LogDataF(__FILE__,__LINE__,__FUNCTION__, @#tag, level, data);  
#define DLOG_IMAGE(level, tag, imagedata, width, height)   LogImageDataF(__FILE__,__LINE__,__FUNCTION__, @#tag, level, width, height, imagedata);

#define DLOG(level, tag, fmt, ...) do{\
    LogMessageF(__FILE__,__LINE__,__FUNCTION__,@#tag ,level,fmt, __VA_ARGS__);\
    NSLog((@"<%@> %@ " fmt), @#tag, [NSString stringWithFormat:@"[%s:%d %@]",basename(__FILE__),__LINE__,NSStringFromSelector(_cmd)], ##__VA_ARGS__);\
} while(0)

#define DLOGM(level, tag) do{\
    LogMessageF(__FILE__,__LINE__,__FUNCTION__,@#tag ,level ,@"%s",__FUNCTION__ );\
    NSLog(@"<%@> %@", @#tag, [NSString stringWithFormat:@"[%s:%d %@]",basename(__FILE__),__LINE__,NSStringFromSelector(_cmd)]);\
} while(0)

#define DLOGV(level, tag, _X_) do{\
	__typeof__(_X_) _Y_ = (_X_);\
	const char * _TYPE_CODE_ = @encode(__typeof__(_X_));\
	NSString *_STR_ = VTPG_DDToStringFromTypeAndValue(_TYPE_CODE_, &_Y_);\
	if(_STR_) {\
		LogMessageF(__FILE__,__LINE__,__FUNCTION__,@#tag,level,@"%s = %@", #_X_, _STR_);\
        NSLog(@"<%@> %@", @#tag, [NSString stringWithFormat:@"[%s:%d %@] %s = %@",basename(__FILE__),__LINE__,NSStringFromSelector(_cmd), #_X_, _STR_]);\
	}else\
		LogMessageCompat(@"DLogv HELPER Unknown _TYPE_CODE_: %s for expression %s in function %s, file %s, line %d", _TYPE_CODE_, #_X_, __func__, __FILE__, __LINE__);\
}while(0)

#define DLOGM_VERBOSE(tag) DLOGM(3, tag);
#define DLOGM_INFO(tag) DLOGM(2, tag);
#define DLOGM_WARN(tag) DLOGM(1, tag);
#define DLOGM_ERROR(tag) DLOGM(0, tag);

#define DLOGV_VERBOSE(tag, data) DLOGV(3, tag, data);
#define DLOGV_INFO(tag, data) DLOGV(2, tag, data);
#define DLOGV_WARN(tag, data) DLOGV(1, tag, data);
#define DLOGV_ERROR(tag, data) DLOGV(0, tag, data);

#define DLOG_VERBOSE(tag, fmt, ...) DLOG(3, tag, fmt, __VA_ARGS__);
#define DLOG_INFO(tag, fmt, ...) DLOG(2, tag, fmt, __VA_ARGS__);
#define DLOG_WARN(tag, fmt, ...) DLOG(1, tag, fmt, __VA_ARGS__);
#define DLOG_ERROR(tag, fmt, ...) DLOG(0, tag, fmt, __VA_ARGS__);

#else /* NO DEBUG */

#define DLOGV(level, tag, ...) do { (void)(__VA_ARGS__); } while (0)
#define DLOG(level, tag, fmt, ...) /* */
#define DLOG_DATA(level, tag, ...) do { (void)(__VA_ARGS__); } while (0)
#define DLOG_IMAGE(level, tag, ...) do { (void)(__VA_ARGS__); } while (0)
#define DLOGM(level, tag) /* */

#define DLOGM_VERBOSE(tag)
#define DLOGM_INFO(tag)
#define DLOGM_WARN(tag)
#define DLOGM_ERROR(tag)

#define DLOGV_VERBOSE(tag, data)
#define DLOGV_INFO(tag, data)
#define DLOGV_WARN(tag, data)
#define DLOGV_ERROR(tag, data)

#define DLOG_VERBOSE(tag, fmt, ...)
#define DLOG_INFO(tag, fmt, ...)
#define DLOG_WARN(tag, fmt, ...)
#define DLOG_ERROR(tag, fmt, ...)

#endif /* NO DEBUG */

