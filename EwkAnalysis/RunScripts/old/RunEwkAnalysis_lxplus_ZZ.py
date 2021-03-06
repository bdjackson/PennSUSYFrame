#!/usr/bin/env python

import RunEwkAnalysis

# ==============================================================================
if __name__ == '__main__':
    print 'getting file list'
    file_list = RunEwkAnalysis.getFileListFromDir('/afs/cern.ch/user/b/bjackson/my_eos/mc12/mc12_8TeV.116600.gg2ZZJimmy_AUET2CT10_ZZ4lep.merge.NTUP_SUSY.e1525_s1499_s1504_r3658_r3549_p1512_tid01267663_00/')
    file_list = RunEwkAnalysis.getFileListFromFile("%s/EosFileLists/d3pd.116600.ZZ4lep.txt" % os.environ["BASE_WORK_DIR"]) 
    print 'file list: %s' % file_list

    print 'About to run EwkAnalysis'
    RunEwkAnalysis.runEwkAnalysis( file_list = file_list
                                         , is_data = False
                                         , is_full_sim = True
                                         , dsid = 116600
                                         , out_file_special_name = 'ZZ4lep'
                                         )


