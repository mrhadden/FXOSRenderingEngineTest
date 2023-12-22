	.file	"Point.cpp"
	.text
	.globl	_Z10AllocPointii
	.def	_Z10AllocPointii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z10AllocPointii
_Z10AllocPointii:
.LFB55:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	$8, %ecx
	call	malloc
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L2
	movq	-8(%rbp), %rax
	movl	$8, %r8d
	movl	$0, %edx
	movq	%rax, %rcx
	call	memset
	movq	-8(%rbp), %rax
	movl	16(%rbp), %edx
	movl	%edx, (%rax)
	movq	-8(%rbp), %rax
	movl	24(%rbp), %edx
	movl	%edx, 4(%rax)
.L2:
	movq	-8(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 7.3-win32 20180312"
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	memset;	.scl	2;	.type	32;	.endef
