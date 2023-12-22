	.file	"GRECT.cpp"
	.text
	.globl	_ZN5GRECT9nextDepthE
	.data
	.align 4
_ZN5GRECT9nextDepthE:
	.long	1
	.globl	_ZN5GRECT6scalerE
	.align 4
_ZN5GRECT6scalerE:
	.long	1
	.text
	.align 2
	.globl	_ZN5GRECTC2EPKciiii
	.def	_ZN5GRECTC2EPKciiii;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN5GRECTC2EPKciiii
_ZN5GRECTC2EPKciiii:
.LFB4432:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	addq	$-128, %rsp
	.seh_stackalloc	128
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	%r9d, 40(%rbp)
	movq	16(%rbp), %rax
	movq	$0, (%rax)
	movq	16(%rbp), %rax
	movl	$0, 36(%rax)
	movq	16(%rbp), %rax
	movl	$0, 40(%rax)
	movq	16(%rbp), %rax
	movq	$0, 48(%rax)
	movl	40(%rbp), %r9d
	movl	32(%rbp), %r8d
	movq	24(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movl	$0, 56(%rsp)
	movl	$-1, 48(%rsp)
	movl	56(%rbp), %ecx
	movl	%ecx, 40(%rsp)
	movl	48(%rbp), %ecx
	movl	%ecx, 32(%rsp)
	movq	%rax, %rcx
	call	_ZN5GRECTC1EPKciiiili
	nop
	subq	$-128, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_ZN5GRECTC1EPKciiii
	.def	_ZN5GRECTC1EPKciiii;	.scl	2;	.type	32;	.endef
	.set	_ZN5GRECTC1EPKciiii,_ZN5GRECTC2EPKciiii
	.align 2
	.globl	_ZN5GRECTC2EPKciiiili
	.def	_ZN5GRECTC2EPKciiiili;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN5GRECTC2EPKciiiili
_ZN5GRECTC2EPKciiiili:
.LFB4435:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	%r9d, 40(%rbp)
	movq	16(%rbp), %rax
	movq	$0, (%rax)
	movq	16(%rbp), %rax
	movl	$0, 36(%rax)
	movq	16(%rbp), %rax
	movl	$0, 40(%rax)
	movq	16(%rbp), %rax
	movq	$0, 48(%rax)
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rdx, (%rax)
	movl	_ZN5GRECT6scalerE(%rip), %eax
	imull	32(%rbp), %eax
	movl	%eax, %edx
	movq	16(%rbp), %rax
	movl	%edx, 8(%rax)
	movl	_ZN5GRECT6scalerE(%rip), %eax
	imull	40(%rbp), %eax
	movl	%eax, %edx
	movq	16(%rbp), %rax
	movl	%edx, 12(%rax)
	movl	_ZN5GRECT6scalerE(%rip), %eax
	imull	48(%rbp), %eax
	movl	%eax, %edx
	movq	16(%rbp), %rax
	movl	%edx, 16(%rax)
	movl	_ZN5GRECT6scalerE(%rip), %eax
	imull	56(%rbp), %eax
	movl	%eax, %edx
	movq	16(%rbp), %rax
	movl	%edx, 20(%rax)
	cmpl	$-1, 64(%rbp)
	jne	.L3
	movl	_ZN5GRECT9nextDepthE(%rip), %eax
	leal	1(%rax), %edx
	movl	%edx, _ZN5GRECT9nextDepthE(%rip)
	movq	16(%rbp), %rdx
	movl	%eax, 24(%rdx)
	jmp	.L4
.L3:
	movq	16(%rbp), %rax
	movl	64(%rbp), %edx
	movl	%edx, 24(%rax)
.L4:
	movq	16(%rbp), %rax
	movl	$0, 28(%rax)
	movq	16(%rbp), %rax
	movl	72(%rbp), %edx
	movl	%edx, 32(%rax)
	nop
	popq	%rbp
	ret
	.seh_endproc
	.globl	_ZN5GRECTC1EPKciiiili
	.def	_ZN5GRECTC1EPKciiiili;	.scl	2;	.type	32;	.endef
	.set	_ZN5GRECTC1EPKciiiili,_ZN5GRECTC2EPKciiiili
	.ident	"GCC: (GNU) 7.3-win32 20180312"
