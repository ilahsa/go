// auto generated by go tool dist
// goos=windows goarch=amd64


#include "runtime.h"
#include "arch_GOARCH.h"
#include "malloc.h"
#include "type.h"
#include "race.h"
#include "hashmap.h"
#include "typekind.h"
#include "../../cmd/ld/textflag.h"

#line 15 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
enum 
{ 
docheck = 0 , 
debug = 0 , 
checkgc = 0 || docheck , 
} ; 
static void 
check ( MapType *t , Hmap *h ) 
{ 
uintptr bucket , oldbucket; 
Bucket *b; 
uintptr i; 
uintptr hash; 
uintgo cnt; 
uint8 top; 
bool eq; 
byte *k , *v; 
#line 33 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
cnt = 0; 
#line 36 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
for ( bucket = 0; bucket < ( uintptr ) 1 << h->B; bucket++ ) { 
for ( b = ( Bucket* ) ( h->buckets + bucket * h->bucketsize ) ; b != nil; b = b->overflow ) { 
for ( i = 0 , k = ( byte* ) b->data , v = k + h->keysize * BUCKETSIZE; i < BUCKETSIZE; i++ , k += h->keysize , v += h->valuesize ) { 
if ( b->tophash[i] == Empty ) 
continue; 
if ( b->tophash[i] > Empty && b->tophash[i] < MinTopHash ) 
runtime·throw ( "evacuated cell in buckets" ) ; 
cnt++; 
t->key->alg->equal ( &eq , t->key->size , IK ( h , k ) , IK ( h , k ) ) ; 
if ( !eq ) 
continue; 
hash = h->hash0; 
t->key->alg->hash ( &hash , t->key->size , IK ( h , k ) ) ; 
top = hash >> ( 8*sizeof ( uintptr ) - 8 ) ; 
if ( top < MinTopHash ) 
top += MinTopHash; 
if ( top != b->tophash[i] ) 
runtime·throw ( "bad hash" ) ; 
} 
} 
} 
#line 59 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( h->oldbuckets != nil ) { 
for ( oldbucket = 0; oldbucket < ( uintptr ) 1 << ( h->B - 1 ) ; oldbucket++ ) { 
b = ( Bucket* ) ( h->oldbuckets + oldbucket * h->bucketsize ) ; 
for ( ; b != nil; b = b->overflow ) { 
for ( i = 0 , k = ( byte* ) b->data , v = k + h->keysize * BUCKETSIZE; i < BUCKETSIZE; i++ , k += h->keysize , v += h->valuesize ) { 
if ( b->tophash[i] < MinTopHash ) 
continue; 
if ( oldbucket < h->nevacuate ) 
runtime·throw ( "unevacuated entry in an evacuated bucket" ) ; 
cnt++; 
t->key->alg->equal ( &eq , t->key->size , IK ( h , k ) , IK ( h , k ) ) ; 
if ( !eq ) 
continue; 
hash = h->hash0; 
t->key->alg->hash ( &hash , t->key->size , IK ( h , k ) ) ; 
top = hash >> ( 8*sizeof ( uintptr ) - 8 ) ; 
if ( top < MinTopHash ) 
top += MinTopHash; 
if ( top != b->tophash[i] ) 
runtime·throw ( "bad hash (old)" ) ; 
} 
} 
} 
} 
#line 84 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( cnt != h->count ) { 
runtime·printf ( "%D %D\n" , ( uint64 ) cnt , ( uint64 ) h->count ) ; 
runtime·throw ( "entries missing" ) ; 
} 
} 
#line 90 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
static void 
hash_init ( MapType *t , Hmap *h , uint32 hint ) 
{ 
uint8 B; 
byte *buckets; 
uintptr keysize , valuesize , bucketsize; 
uint8 flags; 
#line 98 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
flags = 0; 
#line 101 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
keysize = t->key->size; 
if ( keysize > MAXKEYSIZE ) { 
flags |= IndirectKey; 
keysize = sizeof ( byte* ) ; 
} 
valuesize = t->elem->size; 
if ( valuesize > MAXVALUESIZE ) { 
flags |= IndirectValue; 
valuesize = sizeof ( byte* ) ; 
} 
bucketsize = offsetof ( Bucket , data[0] ) + ( keysize + valuesize ) * BUCKETSIZE; 
if ( bucketsize != t->bucket->size ) { 
runtime·printf ( "runtime: bucketsize=%p but t->bucket->size=%p; t=%S\n" , bucketsize , t->bucket->size , *t->string ) ; 
runtime·throw ( "bucketsize wrong" ) ; 
} 
#line 119 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( t->key->align > BUCKETSIZE ) 
runtime·throw ( "key align too big" ) ; 
if ( t->elem->align > BUCKETSIZE ) 
runtime·throw ( "value align too big" ) ; 
if ( t->key->size % t->key->align != 0 ) 
runtime·throw ( "key size not a multiple of key align" ) ; 
if ( t->elem->size % t->elem->align != 0 ) 
runtime·throw ( "value size not a multiple of value align" ) ; 
if ( BUCKETSIZE < 8 ) 
runtime·throw ( "bucketsize too small for proper alignment" ) ; 
if ( ( offsetof ( Bucket , data[0] ) & ( t->key->align-1 ) ) != 0 ) 
runtime·throw ( "need padding in bucket (key)" ) ; 
if ( ( offsetof ( Bucket , data[0] ) & ( t->elem->align-1 ) ) != 0 ) 
runtime·throw ( "need padding in bucket (value)" ) ; 
#line 135 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
B = 0; 
while ( hint > BUCKETSIZE && hint > LOAD * ( ( uintptr ) 1 << B ) ) 
B++; 
#line 141 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( checkgc ) mstats.next_gc = mstats.heap_alloc; 
if ( B == 0 ) { 
#line 144 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
buckets = nil; 
} else { 
buckets = runtime·cnewarray ( t->bucket , ( uintptr ) 1 << B ) ; 
} 
#line 150 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
h->count = 0; 
h->B = B; 
h->flags = flags; 
h->keysize = keysize; 
h->valuesize = valuesize; 
h->bucketsize = bucketsize; 
h->hash0 = runtime·fastrand1 ( ) ; 
h->buckets = buckets; 
h->oldbuckets = nil; 
h->nevacuate = 0; 
if ( docheck ) 
check ( t , h ) ; 
} 
#line 167 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
static void 
evacuate ( MapType *t , Hmap *h , uintptr oldbucket ) 
{ 
Bucket *b; 
Bucket *x , *y; 
Bucket *newx , *newy; 
uintptr xi , yi; 
uintptr newbit; 
uintptr hash; 
uintptr i; 
byte *k , *v; 
byte *xk , *yk , *xv , *yv; 
uint8 top; 
bool eq; 
#line 182 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
b = ( Bucket* ) ( h->oldbuckets + oldbucket * h->bucketsize ) ; 
newbit = ( uintptr ) 1 << ( h->B - 1 ) ; 
#line 185 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( !evacuated ( b ) ) { 
#line 189 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
x = ( Bucket* ) ( h->buckets + oldbucket * h->bucketsize ) ; 
y = ( Bucket* ) ( h->buckets + ( oldbucket + newbit ) * h->bucketsize ) ; 
xi = 0; 
yi = 0; 
xk = ( byte* ) x->data; 
yk = ( byte* ) y->data; 
xv = xk + h->keysize * BUCKETSIZE; 
yv = yk + h->keysize * BUCKETSIZE; 
for ( ; b != nil; b = b->overflow ) { 
for ( i = 0 , k = ( byte* ) b->data , v = k + h->keysize * BUCKETSIZE; i < BUCKETSIZE; i++ , k += h->keysize , v += h->valuesize ) { 
top = b->tophash[i]; 
if ( top == Empty ) { 
b->tophash[i] = EvacuatedEmpty; 
continue; 
} 
if ( top < MinTopHash ) 
runtime·throw ( "bad state" ) ; 
#line 209 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
hash = h->hash0; 
t->key->alg->hash ( &hash , t->key->size , IK ( h , k ) ) ; 
if ( ( h->flags & Iterator ) != 0 ) { 
t->key->alg->equal ( &eq , t->key->size , IK ( h , k ) , IK ( h , k ) ) ; 
if ( !eq ) { 
#line 225 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( ( top & 1 ) != 0 ) 
hash |= newbit; 
else 
hash &= ~newbit; 
top = hash >> ( 8*sizeof ( uintptr ) -8 ) ; 
if ( top < MinTopHash ) 
top += MinTopHash; 
} 
} 
#line 235 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( ( hash & newbit ) == 0 ) { 
b->tophash[i] = EvacuatedX; 
if ( xi == BUCKETSIZE ) { 
if ( checkgc ) mstats.next_gc = mstats.heap_alloc; 
newx = runtime·cnew ( t->bucket ) ; 
x->overflow = newx; 
x = newx; 
xi = 0; 
xk = ( byte* ) x->data; 
xv = xk + h->keysize * BUCKETSIZE; 
} 
x->tophash[xi] = top; 
if ( ( h->flags & IndirectKey ) != 0 ) { 
* ( byte** ) xk = * ( byte** ) k; 
} else { 
t->key->alg->copy ( t->key->size , xk , k ) ; 
} 
if ( ( h->flags & IndirectValue ) != 0 ) { 
* ( byte** ) xv = * ( byte** ) v; 
} else { 
t->elem->alg->copy ( t->elem->size , xv , v ) ; 
} 
xi++; 
xk += h->keysize; 
xv += h->valuesize; 
} else { 
b->tophash[i] = EvacuatedY; 
if ( yi == BUCKETSIZE ) { 
if ( checkgc ) mstats.next_gc = mstats.heap_alloc; 
newy = runtime·cnew ( t->bucket ) ; 
y->overflow = newy; 
y = newy; 
yi = 0; 
yk = ( byte* ) y->data; 
yv = yk + h->keysize * BUCKETSIZE; 
} 
y->tophash[yi] = top; 
if ( ( h->flags & IndirectKey ) != 0 ) { 
* ( byte** ) yk = * ( byte** ) k; 
} else { 
t->key->alg->copy ( t->key->size , yk , k ) ; 
} 
if ( ( h->flags & IndirectValue ) != 0 ) { 
* ( byte** ) yv = * ( byte** ) v; 
} else { 
t->elem->alg->copy ( t->elem->size , yv , v ) ; 
} 
yi++; 
yk += h->keysize; 
yv += h->valuesize; 
} 
} 
} 
#line 290 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( ( h->flags & OldIterator ) == 0 ) { 
b = ( Bucket* ) ( h->oldbuckets + oldbucket * h->bucketsize ) ; 
b->overflow = nil; 
runtime·memclr ( ( byte* ) b->data , h->bucketsize - offsetof ( Bucket , data[0] ) ) ; 
} 
} 
#line 298 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( oldbucket == h->nevacuate ) { 
h->nevacuate = oldbucket + 1; 
if ( oldbucket + 1 == newbit ) 
#line 302 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
h->oldbuckets = nil; 
} 
if ( docheck ) 
check ( t , h ) ; 
} 
#line 308 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
static void 
grow_work ( MapType *t , Hmap *h , uintptr bucket ) 
{ 
uintptr noldbuckets; 
#line 313 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
noldbuckets = ( uintptr ) 1 << ( h->B - 1 ) ; 
#line 317 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
evacuate ( t , h , bucket & ( noldbuckets - 1 ) ) ; 
#line 320 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( h->oldbuckets != nil ) 
evacuate ( t , h , h->nevacuate ) ; 
} 
#line 324 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
static void 
hash_grow ( MapType *t , Hmap *h ) 
{ 
byte *old_buckets; 
byte *new_buckets; 
uint8 flags; 
#line 332 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( h->oldbuckets != nil ) 
runtime·throw ( "evacuation not done in time" ) ; 
old_buckets = h->buckets; 
if ( checkgc ) mstats.next_gc = mstats.heap_alloc; 
new_buckets = runtime·cnewarray ( t->bucket , ( uintptr ) 1 << ( h->B + 1 ) ) ; 
flags = ( h->flags & ~ ( Iterator | OldIterator ) ) ; 
if ( ( h->flags & Iterator ) != 0 ) 
flags |= OldIterator; 
#line 342 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
h->B++; 
h->flags = flags; 
h->oldbuckets = old_buckets; 
h->buckets = new_buckets; 
h->nevacuate = 0; 
#line 350 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( docheck ) 
check ( t , h ) ; 
} 
#line 356 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
static byte* 
hash_lookup ( MapType *t , Hmap *h , byte **keyp ) 
{ 
void *key; 
uintptr hash; 
uintptr bucket , oldbucket; 
Bucket *b; 
uint8 top; 
uintptr i; 
bool eq; 
byte *k , *k2 , *v; 
#line 368 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
key = *keyp; 
if ( docheck ) 
check ( t , h ) ; 
if ( h->count == 0 ) 
return nil; 
hash = h->hash0; 
t->key->alg->hash ( &hash , t->key->size , key ) ; 
bucket = hash & ( ( ( uintptr ) 1 << h->B ) - 1 ) ; 
if ( h->oldbuckets != nil ) { 
oldbucket = bucket & ( ( ( uintptr ) 1 << ( h->B - 1 ) ) - 1 ) ; 
b = ( Bucket* ) ( h->oldbuckets + oldbucket * h->bucketsize ) ; 
if ( evacuated ( b ) ) { 
b = ( Bucket* ) ( h->buckets + bucket * h->bucketsize ) ; 
} 
} else { 
b = ( Bucket* ) ( h->buckets + bucket * h->bucketsize ) ; 
} 
top = hash >> ( sizeof ( uintptr ) *8 - 8 ) ; 
if ( top < MinTopHash ) 
top += MinTopHash; 
do { 
for ( i = 0 , k = ( byte* ) b->data , v = k + h->keysize * BUCKETSIZE; i < BUCKETSIZE; i++ , k += h->keysize , v += h->valuesize ) { 
if ( b->tophash[i] == top ) { 
k2 = IK ( h , k ) ; 
t->key->alg->equal ( &eq , t->key->size , key , k2 ) ; 
if ( eq ) { 
*keyp = k2; 
return IV ( h , v ) ; 
} 
} 
} 
b = b->overflow; 
} while ( b != nil ) ; 
return nil; 
} 
#define HASH_LOOKUP1 runtime·mapaccess1_fast32
#define HASH_LOOKUP2 runtime·mapaccess2_fast32
#define KEYTYPE uint32
#define HASHFUNC runtime·algarray[AMEM32].hash
#define FASTKEY(x) true
#define QUICK_NE(x,y) ((x) != (y))
#define QUICK_EQ(x,y) true
#define SLOW_EQ(x,y) true
#define MAYBE_EQ(x,y) true
#include "hashmap_fast.c"
#undef HASH_LOOKUP1
#undef HASH_LOOKUP2
#undef KEYTYPE
#undef HASHFUNC
#undef FASTKEY
#undef QUICK_NE
#undef QUICK_EQ
#undef SLOW_EQ
#undef MAYBE_EQ
#define HASH_LOOKUP1 runtime·mapaccess1_fast64
#define HASH_LOOKUP2 runtime·mapaccess2_fast64
#define KEYTYPE uint64
#define HASHFUNC runtime·algarray[AMEM64].hash
#define FASTKEY(x) true
#define QUICK_NE(x,y) ((x) != (y))
#define QUICK_EQ(x,y) true
#define SLOW_EQ(x,y) true
#define MAYBE_EQ(x,y) true
#include "hashmap_fast.c"
#undef HASH_LOOKUP1
#undef HASH_LOOKUP2
#undef KEYTYPE
#undef HASHFUNC
#undef FASTKEY
#undef QUICK_NE
#undef QUICK_EQ
#undef SLOW_EQ
#undef MAYBE_EQ
#ifdef GOARCH_amd64
#define CHECKTYPE uint64
#endif
#ifdef GOARCH_amd64p32
#define CHECKTYPE uint32
#endif
#ifdef GOARCH_386
#define CHECKTYPE uint32
#endif
#ifdef GOARCH_arm
#define CHECKTYPE uint8
#endif
#define HASH_LOOKUP1 runtime·mapaccess1_faststr
#define HASH_LOOKUP2 runtime·mapaccess2_faststr
#define KEYTYPE String
#define HASHFUNC runtime·algarray[ASTRING].hash
#define FASTKEY(x) ((x).len < 32)
#define QUICK_NE(x,y) ((x).len != (y).len)
#define QUICK_EQ(x,y) ((x).str == (y).str)
#define SLOW_EQ(x,y) runtime·memeq((x).str, (y).str, (x).len)
#define MAYBE_EQ(x,y) (*(CHECKTYPE*)(x).str == *(CHECKTYPE*)(y).str && *(CHECKTYPE*)((x).str + (x).len - sizeof(CHECKTYPE)) == *(CHECKTYPE*)((y).str + (x).len - sizeof(CHECKTYPE)))
#include "hashmap_fast.c"

