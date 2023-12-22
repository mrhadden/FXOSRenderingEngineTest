	.file	"GRECTP.cpp"
	.text
	.align 2
	.globl	_ZN6GRECTPC2Eiiii
	.def	_ZN6GRECTPC2Eiiii;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN6GRECTPC2Eiiii
_ZN6GRECTPC2Eiiii:
.LFB4432:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	%r9d, 40(%rbp)
	leaq	-16(%rbp), %rax
	movq	%rax, %rcx
	call	_ZN6GRECTPC1Ev
	movq	16(%rbp), %rax
	movq	(%rax), %rax
	movl	24(%rbp), %edx
	movl	%edx, (%rax)
	movq	16(%rbp), %rax
	movq	(%rax), %rax
	movl	32(%rbp), %edx
	movl	%edx, 4(%rax)
	movq	16(%rbp), %rax
	movq	8(%rax), %rax
	movl	40(%rbp), %edx
	movl	%edx, (%rax)
	movq	16(%rbp), %rax
	movq	8(%rax), %rax
	movl	48(%rbp), %edx
	movl	%edx, 4(%rax)
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_ZN6GRECTPC1Eiiii
	.def	_ZN6GRECTPC1Eiiii;	.scl	2;	.type	32;	.endef
	.set	_ZN6GRECTPC1Eiiii,_ZN6GRECTPC2Eiiii
	.align 2
	.globl	_ZN6GRECTPC2Ev
	.def	_ZN6GRECTPC2Ev;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN6GRECTPC2Ev
_ZN6GRECTPC2Ev:
.LFB4435:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 32(%rbp)
	movl	$8, %ecx
.LEHB0:
	call	_Znwy
.LEHE0:
	movq	%rax, %rbx
	movl	$0, %r8d
	movl	$0, %edx
	movq	%rbx, %rcx
.LEHB1:
	call	_ZN5PointC1Eii
.LEHE1:
	movq	32(%rbp), %rax
	movq	%rbx, (%rax)
	movl	$8, %ecx
.LEHB2:
	call	_Znwy
.LEHE2:
	movq	%rax, %rbx
	movl	$0, %r8d
	movl	$0, %edx
	movq	%rbx, %rcx
.LEHB3:
	call	_ZN5PointC1Eii
.LEHE3:
	movq	32(%rbp), %rax
	movq	%rbx, 8(%rax)
	jmp	.L7
.L5:
	movq	%rax, %rsi
	movl	$8, %edx
	movq	%rbx, %rcx
	call	_ZdlPvy
	movq	%rsi, %rax
	movq	%rax, %rcx
.LEHB4:
	call	_Unwind_Resume
.L6:
	movq	%rax, %rsi
	movl	$8, %edx
	movq	%rbx, %rcx
	call	_ZdlPvy
	movq	%rsi, %rax
	movq	%rax, %rcx
	call	_Unwind_Resume
	nop
.LEHE4:
.L7:
	addq	$32, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rbp
	ret
	.def	__gxx_personality_seh0;	.scl	2;	.type	32;	.endef
	.seh_handler	__gxx_personality_seh0, @unwind, @except
	.seh_handlerdata
.LLSDA4435:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4435-.LLSDACSB4435
.LLSDACSB4435:
	.uleb128 .LEHB0-.LFB4435
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB4435
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L5-.LFB4435
	.uleb128 0
	.uleb128 .LEHB2-.LFB4435
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB3-.LFB4435
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L6-.LFB4435
	.uleb128 0
	.uleb128 .LEHB4-.LFB4435
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
.LLSDACSE4435:
	.text
	.seh_endproc
	.globl	_ZN6GRECTPC1Ev
	.def	_ZN6GRECTPC1Ev;	.scl	2;	.type	32;	.endef
	.set	_ZN6GRECTPC1Ev,_ZN6GRECTPC2Ev
	.align 2
	.globl	_ZN6GRECTP6toRECTEPc
	.def	_ZN6GRECTP6toRECTEPc;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN6GRECTP6toRECTEPc
_ZN6GRECTP6toRECTEPc:
.LFB4437:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 32(%rbp)
	movq	%rdx, 40(%rbp)
	movl	$56, %ecx
.LEHB5:
	call	_Znwy
