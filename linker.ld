MEMORY
{
  flash (rx) : ORIGIN = 0x0000, LENGTH = 256K
  ram (rw!x) : ORIGIN = 0x0800, LENGTH = 8K
}

SECTIONS
{
  .vectors :
  {
    *(.vectors)
  } > flash

  .text :
  {
    *(.init0)
    *(.text)
    *(.text.*)
    *(.fini0)
  } > flash

  .data : AT (ADDR(.text) + SIZEOF(.text))
  {
    __data_load_start = LOADADDR(.data);
    __data_start = .;
    *(.data)
    *(.data.*)
    __data_end = .;
  } > ram

  .bss :
  {
    __bss_start = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    __bss_end = .;
  } > ram
}