#line 474 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
static void 
hash_insert ( MapType *t , Hmap *h , void *key , void *value ) 
{ 
uintptr hash; 
uintptr bucket; 
uintptr i; 
bool eq; 
Bucket *b; 
Bucket *newb; 
uint8 *inserti; 
byte *insertk , *insertv; 
uint8 top; 
byte *k , *v; 
byte *kmem , *vmem; 
#line 489 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( docheck ) 
check ( t , h ) ; 
hash = h->hash0; 
t->key->alg->hash ( &hash , t->key->size , key ) ; 
if ( h->buckets == nil ) 
h->buckets = runtime·cnewarray ( t->bucket , 1 ) ; 
#line 496 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
again: 
bucket = hash & ( ( ( uintptr ) 1 << h->B ) - 1 ) ; 
if ( h->oldbuckets != nil ) 
grow_work ( t , h , bucket ) ; 
b = ( Bucket* ) ( h->buckets + bucket * h->bucketsize ) ; 
top = hash >> ( sizeof ( uintptr ) *8 - 8 ) ; 
if ( top < MinTopHash ) 
top += MinTopHash; 
inserti = nil; 
insertk = nil; 
insertv = nil; 
while ( true ) { 
for ( i = 0 , k = ( byte* ) b->data , v = k + h->keysize * BUCKETSIZE; i < BUCKETSIZE; i++ , k += h->keysize , v += h->valuesize ) { 
if ( b->tophash[i] != top ) { 
if ( b->tophash[i] == Empty && inserti == nil ) { 
inserti = &b->tophash[i]; 
insertk = k; 
insertv = v; 
} 
continue; 
} 
t->key->alg->equal ( &eq , t->key->size , key , IK ( h , k ) ) ; 
if ( !eq ) 
continue; 
#line 521 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
t->key->alg->copy ( t->key->size , IK ( h , k ) , key ) ; 
t->elem->alg->copy ( t->elem->size , IV ( h , v ) , value ) ; 
if ( docheck ) 
check ( t , h ) ; 
return; 
} 
if ( b->overflow == nil ) 
break; 
b = b->overflow; 
} 
#line 533 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( h->count >= LOAD * ( ( uintptr ) 1 << h->B ) && h->count >= BUCKETSIZE ) { 
hash_grow ( t , h ) ; 
goto again; 
} 
#line 538 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( inserti == nil ) { 
#line 540 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( checkgc ) mstats.next_gc = mstats.heap_alloc; 
newb = runtime·cnew ( t->bucket ) ; 
b->overflow = newb; 
inserti = newb->tophash; 
insertk = ( byte* ) newb->data; 
insertv = insertk + h->keysize * BUCKETSIZE; 
} 
#line 549 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( ( h->flags & IndirectKey ) != 0 ) { 
if ( checkgc ) mstats.next_gc = mstats.heap_alloc; 
kmem = runtime·cnew ( t->key ) ; 
* ( byte** ) insertk = kmem; 
insertk = kmem; 
} 
if ( ( h->flags & IndirectValue ) != 0 ) { 
if ( checkgc ) mstats.next_gc = mstats.heap_alloc; 
vmem = runtime·cnew ( t->elem ) ; 
* ( byte** ) insertv = vmem; 
insertv = vmem; 
} 
t->key->alg->copy ( t->key->size , insertk , key ) ; 
t->elem->alg->copy ( t->elem->size , insertv , value ) ; 
*inserti = top; 
h->count++; 
if ( docheck ) 
check ( t , h ) ; 
} 
#line 569 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
static void 
hash_remove ( MapType *t , Hmap *h , void *key ) 
{ 
uintptr hash; 
uintptr bucket; 
Bucket *b; 
uint8 top; 
uintptr i; 
byte *k , *v; 
bool eq; 
#line 580 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( docheck ) 
check ( t , h ) ; 
if ( h->count == 0 ) 
return; 
hash = h->hash0; 
t->key->alg->hash ( &hash , t->key->size , key ) ; 
bucket = hash & ( ( ( uintptr ) 1 << h->B ) - 1 ) ; 
if ( h->oldbuckets != nil ) 
grow_work ( t , h , bucket ) ; 
b = ( Bucket* ) ( h->buckets + bucket * h->bucketsize ) ; 
top = hash >> ( sizeof ( uintptr ) *8 - 8 ) ; 
if ( top < MinTopHash ) 
top += MinTopHash; 
do { 
for ( i = 0 , k = ( byte* ) b->data , v = k + h->keysize * BUCKETSIZE; i < BUCKETSIZE; i++ , k += h->keysize , v += h->valuesize ) { 
if ( b->tophash[i] != top ) 
continue; 
t->key->alg->equal ( &eq , t->key->size , key , IK ( h , k ) ) ; 
if ( !eq ) 
continue; 
#line 601 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( ( h->flags & IndirectKey ) != 0 ) { 
* ( byte** ) k = nil; 
} else { 
t->key->alg->copy ( t->key->size , k , nil ) ; 
} 
if ( ( h->flags & IndirectValue ) != 0 ) { 
* ( byte** ) v = nil; 
} else { 
t->elem->alg->copy ( t->elem->size , v , nil ) ; 
} 
#line 612 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
b->tophash[i] = Empty; 
h->count--; 
#line 617 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( docheck ) 
check ( t , h ) ; 
return; 
} 
b = b->overflow; 
} while ( b != nil ) ; 
} 
#line 631 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
static void 
hash_iter_init ( MapType *t , Hmap *h , Hiter *it ) 
{ 
uint32 old; 
#line 636 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( sizeof ( Hiter ) / sizeof ( uintptr ) != 10 ) { 
runtime·throw ( "hash_iter size incorrect" ) ; 
} 
it->t = t; 
it->h = h; 
#line 643 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
it->B = h->B; 
it->buckets = h->buckets; 
#line 647 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
it->bucket = 0; 
it->offset = runtime·fastrand1 ( ) & ( BUCKETSIZE - 1 ) ; 
it->done = false; 
it->bptr = nil; 
#line 654 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
for ( ;; ) { 
old = h->flags; 
if ( ( old& ( Iterator|OldIterator ) ) == ( Iterator|OldIterator ) ) 
break; 
if ( runtime·cas ( &h->flags , old , old|Iterator|OldIterator ) ) 
break; 
} 
#line 662 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( h->buckets == nil ) { 
#line 665 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
it->done = true; 
} 
} 
#line 671 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
static void 
hash_next ( Hiter *it ) 
{ 
Hmap *h; 
MapType *t; 
uintptr bucket , oldbucket; 
uintptr hash; 
Bucket *b; 
uintptr i , offi; 
intptr check_bucket; 
bool eq; 
byte *k , *v; 
byte *rk , *rv; 
#line 685 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
h = it->h; 
t = it->t; 
bucket = it->bucket; 
b = it->bptr; 
i = it->i; 
check_bucket = it->check_bucket; 
#line 692 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
next: 
if ( b == nil ) { 
if ( it->done ) { 
#line 696 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
it->key = nil; 
it->value = nil; 
return; 
} 
if ( h->oldbuckets != nil && it->B == h->B ) { 
#line 705 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
oldbucket = bucket & ( ( ( uintptr ) 1 << ( it->B - 1 ) ) - 1 ) ; 
b = ( Bucket* ) ( h->oldbuckets + oldbucket * h->bucketsize ) ; 
if ( !evacuated ( b ) ) { 
check_bucket = bucket; 
} else { 
b = ( Bucket* ) ( it->buckets + bucket * h->bucketsize ) ; 
check_bucket = -1; 
} 
} else { 
b = ( Bucket* ) ( it->buckets + bucket * h->bucketsize ) ; 
check_bucket = -1; 
} 
bucket++; 
if ( bucket == ( ( uintptr ) 1 << it->B ) ) { 
bucket = 0; 
it->done = true; 
} 
i = 0; 
} 
for ( ; i < BUCKETSIZE; i++ ) { 
offi = ( i + it->offset ) & ( BUCKETSIZE - 1 ) ; 
k = ( byte* ) b->data + h->keysize * offi; 
v = ( byte* ) b->data + h->keysize * BUCKETSIZE + h->valuesize * offi; 
if ( b->tophash[offi] != Empty && b->tophash[offi] != EvacuatedEmpty ) { 
if ( check_bucket >= 0 ) { 
#line 737 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
t->key->alg->equal ( &eq , t->key->size , IK ( h , k ) , IK ( h , k ) ) ; 
if ( eq ) { 
#line 741 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
hash = h->hash0; 
t->key->alg->hash ( &hash , t->key->size , IK ( h , k ) ) ; 
if ( ( hash & ( ( ( uintptr ) 1 << it->B ) - 1 ) ) != check_bucket ) { 
continue; 
} 
} else { 
#line 754 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( check_bucket >> ( it->B - 1 ) != ( b->tophash[offi] & 1 ) ) { 
continue; 
} 
} 
} 
if ( b->tophash[offi] != EvacuatedX && b->tophash[offi] != EvacuatedY ) { 
#line 761 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
it->key = IK ( h , k ) ; 
it->value = IV ( h , v ) ; 
} else { 
#line 766 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
t->key->alg->equal ( &eq , t->key->size , IK ( h , k ) , IK ( h , k ) ) ; 
if ( eq ) { 
#line 773 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
rk = IK ( h , k ) ; 
rv = hash_lookup ( t , it->h , &rk ) ; 
if ( rv == nil ) 
continue; 
it->key = rk; 
it->value = rv; 
} else { 
#line 784 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
it->key = IK ( h , k ) ; 
it->value = IV ( h , v ) ; 
} 
} 
it->bucket = bucket; 
it->bptr = b; 
it->i = i + 1; 
it->check_bucket = check_bucket; 
return; 
} 
} 
b = b->overflow; 
i = 0; 
goto next; 
} 
void
reflect·ismapkey(Type* typ, bool ret)
{
	ret = 0;
	FLUSH(&ret);
#line 804 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	ret = typ != nil && typ->alg->hash != runtime·nohash;
	FLUSH(&ret);
}

