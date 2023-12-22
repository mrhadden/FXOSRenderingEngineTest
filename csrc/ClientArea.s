	.file	"ClientArea.cpp"
	.text
	.align 2
	.globl	_ZN10ClientArea13MakeChildNameEPKcS1_
	.def	_ZN10ClientArea13MakeChildNameEPKcS1_;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN10ClientArea13MakeChildNameEPKcS1_
_ZN10ClientArea13MakeChildNameEPKcS1_:
.LFB4431:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movl	$1, %ecx
	call	_Znwy
	movb	$-128, (%rax)
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	16(%rbp), %r8
	movl	$64, %edx
	movq	%rax, %rcx
	movq	__imp_strcpy_s(%rip), %rax
	call	*%rax
	movq	24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %r8
	movl	$64, %edx
	movq	%rax, %rcx
	movq	__imp_strcat_s(%rip), %rax
	call	*%rax
	movq	-8(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "-child\0"
	.text
	.align 2
	.globl	_ZN10ClientAreaC2EP5GRECTPKciiii
	.def	_ZN10ClientAreaC2EP5GRECTPKciiii;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN10ClientAreaC2EP5GRECTPKciiii
_ZN10ClientAreaC2EP5GRECTPKciiii:
.LFB4433:
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
	movl	%r9d, -24(%rbp)
	movq	-48(%rbp), %rbx
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	leaq	.LC0(%rip), %rdx
	movq	%rax, %rcx
	call	_ZN10ClientArea13MakeChildNameEPKcS1_
	movq	%rax, %r10
	movl	-16(%rbp), %ecx
	movl	-24(%rbp), %edx
	movl	0(%rbp), %eax
	movl	%eax, 40(%rsp)
	movl	-8(%rbp), %eax
	movl	%eax, 32(%rsp)
	movl	%ecx, %r9d
	movl	%edx, %r8d
	movq	%r10, %rdx
	movq	%rbx, %rcx
	call	_ZN5GRECTC2EPKciiii
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 56(%rax)
	nop
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.globl	_ZN10ClientAreaC1EP5GRECTPKciiii
	.def	_ZN10ClientAreaC1EP5GRECTPKciiii;	.scl	2;	.type	32;	.endef
	.set	_ZN10ClientAreaC1EP5GRECTPKciiii,_ZN10ClientAreaC2EP5GRECTPKciiii
	.ident	"GCC: (GNU) 7.3-win32 20180312"
	.def	_Znwy;	.scl	2;	.type	32;	.endef
	.def	_ZN5GRECTC2EPKciiii;	.scl	2;	.type	32;	.endef
