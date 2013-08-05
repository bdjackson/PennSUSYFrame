#!/bin/bash

# =========================
# = Define some variables =
# =========================
DATA_MC='mc'
STREAM='egamma'
SIM_TYPE='fullsim'
OUT_DS_PREFIX='mc12_8TeV.signal_simplified'
EXT_FILES=''

# ==============================
# = define list of input files =
# ==============================
# mc12 list 
ds_list=( 
          # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          "mc12_8TeV.144871.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_5.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144873.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_7.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144874.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_8.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144876.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_10.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144877.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_11.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144879.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_13.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144880.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_14.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144881.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_15.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144883.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_17.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144884.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_18.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144885.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_19.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144886.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_20.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144888.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_22.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144889.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_23.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144890.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_24.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144891.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_25.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144892.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_26.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144894.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_28.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144895.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_29.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.144896.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_30.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157461.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_32.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157464.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_35.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157467.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_38.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157954.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_39.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157955.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_40.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157956.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_41.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157957.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_42.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157958.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_43.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157959.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_44.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157960.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_45.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157961.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_46.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157962.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_47.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157963.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_48.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157964.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_49.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157965.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_50.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157966.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_51.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157967.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_52.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.157968.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_53.merge.NTUP_SUSY.e1417_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176531.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_54.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176532.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_55.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176533.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_56.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176534.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_57.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176535.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_58.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176536.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_59.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176537.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_60.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176538.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_61.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176539.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_62.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176540.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_63.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176541.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_64.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176542.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_65.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176543.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_66.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176544.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_67.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176545.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_68.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176546.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_69.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176547.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_70.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176548.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_71.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176549.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_72.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176550.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_73.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176551.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_74.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176552.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_75.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176553.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_76.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176554.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_77.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176555.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_78.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176556.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_79.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.176557.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_80.merge.NTUP_SUSY.e1708_s1499_s1504_r3658_r3549_p1512/"
          # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          "mc12_8TeV.164274.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_1.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164275.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_2.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164276.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_3.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164277.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_4.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164278.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_5.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164279.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_6.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164280.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_7.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164281.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_8.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164282.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_9.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164283.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_10.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164284.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_11.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164285.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_12.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164286.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_13.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164287.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_14.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164288.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_15.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164289.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_16.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164290.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_17.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164291.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_18.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164292.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_19.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164293.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_20.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164294.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_21.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164295.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_22.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164296.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_23.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164297.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_24.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164298.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_25.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164299.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_26.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164300.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_27.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164301.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_28.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164302.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_29.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164303.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_30.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164304.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_31.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164305.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_32.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164306.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_33.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164307.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_34.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164308.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_35.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164309.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_36.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164310.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_37.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164311.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_38.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164312.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_39.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164313.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_40.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164314.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_41.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164315.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_42.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164316.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_43.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164317.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_44.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164318.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_45.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164319.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_46.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164320.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_47.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164321.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_48.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164322.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_49.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
          "mc12_8TeV.164323.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_50.merge.NTUP_SUSY.e1461_s1499_s1504_r3658_r3549_p1512/"
        )

. ${PWD}/submit_cutflow.sh

