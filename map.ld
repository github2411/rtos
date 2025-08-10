MEMORY
{
    FLASH : ORIGIN = 0x0, LENGTH = 128K
    RAM : ORIGIN = 0x20000000, LENGTH = 8K
}

SECTIONS
{
    .text : {                         # in flash memory, place stext at 0, then vectors, then text(code) section, and then put all read only data
        _stext = .;
        *(.vectors*)
        *(.text*)
        *(.rodata)
        *(.rodata.*)
        _etext = .;
    } > FLASH

    .data : ALIGN(4) {                  #variables should be in the read write memory, so initialize data and bss section
        _sdata = .;                      # .sdata and .edata are the markers [current locations] in the RAM
        _sidata = LOADADDR(.data);
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > FLASH AT > RAM                      # put .data section in flash, but addresses that code are using, should be in RAM.

    .bss : ALIGN(4) {
        _sbss = .;
        *(.bss*)
        . = ALIGN(4);
        _ebss = .;
    } > RAM                                   #unintilaized global variables should be in RAM

    __StackTop = ORIGIN(RAM) + LENGTH(RAM);
    PROVIDE(__stack = __StackTop - 4);

}
