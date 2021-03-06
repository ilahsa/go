// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// +build ignore

/*
Input to cgo.

GOARCH=amd64 go tool cgo -cdefs defs_windows.go > defs_windows_amd64.h
GOARCH=386 go tool cgo -cdefs defs_windows.go > defs_windows_386.h
*/

package runtime

/*
#include <signal.h>
#include <stdarg.h>
#include <windef.h>
#include <winbase.h>
#include <wincon.h>

#ifndef _X86_
typedef struct {} FLOATING_SAVE_AREA;
#endif
#ifndef _AMD64_
typedef struct {} M128A;
#endif
*/
import "C"

const (
	PROT_NONE  = 0
	PROT_READ  = 1
	PROT_WRITE = 2
	PROT_EXEC  = 4

	MAP_ANON    = 1
	MAP_PRIVATE = 2

	DUPLICATE_SAME_ACCESS   = C.DUPLICATE_SAME_ACCESS
	THREAD_PRIORITY_HIGHEST = C.THREAD_PRIORITY_HIGHEST

	SIGINT           = C.SIGINT
	CTRL_C_EVENT     = C.CTRL_C_EVENT
	CTRL_BREAK_EVENT = C.CTRL_BREAK_EVENT

	CONTEXT_CONTROL = C.CONTEXT_CONTROL
	CONTEXT_FULL    = C.CONTEXT_FULL

	EXCEPTION_ACCESS_VIOLATION     = C.STATUS_ACCESS_VIOLATION
	EXCEPTION_BREAKPOINT           = C.STATUS_BREAKPOINT
	EXCEPTION_FLT_DENORMAL_OPERAND = C.STATUS_FLOAT_DENORMAL_OPERAND
	EXCEPTION_FLT_DIVIDE_BY_ZERO   = C.STATUS_FLOAT_DIVIDE_BY_ZERO
	EXCEPTION_FLT_INEXACT_RESULT   = C.STATUS_FLOAT_INEXACT_RESULT
	EXCEPTION_FLT_OVERFLOW         = C.STATUS_FLOAT_OVERFLOW
	EXCEPTION_FLT_UNDERFLOW        = C.STATUS_FLOAT_UNDERFLOW
	EXCEPTION_INT_DIVIDE_BY_ZERO   = C.STATUS_INTEGER_DIVIDE_BY_ZERO
	EXCEPTION_INT_OVERFLOW         = C.STATUS_INTEGER_OVERFLOW

	INFINITE     = C.INFINITE
	WAIT_TIMEOUT = C.WAIT_TIMEOUT
)

type SystemInfo C.SYSTEM_INFO
type ExceptionRecord C.EXCEPTION_RECORD
type FloatingSaveArea C.FLOATING_SAVE_AREA
type M128a C.M128A
type Context C.CONTEXT
type Overlapped C.OVERLAPPED