#line 808 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
static Hmap* 
makemap_c ( MapType *typ , int64 hint ) 
{ 
Hmap *h; 
Type *key; 
#line 814 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
key = typ->key; 
#line 816 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( sizeof ( Hmap ) > 48 ) 
runtime·panicstring ( "hmap too large" ) ; 
#line 819 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( hint < 0 || ( int32 ) hint != hint ) 
runtime·panicstring ( "makemap: size out of range" ) ; 
#line 822 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( key->alg->hash == runtime·nohash ) 
runtime·throw ( "runtime.makemap: unsupported map key type" ) ; 
#line 825 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
h = runtime·cnew ( typ->hmap ) ; 
hash_init ( typ , h , hint ) ; 
#line 831 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
if ( debug ) { 
runtime·printf ( "makemap: map=%p; keysize=%p; valsize=%p; keyalg=%p; valalg=%p\n" , 
h , key->size , typ->elem->size , key->alg , typ->elem->alg ) ; 
} 
#line 836 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
return h; 
} 
void
runtime·makemap(MapType* typ, int64 hint, Hmap* ret)
{
	ret = 0;
	FLUSH(&ret);
#line 839 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	ret = makemap_c(typ, hint);
	FLUSH(&ret);
}
void
reflect·makemap(MapType* t, Hmap* ret)
{
	ret = 0;
	FLUSH(&ret);
#line 843 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	ret = makemap_c(t, 0);
	FLUSH(&ret);
}

