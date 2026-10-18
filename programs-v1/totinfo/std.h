#ifndef	VLD_STD_H_
#define	VLD_STD_H_			 

 

typedef int	bool;			 
#define 	false	0
#define 	true	1
 
#ifdef STD_C
#undef STD_C
#endif
#ifdef __STDC__
#if __STDC__ > 0
#define	STD_C	__STDC__		 
#endif
#endif

#ifdef STD_C
typedef void	*pointer;		 
#else
typedef char	*pointer;		 
#define	const		 
 
#define	signed		
#define	volatile	 
#endif

#ifndef EXIT_SUCCESS
#define	EXIT_SUCCESS	0
#endif

#ifndef EXIT_FAILURE
#define	EXIT_FAILURE	1
#endif

#ifndef NULL
#define NULL	0			 
#endif
 

#define DEGRAD	57.2957795130823208767981548141051703324054724665642
					 
#define	E	2.71828182845904523536028747135266249775724709369996
					 
#define	GAMMA	0.57721566490153286061
					 
#define LOG10E	0.43429448190325182765112891891660508229439700580367
					 
#define PHI	1.618033988749894848204586834365638117720309180
					 
#define PI	3.14159265358979323846264338327950288419716939937511
					  
#define Abs( x )	((x) < 0 ? -(x) : (x))			 
#define Max( a, b )	((a) > (b) ? (a) : (b))			 
#define Min( a, b )	((a) < (b) ? (a) : (b))			 

 
#define Round( d )	(floor( (d) + 0.5 ))		 
 
#define	Sgn( x )	((x) == 0 ? 0 : (x) > 0 ? 1 : -1)	 
 
#ifdef gould	 
#define	StrEq( a, b )	(strcmp( a, b ) == 0)			 
#else
#define	StrEq( a, b )	(*(a) == *(b) && strcmp( a, b ) == 0)	 
#endif


#define	Elements( a )	(sizeof a / sizeof a[0])
 
#define fromhostc( c )	(c)		 
#define tohostc( c )	(c)		 
#define tonumber( c )	((c) - '0')	 
#define todigit( n )	((n) + '0') 
 

#endif	 
