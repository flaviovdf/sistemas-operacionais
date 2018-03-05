// Daqui:
// https://stackoverflow.com/questions/15596688/gcc-putcharchar-in-inline-assembly
// compilar com: gcc -ggdb -masm=intel
void asm_putchar(char my_char) {
  int dword_char;
  dword_char = (int)my_char;
  asm volatile(
    ".intel_syntax noprefix;"
    "mov r10,rsp;"   // save rsp.
    "sub rsp,8;"     // space for buffer, align by 8.
    "mov [rsp],al;"  // store the character into buffer.
    "mov edi,1;"     // STDOUT.
    "mov rsi,rsp;"   // pointer to buffer.
    "mov edx,1;"     // string length in bytes.
    "mov eax,1;"     // WRITE.
    "syscall;"       // clobbers rcx & r11.
    "mov rsp,r10;"   // restore rsp.
    ".att_syntax prefix;"
    /* outputs */
    :
    /* inputs: eax */
    : "a"(dword_char)
    /* clobbered regs */
    : "rcx", "rdx", "rsi", "rdi", "r10", "r11"
  );
}

void imprime(char *s) {
  int i = 0;
  for (; s[i] != '\0'; i++) asm_putchar(s[i]);
  asm_putchar('\n');
}