#pragma textflag NOSPLIT
void
runtime·mapaccess1(MapType* t, Hmap* h, byte* key, byte* val)
{
	val = 0;
	FLUSH(&val);
#line 850 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	if(raceenabled && h != nil) {
		runtime·racereadpc(h, runtime·getcallerpc(&t), runtime·mapaccess1);
		runtime·racereadobjectpc(key, t->key, runtime·getcallerpc(&t), runtime·mapaccess1);
	}
	if(h == nil || h->count == 0) {
		val = t->elem->zero;
	} else {
		val = hash_lookup(t, h, &key);
		if(val == nil)
			val = t->elem->zero;
	}

	if(debug) {
		runtime·prints("runtime.mapaccess1: map=");
		runtime·printpointer(h);
		runtime·prints("; key=");
		t->key->alg->print(t->key->size, key);
		runtime·prints("; val=");
		t->elem->alg->print(t->elem->size, val);
		runtime·prints("\n");
	}
	FLUSH(&val);
}

#pragma textflag NOSPLIT
void
runtime·mapaccess2(MapType* t, Hmap* h, byte* key, byte* val, bool pres)
{
	val = 0;
	FLUSH(&val);
	pres = 0;
	FLUSH(&pres);
#line 877 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	if(raceenabled && h != nil) {
		runtime·racereadpc(h, runtime·getcallerpc(&t), runtime·mapaccess2);
		runtime·racereadobjectpc(key, t->key, runtime·getcallerpc(&t), runtime·mapaccess2);
	}

	if(h == nil || h->count == 0) {
		val = t->elem->zero;
		pres = false;
	} else {
		val = hash_lookup(t, h, &key);
		if(val == nil) {
			val = t->elem->zero;
			pres = false;
		} else {
			pres = true;
		}
	}

	if(debug) {
		runtime·prints("runtime.mapaccess2: map=");
		runtime·printpointer(h);
		runtime·prints("; key=");
		t->key->alg->print(t->key->size, key);
		runtime·prints("; val=");
		t->elem->alg->print(t->elem->size, val);
		runtime·prints("; pres=");
		runtime·printbool(pres);
		runtime·prints("\n");
	}
	FLUSH(&val);
	FLUSH(&pres);
}

