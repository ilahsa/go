// auto generated by go tool dist
// goos=windows goarch=amd64


#include "runtime.h"
#include "arch_GOARCH.h"
#include "malloc.h"
#include "race.h"
#include "../../cmd/ld/textflag.h"

#line 12 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
String runtime·emptystring; 
#pragma textflag NOSPLIT

#line 15 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
intgo 
runtime·findnull ( byte *s ) 
{ 
intgo l; 
#line 20 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
if ( s == nil ) 
return 0; 
for ( l=0; s[l]!=0; l++ ) 
; 
return l; 
} 
#line 27 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
intgo 
runtime·findnullw ( uint16 *s ) 
{ 
intgo l; 
#line 32 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
if ( s == nil ) 
return 0; 
for ( l=0; s[l]!=0; l++ ) 
; 
return l; 
} 
#line 39 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
uintptr runtime·maxstring = 256; 
#line 41 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
static String 
gostringsize ( intgo l ) 
{ 
String s; 
uintptr ms; 
#line 47 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
if ( l == 0 ) 
return runtime·emptystring; 
s.str = runtime·mallocgc ( l , 0 , FlagNoScan|FlagNoZero ) ; 
s.len = l; 
for ( ;; ) { 
ms = runtime·maxstring; 
if ( ( uintptr ) l <= ms || runtime·casp ( ( void** ) &runtime·maxstring , ( void* ) ms , ( void* ) l ) ) 
break; 
} 
return s; 
} 
#line 59 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
String 
runtime·gostring ( byte *str ) 
{ 
intgo l; 
String s; 
#line 65 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
l = runtime·findnull ( str ) ; 
s = gostringsize ( l ) ; 
runtime·memmove ( s.str , str , l ) ; 
return s; 
} 
#line 71 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
String 
runtime·gostringn ( byte *str , intgo l ) 
{ 
String s; 
#line 76 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
s = gostringsize ( l ) ; 
runtime·memmove ( s.str , str , l ) ; 
return s; 
} 
#line 82 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
Slice 
runtime·gobytes ( byte *p , intgo n ) 
{ 
Slice sl; 
#line 87 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
sl.array = runtime·mallocgc ( n , 0 , FlagNoScan|FlagNoZero ) ; 
sl.len = n; 
sl.cap = n; 
runtime·memmove ( sl.array , p , n ) ; 
return sl; 
} 
#line 94 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
String 
runtime·gostringnocopy ( byte *str ) 
{ 
String s; 
#line 99 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
s.str = str; 
s.len = runtime·findnull ( str ) ; 
return s; 
} 
void
runtime·cstringToGo(byte* str, String s)
{
	s.str = 0;
	s.len = 0;
	FLUSH(&s);
#line 104 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	s = runtime·gostringnocopy(str);
	FLUSH(&s);
}

#line 108 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
String 
runtime·gostringw ( uint16 *str ) 
{ 
intgo n1 , n2 , i; 
byte buf[8]; 
String s; 
#line 115 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
n1 = 0; 
for ( i=0; str[i]; i++ ) 
n1 += runtime·runetochar ( buf , str[i] ) ; 
s = gostringsize ( n1+4 ) ; 
n2 = 0; 
for ( i=0; str[i]; i++ ) { 
#line 122 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
if ( n2 >= n1 ) 
break; 
n2 += runtime·runetochar ( s.str+n2 , str[i] ) ; 
} 
s.len = n2; 
s.str[s.len] = 0; 
return s; 
} 
#line 131 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
String 
runtime·catstring ( String s1 , String s2 ) 
{ 
String s3; 
#line 136 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
if ( s1.len == 0 ) 
return s2; 
if ( s2.len == 0 ) 
return s1; 
#line 141 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
s3 = gostringsize ( s1.len + s2.len ) ; 
runtime·memmove ( s3.str , s1.str , s1.len ) ; 
runtime·memmove ( s3.str+s1.len , s2.str , s2.len ) ; 
return s3; 
} 
#line 147 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
static String 
concatstring ( intgo n , String *s ) 
{ 
intgo i , l , count; 
String out; 
#line 153 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
l = 0; 
count = 0; 
for ( i=0; i<n; i++ ) { 
if ( l + s[i].len < l ) 
runtime·throw ( "string concatenation too long" ) ; 
l += s[i].len; 
if ( s[i].len > 0 ) { 
count++; 
out = s[i]; 
} 
} 
if ( count == 0 ) 
return runtime·emptystring; 
if ( count == 1 ) 
return out; 
#line 169 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
out = gostringsize ( l ) ; 
l = 0; 
for ( i=0; i<n; i++ ) { 
runtime·memmove ( out.str+l , s[i].str , s[i].len ) ; 
l += s[i].len; 
} 
return out; 
} 
#pragma textflag NOSPLIT

