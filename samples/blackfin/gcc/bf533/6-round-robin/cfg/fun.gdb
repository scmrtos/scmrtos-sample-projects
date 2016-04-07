
source cfg/prj.gdb

#-------------------------------------------------------------------------------
define cn
    target remote :2000
end
#-------------------------------------------------------------------------------
define ldp
    monitor reset
    load
end
#-------------------------------------------------------------------------------
define db
    if $argc == 1
        printf "*******************\n"
        printf "Delete breakpoint:\n"
        info breakpoints $arg0
        printf "*******************\n"
        delete breakpoints $arg0
    else 
        printf "Delete all breakpoints\n"
        delete breakpoints
    end

    printf "\n*******************\n"
    printf "Current breakpoints list:\n"
    info breakpoints
    printf "*******************\n"
end
document db
Usage: db [n]
Delete breakpoint specified by number or all breakpoints if no arg
end
#-------------------------------------------------------------------------------
define go_main
    break main
    continue
    clear main
end    
#-------------------------------------------------------------------------------
define rl
    printf "*******************\n"
    printf "Reset\n"
    monitor reset

    printf "Load init\n"
    file bin/rtinit.elf
    load
    go_main

    printf "Load program\n"
    set_program
    load 
    go_main
end
#-------------------------------------------------------------------------------

