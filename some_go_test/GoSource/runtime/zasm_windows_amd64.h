// auto generated by go tool dist

#define	get_tls(r)	MOVQ TLS, r
#define	g(r)	0(r)(TLS*1)
#define	m(r)	8(r)(TLS*1)
#define const_Gidle 0
#define const_Grunnable 1
#define const_Grunning 2
#define const_Gsyscall 3
#define const_Gwaiting 4
#define const_Gmoribund_unused 5
#define const_Gdead 6
#define const_Pidle 0
#define const_Prunning 1
#define const_Psyscall 2
#define const_Pgcstop 3
#define const_Pdead 4
#define const_true 1
#define const_false 0
#define const_PtrSize 8
#define const_StackCacheSize 32
#define const_StackCacheBatch 16
#define const_sizeofLock 8
#define const_sizeofNote 8
#define const_sizeofString 16
#define const_sizeofFuncVal 8
#define const_sizeofIface 16
#define const_sizeofEface 16
#define const_sizeofComplex64 8
#define const_sizeofComplex128 16
#define const_sizeofSlice 24
#define const_sizeofGobuf 48
#define gobuf_sp 0
#define gobuf_pc 8
#define gobuf_g 16
#define gobuf_ctxt 24
#define gobuf_ret 32
#define gobuf_lr 40
#define const_sizeofGCStats 40
#define const_sizeofLibCall 48
#define libcall_fn 0
#define libcall_n 8
#define libcall_args 16
#define libcall_r1 24
#define libcall_r2 32
#define libcall_err 40
#define const_sizeofWinCallbackContext 32
#define cbctxt_gobody 0
#define cbctxt_argsize 8
#define cbctxt_restorestack 16
#define cbctxt_cleanstack 24
#define const_sizeofG 272
#define g_stackguard0 0
#define g_stackbase 8
#define g_panicwrap 16
#define g_defer 24
#define g_panic 32
#define g_sched 40
#define g_syscallstack 88
#define g_syscallsp 96
#define g_syscallpc 104
#define g_syscallguard 112
#define g_stackguard 120
#define g_stack0 128
#define g_stacksize 136
#define g_param 144
#define g_status 152
#define g_goid 160
#define g_waitsince 168
#define g_waitreason 176
#define g_schedlink 184
#define g_ispanic 192
#define g_issystem 193
#define g_isbackground 194
#define g_preempt 195
#define g_paniconfault 196
#define g_raceignore 197
#define g_m 200
#define g_lockedm 208
#define g_sig 216
#define g_writenbuf 220
#define g_writebuf 224
#define g_sigcode0 232
#define g_sigcode1 240
#define g_sigpc 248
#define g_gopc 256
#define g_racectx 264
#define g_end 272
#define const_sizeofM 1128
#define m_g0 0
#define m_moreargp 8
#define m_morebuf 16
#define m_moreframesize 64
#define m_moreargsize 68
#define m_cret 72
#define m_procid 80
#define m_gsignal 88
#define m_tls 96
#define m_mstartfn 128
#define m_curg 136
#define m_caughtsig 144
#define m_p 152
#define m_nextp 160
#define m_id 168
#define m_mallocing 172
#define m_throwing 176
#define m_gcing 180
#define m_locks 184
#define m_softfloat 188
#define m_dying 192
#define m_profilehz 196
#define m_helpgc 200
#define m_spinning 204
#define m_blocked 205
#define m_fastrand 208
#define m_ncgocall 216
#define m_ncgo 224
#define m_cgomal 232
#define m_park 240
#define m_alllink 248
#define m_schedlink 256
#define m_machport 264
#define m_mcache 272
#define m_stackinuse 280
#define m_stackcachepos 284
#define m_stackcachecnt 288
#define m_stackcache 296
#define m_lockedg 552
#define m_createstack 560
#define m_freglo 816
#define m_freghi 880
#define m_fflag 944
#define m_locked 948
#define m_nextwaitm 952
#define m_waitsema 960
#define m_waitsemacount 968
#define m_waitsemalock 972
#define m_gcstats 976
#define m_needextram 1016
#define m_traceback 1017
#define m_waitunlockf 1024
#define m_waitlock 1032
#define m_forkstackguard 1040
#define m_thread 1048
#define m_libcall 1056
#define m_libcallpc 1104
#define m_libcallsp 1112
#define m_libcallg 1120
#define m_end 1128
#define const_sizeofP 2240
#define p_key 0
#define p_id 8
#define p_status 12
#define p_link 16
#define p_schedtick 24
#define p_syscalltick 28
#define p_m 32
#define p_mcache 40
#define p_deferpool 48
#define p_goidcache 88
#define p_goidcacheend 96
#define p_runqhead 104
#define p_runqtail 108
#define p_runq 112
#define p_gfree 2160
#define p_gfreecnt 2168
#define p_pad 2172
#define const_LockExternal 1
#define const_LockInternal 2
#define const_sizeofStktop 88
#define const_sizeofSigTab 16
#define const_SigNotify 1
#define const_SigKill 2
#define const_SigThrow 4
#define const_SigPanic 8
#define const_SigDefault 16
#define const_SigHandling 32
#define const_SigIgnored 64
#define const_SigGoExit 128
#define const_sizeofFunc 40
#define const_sizeofItab 32
#define const_NaCl 0
#define const_Windows 1
#define const_Solaris 0
#define const_sizeofTimers 48
#define const_sizeofTimer 48
#define const_sizeofLFNode 16
#define const_sizeofParFor 104
#define const_sizeofCgoMal 16
#define const_sizeofDebugVars 24
#define const_Structrnd 8
#define const_AMEM 0
#define const_AMEM0 1
#define const_AMEM8 2
#define const_AMEM16 3
#define const_AMEM32 4
#define const_AMEM64 5
#define const_AMEM128 6
#define const_ANOEQ 7
#define const_ANOEQ0 8
#define const_ANOEQ8 9
#define const_ANOEQ16 10
#define const_ANOEQ32 11
#define const_ANOEQ64 12
#define const_ANOEQ128 13
#define const_ASTRING 14
#define const_AINTER 15
#define const_ANILINTER 16
#define const_ASLICE 17
#define const_AFLOAT32 18
#define const_AFLOAT64 19
#define const_ACPLX64 20
#define const_ACPLX128 21
#define const_Amax 22
#define const_sizeofAlg 32
#define const_HashRandomBytes 32
#define const_sizeofDefer 48
#define const_sizeofPanic 48
#define const_sizeofStkframe 72
#define const_TracebackMaxFrames 100
#define const_UseSpanType 1
#define const_thechar 54
#define const_BigEndian 0
#define const_CacheLineSize 64
#define const_RuntimeGogoBytes 80
#define const_PhysPageSize 4096
#define const_PCQuantum 1
#define const_PageShift 13
#define const_PageSize 8192
#define const_PageMask 8191
#define const_NumSizeClasses 67
#define const_MaxSmallSize 32768
#define const_TinySize 16
#define const_TinySizeClass 2
#define const_FixAllocChunk 16384
#define const_MaxMHeapList 128
#define const_HeapAllocChunk 1048576
#define const_MHeapMap_Bits 22
#define const_MaxGcproc 8
#define const_sizeofMLink 8
#define const_sizeofFixAlloc 64
#define const_sizeof_1_ 24
#define const_sizeofMStats 3856
#define const_sizeofMCacheList 16
#define const_sizeofMCache 2200
#define const_MTypes_Empty 0
#define const_MTypes_Single 1
#define const_MTypes_Words 2
#define const_MTypes_Bytes 3
#define const_sizeofMTypes 16
#define const_KindSpecialFinalizer 1
#define const_KindSpecialProfile 2
#define const_sizeofSpecial 16
#define const_sizeofSpecialFinalizer 48
#define const_sizeofSpecialProfile 24
#define const_MSpanInUse 0
#define const_MSpanFree 1
#define const_MSpanListHead 2
#define const_MSpanDead 3
#define const_sizeofMSpan 128
#define const_sizeofMCentral 280
#define const_sizeof_2_ 344
#define const_sizeofMHeap 56992
#define const_FlagNoScan 1
#define const_FlagNoProfiling 2
#define const_FlagNoGC 4
#define const_FlagNoZero 8
#define const_FlagNoInvokeGC 16
#define const_TypeInfo_SingleObject 0
#define const_TypeInfo_Array 1
#define const_TypeInfo_Chan 2
#define const_DebugTypeAtBlockEnd 0
#define const_sizeofBitVector 16
#define const_sizeofStackMap 8
#define const_BitsPerPointer 2
#define const_BitsDead 0
#define const_BitsScalar 1
#define const_BitsPointer 2
#define const_BitsMultiWord 3
#define const_BitsString 0
#define const_BitsSlice 1
#define const_BitsIface 2
#define const_BitsEface 3
#define const_StackSystem 4096
#define const_StackExtra 2048
#define const_StackMin 8192
#define const_StackSystemRounded 8192
#define const_FixedStack 16384
#define const_StackBig 4096
#define const_StackGuard 4352
#define const_StackSmall 128
#define const_StackLimit 128
#define const_StackTop 88
#define const_raceenabled 0
#define const_sizeofType 64
#define const_sizeofMethod 48
#define const_sizeofUncommonType 40
#define const_sizeofIMethod 24
#define const_sizeofInterfaceType 88
#define const_sizeofMapType 96
#define const_sizeofChanType 80
#define const_sizeofSliceType 72
#define const_sizeofFuncType 120
#define const_sizeofPtrType 72
#define const_sizeofSched 144
#define const_MaxGomaxprocs 256
#define const_GoidCacheBatch 16
#define const_sizeofCgoThreadStart 32
#define const_sizeof_3_ 824
#define const_sizeofPdesc 32
#define cb_max 2000
#define GOEXPERIMENT ""