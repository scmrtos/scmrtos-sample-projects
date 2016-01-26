#*******************************************************************************
#*
#*    Build support utilities
#*
#*    Version 1.0
#*
#*    Copyright (c) 2016, Harry E. Zhurov
#*
#*******************************************************************************

import os
import subprocess
import re

#-------------------------------------------------------------------------------
# 
# 
# 
def namegen(fullpath, ext):
    basename = os.path.basename(fullpath)
    name     = os.path.splitext(basename)[0]
    return name + os.path.extsep + ext
#-------------------------------------------------------------------------------
def pexec(cmd):
    p = subprocess.Popen( cmd.split(), universal_newlines = True,
                         stdin  = subprocess.PIPE,
                         stdout = subprocess.PIPE,
                         stderr = subprocess.PIPE )


    out, err = p.communicate()

    return p.returncode, out, err
    
#-------------------------------------------------------------------------------
def print_size(datain):
    
    #--------------------------------------------
    #
    #    Get data
    #
    res  = re.search('\.text\s+(\d+)\s+(\d+)\n',  datain)
    if res: csz = res.group(1)
    else:   csz = 'none'
     
    res  = re.search('\.bss\s+(\d+)\s+(\d+)\n',  datain)
    if res: bsz= res.group(1)
    else:   bsz = 'none'
               
    res  = re.search('\.data\s+(\d+)\s+(\d+)\n',  datain)
    if res: dsz = res.group(1)
    else:   dsz = 'none'
    
    res  = re.search('\.sdram\s+(\d+)\s+(\d+)\n',  datain)
    if res: ssz = res.group(1)
    else:   ssz = 'none'
          
    #--------------------------------------------
    #
    #    Print results
    #
    sep    = '+--------------+--------------+--------------+--------------+'
    header = '|      code    |       bss    |      data    |     sdram    |'
    
    fw    = 10                                         # field width
    
    code  = '|' + ' '*(fw - len(csz)) + csz + '    '
    bss   = '|' + ' '*(fw - len(bsz)) + bsz + '    '
    data  = '|' + ' '*(fw - len(dsz)) + dsz + '    '
    sdram = '|' + ' '*(fw - len(ssz)) + ssz + '    |'
    
    print sep
    print header
    print sep
    print code + bss + data + sdram
    print sep
#-------------------------------------------------------------------------------

