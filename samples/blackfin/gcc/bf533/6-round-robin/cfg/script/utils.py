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
def sizeof_fmt(num, suffix='B'):
    for unit in ['','Ki','Mi','Gi','Ti','Pi','Ei','Zi']:
        if abs(num) < 1024.0:
            return "%3.1f%s%s" % (num, unit, suffix)
        num /= 1024.0
    return "%.1f%s%s" % (num, 'Yi', suffix)
#-------------------------------------------------------------------------------
def print_size(datain):
    
    #--------------------------------------------
    #
    #    Get data
    #
    res  = re.search('\.text\s+(\d+)\s+(\d+)\n',  datain)
    if res: csz = res.group(1)
    else:   csz = '0'
     
    res  = re.search('\.bss\s+(\d+)\s+(\d+)\n',  datain)
    if res: bsz= res.group(1)
    else:   bsz = '0'
               
    res  = re.search('\.data\s+(\d+)\s+(\d+)\n',  datain)
    if res: dsz = res.group(1)
    else:   dsz = '0'
    
    res  = re.search('\.rodata\s+(\d+)\s+(\d+)\n',  datain)
    if res: rosz = res.group(1)
    else:   rosz = '0'

    in_records = datain.split('\n')
    sdram_size = 0;
    for i in in_records:
        res  = re.search('\.sdram\w*\s+(\d+)\s+(\d+)',  i)
        if res: sdram_size += int(res.group(1))
  
    if sdram_size != 0:
        ssz = sizeof_fmt(sdram_size)
    else:
        ssz = '0'
          
    #--------------------------------------------
    #
    #    Print results
    #
    sep    = '+--------------+--------------+--------------+--------------+--------------+'
    header = '|      code    |       bss    |      data    |    rodata    |     sdram    |'
    
    fw    = 10                                         # field width
    
    code    = '|' + ' '*(fw - len(csz))  + csz  + '    '
    bss     = '|' + ' '*(fw - len(bsz))  + bsz  + '    '
    data    = '|' + ' '*(fw - len(dsz))  + dsz  + '    '
    rodata  = '|' + ' '*(fw - len(rosz)) + rosz + '    '
    sdram   = '|' + ' '*(fw - len(ssz))  + ssz  + '    |'
    
    print sep
    print header
    print sep
    print code + bss + data + rodata + sdram
    print sep
    
    print '        L1 Code: ' + csz + ' bytes'
    print '        L1 Data: ' + str( int(bsz) + int(dsz) + int(rosz) ) + ' bytes'
    print ''
#-------------------------------------------------------------------------------

