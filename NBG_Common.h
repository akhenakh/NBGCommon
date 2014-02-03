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


#else /* NO DEBUG */
#define DLOGV(level, tag, data)
#define DLOG(level, tag, ...) /* */
#define DLOG_DATA(level, tag, data)
#define DLOG_IMAGE(level, tag, imagedata, width, height)
#define DLOGM(level, tag) /* */
#endif /* NO DEBUG */

