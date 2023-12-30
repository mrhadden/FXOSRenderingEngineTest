	.file	"winmain.c"
	.text
	.section	.text$_Z7sprintfPcPKcz,"x"
	.linkonce discard
	.globl	_Z7sprintfPcPKcz
	.def	_Z7sprintfPcPKcz;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z7sprintfPcPKcz
_Z7sprintfPcPKcz:
.LFB4439:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	movq	%rcx, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%r8, -32(%rbp)
	movq	%r9, -24(%rbp)
	leaq	-32(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %r8
	movq	%rax, %rdx
	movq	-48(%rbp), %rcx
	call	__mingw_vsprintf
	movl	%eax, %ebx
	movl	%ebx, %eax
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.globl	fillBackground
	.data
	.align 4
fillBackground:
	.long	1
	.globl	pguiEnv
	.bss
	.align 8
pguiEnv:
	.space 8
	.globl	chwnd
	.align 8
chwnd:
	.space 8
	.globl	debugOut
	.align 32
debugOut:
	.space 1024
	.globl	fApplyChrome
	.data
	.align 32
fApplyChrome:
	.quad	_Z14AddCloseGadgetP5HDC__P8_fx_rect
	.quad	_Z12AddMinGadgetP5HDC__P8_fx_rect
	.quad	_Z14AddTitleGadgetP5HDC__P8_fx_rect
	.quad	0
	.section .rdata,"dr"
.LC0:
	.ascii "Client Text\0"
	.text
	.globl	_Z10clientProcP5HDC__P8_fx_rect
	.def	_Z10clientProcP5HDC__P8_fx_rect;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z10clientProcP5HDC__P8_fx_rect
_Z10clientProcP5HDC__P8_fx_rect:
.LFB4474:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$80, %rsp
	.seh_stackalloc	80
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, -16(%rbp)
	movq	24(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rax, %rcx
	call	_Z9ToWinRECTP7tagRECTP8_fx_rect
	movl	$0, %edx
	movq	16(%rbp), %rcx
	movq	__imp_SetTextColor(%rip), %rax
	call	*%rax
	movl	$16777215, %edx
	movq	16(%rbp), %rcx
	movq	__imp_SetBkColor(%rip), %rax
	call	*%rax
	movq	-16(%rbp), %rax
	movq	%rax, %rcx
	call	strlen
	movl	%eax, %r8d
	movl	-28(%rbp), %eax
	leal	3(%rax), %ecx
	movl	-32(%rbp), %eax
	addl	$3, %eax
	movq	-16(%rbp), %rdx
	movl	%r8d, 32(%rsp)
	movq	%rdx, %r9
	movl	%ecx, %r8d
	movl	%eax, %edx
	movq	16(%rbp), %rcx
	movq	__imp_TextOutA(%rip), %rax
	call	*%rax
	movl	$0, -4(%rbp)
.L5:
	cmpl	$199, -4(%rbp)
	jg	.L6
	movl	-28(%rbp), %eax
	leal	33(%rax), %edx
	movl	-32(%rbp), %eax
	leal	3(%rax), %ecx
	movl	-4(%rbp), %eax
	addl	%ecx, %eax
	movl	$255, %r9d
	movl	%edx, %r8d
	movl	%eax, %edx
	movq	16(%rbp), %rcx
	movq	__imp_SetPixel(%rip), %rax
	call	*%rax
	addl	$1, -4(%rbp)
	jmp	.L5
.L6:
	nop
	addq	$80, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	fWndProcs
	.data
	.align 16
fWndProcs:
	.quad	_Z10clientProcP5HDC__P8_fx_rect
	.quad	0
	.section .rdata,"dr"
	.align 8
.LC1:
	.ascii "S\0a\0m\0p\0l\0e\0 \0W\0i\0n\0d\0o\0w\0 \0C\0l\0a\0s\0s\0\0\0"
.LC2:
	.ascii "wWinMain...\12\0"
.LC3:
	.ascii "CreateWindowEx...\12\0"
	.align 8
.LC4:
	.ascii "F\0X\0O\0S\0 \0R\0e\0n\0d\0e\0r\0 \0T\0e\0s\0t\0i\0n\0g\0\0\0"
.LC5:
	.ascii "GetMessage...\12\0"
	.text
	.globl	wWinMain
	.def	wWinMain;	.scl	2;	.type	32;	.endef
	.seh_proc	wWinMain
wWinMain:
.LFB4475:
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
	leaq	.LC1(%rip), %rax
	movq	%rax, -8(%rbp)
	leaq	.LC2(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
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
	leaq	_Z10WindowProcP6HWND__jyx(%rip), %rax
	movq	%rax, -88(%rbp)
	movq	16(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -32(%rbp)
	movl	$32512, %edx
	movl	$0, %ecx
	movq	__imp_LoadCursorW(%rip), %rax
	call	*%rax
	movq	%rax, -56(%rbp)
	movq	$1, -48(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	movq	__imp_RegisterClassW(%rip), %rax
	call	*%rax
	leaq	.LC3(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	call	_Z17InitUIEnvironmentv
	movq	%rax, pguiEnv(%rip)
	movq	-8(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	16(%rbp), %rdx
	movq	%rdx, 80(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 64(%rsp)
	movl	$500, 56(%rsp)
	movl	$500, 48(%rsp)
	movl	$-2147483648, 40(%rsp)
	movl	$-2147483648, 32(%rsp)
	movl	$13565952, %r9d
	leaq	.LC4(%rip), %r8
	movq	%rax, %rdx
	movl	$0, %ecx
	movq	__imp_CreateWindowExW(%rip), %rax
	call	*%rax
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L8
	movl	$0, %eax
	jmp	.L12
.L8:
	movq	-16(%rbp), %rax
	movq	%rax, chwnd(%rip)
	movl	40(%rbp), %edx
	movq	-16(%rbp), %rax
	movq	%rax, %rcx
	movq	__imp_ShowWindow(%rip), %rax
	call	*%rax
	leaq	.LC5(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	$0, -144(%rbp)
	movq	$0, -136(%rbp)
	movq	$0, -128(%rbp)
	movq	$0, -120(%rbp)
	movq	$0, -112(%rbp)
	movq	$0, -104(%rbp)
.L11:
	leaq	-144(%rbp), %rax
	movl	$0, %r9d
	movl	$0, %r8d
	movl	$0, %edx
	movq	%rax, %rcx
	movq	__imp_GetMessageW(%rip), %rax
	call	*%rax
	testl	%eax, %eax
	setg	%al
	testb	%al, %al
	je	.L10
	leaq	-144(%rbp), %rax
	movq	%rax, %rcx
	movq	__imp_TranslateMessage(%rip), %rax
	call	*%rax
	leaq	-144(%rbp), %rax
	movq	%rax, %rcx
	movq	__imp_DispatchMessageW(%rip), %rax
	call	*%rax
	jmp	.L11
.L10:
	movl	$0, %eax
.L12:
	addq	$240, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC6:
	.ascii "%s[%d]: %d %d %d %d\12\0"
	.text
	.globl	_Z9DebugNodeP4node
	.def	_Z9DebugNodeP4node;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z9DebugNodeP4node
_Z9DebugNodeP4node:
.LFB4476:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$80, %rsp
	.seh_stackalloc	80
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	20(%rax), %r8d
	movq	-8(%rbp), %rax
	movl	16(%rax), %ecx
	movq	-8(%rbp), %rax
	movl	12(%rax), %edx
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	movq	-8(%rbp), %r9
	movl	24(%r9), %r11d
	movq	-8(%rbp), %r9
	movq	(%r9), %r10
	movl	%r8d, 56(%rsp)
	movl	%ecx, 48(%rsp)
	movl	%edx, 40(%rsp)
	movl	%eax, 32(%rsp)
	movl	%r11d, %r9d
	movq	%r10, %r8
	leaq	.LC6(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
	leaq	debugOut(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	nop
	addq	$80, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z13__UnhighlightP4node
	.def	_Z13__UnhighlightP4node;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z13__UnhighlightP4node
_Z13__UnhighlightP4node:
.LFB4477:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 32(%rax)
	nop
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z11Unhighlightv
	.def	_Z11Unhighlightv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z11Unhighlightv
_Z11Unhighlightv:
.LFB4478:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	pguiEnv(%rip), %rax
	movq	8(%rax), %rax
	leaq	_Z13__UnhighlightP4node(%rip), %rdx
	movq	%rax, %rcx
	call	_Z9VisitListP9node_listPFvP4nodeE
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC7:
	.ascii "AddGRect...\12\0"
	.text
	.globl	_Z8AddGRectPKciiii
	.def	_Z8AddGRectPKciiii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z8AddGRectPKciiii
_Z8AddGRectPKciiii:
.LFB4479:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$80, %rsp
	.seh_stackalloc	80
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	%r9d, 40(%rbp)
	leaq	.LC7(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movl	40(%rbp), %r8d
	movl	32(%rbp), %ecx
	movl	24(%rbp), %eax
	movl	$2, 48(%rsp)
	movl	$-1, 40(%rsp)
	movl	48(%rbp), %edx
	movl	%edx, 32(%rsp)
	movl	%r8d, %r9d
	movl	%ecx, %r8d
	movl	%eax, %edx
	movq	16(%rbp), %rcx
	call	_Z11AllocRectExPKciiiili
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rcx
	call	strlen
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, 48(%rax)
	movq	-8(%rbp), %rax
	movl	$8224125, 28(%rax)
	movq	-8(%rbp), %rax
	movl	$15438388, 32(%rax)
	movq	-8(%rbp), %rax
	movl	36(%rax), %eax
	orb	$64, %ah
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, 36(%rax)
	movl	48(%rbp), %eax
	leal	-20(%rax), %edx
	movl	40(%rbp), %eax
	leal	-4(%rax), %r8d
	movl	32(%rbp), %eax
	leal	18(%rax), %ecx
	movl	24(%rbp), %eax
	addl	$2, %eax
	movl	$2, 48(%rsp)
	movl	$-1, 40(%rsp)
	movl	%edx, 32(%rsp)
	movl	%r8d, %r9d
	movl	%ecx, %r8d
	movl	%eax, %edx
	movq	16(%rbp), %rcx
	call	_Z11AllocRectExPKciiiili
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 56(%rax)
	movq	fWndProcs(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 64(%rax)
	call	_Z11Unhighlightv
	movq	pguiEnv(%rip), %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rax, %rcx
	call	_Z12ListAddStartP9node_listPv
	movq	pguiEnv(%rip), %rax
	movq	8(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rax, %rcx
	call	_Z10ListAddEndP9node_listPv
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	testq	%rax, %rax
	je	.L17
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	movl	36(%rax), %edx
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	orb	$64, %dh
	movl	%edx, 36(%rax)
.L17:
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 88(%rax)
	movq	-8(%rbp), %rax
	addq	$80, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z10RedrawRectP4node
	.def	_Z10RedrawRectP4node;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z10RedrawRectP4node
_Z10RedrawRectP4node:
.LFB4480:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$72, %rsp
	.seh_stackalloc	72
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	movq	%rcx, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movl	36(%rax), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L21
	movq	chwnd(%rip), %rax
	movq	%rax, %rcx
	movq	__imp_GetDC(%rip), %rax
	call	*%rax
	movq	%rax, -80(%rbp)
	movl	$0, %ecx
	movq	__imp_CreateSolidBrush(%rip), %rax
	call	*%rax
	movq	%rax, %rbx
	movq	-72(%rbp), %rdx
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	call	_Z9ToWinRECTP7tagRECTP8_fx_rect
	movq	%rax, %rdx
	movq	-80(%rbp), %rax
	movq	%rbx, %r8
	movq	%rax, %rcx
	movq	__imp_FillRect(%rip), %rax
	call	*%rax
	movq	chwnd(%rip), %rax
	movq	-80(%rbp), %rdx
	movq	%rax, %rcx
	movq	__imp_ReleaseDC(%rip), %rax
	call	*%rax
.L21:
	nop
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z13RedrawInvalidP4node
	.def	_Z13RedrawInvalidP4node;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z13RedrawInvalidP4node
_Z13RedrawInvalidP4node:
.LFB4481:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$72, %rsp
	.seh_stackalloc	72
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	movq	%rcx, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movl	36(%rax), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L24
	movq	-72(%rbp), %rax
	movl	36(%rax), %eax
	andl	$16384, %eax
	testl	%eax, %eax
	je	.L24
	movq	chwnd(%rip), %rax
	movq	%rax, %rcx
	movq	__imp_GetDC(%rip), %rax
	call	*%rax
	movq	%rax, -80(%rbp)
	movl	$4210752, %ecx
	movq	__imp_CreateSolidBrush(%rip), %rax
	call	*%rax
	movq	%rax, %rbx
	movq	-72(%rbp), %rdx
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	call	_Z9ToWinRECTP7tagRECTP8_fx_rect
	movq	%rax, %rdx
	movq	-80(%rbp), %rax
	movq	%rbx, %r8
	movq	%rax, %rcx
	movq	__imp_FillRect(%rip), %rax
	call	*%rax
	movq	chwnd(%rip), %rax
	movq	-80(%rbp), %rdx
	movq	%rax, %rcx
	movq	__imp_ReleaseDC(%rip), %rax
	call	*%rax
	movq	-72(%rbp), %rax
	movl	36(%rax), %eax
	andb	$-65, %ah
	movl	%eax, %edx
	movq	-72(%rbp), %rax
	movl	%edx, 36(%rax)
.L24:
	nop
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z12RedrawScreeni
	.def	_Z12RedrawScreeni;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z12RedrawScreeni
_Z12RedrawScreeni:
.LFB4482:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movq	chwnd(%rip), %rax
	movq	%rax, %rcx
	movq	__imp_GetDC(%rip), %rax
	call	*%rax
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L27
	movq	pguiEnv(%rip), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rcx
	call	_Z14DrawRectanglesP5HDC__P9node_list
	movq	chwnd(%rip), %rax
	movq	-8(%rbp), %rdx
	movq	%rax, %rcx
	movq	__imp_ReleaseDC(%rip), %rax
	call	*%rax
.L27:
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z14DrawRectanglesP5HDC__P9node_list
	.def	_Z14DrawRectanglesP5HDC__P9node_list;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z14DrawRectanglesP5HDC__P9node_list
_Z14DrawRectanglesP5HDC__P9node_list:
.LFB4483:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$88, %rsp
	.seh_stackalloc	88
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	movq	%rcx, -16(%rbp)
	movq	%rdx, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -56(%rbp)
.L36:
	cmpq	$0, -56(%rbp)
	je	.L38
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -72(%rbp)
	cmpq	$0, -72(%rbp)
	je	.L39
	movq	-72(%rbp), %rax
	movl	36(%rax), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L31
	movq	-72(%rbp), %rax
	movl	36(%rax), %eax
	andl	$16384, %eax
	testl	%eax, %eax
	je	.L31
	movq	-72(%rbp), %rax
	movl	32(%rax), %eax
	movl	%eax, %ecx
	movq	__imp_CreateSolidBrush(%rip), %rax
	call	*%rax
	movq	%rax, %rbx
	movq	-72(%rbp), %rdx
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	call	_Z9ToWinRECTP7tagRECTP8_fx_rect
	movq	%rbx, %r8
	movq	%rax, %rdx
	movq	-16(%rbp), %rcx
	movq	__imp_FillRect(%rip), %rax
	call	*%rax
	movl	$0, -60(%rbp)
.L33:
	movl	-60(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	fApplyChrome(%rip), %rax
	movq	(%rdx,%rax), %rax
	testq	%rax, %rax
	je	.L32
	movl	-60(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -60(%rbp)
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	fApplyChrome(%rip), %rax
	movq	(%rdx,%rax), %rax
	movq	-72(%rbp), %rdx
	movq	-16(%rbp), %rcx
	call	*%rax
	jmp	.L33
.L32:
	movq	-72(%rbp), %rax
	movq	56(%rax), %rax
	testq	%rax, %rax
	je	.L34
	movl	$16777215, %ecx
	movq	__imp_CreateSolidBrush(%rip), %rax
	call	*%rax
	movq	%rax, %rbx
	movq	-72(%rbp), %rax
	movq	56(%rax), %rdx
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	call	_Z9ToWinRECTP7tagRECTP8_fx_rect
	movq	%rbx, %r8
	movq	%rax, %rdx
	movq	-16(%rbp), %rcx
	movq	__imp_FillRect(%rip), %rax
	call	*%rax
	movq	-72(%rbp), %rax
	movq	64(%rax), %rax
	movq	%rax, %r8
	movq	-72(%rbp), %rax
	movq	56(%rax), %rax
	movq	%rax, %rdx
	movq	-16(%rbp), %rcx
	call	*%r8
.L34:
	movq	-72(%rbp), %rax
	movl	36(%rax), %eax
	andb	$-65, %ah
	movl	%eax, %edx
	movq	-72(%rbp), %rax
	movl	%edx, 36(%rax)
	jmp	.L35
.L31:
	movq	-72(%rbp), %rax
	movl	36(%rax), %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L35
	movq	-72(%rbp), %rax
	movl	32(%rax), %eax
	movl	%eax, %ecx
	movq	__imp_CreateSolidBrush(%rip), %rax
	call	*%rax
	movq	%rax, %rbx
	movq	-72(%rbp), %rdx
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	call	_Z9ToWinRECTP7tagRECTP8_fx_rect
	movq	%rbx, %r8
	movq	%rax, %rdx
	movq	-16(%rbp), %rcx
	movq	__imp_FillRect(%rip), %rax
	call	*%rax
	movq	-72(%rbp), %rax
	movl	36(%rax), %eax
	andb	$-33, %ah
	movl	%eax, %edx
	movq	-72(%rbp), %rax
	movl	%edx, 36(%rax)
.L35:
	movq	-56(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -56(%rbp)
	jmp	.L36
.L39:
	nop
.L38:
	nop
	addq	$88, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC8:
	.ascii "OnClick::GetSelectedRect...\12\0"
.LC9:
	.ascii "FX_LOST_FOCUS:\0"
.LC10:
	.ascii "FX_GOT_FOCUS: %s \12\0"
.LC11:
	.ascii "Overlaps currentFocus: %s\12\0"
.LC12:
	.ascii "OVERLAPS:\12\0"
.LC13:
	.ascii "\11Overlap: %s\12\0"
.LC14:
	.ascii "\11Intersecting: %s\12\0"
.LC15:
	.ascii "%s Still Has Focus.\12\0"
	.align 8
.LC16:
	.ascii "WM_LBUTTONDOWN x: %d y: %d %p \12\0"
	.text
	.globl	_Z7OnClickii
	.def	_Z7OnClickii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z7OnClickii
_Z7OnClickii:
.LFB4484:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$112, %rsp
	.seh_stackalloc	112
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	$0, -4(%rbp)
	movq	pguiEnv(%rip), %rax
	movq	8(%rax), %rax
	movl	24(%rbp), %edx
	movl	$2, %r9d
	movl	%edx, %r8d
	movl	16(%rbp), %edx
	movq	%rax, %rcx
	call	_Z15GetSelectedRectP9node_listiii
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	je	.L41
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	cmpq	%rax, -24(%rbp)
	je	.L41
	leaq	.LC8(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	testq	%rax, %rax
	je	.L42
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	cmpq	%rax, -24(%rbp)
	je	.L42
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rdx
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	movl	28(%rdx), %edx
	movl	%edx, 32(%rax)
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	movl	36(%rax), %edx
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	orb	$64, %dh
	movl	%edx, 36(%rax)
	leaq	.LC9(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	movq	(%rax), %rax
	movq	%rax, %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
.L42:
	movq	-24(%rbp), %rax
	movl	$15438388, 32(%rax)
	call	_Z9NextDepthv
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-24(%rbp), %rax
	movl	36(%rax), %eax
	orb	$64, %ah
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, 36(%rax)
	movq	pguiEnv(%rip), %rax
	movq	8(%rax), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	call	_Z10ListRemoveP9node_listPv
	movq	%rax, -32(%rbp)
	movq	pguiEnv(%rip), %rax
	movq	8(%rax), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	call	_Z10ListAddEndP9node_listPv
	movq	-32(%rbp), %rax
	movq	%rax, %rcx
	call	_Z11DeallocNodeP4node
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 88(%rax)
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	movq	(%rax), %rax
	movq	%rax, %r8
	leaq	.LC10(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
	leaq	debugOut(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	pguiEnv(%rip), %rax
	movq	32(%rax), %rax
	movq	%rax, %rcx
	call	_Z9ListClearP9node_list
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	movq	(%rax), %rax
	movq	%rax, %r8
	leaq	.LC11(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
	leaq	debugOut(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	pguiEnv(%rip), %rax
	movq	8(%rax), %rdx
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	movq	%rax, %rcx
	call	_Z17GetOverLappedRectP8_fx_rectP9node_list
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L43
	leaq	.LC12(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
.L47:
	cmpq	$0, -16(%rbp)
	je	.L44
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	cmpq	$0, -48(%rbp)
	je	.L45
	movq	-48(%rbp), %rax
	movl	36(%rax), %eax
	andl	$32768, %eax
	testl	%eax, %eax
	jne	.L45
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %r8
	leaq	.LC13(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
	leaq	debugOut(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	movq	-48(%rbp), %rdx
	movq	%rax, %rcx
	call	_Z12IntersectionP8_fx_rectS0_
	movq	%rax, -56(%rbp)
	cmpq	$0, -56(%rbp)
	je	.L45
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %r8
	leaq	.LC14(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
	leaq	debugOut(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	pguiEnv(%rip), %rax
	movq	32(%rax), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, %rcx
	call	_Z12ListAddStartP9node_listPv
.L45:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	jmp	.L47
.L44:
	movq	-40(%rbp), %rax
	movq	%rax, %rcx
	call	_Z11DeallocListP9node_list
.L43:
	movl	$1, -4(%rbp)
	jmp	.L48
.L41:
	cmpq	$0, -24(%rbp)
	je	.L48
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	cmpq	%rax, -24(%rbp)
	jne	.L48
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %r8
	leaq	.LC15(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
	leaq	debugOut(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
.L48:
	movl	24(%rbp), %edx
	movq	-24(%rbp), %rax
	movq	%rax, 32(%rsp)
	movl	%edx, %r9d
	movl	16(%rbp), %r8d
	leaq	.LC16(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
	movl	-4(%rbp), %eax
	addq	$112, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC17:
	.ascii "OnCtlClick::GetSelectedRect...\12\0"
	.align 8
.LC18:
	.ascii "OnCtlClick::FX_GOT_FOCUS: %s \12\0"
	.align 8
.LC19:
	.ascii "OnCtlClick::Overlaps currentFocus: %s\12\0"
.LC20:
	.ascii "OnCtlClick::OVERLAPS:\12\0"
	.align 8
.LC21:
	.ascii "WM_LBUTTONDOWN WITH CONTROL x: %d y: %d %p \12\0"
	.text
	.globl	_Z10OnCtlClickii
	.def	_Z10OnCtlClickii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z10OnCtlClickii
_Z10OnCtlClickii:
.LFB4485:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$112, %rsp
	.seh_stackalloc	112
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	$0, -4(%rbp)
	movq	pguiEnv(%rip), %rax
	movq	8(%rax), %rax
	movl	24(%rbp), %edx
	movl	$2, %r9d
	movl	%edx, %r8d
	movl	16(%rbp), %edx
	movq	%rax, %rcx
	call	_Z15GetSelectedRectP9node_listiii
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	je	.L51
	leaq	.LC17(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	testq	%rax, %rax
	je	.L52
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	cmpq	%rax, -24(%rbp)
	je	.L52
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rdx
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	movl	28(%rdx), %edx
	movl	%edx, 32(%rax)
	leaq	.LC9(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	movq	(%rax), %rax
	movq	%rax, %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
.L52:
	movq	-24(%rbp), %rax
	movl	36(%rax), %eax
	andl	$-3, %eax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, 36(%rax)
	movq	-24(%rbp), %rax
	movl	36(%rax), %eax
	orb	$32, %ah
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, 36(%rax)
	movq	-24(%rbp), %rax
	movl	$4210752, 32(%rax)
	movq	-24(%rbp), %rax
	movl	$0, 24(%rax)
	movq	pguiEnv(%rip), %rax
	movq	8(%rax), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	call	_Z10ListRemoveP9node_listPv
	movq	%rax, -32(%rbp)
	movq	pguiEnv(%rip), %rax
	movq	8(%rax), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	call	_Z12ListAddStartP9node_listPv
	movq	-32(%rbp), %rax
	movq	%rax, %rcx
	call	_Z11DeallocNodeP4node
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 88(%rax)
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	movq	(%rax), %rax
	movq	%rax, %r8
	leaq	.LC18(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
	leaq	debugOut(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	pguiEnv(%rip), %rax
	movq	32(%rax), %rax
	movq	%rax, %rcx
	call	_Z9ListClearP9node_list
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	movq	(%rax), %rax
	movq	%rax, %r8
	leaq	.LC19(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
	leaq	debugOut(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	pguiEnv(%rip), %rax
	movq	8(%rax), %rdx
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	movq	%rax, %rcx
	call	_Z17GetOverLappedRectP8_fx_rectP9node_list
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L53
	leaq	.LC20(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
.L57:
	cmpq	$0, -16(%rbp)
	je	.L54
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	cmpq	$0, -48(%rbp)
	je	.L55
	movq	-48(%rbp), %rax
	movl	36(%rax), %eax
	andl	$32768, %eax
	testl	%eax, %eax
	jne	.L55
	movq	-48(%rbp), %rax
	movl	36(%rax), %eax
	orb	$64, %ah
	movl	%eax, %edx
	movq	-48(%rbp), %rax
	movl	%edx, 36(%rax)
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %r8
	leaq	.LC13(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
	leaq	debugOut(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	88(%rax), %rax
	movq	-48(%rbp), %rdx
	movq	%rax, %rcx
	call	_Z12IntersectionP8_fx_rectS0_
	movq	%rax, -56(%rbp)
	cmpq	$0, -56(%rbp)
	je	.L55
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %r8
	leaq	.LC14(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
	leaq	debugOut(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movq	pguiEnv(%rip), %rax
	movq	32(%rax), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, %rcx
	call	_Z12ListAddStartP9node_listPv
.L55:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	jmp	.L57
.L54:
	movq	-40(%rbp), %rax
	movq	%rax, %rcx
	call	_Z11DeallocListP9node_list
.L53:
	movl	$1, -4(%rbp)
.L51:
	movl	24(%rbp), %edx
	movq	-24(%rbp), %rax
	movq	%rax, 32(%rsp)
	movl	%edx, %r9d
	movl	16(%rbp), %r8d
	leaq	.LC21(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
	movl	-4(%rbp), %eax
	addq	$112, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z6OnMoveii
	.def	_Z6OnMoveii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z6OnMoveii
_Z6OnMoveii:
.LFB4486:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	$0, -4(%rbp)
	movq	pguiEnv(%rip), %rax
	movq	8(%rax), %rax
	movl	24(%rbp), %edx
	movl	$-1, %r9d
	movl	%edx, %r8d
	movl	16(%rbp), %edx
	movq	%rax, %rcx
	call	_Z15GetSelectedRectP9node_listiii
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	je	.L60
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	96(%rax), %rax
	cmpq	%rax, -16(%rbp)
	je	.L60
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	96(%rax), %rax
	testq	%rax, %rax
	je	.L61
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	96(%rax), %rdx
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	96(%rax), %rax
	movl	28(%rdx), %edx
	movl	%edx, 32(%rax)
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	$0, 96(%rax)
.L61:
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 96(%rax)
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	96(%rax), %rax
	movl	$8421504, 32(%rax)
	movl	$1, -4(%rbp)
.L60:
	movl	-4(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC22:
	.ascii "LEFT SHIFT MOVE!\12\0"
.LC23:
	.ascii "WM_MOUSEMOVE x: %d y: %d\12\0"
.LC24:
	.ascii "LEFT CONTROL CLICK!\12\0"
.LC25:
	.ascii "LEFT SHIFT CLICK!\12\0"
.LC26:
	.ascii "RIGHT CONTROL CLICK!\12\0"
.LC27:
	.ascii "WM_RBUTTONDOWN x: %d y: %d\12\0"
.LC28:
	.ascii "WM_NCMOUSELEAVE x: %d y: %d\12\0"
	.text
	.globl	_Z10WindowProcP6HWND__jyx
	.def	_Z10WindowProcP6HWND__jyx;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z10WindowProcP6HWND__jyx
_Z10WindowProcP6HWND__jyx:
.LFB4487:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$192, %rsp
	.seh_stackalloc	192
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movq	%r8, 32(%rbp)
	movq	%r9, 40(%rbp)
	movl	24(%rbp), %eax
	cmpl	$20, %eax
	je	.L86
	cmpl	$20, %eax
	ja	.L66
	cmpl	$5, %eax
	je	.L87
	cmpl	$15, %eax
	je	.L68
	cmpl	$2, %eax
	je	.L69
	jmp	.L64
.L66:
	cmpl	$513, %eax
	je	.L70
	cmpl	$513, %eax
	ja	.L71
	cmpl	$512, %eax
	je	.L72
	jmp	.L64
.L71:
	cmpl	$516, %eax
	je	.L73
	cmpl	$674, %eax
	je	.L74
	jmp	.L64
.L69:
	movl	$0, %ecx
	movq	__imp_PostQuitMessage(%rip), %rax
	call	*%rax
	movl	$0, %eax
	jmp	.L75
.L68:
	leaq	-144(%rbp), %rax
	movq	%rax, %rdx
	movq	16(%rbp), %rcx
	movq	__imp_BeginPaint(%rip), %rax
	call	*%rax
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L76
	movl	$4210752, %ecx
	movq	__imp_CreateSolidBrush(%rip), %rax
	call	*%rax
	movq	%rax, %rcx
	leaq	-144(%rbp), %rax
	leaq	12(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rcx, %r8
	movq	%rax, %rcx
	movq	__imp_FillRect(%rip), %rax
	call	*%rax
	movq	pguiEnv(%rip), %rax
	movq	8(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rax, %rcx
	call	_Z14DrawRectanglesP5HDC__P9node_list
	leaq	-144(%rbp), %rax
	movq	%rax, %rdx
	movq	16(%rbp), %rcx
	movq	__imp_EndPaint(%rip), %rax
	call	*%rax
.L76:
	movl	$0, %eax
	jmp	.L75
.L72:
	movq	40(%rbp), %rax
	cwtl
	movl	%eax, -28(%rbp)
	movq	40(%rbp), %rax
	shrq	$16, %rax
	cwtl
	movl	%eax, -32(%rbp)
	movl	$16, %ecx
	movq	__imp_GetKeyState(%rip), %rax
	call	*%rax
	shrw	$15, %ax
	testb	%al, %al
	je	.L77
	leaq	.LC22(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	jmp	.L64
.L77:
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	96(%rax), %rax
	testq	%rax, %rax
	jne	.L79
	movl	-32(%rbp), %edx
	movl	-28(%rbp), %eax
	movl	%edx, %r9d
	movl	%eax, %r8d
	leaq	.LC23(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
.L79:
	movl	-32(%rbp), %edx
	movl	-28(%rbp), %eax
	movl	%eax, %ecx
	call	_Z6OnMoveii
	jmp	.L64
.L70:
	movq	40(%rbp), %rax
	cwtl
	movl	%eax, -20(%rbp)
	movq	40(%rbp), %rax
	shrq	$16, %rax
	cwtl
	movl	%eax, -24(%rbp)
	movl	$17, %ecx
	movq	__imp_GetKeyState(%rip), %rax
	call	*%rax
	shrw	$15, %ax
	testb	%al, %al
	je	.L80
	leaq	.LC24(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movl	-24(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %ecx
	call	_Z10OnCtlClickii
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L88
	movl	$0, %ecx
	call	_Z12RedrawScreeni
	jmp	.L88
.L80:
	movl	$16, %ecx
	movq	__imp_GetKeyState(%rip), %rax
	call	*%rax
	shrw	$15, %ax
	testb	%al, %al
	je	.L82
	leaq	.LC25(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	jmp	.L88
.L82:
	movl	-24(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %ecx
	call	_Z7OnClickii
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L88
	movl	$0, %ecx
	call	_Z12RedrawScreeni
	jmp	.L88
.L73:
	movq	40(%rbp), %rax
	cwtl
	movl	%eax, -12(%rbp)
	movq	40(%rbp), %rax
	shrq	$16, %rax
	cwtl
	movl	%eax, -16(%rbp)
	movl	$17, %ecx
	movq	__imp_GetKeyState(%rip), %rax
	call	*%rax
	shrw	$15, %ax
	testb	%al, %al
	je	.L83
	leaq	.LC26(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	movl	$1, %ecx
	call	_Z12RedrawScreeni
	jmp	.L64
.L83:
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %eax
	movl	$200, 32(%rsp)
	movl	$400, %r9d
	movl	%edx, %r8d
	movl	%eax, %edx
	movl	$0, %ecx
	call	_Z8AddGRectPKciiii
	movl	$1, %ecx
	call	_Z12RedrawScreeni
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %eax
	movl	%edx, %r9d
	movl	%eax, %r8d
	leaq	.LC27(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
	leaq	debugOut(%rip), %rcx
	movq	__imp_OutputDebugStringA(%rip), %rax
	call	*%rax
	jmp	.L64
.L74:
	movq	40(%rbp), %rax
	cwtl
	movl	%eax, -4(%rbp)
	movq	40(%rbp), %rax
	shrq	$16, %rax
	cwtl
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edx, %r9d
	movl	%eax, %r8d
	leaq	.LC28(%rip), %rdx
	leaq	debugOut(%rip), %rcx
	call	_Z7sprintfPcPKcz
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	96(%rax), %rax
	testq	%rax, %rax
	je	.L89
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	96(%rax), %rdx
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	96(%rax), %rax
	movl	28(%rdx), %edx
	movl	%edx, 32(%rax)
	movq	pguiEnv(%rip), %rax
	movq	40(%rax), %rax
	movq	$0, 96(%rax)
	jmp	.L89
.L86:
	nop
	jmp	.L64
.L87:
	nop
	jmp	.L64
.L88:
	nop
	jmp	.L64
.L89:
	nop
.L64:
	movq	40(%rbp), %rcx
	movq	32(%rbp), %rdx
	movl	24(%rbp), %eax
	movq	%rcx, %r9
	movq	%rdx, %r8
	movl	%eax, %edx
	movq	16(%rbp), %rcx
	movq	__imp_DefWindowProcW(%rip), %rax
	call	*%rax
.L75:
	addq	$192, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 7.3-win32 20180312"
	.def	__mingw_vsprintf;	.scl	2;	.type	32;	.endef
	.def	_Z14AddCloseGadgetP5HDC__P8_fx_rect;	.scl	2;	.type	32;	.endef
	.def	_Z12AddMinGadgetP5HDC__P8_fx_rect;	.scl	2;	.type	32;	.endef
	.def	_Z14AddTitleGadgetP5HDC__P8_fx_rect;	.scl	2;	.type	32;	.endef
	.def	_Z9ToWinRECTP7tagRECTP8_fx_rect;	.scl	2;	.type	32;	.endef
	.def	strlen;	.scl	2;	.type	32;	.endef
	.def	_Z17InitUIEnvironmentv;	.scl	2;	.type	32;	.endef
	.def	_Z9VisitListP9node_listPFvP4nodeE;	.scl	2;	.type	32;	.endef
	.def	_Z11AllocRectExPKciiiili;	.scl	2;	.type	32;	.endef
	.def	_Z12ListAddStartP9node_listPv;	.scl	2;	.type	32;	.endef
	.def	_Z10ListAddEndP9node_listPv;	.scl	2;	.type	32;	.endef
	.def	_Z15GetSelectedRectP9node_listiii;	.scl	2;	.type	32;	.endef
	.def	_Z9NextDepthv;	.scl	2;	.type	32;	.endef
	.def	_Z10ListRemoveP9node_listPv;	.scl	2;	.type	32;	.endef
	.def	_Z11DeallocNodeP4node;	.scl	2;	.type	32;	.endef
	.def	_Z9ListClearP9node_list;	.scl	2;	.type	32;	.endef
	.def	_Z17GetOverLappedRectP8_fx_rectP9node_list;	.scl	2;	.type	32;	.endef
	.def	_Z12IntersectionP8_fx_rectS0_;	.scl	2;	.type	32;	.endef
	.def	_Z11DeallocListP9node_list;	.scl	2;	.type	32;	.endef