#pragma textflag NOSPLIT
void
reflect·mapaccess(MapType* t, Hmap* h, byte* key, byte* val)
{
	val = 0;
	FLUSH(&val);
#line 910 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	if(h == nil)
		val = nil;
	else {
		if(raceenabled) {
			runtime·racereadpc(h, runtime·getcallerpc(&t), reflect·mapaccess);
			runtime·racereadobjectpc(key, t->key, runtime·getcallerpc(&t), reflect·mapaccess);
		}
		val = hash_lookup(t, h, &key);
	}
	FLUSH(&val);
}

#pragma textflag NOSPLIT
void
runtime·mapassign1(MapType* t, Hmap* h, byte* key, byte* val)
{
#line 923 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	if(h == nil)
		runtime·panicstring("assignment to entry in nil map");

	if(raceenabled) {
		runtime·racewritepc(h, runtime·getcallerpc(&t), runtime·mapassign1);
		runtime·racereadobjectpc(key, t->key, runtime·getcallerpc(&t), runtime·mapassign1);
		runtime·racereadobjectpc(val, t->elem, runtime·getcallerpc(&t), runtime·mapassign1);
	}

	hash_insert(t, h, key, val);

	if(debug) {
		runtime·prints("mapassign1: map=");
		runtime·printpointer(h);
		runtime·prints("; key=");
		t->key->alg->print(t->key->size, key);
		runtime·prints("; val=");
		t->elem->alg->print(t->elem->size, val);
		runtime·prints("\n");
	}
}