void
runtime·concatstring2(String s1, String s2, String res)
{
	res.str = 0;
	res.len = 0;
	FLUSH(&res);
#line 179 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	USED(&s2);
	res = concatstring(2, &s1);
	FLUSH(&res);
}

#pragma textflag NOSPLIT
void
runtime·concatstring3(String s1, String s2, String s3, String res)
{
	res.str = 0;
	res.len = 0;
	FLUSH(&res);
#line 184 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	USED(&s2);
	USED(&s3);
	res = concatstring(3, &s1);
	FLUSH(&res);
}

#pragma textflag NOSPLIT
void
runtime·concatstring4(String s1, String s2, String s3, String s4, String res)
{
	res.str = 0;
	res.len = 0;
	FLUSH(&res);
#line 190 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	USED(&s2);
	USED(&s3);
	USED(&s4);
	res = concatstring(4, &s1);
	FLUSH(&res);
}

#pragma textflag NOSPLIT
void
runtime·concatstring5(String s1, String s2, String s3, String s4, String s5, String res)
{
	res.str = 0;
	res.len = 0;
	FLUSH(&res);
#line 197 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	USED(&s2);
	USED(&s3);
	USED(&s4);
	USED(&s5);
	res = concatstring(5, &s1);
	FLUSH(&res);
}

#pragma textflag NOSPLIT
void
runtime·concatstrings(Slice s, String res)
{
	res.str = 0;
	res.len = 0;
	FLUSH(&res);
#line 205 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	res = concatstring(s.len, (String*)s.array);
	FLUSH(&res);
}
void
runtime·eqstring(String s1, String s2, bool v)
{
	v = 0;
	FLUSH(&v);
#line 209 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	if(s1.len != s2.len) {
		v = false;
		return;
	}
	if(s1.str == s2.str) {
		v = true;
		return;
	}
	v = runtime·memeq(s1.str, s2.str, s1.len);
	FLUSH(&v);
}

