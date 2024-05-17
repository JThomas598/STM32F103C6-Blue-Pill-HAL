MEMORY {
    flash(rx)  : ORIGIN = 0x08000000 , LENGTH = 64K
    sram (!rx) : ORIGIN = 0x20000000 , LENGTH = 10K 
}

PROVIDE(_estack = ORIGIN(sram) + LENGTH(sram));

SECTIONS {
    .vectors :{
        *(.vectors)
    } > flash

    .text    : {
        *(.text)
    } > flash 

    .rodata  : {
        *(.rodata)
    } > flash

    .data  : {
        _sdata = .;
        *(.data)
        _edata = .;
    } > sram AT > flash
    _sidata = LOADADDR(.data);
    
    .bss     : {
        _sbss = .;
        *(.bss)
        _ebss = .;
    } > sram
}