#pragma textflag NOSPLIT
void
runtime·mapdelete(MapType* t, Hmap* h, byte* key)
{
#line 947 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	if(h == nil)
		return;

	if(raceenabled) {
		runtime·racewritepc(h, runtime·getcallerpc(&t), runtime·mapdelete);
		runtime·racereadobjectpc(key, t->key, runtime·getcallerpc(&t), runtime·mapdelete);
	}

	hash_remove(t, h, key);

	if(debug) {
		runtime·prints("mapdelete: map=");
		runtime·printpointer(h);
		runtime·prints("; key=");
		t->key->alg->print(t->key->size, key);
		runtime·prints("\n");
	}
}

#pragma textflag NOSPLIT
void
reflect·mapassign(MapType* t, Hmap* h, byte* key, byte* val)
{
#line 968 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	if(h == nil)
		runtime·panicstring("assignment to entry in nil map");
	if(raceenabled) {
		runtime·racewritepc(h, runtime·getcallerpc(&t), reflect·mapassign);
		runtime·racereadobjectpc(key, t->key, runtime·getcallerpc(&t), reflect·mapassign);
		runtime·racereadobjectpc(val, t->elem, runtime·getcallerpc(&t), reflect·mapassign);
	}

	hash_insert(t, h, key, val);

	if(debug) {
		runtime·prints("mapassign: map=");
		runtime·printpointer(h);
		runtime·prints("; key=");
		t->key->alg->print(t->key->size, key);
		runtime·prints("; val=");
		t->elem->alg->print(t->elem->size, val);
		runtime·prints("\n");
	}
}

