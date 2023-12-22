	.file	"winmain.c"
	.text
	.section .rdata,"dr"
	.align 8
.LC0:
	.ascii "S\0a\0m\0p\0l\0e\0 \0W\0i\0n\0d\0o\0w\0 \0C\0l\0a\0s\0s\0\0\0"
.LC1:
	.ascii "My output string.\12\0"
	.align 8
.LC2:
	.ascii "M\0y\0 \0o\0u\0t\0p\0u\0t\0 \0s\0t\0r\0i\0n\0g\0 \0U\0N\0I\0C\0O\0D\0E\0.\0\12\0\0\0"
	.align 8
.LC3:
	.ascii "L\0e\0a\0r\0n\0 \0t\0o\0 \0P\0r\0o\0g\0r\0a\0m\0 \0W\0i\0n\0d\0o\0w\0s\0\0\0"
	.text
	.globl	wWinMain
	.def	wWinMain;	.scl	2;	.type	32;	.endef
	.seh_proc	wWinMain
wWinMain:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$240, %rsp
	.seh_stackalloc	240
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	%r8, 32(%rbp)
	movl	%r9d, 40(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, -8(%rbp)
	leaq	.LC1(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	leaq	.LC2(%rip), %rcx
	movq	__imp_OutputDebugStringW(%rip), %rax
	call	*%rax
	movq	$0, -96(%rbp)
	movq	$0, -88(%rbp)
	movq	$0, -80(%rbp)
	movq	$0, -72(%rbp)
	movq	$0, -64(%rbp)
	movq	$0, -56(%rbp)
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -32(%rbp)
	leaq	WindowProc(%rip), %rax
	movq	%rax, -88(%rbp)
	movq	16(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -32(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	movq	__imp_RegisterClassW(%rip), %rax
	call	*%rax
	movq	-8(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	16(%rbp), %rdx
	movq	%rdx, 80(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 64(%rsp)
	movl	$-2147483648, 56(%rsp)
	movl	$-2147483648, 48(%rsp)
	movl	$-2147483648, 40(%rsp)
	movl	$-2147483648, 32(%rsp)
	movl	$13565952, %r9d
	leaq	.LC3(%rip), %r8
	movq	%rax, %rdx
	movl	$0, %ecx
	movq	__imp_CreateWindowExW(%rip), %rax
	call	*%rax
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L2
	movl	$0, %eax
	jmp	.L6
.L2:
	movl	40(%rbp), %edx
	movq	-16(%rbp), %rax
	movq	%rax, %rcx
	movq	__imp_ShowWindow(%rip), %rax
	call	*%rax
	movq	$0, -144(%rbp)
	movq	$0, -136(%rbp)
	movq	$0, -128(%rbp)
	movq	$0, -120(%rbp)
	movq	$0, -112(%rbp)
	movq	$0, -104(%rbp)
	jmp	.L4
.L5:
	leaq	-144(%rbp), %rax
	movq	%rax, %rcx
	movq	__imp_TranslateMessage(%rip), %rax
	call	*%rax
	leaq	-144(%rbp), %rax
	movq	%rax, %rcx
	movq	__imp_DispatchMessageW(%rip), %rax
	call	*%rax
.L4:
	leaq	-144(%rbp), %rax
	movl	$0, %r9d
	movl	$0, %r8d
	movl	$0, %edx
	movq	%rax, %rcx
	movq	__imp_GetMessageW(%rip), %rax
	call	*%rax
	testl	%eax, %eax
	jg	.L5
	movl	$0, %eax
.L6:
	addq	$240, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC4:
	.ascii "top: %d left: %d bottom: %d right: %d\12\0"
	.text
	.globl	WindowProc
	.def	WindowProc;	.scl	2;	.type	32;	.endef
	.seh_proc	WindowProc
WindowProc:
	pushq	%rbp
	.seh_pushreg	%rbp
	subq	$672, %rsp
	.seh_stackalloc	672
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	movq	%rcx, 560(%rbp)
	movl	%edx, 568(%rbp)
	movq	%r8, 576(%rbp)
	movq	%r9, 584(%rbp)
	movl	568(%rbp), %eax
	cmpl	$2, %eax
	je	.L9
	cmpl	$15, %eax
	je	.L10
	jmp	.L13
.L9:
	movl	$0, %ecx
	movq	__imp_PostQuitMessage(%rip), %rax
	call	*%rax
	movl	$0, %eax
	jmp	.L12
.L10:
	leaq	-80(%rbp), %rax
	movq	%rax, %rdx
	movq	560(%rbp), %rcx
	movq	__imp_BeginPaint(%rip), %rax
	call	*%rax
	movq	%rax, 536(%rbp)
	movl	-60(%rbp), %ecx
	movl	-56(%rbp), %edx
	movl	-68(%rbp), %r9d
	movl	-64(%rbp), %r8d
	leaq	16(%rbp), %rax
	movl	%ecx, 40(%rsp)
	movl	%edx, 32(%rsp)
	leaq	.LC4(%rip), %rdx
	movq	%rax, %rcx
	call	sprintf
	leaq	16(%rbp), %rax
	movq	%rax, %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	leaq	-80(%rbp), %rax
	leaq	12(%rax), %rdx
	movq	536(%rbp), %rax
	movl	$6, %r8d
	movq	%rax, %rcx
	movq	__imp_FillRect(%rip), %rax
	call	*%rax
	movl	$10, 4(%rbp)
	movl	$10, 0(%rbp)
	movl	$100, 8(%rbp)
	movl	$100, 12(%rbp)
	movq	%rbp, %rdx
	movq	536(%rbp), %rax
	movl	$7, %r8d
	movq	%rax, %rcx
	movq	__imp_FillRect(%rip), %rax
	call	*%rax
	leaq	-80(%rbp), %rax
	movq	%rax, %rdx
	movq	560(%rbp), %rcx
	movq	__imp_EndPaint(%rip), %rax
	call	*%rax
	movl	$0, %eax
	jmp	.L12
.L13:
	movq	584(%rbp), %rcx
	movq	576(%rbp), %rdx
	movl	568(%rbp), %eax
	movq	%rcx, %r9
	movq	%rdx, %r8
	movl	%eax, %edx
	movq	560(%rbp), %rcx
	movq	__imp_DefWindowProcW(%rip), %rax
	call	*%rax
.L12:
	addq	$672, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 7.3-win32 20180312"
	.def	sprintf;	.scl	2;	.type	32;	.endef
