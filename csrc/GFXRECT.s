	.file	"GFXRECT.cpp"
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
	.globl	nextDepth
	.data
	.align 4
nextDepth:
	.long	1
	.globl	scaler
	.align 4
scaler:
	.long	1
	.text
	.globl	_Z9AllocRectPKciiii
	.def	_Z9AllocRectPKciiii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z9AllocRectPKciiii
_Z9AllocRectPKciiii:
.LFB4474:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	%r9d, 40(%rbp)
	movl	40(%rbp), %r8d
	movl	32(%rbp), %ecx
	movl	24(%rbp), %eax
	movl	$0, 48(%rsp)
	movl	$-1, 40(%rsp)
	movl	48(%rbp), %edx
	movl	%edx, 32(%rsp)
	movl	%r8d, %r9d
	movl	%ecx, %r8d
	movl	%eax, %edx
	movq	16(%rbp), %rcx
	call	_Z11AllocRectExPKciiiili
	addq	$64, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "P:%p\0"
	.text
	.globl	_Z11AllocRectExPKciiiili
	.def	_Z11AllocRectExPKciiiili;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z11AllocRectExPKciiiili
_Z11AllocRectExPKciiiili:
.LFB4475:
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
	movl	$56, %ecx
	call	malloc
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L6
	cmpq	$0, 16(%rbp)
	jne	.L7
	movl	$64, %ecx
	call	malloc
	movq	%rax, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %r8
	leaq	.LC0(%rip), %rdx
	movq	%rax, %rcx
	call	_Z7sprintfPcPKcz
	movq	-16(%rbp), %rax
	movq	%rax, 16(%rbp)
.L7:
	movq	-8(%rbp), %rax
	movq	16(%rbp), %rdx
	movq	%rdx, (%rax)
	movl	scaler(%rip), %eax
	imull	24(%rbp), %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, 8(%rax)
	movl	scaler(%rip), %eax
	imull	32(%rbp), %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, 12(%rax)
	movl	scaler(%rip), %eax
	imull	40(%rbp), %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, 16(%rax)
	movl	scaler(%rip), %eax
	imull	48(%rbp), %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, 20(%rax)
	cmpl	$-1, 56(%rbp)
	jne	.L8
	movl	nextDepth(%rip), %eax
	leal	1(%rax), %edx
	movl	%edx, nextDepth(%rip)
	movq	-8(%rbp), %rdx
	movl	%eax, 24(%rdx)
	jmp	.L9
.L8:
	movq	-8(%rbp), %rax
	movl	56(%rbp), %edx
	movl	%edx, 24(%rax)
.L9:
	movq	-8(%rbp), %rax
	movl	$0, 28(%rax)
	movq	-8(%rbp), %rax
	movl	64(%rbp), %edx
	movl	%edx, 32(%rax)
.L6:
	movq	-8(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 7.3-win32 20180312"
	.def	__mingw_vsprintf;	.scl	2;	.type	32;	.endef
	.def	malloc;	.scl	2;	.type	32;	.endef