#pragma textflag NOSPLIT
void
reflect·mapdelete(MapType* t, Hmap* h, byte* key)
{
#line 991 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	if(h == nil)
		return; // see bug 8051
	if(raceenabled) {
		runtime·racewritepc(h, runtime·getcallerpc(&t), reflect·mapdelete);
		runtime·racereadobjectpc(key, t->key, runtime·getcallerpc(&t), reflect·mapdelete);
	}
	hash_remove(t, h, key);

	if(debug) {
		runtime·prints("mapdelete: map=");
		runtime·printpointer(h);
		runtime·prints("; key=");
		t->key->alg->print(t->key->size, key);
		runtime·prints("\n");
	}
}

#pragma textflag NOSPLIT
void
runtime·mapiterinit(MapType* t, Hmap* h, Hiter* it)
{
#line 1010 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	// Clear pointer fields so garbage collector does not complain.
	it->key = nil;
	it->value = nil;
	it->t = nil;
	it->h = nil;
	it->buckets = nil;
	it->bptr = nil;

	if(h == nil || h->count == 0) {
		it->key = nil;
		return;
	}
	if(raceenabled)
		runtime·racereadpc(h, runtime·getcallerpc(&t), runtime·mapiterinit);
	hash_iter_init(t, h, it);
	hash_next(it);
	if(debug) {
		runtime·prints("runtime.mapiterinit: map=");
		runtime·printpointer(h);
		runtime·prints("; iter=");
		runtime·printpointer(it);
		runtime·prints("; key=");
		runtime·printpointer(it->key);
		runtime·prints("\n");
	}
}
void
reflect·mapiterinit(MapType* t, Hmap* h, Hiter* it)
{
	it = 0;
	FLUSH(&it);
#line 1038 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	it = runtime·mal(sizeof *it);
	runtime·mapiterinit(t, h, it);
	FLUSH(&it);
}

#pragma textflag NOSPLIT
void
runtime·mapiternext(Hiter* it)
{
#line 1044 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	if(raceenabled)
		runtime·racereadpc(it->h, runtime·getcallerpc(&it), runtime·mapiternext);

	hash_next(it);
	if(debug) {
		runtime·prints("runtime.mapiternext: iter=");
		runtime·printpointer(it);
		runtime·prints("; key=");
		runtime·printpointer(it->key);
		runtime·prints("\n");
	}
}
void
reflect·mapiternext(Hiter* it)
{
#line 1058 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	runtime·mapiternext(it);
}
void
reflect·mapiterkey(Hiter* it, byte* key)
{
	key = 0;
	FLUSH(&key);
#line 1062 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	key = it->key;
	FLUSH(&key);
}

#pragma textflag NOSPLIT
void
reflect·maplen(Hmap* h, intgo len)
{
	len = 0;
	FLUSH(&len);
#line 1067 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"

	if(h == nil)
		len = 0;
	else {
		len = h->count;
		if(raceenabled)
			runtime·racereadpc(h, runtime·getcallerpc(&h), reflect·maplen);
	}
	FLUSH(&len);
}

#line 1078 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\hashmap.goc"
float64 runtime·hashLoad = LOAD; 