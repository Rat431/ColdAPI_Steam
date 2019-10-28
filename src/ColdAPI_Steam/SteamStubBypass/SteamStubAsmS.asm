ifdef RBX
.code
else
.model flat
.code
endif
ifdef RBX
CallDispatcherData proc
	mov rbx, rcx
	mov rcx, rsp
	add rcx, 1264
	mov rdx, rsp
	call rbx
CallDispatcherData endp
else
_CallDispatcherData proc
	cld
	add esp, 4
	pop ebx
	push dword ptr [esp + 4]
    push dword ptr [esp + 4]
	call ebx
	ret
_CallDispatcherData endp
endif
end