#line 221 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
int32 
runtime·strcmp ( byte *s1 , byte *s2 ) 
{ 
uintptr i; 
byte c1 , c2; 
#line 227 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
for ( i=0;; i++ ) { 
c1 = s1[i]; 
c2 = s2[i]; 
if ( c1 < c2 ) 
return -1; 
if ( c1 > c2 ) 
return +1; 
if ( c1 == 0 ) 
return 0; 
} 
} 
#line 239 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
int32 
runtime·strncmp ( byte *s1 , byte *s2 , uintptr n ) 
{ 
uintptr i; 
byte c1 , c2; 
#line 245 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
for ( i=0; i<n; i++ ) { 
c1 = s1[i]; 
c2 = s2[i]; 
if ( c1 < c2 ) 
return -1; 
if ( c1 > c2 ) 
return +1; 
if ( c1 == 0 ) 
break; 
} 
return 0; 
} 
#line 258 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
byte* 
runtime·strstr ( byte *s1 , byte *s2 ) 
{ 
byte *sp1 , *sp2; 
#line 263 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
if ( *s2 == 0 ) 
return s1; 
for ( ; *s1; s1++ ) { 
if ( *s1 != *s2 ) 
continue; 
sp1 = s1; 
sp2 = s2; 
for ( ;; ) { 
if ( *sp2 == 0 ) 
return s1; 
if ( *sp1++ != *sp2++ ) 
break; 
} 
} 
return nil; 
} 
void
runtime·intstring(int64 v, String s)
{
	s.str = 0;
	s.len = 0;
	FLUSH(&s);
#line 280 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	s = gostringsize(8);
	s.len = runtime·runetochar(s.str, v);
	s.str[s.len] = 0;
	FLUSH(&s);
}
void
runtime·slicebytetostring(Slice b, String s)
{
	s.str = 0;
	s.len = 0;
	FLUSH(&s);
#line 286 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	void *pc;

	if(raceenabled) {
		pc = runtime·getcallerpc(&b);
		runtime·racereadrangepc(b.array, b.len, pc, runtime·slicebytetostring);
	}
	s = gostringsize(b.len);
	runtime·memmove(s.str, b.array, s.len);
	FLUSH(&s);
}
void
runtime·slicebytetostringtmp(Slice b, String s)
{
	s.str = 0;
	s.len = 0;
	FLUSH(&s);
#line 297 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	void *pc;

	if(raceenabled) {
		pc = runtime·getcallerpc(&b);
		runtime·racereadrangepc(b.array, b.len, pc, runtime·slicebytetostringtmp);
	}
	
	// Return a "string" referring to the actual []byte bytes.
	// This is only for use by internal compiler optimizations
	// that know that the string form will be discarded before
	// the calling goroutine could possibly modify the original
	// slice or synchronize with another goroutine.
	// Today, the only such case is a m[string(k)] lookup where
	// m is a string-keyed map and k is a []byte.
	s.str = b.array;
	s.len = b.len;
	FLUSH(&s);
}
void
runtime·stringtoslicebyte(String s, Slice b)
{
	b.array = 0;
	b.len = 0;
	b.cap = 0;
	FLUSH(&b);
#line 316 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	uintptr cap;

	cap = runtime·roundupsize(s.len);
	b.array = runtime·mallocgc(cap, 0, FlagNoScan|FlagNoZero);
	b.len = s.len;
	b.cap = cap;
	runtime·memmove(b.array, s.str, s.len);
	if(cap != b.len)
		runtime·memclr(b.array+b.len, cap-b.len);
	FLUSH(&b);
}
void
runtime·slicerunetostring(Slice b, String s)
{
	s.str = 0;
	s.len = 0;
	FLUSH(&s);
#line 328 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	intgo siz1, siz2, i;
	int32 *a;
	byte dum[8];
	void *pc;

	if(raceenabled) {
		pc = runtime·getcallerpc(&b);
		runtime·racereadrangepc(b.array, b.len*sizeof(*a), pc, runtime·slicerunetostring);
	}
	a = (int32*)b.array;
	siz1 = 0;
	for(i=0; i<b.len; i++) {
		siz1 += runtime·runetochar(dum, a[i]);
	}

	s = gostringsize(siz1+4);
	siz2 = 0;
	for(i=0; i<b.len; i++) {
		// check for race
		if(siz2 >= siz1)
			break;
		siz2 += runtime·runetochar(s.str+siz2, a[i]);
	}
	s.len = siz2;
	s.str[s.len] = 0;
	FLUSH(&s);
}
void
runtime·stringtoslicerune(String s, Slice b)
{
	b.array = 0;
	b.len = 0;
	b.cap = 0;
	FLUSH(&b);
#line 356 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	intgo n;
	int32 dum, *r;
	uint8 *p, *ep;
	uintptr mem;

	// two passes.
	// unlike slicerunetostring, no race because strings are immutable.
	p = s.str;
	ep = s.str+s.len;
	n = 0;
	while(p < ep) {
		p += runtime·charntorune(&dum, p, ep-p);
		n++;
	}

	if(n > MaxMem/sizeof(r[0]))
		runtime·throw("out of memory");
	mem = runtime·roundupsize(n*sizeof(r[0]));
	b.array = runtime·mallocgc(mem, 0, FlagNoScan|FlagNoZero);
	b.len = n;
	b.cap = mem/sizeof(r[0]);
	p = s.str;
	r = (int32*)b.array;
	while(p < ep)
		p += runtime·charntorune(r++, p, ep-p);
	if(b.cap > b.len)
		runtime·memclr(b.array+b.len*sizeof(r[0]), (b.cap-b.len)*sizeof(r[0]));
	FLUSH(&b);
}

#line 386 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"
enum 
{ 
Runeself = 0x80 , 
} ; 
void
runtime·stringiter(String s, intgo k, intgo retk)
{
	retk = 0;
	FLUSH(&retk);
#line 391 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	int32 l;

	if(k >= s.len) {
		// retk=0 is end of iteration
		retk = 0;
		goto out;
	}

	l = s.str[k];
	if(l < Runeself) {
		retk = k+1;
		goto out;
	}

	// multi-char rune
	retk = k + runtime·charntorune(&l, s.str+k, s.len-k);

out:
	FLUSH(&retk);
}
void
runtime·stringiter2(String s, intgo k, intgo retk, int32 retv)
{
	retk = 0;
	FLUSH(&retk);
	retv = 0;
	FLUSH(&retv);
#line 412 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\string.goc"

	if(k >= s.len) {
		// retk=0 is end of iteration
		retk = 0;
		retv = 0;
		goto out;
	}

	retv = s.str[k];
	if(retv < Runeself) {
		retk = k+1;
		goto out;
	}

	// multi-char rune
	retk = k + runtime·charntorune(&retv, s.str+k, s.len-k);

out:
	FLUSH(&retk);
	FLUSH(&retv);
}
