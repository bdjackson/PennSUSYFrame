#!/usr/bin/env python
# ==============================================================================
# = quick and dirty script to make file list for TTNT skims of TNT files
# =
# = usage:
# =     First, modify the relevant lines below, then call:
# =     python MakeNewEosLists.py
# ==============================================================================

import glob
import ROOT

import os

# ------------------------------------------------------------------------------
# MODIFY THESE LINES!!!
ttnt_header = '%s/../../SafeTTNTDir/BMinusL.' % os.getcwd()
old_eos_file_list_header = '../tnt_103_w_weights/tnt_103'
ttnt_file_list = glob.glob('%s*tnt.root' % ttnt_header)

# ------------------------------------------------------------------------------
def getNumEntries(in_file):
    f = ROOT.TFile.Open(in_file)
    t = f.Get('BMinusLTTNT')
    total_num_entries = t.GetEntries()
    f.Close()
    return total_num_entries

# ------------------------------------------------------------------------------
for tfl in ttnt_file_list:
    print 'file: ' , tfl

    tag = tfl.replace('.tnt.root', '').replace(ttnt_header, '')
    print 'tag: ' , tag

    old_eos_list_file_name = '%s.%s.txt' % (old_eos_file_list_header, tag)
    print 'old eos file list: ', old_eos_list_file_name

    out_file_name = 'ttnt.%s.txt' % tag
    print 'new ttnt file list: ' , out_file_name

    total_num_events = 0
    skimmed_events   = 0
    sum_mc_events    = 0.

    old_eos_file = file(old_eos_list_file_name)
    for lines in old_eos_file.readlines():
        splits = lines.rstrip('\n').split()

        total_num_events += int(splits[1])
        if len(splits) > 3:
            sum_mc_events += float(splits[3])

    skimmed_events = getNumEntries(tfl)
    if sum_mc_events == 0:
        sum_mc_events = total_num_events

    print 'total_num_events: ' , total_num_events
    print 'skimmed_events  : ' , skimmed_events
    print 'sum_mc_events   : ' , sum_mc_events

    out_file = file(out_file_name, 'w')
    out_file.write( '%s    %s    %s    %s\n' % ( tfl, total_num_events, skimmed_events, sum_mc_events ) )
    out_file.close()

    print ''