.LEHE5:
	movq	%rax, %rbx
	movq	32(%rbp), %rax
	movq	8(%rax), %rax
	movl	4(%rax), %edx
	movq	32(%rbp), %rax
	movq	(%rax), %rax
	movl	4(%rax), %eax
	subl	%eax, %edx
	movl	%edx, %r9d
	movq	32(%rbp), %rax
	movq	8(%rax), %rax
	movl	(%rax), %edx
	movq	32(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %eax
	subl	%eax, %edx
	movl	%edx, %r8d
	movq	32(%rbp), %rax
	movq	(%rax), %rax
	movl	4(%rax), %ecx
	movq	32(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %edx
	movq	40(%rbp), %rax
	movl	%r9d, 40(%rsp)
	movl	%r8d, 32(%rsp)
	movl	%ecx, %r9d
	movl	%edx, %r8d
	movq	%rax, %rdx
	movq	%rbx, %rcx
.LEHB6:
	call	_ZN5GRECTC1EPKciiii
.LEHE6:
	movq	%rbx, %rax
	jmp	.L12
.L11:
	movq	%rax, %rsi
	movl	$56, %edx
	movq	%rbx, %rcx
	call	_ZdlPvy
	movq	%rsi, %rax
	movq	%rax, %rcx
.LEHB7:
	call	_Unwind_Resume
.LEHE7:
.L12:
	addq	$48, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rbp
	ret
	.seh_handler	__gxx_personality_seh0, @unwind, @except
	.seh_handlerdata
.LLSDA4437:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4437-.LLSDACSB4437
.LLSDACSB4437:
	.uleb128 .LEHB5-.LFB4437
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB6-.LFB4437
	.uleb128 .LEHE6-.LEHB6
	.uleb128 .L11-.LFB4437
	.uleb128 0
	.uleb128 .LEHB7-.LFB4437
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
.LLSDACSE4437:
	.text
	.seh_endproc
	.align 2
	.globl	_ZN6GRECTP7toRECTPEP5GRECT
	.def	_ZN6GRECTP7toRECTPEP5GRECT;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN6GRECTP7toRECTPEP5GRECT
_ZN6GRECTP7toRECTPEP5GRECT:
.LFB4438:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 32(%rbp)
	movl	$16, %ecx
.LEHB8:
	call	_Znwy
.LEHE8:
	movq	%rax, %rbx
	movq	32(%rbp), %rax
	movl	12(%rax), %edx
	movq	32(%rbp), %rax
	movl	20(%rax), %eax
	leal	(%rdx,%rax), %ecx
	movq	32(%rbp), %rax
	movl	8(%rax), %edx
	movq	32(%rbp), %rax
	movl	16(%rax), %eax
	leal	(%rdx,%rax), %r8d
	movq	32(%rbp), %rax
	movl	12(%rax), %edx
	movq	32(%rbp), %rax
	movl	8(%rax), %eax
	movl	%ecx, 32(%rsp)
	movl	%r8d, %r9d
	movl	%edx, %r8d
	movl	%eax, %edx
	movq	%rbx, %rcx
.LEHB9:
	call	_ZN6GRECTPC1Eiiii
.LEHE9:
	movq	%rbx, %rax
	jmp	.L17
.L16:
	movq	%rax, %rsi
	movl	$16, %edx
	movq	%rbx, %rcx
	call	_ZdlPvy
	movq	%rsi, %rax
	movq	%rax, %rcx
.LEHB10:
	call	_Unwind_Resume
.LEHE10:
.L17:
	addq	$48, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rbp
	ret
	.seh_handler	__gxx_personality_seh0, @unwind, @except
	.seh_handlerdata
.LLSDA4438:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4438-.LLSDACSB4438
.LLSDACSB4438:
	.uleb128 .LEHB8-.LFB4438
	.uleb128 .LEHE8-.LEHB8
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB9-.LFB4438
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L16-.LFB4438
	.uleb128 0
	.uleb128 .LEHB10-.LFB4438
	.uleb128 .LEHE10-.LEHB10
	.uleb128 0
	.uleb128 0
.LLSDACSE4438:
	.text
	.seh_endproc
	.ident	"GCC: (GNU) 7.3-win32 20180312"
	.def	_Znwy;	.scl	2;	.type	32;	.endef
	.def	_ZN5PointC1Eii;	.scl	2;	.type	32;	.endef
	.def	_ZdlPvy;	.scl	2;	.type	32;	.endef
	.def	_Unwind_Resume;	.scl	2;	.type	32;	.endef
	.def	_ZN5GRECTC1EPKciiii;	.scl	2;	.type	32;	.endef
