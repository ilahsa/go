// auto generated by go tool dist
// goos=windows goarch=amd64


#include "runtime.h"
#include "os_GOOS.h"
#include "cgocall.h"
void
syscall·loadlibrary(uint16* filename, uintptr handle, uintptr err)
{
	handle = 0;
	FLUSH(&handle);
	err = 0;
	FLUSH(&err);
#line 10 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\syscall_windows.goc"

	LibCall c;

	c.fn = runtime·LoadLibrary;
	c.n = 1;
	c.args = &filename;
	runtime·cgocall(runtime·asmstdcall, &c);
	handle = c.r1;
	if(handle == 0)
		err = c.err;
	else
		err = 0;
	FLUSH(&handle);
	FLUSH(&err);
}
void
syscall·getprocaddress(uintptr handle, uint8* procname, uintptr proc, uintptr err)
{
	proc = 0;
	FLUSH(&proc);
	err = 0;
	FLUSH(&err);
#line 24 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\syscall_windows.goc"

	LibCall c;

	USED(procname);
	c.fn = runtime·GetProcAddress;
	c.n = 2;
	c.args = &handle;
	runtime·cgocall(runtime·asmstdcall, &c);
	proc = c.r1;
	if(proc == 0)
		err = c.err;
	else
		err = 0;
	FLUSH(&proc);
	FLUSH(&err);
}
void
syscall·NewCallback(Eface fn, uintptr code)
{
	code = 0;
	FLUSH(&code);
#line 39 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\syscall_windows.goc"

	code = (uintptr)runtime·compilecallback(fn, true);
	FLUSH(&code);
}
void
syscall·NewCallbackCDecl(Eface fn, uintptr code)
{
	code = 0;
	FLUSH(&code);
#line 43 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\syscall_windows.goc"

	code = (uintptr)runtime·compilecallback(fn, false);
	FLUSH(&code);
}
void
syscall·Syscall(uintptr fn, uintptr nargs, uintptr a1, uintptr a2, uintptr a3, uintptr r1, uintptr r2, uintptr err)
{
	r1 = 0;
	FLUSH(&r1);
	r2 = 0;
	FLUSH(&r2);
	err = 0;
	FLUSH(&err);
#line 47 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\syscall_windows.goc"

	LibCall c;

	USED(a2);
	USED(a3);
	c.fn = (void*)fn;
	c.n = nargs;
	c.args = &a1;
	runtime·cgocall(runtime·asmstdcall, &c);
	err = c.err;
	r1 = c.r1;
	r2 = c.r2;
	FLUSH(&r1);
	FLUSH(&r2);
	FLUSH(&err);
}
void
syscall·Syscall6(uintptr fn, uintptr nargs, uintptr a1, uintptr a2, uintptr a3, uintptr a4, uintptr a5, uintptr a6, uintptr r1, uintptr r2, uintptr err)
{
	r1 = 0;
	FLUSH(&r1);
	r2 = 0;
	FLUSH(&r2);
	err = 0;
	FLUSH(&err);
#line 61 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\syscall_windows.goc"

	LibCall c;

	USED(a2);
	USED(a3);
	USED(a4);
	USED(a5);
	USED(a6);
	c.fn = (void*)fn;
	c.n = nargs;
	c.args = &a1;
	runtime·cgocall(runtime·asmstdcall, &c);
	err = c.err;
	r1 = c.r1;
	r2 = c.r2;
	FLUSH(&r1);
	FLUSH(&r2);
	FLUSH(&err);
}
void
syscall·Syscall9(uintptr fn, uintptr nargs, uintptr a1, uintptr a2, uintptr a3, uintptr a4, uintptr a5, uintptr a6, uintptr a7, uintptr a8, uintptr a9, uintptr r1, uintptr r2, uintptr err)
{
	r1 = 0;
	FLUSH(&r1);
	r2 = 0;
	FLUSH(&r2);
	err = 0;
	FLUSH(&err);
#line 78 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\syscall_windows.goc"

	LibCall c;

	USED(a2);
	USED(a3);
	USED(a4);
	USED(a5);
	USED(a6);
	USED(a7);
	USED(a8);
	USED(a9);
	c.fn = (void*)fn;
	c.n = nargs;
	c.args = &a1;
	runtime·cgocall(runtime·asmstdcall, &c);
	err = c.err;
	r1 = c.r1;
	r2 = c.r2;
	FLUSH(&r1);
	FLUSH(&r2);
	FLUSH(&err);
}
void
syscall·Syscall12(uintptr fn, uintptr nargs, uintptr a1, uintptr a2, uintptr a3, uintptr a4, uintptr a5, uintptr a6, uintptr a7, uintptr a8, uintptr a9, uintptr a10, uintptr a11, uintptr a12, uintptr r1, uintptr r2, uintptr err)
{
	r1 = 0;
	FLUSH(&r1);
	r2 = 0;
	FLUSH(&r2);
	err = 0;
	FLUSH(&err);
#line 98 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\syscall_windows.goc"

	LibCall c;

	USED(a2);
	USED(a3);
	USED(a4);
	USED(a5);
	USED(a6);
	USED(a7);
	USED(a8);
	USED(a9);
	USED(a10);
	USED(a11);
	USED(a12);
	c.fn = (void*)fn;
	c.n = nargs;
	c.args = &a1;
	runtime·cgocall(runtime·asmstdcall, &c);
	err = c.err;
	r1 = c.r1;
	r2 = c.r2;
	FLUSH(&r1);
	FLUSH(&r2);
	FLUSH(&err);
}
void
syscall·Syscall15(uintptr fn, uintptr nargs, uintptr a1, uintptr a2, uintptr a3, uintptr a4, uintptr a5, uintptr a6, uintptr a7, uintptr a8, uintptr a9, uintptr a10, uintptr a11, uintptr a12, uintptr a13, uintptr a14, uintptr a15, uintptr r1, uintptr r2, uintptr err)
{
	r1 = 0;
	FLUSH(&r1);
	r2 = 0;
	FLUSH(&r2);
	err = 0;
	FLUSH(&err);
#line 121 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\syscall_windows.goc"

	LibCall c;

	USED(a2);
	USED(a3);
	USED(a4);
	USED(a5);
	USED(a6);
	USED(a7);
	USED(a8);
	USED(a9);
	USED(a10);
	USED(a11);
	USED(a12);
	USED(a13);
	USED(a14);
	USED(a15);
	c.fn = (void*)fn;
	c.n = nargs;
	c.args = &a1;
	runtime·cgocall(runtime·asmstdcall, &c);
	err = c.err;
	r1 = c.r1;
	r2 = c.r2;
	FLUSH(&r1);
	FLUSH(&r2);
	FLUSH(&err);
}
