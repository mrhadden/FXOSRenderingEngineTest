	.file	"List.c"
	.text
	.globl	head
	.bss
	.align 8
head:
	.space 8
	.globl	current
	.align 8
current:
	.space 8
	.text
	.globl	_Z13insertatbeginPv
	.def	_Z13insertatbeginPv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z13insertatbeginPv
_Z13insertatbeginPv:
.LFB55:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	$16, %ecx
	call	malloc
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	head(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, head(%rip)
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z11insertatendPv
	.def	_Z11insertatendPv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z11insertatendPv
_Z11insertatendPv:
.LFB56:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	$16, %ecx
	call	malloc
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	head(%rip), %rax
	movq	%rax, -8(%rbp)
.L4:
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L3
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	.L4
.L3:
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 8(%rax)
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z15insertafternodeP4nodePv
	.def	_Z15insertafternodeP4nodePv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z15insertafternodeP4nodePv
_Z15insertafternodeP4nodePv:
.LFB57:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movl	$16, %ecx
	call	malloc
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	16(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z13deleteatbeginv
	.def	_Z13deleteatbeginv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z13deleteatbeginv
_Z13deleteatbeginv:
.LFB58:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	head(%rip), %rax
	movq	8(%rax), %rax
	movq	%rax, head(%rip)
	nop
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z11deleteatendv
	.def	_Z11deleteatendv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z11deleteatendv
_Z11deleteatendv:
.LFB59:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movq	head(%rip), %rax
	movq	%rax, -8(%rbp)
.L9:
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L8
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	.L9
.L8:
	movq	-8(%rbp), %rax
	movq	$0, 8(%rax)
	nop
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z10deletenodePv
	.def	_Z10deletenodePv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z10deletenodePv
_Z10deletenodePv:
.LFB60:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	head(%rip), %rax
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L14
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, 16(%rbp)
	jne	.L14
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, head(%rip)
	jmp	.L10
.L14:
	cmpq	$0, -8(%rbp)
	je	.L13
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, 16(%rbp)
	je	.L13
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	.L14
.L13:
	cmpq	$0, -8(%rbp)
	je	.L16
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, 8(%rax)
	jmp	.L10
.L16:
	nop
.L10:
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z10searchlistPv
	.def	_Z10searchlistPv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z10searchlistPv
_Z10searchlistPv:
.LFB61:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	head(%rip), %rax
	movq	%rax, -8(%rbp)
.L21:
	cmpq	$0, -8(%rbp)
	je	.L18
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, 16(%rbp)
	jne	.L19
	movl	$1, %eax
	jmp	.L20
.L19:
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	.L21
.L18:
	movl	$0, %eax
.L20:
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z9AllocListv
	.def	_Z9AllocListv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z9AllocListv
_Z9AllocListv:
.LFB62:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	$16, %ecx
	call	malloc
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z11ListAddNodeP9node_listPv
	.def	_Z11ListAddNodeP9node_listPv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z11ListAddNodeP9node_listPv
_Z11ListAddNodeP9node_listPv:
.LFB63:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$16, %ecx
	call	malloc
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	16(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z10ListAddEndP9node_listPv
	.def	_Z10ListAddEndP9node_listPv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z10ListAddEndP9node_listPv
_Z10ListAddEndP9node_listPv:
.LFB64:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movl	$16, %ecx
	call	malloc
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	16(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
.L28:
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L27
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	.L28
.L27:
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-24(%rbp), %rax
	addq	$64, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 7.3-win32 20180312"
	.def	malloc;	.scl	2;	.type	32;	.endef
