#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int stringEqual(char *s, char *t);
int *initArray(int len, int init);
int *initRecord(int size);
int ARG[2048];
int TEMP[2048];
int LevelFrame[2048];
int execute();
char L13[]="\x68\x65\x6c\x6c\x6f";
char L14[]="\x68\x65\x6c\x6c\x6f";
int main()
{
	execute();
	system("pause");
}
int execute()
{
	__asm {
push ebp
mov ebp, esp
sub esp, 0xFF
mov LevelFrame[4], ebp
push eax
push ebx
mov eax, ebp
push eax
mov ecx, -4
pop eax
add eax, ecx
mov ebx, eax
mov esi, ebx
mov ebx, [ebx]
push ebx
push esi
mov eax, 0
pop esi
pop ebx
mov [esi], eax
pop ebx
pop eax
L1:
push ebp
mov ebp, esp
sub esp, 0xFF
push eax
lea ebx, L11
push ebx
pop ebx
call ebx
add esp, 0
pop eax
push ebp
pop esp
pop ebp
jmp end
L11:
push ebp
mov ebp, esp
sub esp, 0xFF
mov LevelFrame[8], ebp
push eax
push eax
lea eax, L15
push eax
pop eax
pop eax
jmp [esp-8]
L16:
push eax
push eax
lea ebx, printf
push ebx
lea edx, L13
mov ARG[0], edx
pop ebx
mov ecx, ARG[0]
push ecx
call ebx
add esp, 4
pop eax
push eax
lea eax, L12
push eax
pop eax
pop eax
jmp [esp-8]
mov eax, 0
pop eax
L15:
push eax
push ecx
push eax
push ebx
mov ebx, TEMP[4]
lea edi, TEMP[4]
push ebx
push edi
mov eax, 1
pop edi
pop ebx
mov [edi], eax
pop ebx
pop eax
push eax
push ecx
lea ebx, LevelFrame[4]
mov esi, ebx
mov eax, [ebx]
push eax
mov ecx, -4
pop eax
add eax, ecx
mov ebx, eax
mov esi, ebx
mov eax, [ebx]
push eax
mov ecx, 3
pop eax
cmp eax, ecx
pop ecx
pop eax
jl L17
jmp L18
L18:
push eax
push ebx
mov ebx, TEMP[4]
lea edi, TEMP[4]
push ebx
push edi
mov eax, 0
pop edi
pop ebx
mov [edi], eax
pop ebx
pop eax
L17:
mov eax, TEMP[4]
lea edi, TEMP[4]
push eax
mov ecx, 0
pop eax
cmp eax, ecx
pop ecx
pop eax
je L12
jmp L16
L12:
mov eax, 0
pop eax
push ebp
pop esp
pop ebp
ret
	}
__asm {
end:
push ebp
pop esp
pop ebp
}
}
int *initArray(int len, int init)
{
	int *p = (int *)malloc(4 * len);
	for (int i = 0; i < len; i++)
		p[i] = init;
	return p;
}
 int *initRecord(int size)
{
	int *p = (int *)malloc(size);
	memset(p, 0, size);
	return p;
}
int stringEqual(char *s, char *t)
{
	if (strcmp(s, t) == 0)
		return 1;
	else
		return 0;
}