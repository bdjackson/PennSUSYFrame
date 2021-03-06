#!/usr/bin/env python

import os
import stat
import subprocess

# ------------------------------------------------------------------------------
def containerize(output_container, input_container_list):
    print 'Registering the container ', output_container
    temp_register = subprocess.Popen( 'dq2-register-container %s' % output_container
                                    , shell=True
                                    , stdout=subprocess.PIPE
                                    , stderr=subprocess.STDOUT
                                    )
    print temp_register.stdout.readlines()

    for icl in input_container_list:
        print 'adding datasets from input container (%s) to output container: %s' % (icl, output_container)

        temp_get_list = subprocess.Popen( 'dq2-list-datasets-container %s' % icl
                                        , shell=True
                                        , stdout=subprocess.PIPE
                                        , stderr=subprocess.STDOUT
                                        )
        for line in temp_get_list.stdout.readlines():
            print line
            temp_add_data_set = subprocess.Popen( 'dq2-register-datasets-container %s %s' % (output_container, line)
                                                , shell=True
                                                , stdout=subprocess.PIPE
                                                , stderr=subprocess.STDOUT
                                                )
            print temp_add_data_set.stdout.readlines()

# ------------------------------------------------------------------------------
def main():
    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.data_part_1.merge2.tnt_103/'
    input_container_list = [
                             "user.bjackson.periodA_egamma.tnt_103/"
                           , "user.bjackson.periodA_muon.tnt_103/"
                           , "user.bjackson.periodB_egamma.tnt_103/"
                           , "user.bjackson.periodB_muon.tnt_103/"
                           , "user.bjackson.periodC_egamma.tnt_103/"
                           , "user.bjackson.periodC_muon.tnt_103/"
                           , "user.bjackson.periodD_egamma.tnt_103/"
                           , "user.bjackson.periodD_muon.tnt_103/"
                           , "user.bjackson.periodE_egamma.tnt_103/"
                           , "user.bjackson.periodE_muon.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)

    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.data_part_2.merge2.tnt_103/'
    input_container_list = [
                             "user.bjackson.periodG_egamma.tnt_103/"
                           , "user.bjackson.periodG_muon.tnt_103/"
                           , "user.bjackson.periodH_egamma.tnt_103/"
                           , "user.bjackson.periodH_muon.tnt_103/"
                           , "user.bjackson.periodI_egamma.tnt_103/"
                           , "user.bjackson.periodI_muon.tnt_103/"
                           , "user.bjackson.periodJ_egamma.tnt_103/"
                           , "user.bjackson.periodJ_muon.tnt_103/"
                           , "user.bjackson.periodL_egamma.tnt_103/"
                           , "user.bjackson.periodL_muon.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)

    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.bkg_top_part_1.merge2.tnt_103/'
    input_container_list = [
                           # ttbar
                             "user.bjackson.117050.PowhegPythia_P2011C_ttbar.af2_v2.tnt_103/"
                           , "user.bjackson.105200.McAtNloJimmy_CT10_ttbar_LeptonFilter.tnt_103/"
                           # single top Wt channel
                           , "user.bjackson.110141.PowhegPythia_P2011C_st_Wtchan_dilepton_DR.tnt_103/"
                           # single top s channel
                           , "user.bjackson.110119.PowhegPythia_P2011C_st_schan_lep.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)

    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.bkg_top_part_2.merge2.tnt_103/'
    input_container_list = [
                             "user.bjackson.105860.PowhegJimmy_AUET2CT10_ttbar_LeptonFilter.tnt_103/"
                           , "user.bjackson.105861.PowhegPythia_AUET2BCT10_ttbar_LeptonFilter.tnt_103/"
                           , "user.bjackson.110001.McAtNloJimmy_CT10_ttbar_dilepton.tnt_103/"
                           , "user.bjackson.110101.AcerMCPythia_P2011CCTEQ6L1_singletop_tchan_l.tnt_103/"
                           , "user.bjackson.110140.PowhegPythia_P2011C_st_Wtchan_incl_DR.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)

    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.bkg_ZX_part_1.merge2.tnt_103/'
    input_container_list = [
                           # Z > ee
                             "user.bjackson.117650.AlpgenPythia_P2011C_ZeeNp0.tnt_103/"
                           , "user.bjackson.117651.AlpgenPythia_P2011C_ZeeNp1.tnt_103/"
                           , "user.bjackson.117652.AlpgenPythia_P2011C_ZeeNp2.tnt_103/"
                           , "user.bjackson.117653.AlpgenPythia_P2011C_ZeeNp3.tnt_103/"
                           , "user.bjackson.117654.AlpgenPythia_P2011C_ZeeNp4.tnt_103/"
                           , "user.bjackson.117655.AlpgenPythia_P2011C_ZeeNp5.tnt_103/"
                           # Z > mumu
                           , "user.bjackson.117660.AlpgenPythia_P2011C_ZmumuNp0.tnt_103/"
                           , "user.bjackson.117661.AlpgenPythia_P2011C_ZmumuNp1.tnt_103/"
                           , "user.bjackson.117662.AlpgenPythia_P2011C_ZmumuNp2.tnt_103/"
                           , "user.bjackson.117663.AlpgenPythia_P2011C_ZmumuNp3.tnt_103/"
                           , "user.bjackson.117664.AlpgenPythia_P2011C_ZmumuNp4.tnt_103/"
                           , "user.bjackson.117665.AlpgenPythia_P2011C_ZmumuNp5.tnt_103/"
                           # Z > tautau
                           , "user.bjackson.117670.AlpgenPythia_P2011C_ZtautauNp0.tnt_103/"
                           , "user.bjackson.117671.AlpgenPythia_P2011C_ZtautauNp1.tnt_103/"
                           , "user.bjackson.117672.AlpgenPythia_P2011C_ZtautauNp2.tnt_103/"
                           , "user.bjackson.117673.AlpgenPythia_P2011C_ZtautauNp3.tnt_103/"
                           , "user.bjackson.117674.AlpgenPythia_P2011C_ZtautauNp4.tnt_103/"
                           , "user.bjackson.117675.AlpgenPythia_P2011C_ZtautauNp5.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)

    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.bkg_ZX_part_2.merge2.tnt_103/'
    input_container_list = [
                             "user.bjackson.147770.Sherpa_CT10_Zee.tnt_103/"
                           , "user.bjackson.147771.Sherpa_CT10_Zmumu.tnt_103/"
                           , "user.bjackson.147772.Sherpa_CT10_Ztautau.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)

    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.bkg_DY_part_1.merge2.tnt_103/'
    input_container_list = [
                             "user.bjackson.146830.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZeeNp0Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146831.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZeeNp1Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146832.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZeeNp2Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146833.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZeeNp3Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146834.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZeeNp4Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146835.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZeeNp5Incl_Mll10to60.tnt_103/"
                           , "user.bjackson.146840.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZmumuNp0Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146841.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZmumuNp1Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146842.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZmumuNp2Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146843.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZmumuNp3Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146844.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZmumuNp4Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146845.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZmumuNp5Incl_Mll10to60.tnt_103/"
                           , "user.bjackson.146850.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZtautauNp0Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146851.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZtautauNp1Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146852.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZtautauNp2Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146853.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZtautauNp3Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146854.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZtautauNp4Excl_Mll10to60.tnt_103/"
                           , "user.bjackson.146855.AlpgenJimmy_Auto_AUET2CTEQ6L1_ZtautauNp5Incl_Mll10to60.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)

    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.bkg_DY_part_2.merge2.tnt_103/'
    input_container_list = [
                             "user.bjackson.173041.Sherpa_CT10_DYeeM08to15.tnt_103/"
                           , "user.bjackson.173042.Sherpa_CT10_DYeeM15to40.tnt_103/"
                           , "user.bjackson.173043.Sherpa_CT10_DYmumuM08to15.tnt_103/"
                           , "user.bjackson.173044.Sherpa_CT10_DYmumuM15to40.tnt_103/"
                           , "user.bjackson.173045.Sherpa_CT10_DYtautauM08to15.tnt_103/"
                           , "user.bjackson.173046.Sherpa_CT10_DYtautauM15to40.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)

    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.bkg_Z_heavy_flavor_part_1.merge2.tnt_103/'
    input_container_list = [
                           # Z > ee + heavy flavor
                             "user.bjackson.167749.Sherpa_CT10_ZeeMassiveCBPt0_BFilter.tnt_103/"
                           , "user.bjackson.167750.Sherpa_CT10_ZeeMassiveCBPt0_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167751.Sherpa_CT10_ZeeMassiveCBPt0_CVetoBVeto.tnt_103/"
                           , "user.bjackson.180543.Sherpa_CT10_ZeeMassiveCBPt40_70_BFilter.tnt_103/"
                           , "user.bjackson.180544.Sherpa_CT10_ZeeMassiveCBPt40_70_CFilterBVeto.tnt_103/"
                           , "user.bjackson.180545.Sherpa_CT10_ZeeMassiveCBPt40_70_CVetoBVeto.tnt_103/"
                           , "user.bjackson.167797.Sherpa_CT10_ZeeMassiveCBPt70_140_BFilter.tnt_103/"
                           , "user.bjackson.167798.Sherpa_CT10_ZeeMassiveCBPt70_140_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167799.Sherpa_CT10_ZeeMassiveCBPt70_140_CVetoBVeto.tnt_103/"
                           , "user.bjackson.167809.Sherpa_CT10_ZeeMassiveCBPt140_280_BFilter.tnt_103/"
                           , "user.bjackson.167810.Sherpa_CT10_ZeeMassiveCBPt140_280_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167811.Sherpa_CT10_ZeeMassiveCBPt140_280_CVetoBVeto.tnt_103/"
                           , "user.bjackson.167821.Sherpa_CT10_ZeeMassiveCBPt280_500_BFilter.tnt_103/"
                           , "user.bjackson.167822.Sherpa_CT10_ZeeMassiveCBPt280_500_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167823.Sherpa_CT10_ZeeMassiveCBPt280_500_CVetoBVeto.tnt_103/"
                           , "user.bjackson.167833.Sherpa_CT10_ZeeMassiveCBPt500_BFilter.tnt_103/"
                           , "user.bjackson.167834.Sherpa_CT10_ZeeMassiveCBPt500_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167835.Sherpa_CT10_ZeeMassiveCBPt500_CVetoBVeto.tnt_103/"
                           # Z > mumu + heavy flavor
                           , "user.bjackson.167752.Sherpa_CT10_ZmumuMassiveCBPt0_BFilter.tnt_103/"
                           , "user.bjackson.167753.Sherpa_CT10_ZmumuMassiveCBPt0_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167754.Sherpa_CT10_ZmumuMassiveCBPt0_CVetoBVeto.tnt_103/"
                           , "user.bjackson.180546.Sherpa_CT10_ZmumuMassiveCBPt40_70_BFilter.tnt_103/"
                           , "user.bjackson.180547.Sherpa_CT10_ZmumuMassiveCBPt40_70_CFilterBVeto.tnt_103/"
                           , "user.bjackson.180548.Sherpa_CT10_ZmumuMassiveCBPt40_70_CVetoBVeto.tnt_103/"
                           , "user.bjackson.167800.Sherpa_CT10_ZmumuMassiveCBPt70_140_BFilter.tnt_103/"
                           , "user.bjackson.167801.Sherpa_CT10_ZmumuMassiveCBPt70_140_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167802.Sherpa_CT10_ZmumuMassiveCBPt70_140_CVetoBVeto.tnt_103/"
                           , "user.bjackson.167812.Sherpa_CT10_ZmumuMassiveCBPt140_280_BFilter.tnt_103/"
                           , "user.bjackson.167813.Sherpa_CT10_ZmumuMassiveCBPt140_280_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167814.Sherpa_CT10_ZmumuMassiveCBPt140_280_CVetoBVeto.tnt_103/"
                           , "user.bjackson.167824.Sherpa_CT10_ZmumuMassiveCBPt280_500_BFilter.tnt_103/"
                           , "user.bjackson.167825.Sherpa_CT10_ZmumuMassiveCBPt280_500_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167826.Sherpa_CT10_ZmumuMassiveCBPt280_500_CVetoBVeto.tnt_103/"
                           , "user.bjackson.167836.Sherpa_CT10_ZmumuMassiveCBPt500_BFilter.tnt_103/"
                           , "user.bjackson.167837.Sherpa_CT10_ZmumuMassiveCBPt500_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167838.Sherpa_CT10_ZmumuMassiveCBPt500_CVetoBVeto.tnt_103/"
                           # Z > tautau + heavy flavor
                           , "user.bjackson.167755.Sherpa_CT10_ZtautauMassiveCBPt0_BFilter.tnt_103/"
                           , "user.bjackson.167756.Sherpa_CT10_ZtautauMassiveCBPt0_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167757.Sherpa_CT10_ZtautauMassiveCBPt0_CVetoBVeto.tnt_103/"
                           , "user.bjackson.180549.Sherpa_CT10_ZtautauMassiveCBPt40_70_BFilter.tnt_103/"
                           , "user.bjackson.180550.Sherpa_CT10_ZtautauMassiveCBPt40_70_CFilterBVeto.tnt_103/"
                           , "user.bjackson.180551.Sherpa_CT10_ZtautauMassiveCBPt40_70_CVetoBVeto.tnt_103/"
                           , "user.bjackson.167803.Sherpa_CT10_ZtautauMassiveCBPt70_140_BFilter.tnt_103/"
                           , "user.bjackson.167804.Sherpa_CT10_ZtautauMassiveCBPt70_140_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167805.Sherpa_CT10_ZtautauMassiveCBPt70_140_CVetoBVeto.tnt_103/"
                           , "user.bjackson.167815.Sherpa_CT10_ZtautauMassiveCBPt140_280_BFilter.tnt_103/"
                           , "user.bjackson.167816.Sherpa_CT10_ZtautauMassiveCBPt140_280_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167817.Sherpa_CT10_ZtautauMassiveCBPt140_280_CVetoBVeto.tnt_103/"
                           , "user.bjackson.167827.Sherpa_CT10_ZtautauMassiveCBPt280_500_BFilter.tnt_103/"
                           , "user.bjackson.167828.Sherpa_CT10_ZtautauMassiveCBPt280_500_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167829.Sherpa_CT10_ZtautauMassiveCBPt280_500_CVetoBVeto.tnt_103/"
                           , "user.bjackson.167839.Sherpa_CT10_ZtautauMassiveCBPt500_BFilter.tnt_103/"
                           , "user.bjackson.167840.Sherpa_CT10_ZtautauMassiveCBPt500_CFilterBVeto.tnt_103/"
                           , "user.bjackson.167841.Sherpa_CT10_ZtautauMassiveCBPt500_CVetoBVeto.tnt_103/"
                           # Z + cc
                           , "user.bjackson.110805.AlpgenPythia_P2011C_ZeeccNp0.tnt_103/"
                           , "user.bjackson.110806.AlpgenPythia_P2011C_ZeeccNp1.tnt_103/"
                           , "user.bjackson.110807.AlpgenPythia_P2011C_ZeeccNp2.tnt_103/"
                           , "user.bjackson.110808.AlpgenPythia_P2011C_ZeeccNp3.tnt_103/"
                           , "user.bjackson.110809.AlpgenPythia_P2011C_ZmumuccNp0.tnt_103/"
                           , "user.bjackson.110810.AlpgenPythia_P2011C_ZmumuccNp1.tnt_103/"
                           , "user.bjackson.110811.AlpgenPythia_P2011C_ZmumuccNp2.tnt_103/"
                           , "user.bjackson.110812.AlpgenPythia_P2011C_ZmumuccNp3.tnt_103/"
                           , "user.bjackson.110813.AlpgenPythia_P2011C_ZtautauccNp0.tnt_103/"
                           , "user.bjackson.110814.AlpgenPythia_P2011C_ZtautauccNp1.tnt_103/"
                           , "user.bjackson.110815.AlpgenPythia_P2011C_ZtautauccNp2.tnt_103/"
                           , "user.bjackson.110816.AlpgenPythia_P2011C_ZtautauccNp3.tnt_103/"
                           # Z + bb
                           , "user.bjackson.110817.AlpgenPythia_P2011C_ZeebbNp0.tnt_103/"
                           , "user.bjackson.110818.AlpgenPythia_P2011C_ZeebbNp1.tnt_103/"
                           , "user.bjackson.110819.AlpgenPythia_P2011C_ZeebbNp2.tnt_103/"
                           , "user.bjackson.110820.AlpgenPythia_P2011C_ZeebbNp3.tnt_103/"
                           , "user.bjackson.110821.AlpgenPythia_P2011C_ZmumubbNp0.tnt_103/"
                           , "user.bjackson.110822.AlpgenPythia_P2011C_ZmumubbNp1.tnt_103/"
                           , "user.bjackson.110823.AlpgenPythia_P2011C_ZmumubbNp2.tnt_103/"
                           , "user.bjackson.110824.AlpgenPythia_P2011C_ZmumubbNp3.tnt_103/"
                           , "user.bjackson.110825.AlpgenPythia_P2011C_ZtautaubbNp0.tnt_103/"
                           , "user.bjackson.110826.AlpgenPythia_P2011C_ZtautaubbNp1.tnt_103/"
                           , "user.bjackson.110827.AlpgenPythia_P2011C_ZtautaubbNp2.tnt_103/"
                           , "user.bjackson.110828.AlpgenPythia_P2011C_ZtautaubbNp3.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)

    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.bkg_Z_heavy_flavor_part_2.merge2.tnt_103/'
    input_container_list = [
                             "user.bjackson.200332.AlpgenPythia_Auto_P2011C_ZeebbNp0.tnt_103/"
                           , "user.bjackson.200333.AlpgenPythia_Auto_P2011C_ZeebbNp1.tnt_103/"
                           , "user.bjackson.200334.AlpgenPythia_Auto_P2011C_ZeebbNp2.tnt_103/"
                           , "user.bjackson.200335.AlpgenPythia_Auto_P2011C_ZeebbNp3incl.tnt_103/"
                           , "user.bjackson.200340.AlpgenPythia_Auto_P2011C_ZmumubbNp0.tnt_103/"
                           , "user.bjackson.200341.AlpgenPythia_Auto_P2011C_ZmumubbNp1.tnt_103/"
                           , "user.bjackson.200342.AlpgenPythia_Auto_P2011C_ZmumubbNp2.tnt_103/"
                           , "user.bjackson.200343.AlpgenPythia_Auto_P2011C_ZmumubbNp3incl.tnt_103/"
                           , "user.bjackson.200348.AlpgenPythia_Auto_P2011C_ZtautaubbNp0.tnt_103/"
                           , "user.bjackson.200349.AlpgenPythia_Auto_P2011C_ZtautaubbNp1.tnt_103/"
                           , "user.bjackson.200350.AlpgenPythia_Auto_P2011C_ZtautaubbNp2.tnt_103/"
                           , "user.bjackson.200351.AlpgenPythia_Auto_P2011C_ZtautaubbNp3incl.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)

    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.bkg_diboson_part_1.merge2.tnt_103/'
    input_container_list = [
                           # WZ
                             "user.bjackson.129477.PowhegPythia8_AU2CT10_WZ_Wm11Z11_mll0p250d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129478.PowhegPythia8_AU2CT10_WZ_Wm11Z13_mll0p4614d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129479.PowhegPythia8_AU2CT10_WZ_Wm11Z15_mll3p804d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129480.PowhegPythia8_AU2CT10_WZ_Wm13Z11_mll0p250d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129481.PowhegPythia8_AU2CT10_WZ_Wm13Z13_mll0p4614d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129482.PowhegPythia8_AU2CT10_WZ_Wm13Z15_mll3p804d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129483.PowhegPythia8_AU2CT10_WZ_Wm15Z11_mll0p250d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129484.PowhegPythia8_AU2CT10_WZ_Wm15Z13_mll0p4614d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129485.PowhegPythia8_AU2CT10_WZ_Wm15Z15_mll3p804d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129486.PowhegPythia8_AU2CT10_WZ_W11Z11_mll0p250d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129487.PowhegPythia8_AU2CT10_WZ_W11Z13_mll0p4614d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129488.PowhegPythia8_AU2CT10_WZ_W11Z15_mll3p804d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129489.PowhegPythia8_AU2CT10_WZ_W13Z11_mll0p250d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129490.PowhegPythia8_AU2CT10_WZ_W13Z13_mll0p4614d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129491.PowhegPythia8_AU2CT10_WZ_W13Z15_mll3p804d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129492.PowhegPythia8_AU2CT10_WZ_W15Z11_mll0p250d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129493.PowhegPythia8_AU2CT10_WZ_W15Z13_mll0p4614d0_2LeptonFilter5.tnt_103/"
                           , "user.bjackson.129494.PowhegPythia8_AU2CT10_WZ_W15Z15_mll3p804d0_2LeptonFilter5.tnt_103/"
                           # WZjj
                           , "user.bjackson.147194.Sherpa_CT10_lllnjj_WZjj_EW6.tnt_103/"
                           , "user.bjackson.147195.Sherpa_CT10_llnnjj_ZZjj_EW6.tnt_103/"
                           , "user.bjackson.147196.Sherpa_CT10_lllljj_ZZjj_EW6.tnt_103/"
                           # WW
                           , "user.bjackson.126928.PowhegPythia8_AU2CT10_WpWm_ee.tnt_103/"
                           , "user.bjackson.126929.PowhegPythia8_AU2CT10_WpWm_me.tnt_103/"
                           , "user.bjackson.126930.PowhegPythia8_AU2CT10_WpWm_te.tnt_103/"
                           , "user.bjackson.126931.PowhegPythia8_AU2CT10_WpWm_em.tnt_103/"
                           , "user.bjackson.126932.PowhegPythia8_AU2CT10_WpWm_mm.tnt_103/"
                           , "user.bjackson.126933.PowhegPythia8_AU2CT10_WpWm_tm.tnt_103/"
                           , "user.bjackson.126934.PowhegPythia8_AU2CT10_WpWm_et.tnt_103/"
                           , "user.bjackson.126935.PowhegPythia8_AU2CT10_WpWm_mt.tnt_103/"
                           , "user.bjackson.126936.PowhegPythia8_AU2CT10_WpWm_tt.tnt_103/"
                           # gg > WW
                           , "user.bjackson.169471.gg2wwJimmy_AUET2CT10_WpWmenuenu.tnt_103/"
                           , "user.bjackson.169472.gg2wwJimmy_AUET2CT10_WpWmenumunu.tnt_103/"
                           , "user.bjackson.169473.gg2wwJimmy_AUET2CT10_WpWmenutaunu.tnt_103/"
                           , "user.bjackson.169474.gg2wwJimmy_AUET2CT10_WpWmmunumunu.tnt_103/"
                           , "user.bjackson.169475.gg2wwJimmy_AUET2CT10_WpWmmunuenu.tnt_103/"
                           , "user.bjackson.169476.gg2wwJimmy_AUET2CT10_WpWmmunutaunu.tnt_103/"
                           , "user.bjackson.169477.gg2wwJimmy_AUET2CT10_WpWmtaunutaunu.tnt_103/"
                           , "user.bjackson.169478.gg2wwJimmy_AUET2CT10_WpWmtaunuenu.tnt_103/"
                           , "user.bjackson.169479.gg2wwJimmy_AUET2CT10_WpWmtaunumunu.tnt_103/"
                           # WWjj
                           , "user.bjackson.126988.Sherpa_CT10_llnunu_SS_EW6.tnt_103/"
                           , "user.bjackson.126989.Sherpa_CT10_llnunujj_SS.tnt_103/"
                           # VV > lnuqq
                           , "user.bjackson.157817.Sherpa_CT10_VVtoenuqq.tnt_103/"
                           , "user.bjackson.157818.Sherpa_CT10_VVtomunuqq.tnt_103/"
                           , "user.bjackson.157819.Sherpa_CT10_VVtotaunuqq.tnt_103/"
                           # ZZ
                           , "user.bjackson.126937.PowhegPythia8_AU2CT10_ZZ_4e_mll4_2pt5.tnt_103/"
                           , "user.bjackson.126938.PowhegPythia8_AU2CT10_ZZ_2e2mu_mll4_2pt5.tnt_103/"
                           , "user.bjackson.126939.PowhegPythia8_AU2CT10_ZZ_2e2tau_mll4_2pt5.tnt_103/"
                           , "user.bjackson.126940.PowhegPythia8_AU2CT10_ZZ_4mu_mll4_2pt5.tnt_103/"
                           , "user.bjackson.126941.PowhegPythia8_AU2CT10_ZZ_2mu2tau_mll4_2pt5.tnt_103/"
                           , "user.bjackson.126942.PowhegPythia8_AU2CT10_ZZ_4tau_mll4_2pt5.tnt_103/"
                           # gg > ZZ
                           , "user.bjackson.116600.gg2ZZJimmy_AUET2CT10_ZZ4lep.tnt_103/"
                           , "user.bjackson.116601.gg2ZZJimmy_AUET2CT10_ZZ4e.tnt_103/"
                           , "user.bjackson.116602.gg2ZZJimmy_AUET2CT10_ZZ4mu.tnt_103/"
                           , "user.bjackson.116603.gg2ZZJimmy_AUET2CT10_ZZ2e2mu.tnt_103/"
                           # VV > llqq
                           , "user.bjackson.157814.Sherpa_CT10_VVtoeeqq.tnt_103/"
                           , "user.bjackson.157815.Sherpa_CT10_VVtomumuqq.tnt_103/"
                           , "user.bjackson.157816.Sherpa_CT10_VVtotautauqq.tnt_103/"




                           , "user.bjackson.126949.PowhegPythia8_AU2CT10_ZZllnunu_ee_mll4.tnt_103/"
                           , "user.bjackson.126950.PowhegPythia8_AU2CT10_ZZllnunu_mm_mll4.tnt_103/"
                           , "user.bjackson.126951.PowhegPythia8_AU2CT10_ZZllnunu_tt_mll4.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)

    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.bkg_rare_part_1.merge2.tnt_103/'
    input_container_list = [
                           # triboson
                             "user.bjackson.167006.MadGraphPythia_AUET2BCTEQ6L1_WWWStar_lnulnulnu.tnt_103/"
                           , "user.bjackson.167007.MadGraphPythia_AUET2BCTEQ6L1_ZWWStar_lllnulnu.tnt_103/"
                           , "user.bjackson.167008.MadGraphPythia_AUET2BCTEQ6L1_ZZZStar_nunullll.tnt_103/"
                           # higgs
                           , "user.bjackson.160155.PowhegPythia8_AU2CT10_ggH125_ZZ4lep.tnt_103/"
                           , "user.bjackson.160205.PowhegPythia8_AU2CT10_VBFH125_ZZ4lep.tnt_103/"
                           , "user.bjackson.160655.PowhegPythia8_AU2CT10_ggH125_ZZllnunu.tnt_103/"
                           , "user.bjackson.160705.PowhegPythia8_AU2CT10_VBFH125_ZZllnunu.tnt_103/"
                           , "user.bjackson.161005.PowhegPythia8_AU2CT10_ggH125_WW2lep_EF_15_5.tnt_103/"
                           , "user.bjackson.161055.PowhegPythia8_AU2CT10_VBFH125_WW2lep_EF_15_5.tnt_103/"
                           , "user.bjackson.161305.Pythia8_AU2CTEQ6L1_ttH125_WWinclusive.tnt_103/"
                           , "user.bjackson.160255.Pythia8_AU2CTEQ6L1_WH125_ZZ4lep.tnt_103/"
                           , "user.bjackson.160305.Pythia8_AU2CTEQ6L1_ZH125_ZZ4lep.tnt_103/"
                           , "user.bjackson.160755.Pythia8_AU2CTEQ6L1_WH125_ZZllnunu.tnt_103/"
                           , "user.bjackson.160805.Pythia8_AU2CTEQ6L1_ZH125_ZZllnunu.tnt_103/"
                           , "user.bjackson.161105.Pythia8_AU2CTEQ6L1_WH125_WW2lep.tnt_103/"
                           , "user.bjackson.161155.Pythia8_AU2CTEQ6L1_ZH125_WW2lep.tnt_103/"
                           # tt+V
                           , "user.bjackson.119353.MadGraphPythia_AUET2BCTEQ6L1_ttbarW.tnt_103/"
                           , "user.bjackson.119354.MadGraphPythia_AUET2BCTEQ6L1_ttbarWj.tnt_103/"
                           , "user.bjackson.119355.MadGraphPythia_AUET2BCTEQ6L1_ttbarZ.tnt_103/"
                           , "user.bjackson.119356.MadGraphPythia_AUET2BCTEQ6L1_ttbarZj.tnt_103/"
                           , "user.bjackson.119583.MadgraphPythia_AUET2B_CTEQ6L1_ttbarWW.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)

    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.signal_ewk_slep.merge2.tnt_103/'
    input_container_list = [
                             "user.bjackson.144871.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_5.tnt_103/"
                           , "user.bjackson.144873.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_7.tnt_103/"
                           , "user.bjackson.144874.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_8.tnt_103/"
                           , "user.bjackson.144876.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_10.tnt_103/"
                           , "user.bjackson.144877.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_11.tnt_103/"
                           , "user.bjackson.144879.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_13.tnt_103/"
                           , "user.bjackson.144880.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_14.tnt_103/"
                           , "user.bjackson.144881.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_15.tnt_103/"
                           , "user.bjackson.144883.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_17.tnt_103/"
                           , "user.bjackson.144884.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_18.tnt_103/"
                           , "user.bjackson.144885.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_19.tnt_103/"
                           , "user.bjackson.144886.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_20.tnt_103/"
                           , "user.bjackson.144888.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_22.tnt_103/"
                           , "user.bjackson.144889.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_23.tnt_103/"
                           , "user.bjackson.144890.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_24.tnt_103/"
                           , "user.bjackson.144891.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_25.tnt_103/"
                           , "user.bjackson.144892.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_26.tnt_103/"
                           , "user.bjackson.144894.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_28.tnt_103/"
                           , "user.bjackson.144895.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_29.tnt_103/"
                           , "user.bjackson.144896.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_30.tnt_103/"
                           , "user.bjackson.157461.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_32.tnt_103/"
                           , "user.bjackson.157464.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_35.tnt_103/"
                           , "user.bjackson.157467.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_38.tnt_103/"
                           , "user.bjackson.157954.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_39.tnt_103/"
                           , "user.bjackson.157955.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_40.tnt_103/"
                           , "user.bjackson.157956.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_41.tnt_103/"
                           , "user.bjackson.157957.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_42.tnt_103/"
                           , "user.bjackson.157958.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_43.tnt_103/"
                           , "user.bjackson.157959.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_44.tnt_103/"
                           , "user.bjackson.157960.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_45.tnt_103/"
                           , "user.bjackson.157961.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_46.tnt_103/"
                           , "user.bjackson.157962.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_47.tnt_103/"
                           , "user.bjackson.157963.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_48.tnt_103/"
                           , "user.bjackson.157964.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_49.tnt_103/"
                           , "user.bjackson.157965.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_50.tnt_103/"
                           , "user.bjackson.157966.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_51.tnt_103/"
                           , "user.bjackson.157967.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_52.tnt_103/"
                           , "user.bjackson.157968.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcascade_53.tnt_103/"
                           , "user.bjackson.176531.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_54.tnt_103/"
                           , "user.bjackson.176532.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_55.tnt_103/"
                           , "user.bjackson.176533.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_56.tnt_103/"
                           , "user.bjackson.176534.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_57.tnt_103/"
                           , "user.bjackson.176535.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_58.tnt_103/"
                           , "user.bjackson.176536.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_59.tnt_103/"
                           , "user.bjackson.176537.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_60.tnt_103/"
                           , "user.bjackson.176538.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_61.tnt_103/"
                           , "user.bjackson.176539.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_62.tnt_103/"
                           , "user.bjackson.176540.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_63.tnt_103/"
                           , "user.bjackson.176541.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_64.tnt_103/"
                           , "user.bjackson.176542.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_65.tnt_103/"
                           , "user.bjackson.176543.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_66.tnt_103/"
                           , "user.bjackson.176544.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_67.tnt_103/"
                           , "user.bjackson.176545.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_68.tnt_103/"
                           , "user.bjackson.176546.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_69.tnt_103/"
                           , "user.bjackson.176547.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_70.tnt_103/"
                           , "user.bjackson.176548.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_71.tnt_103/"
                           , "user.bjackson.176549.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_72.tnt_103/"
                           , "user.bjackson.176550.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_73.tnt_103/"
                           , "user.bjackson.176551.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_74.tnt_103/"
                           , "user.bjackson.176552.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_75.tnt_103/"
                           , "user.bjackson.176553.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_76.tnt_103/"
                           , "user.bjackson.176554.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_77.tnt_103/"
                           , "user.bjackson.176555.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_78.tnt_103/"
                           , "user.bjackson.176556.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_79.tnt_103/"
                           , "user.bjackson.176557.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_slep_noWcasc_80.tnt_103/"
                           , "user.bjackson.179578.Herwigpp_UEEE3_CTEQ6L1_sM_wA_slep_C1N2_117_5_N1_82_5_2L.tnt_103/"
                           , "user.bjackson.179579.Herwigpp_UEEE3_CTEQ6L1_sM_wA_slep_C1N2_142_5_N1_107_5_2L.tnt_103/"
                           , "user.bjackson.179580.Herwigpp_UEEE3_CTEQ6L1_sM_wA_slep_C1N2_192_5_N1_157_5_2L.tnt_103/"
                           , "user.bjackson.179581.Herwigpp_UEEE3_CTEQ6L1_sM_wA_slep_C1N2_135_0_N1_115_0_2L.tnt_103/"
                           , "user.bjackson.179582.Herwigpp_UEEE3_CTEQ6L1_sM_wA_slep_C1N2_185_0_N1_165_0_2L.tnt_103/"
                           , "user.bjackson.179583.Herwigpp_UEEE3_CTEQ6L1_sM_wA_slep_C1N2_260_0_N1_240_0_2L.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)

    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.signal_ewk_noslep.merge2.tnt_103/'
    input_container_list = [
                             "user.bjackson.127994.Herwigpp_UEEE3_CTEQ6L1_sM_wA_noslep_C1N2_100_0_N1_75_0_2L.tnt_103/"
                           , "user.bjackson.127995.Herwigpp_UEEE3_CTEQ6L1_sM_wA_noslep_C1N2_125_0_N1_100_0_2L.tnt_103/"
                           , "user.bjackson.127996.Herwigpp_UEEE3_CTEQ6L1_sM_wA_noslep_C1N2_200_0_N1_150_0_2L.tnt_103/"
                           , "user.bjackson.164274.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_1.tnt_103/"
                           , "user.bjackson.164275.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_2.tnt_103/"
                           , "user.bjackson.164276.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_3.tnt_103/"
                           , "user.bjackson.164277.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_4.tnt_103/"
                           , "user.bjackson.164278.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_5.tnt_103/"
                           , "user.bjackson.164279.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_6.tnt_103/"
                           , "user.bjackson.164280.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_7.tnt_103/"
                           , "user.bjackson.164281.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_8.tnt_103/"
                           , "user.bjackson.164282.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_9.tnt_103/"
                           , "user.bjackson.164283.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_10.tnt_103/"
                           , "user.bjackson.164284.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_11.tnt_103/"
                           , "user.bjackson.164285.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_12.tnt_103/"
                           , "user.bjackson.164286.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_13.tnt_103/"
                           , "user.bjackson.164287.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_14.tnt_103/"
                           , "user.bjackson.164288.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_15.tnt_103/"
                           , "user.bjackson.164289.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_16.tnt_103/"
                           , "user.bjackson.164290.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_17.tnt_103/"
                           , "user.bjackson.164291.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_18.tnt_103/"
                           , "user.bjackson.164292.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_19.tnt_103/"
                           , "user.bjackson.164293.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_20.tnt_103/"
                           , "user.bjackson.164294.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_21.tnt_103/"
                           , "user.bjackson.164295.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_22.tnt_103/"
                           , "user.bjackson.164296.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_23.tnt_103/"
                           , "user.bjackson.164297.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_24.tnt_103/"
                           , "user.bjackson.164298.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_25.tnt_103/"
                           , "user.bjackson.164299.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_26.tnt_103/"
                           , "user.bjackson.164300.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_27.tnt_103/"
                           , "user.bjackson.164301.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_28.tnt_103/"
                           , "user.bjackson.164302.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_29.tnt_103/"
                           , "user.bjackson.164303.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_30.tnt_103/"
                           , "user.bjackson.164304.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_31.tnt_103/"
                           , "user.bjackson.164305.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_32.tnt_103/"
                           , "user.bjackson.164306.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_33.tnt_103/"
                           , "user.bjackson.164307.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_34.tnt_103/"
                           , "user.bjackson.164308.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_35.tnt_103/"
                           , "user.bjackson.164309.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_36.tnt_103/"
                           , "user.bjackson.164310.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_37.tnt_103/"
                           , "user.bjackson.164311.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_38.tnt_103/"
                           , "user.bjackson.164312.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_39.tnt_103/"
                           , "user.bjackson.164313.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_40.tnt_103/"
                           , "user.bjackson.164314.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_41.tnt_103/"
                           , "user.bjackson.164315.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_42.tnt_103/"
                           , "user.bjackson.164316.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_43.tnt_103/"
                           , "user.bjackson.164317.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_44.tnt_103/"
                           , "user.bjackson.164318.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_45.tnt_103/"
                           , "user.bjackson.164319.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_46.tnt_103/"
                           , "user.bjackson.164320.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_47.tnt_103/"
                           , "user.bjackson.164321.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_48.tnt_103/"
                           , "user.bjackson.164322.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_49.tnt_103/"
                           , "user.bjackson.164323.Herwigpp_UEEE3_CTEQ6L1_simplifiedModel_wA_noslep_lepW_50.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)

    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.signal_ewk_95.merge2.tnt_103/'
    input_container_list = [
                             "user.bjackson.186283.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_117_5_n1_82_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186284.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_135_0_n1_115_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186285.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_142_5_n1_107_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186287.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_192_5_n1_157_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186288.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_260_0_n1_240_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186289.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_110_0_n1_90_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186290.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_112_5_n1_12_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186291.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_112_5_n1_47_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186292.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_130_0_n1_30_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186293.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_132_5_n1_67_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186294.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_150_0_n1_50_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186295.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_155_0_n1_5_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186296.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_157_5_n1_92_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186297.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_175_0_n1_25_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186298.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_175_0_n1_75_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186299.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_200_0_n1_50_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186300.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_207_5_n1_142_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186301.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_225_0_n1_125_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186302.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_250_0_n1_0_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186303.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_250_0_n1_100_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186304.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_267_5_n1_232_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186305.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_282_5_n1_217_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186306.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_300_0_n1_200_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186307.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_300_0_n1_50_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186308.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_325_0_n1_175_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186309.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_350_0_n1_0_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186310.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_375_0_n1_125_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186311.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_392_5_n1_357_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186312.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_407_5_n1_342_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186313.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_425_0_n1_325_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186314.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_425_0_n1_75_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186315.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_450_0_n1_300_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186316.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_455_0_n1_420_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186317.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_470_0_n1_405_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186318.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_487_5_n1_387_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186319.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_500_0_n1_0_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186320.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_500_0_n1_250_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186321.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_512_5_n1_362_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186322.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_517_5_n1_482_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186323.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_532_5_n1_467_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186324.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_550_0_n1_200_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186325.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_550_0_n1_450_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186326.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_562_5_n1_312_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186327.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_575_0_n1_425_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186328.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_612_5_n1_262_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186329.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_625_0_n1_0_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186330.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_625_0_n1_125_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186331.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_625_0_n1_375_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186332.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_642_5_n1_607_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186333.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_675_0_n1_325_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186334.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_675_0_n1_575_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186335.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_687_5_n1_187_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186336.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_687_5_n1_62_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186338.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_750_0_n1_0_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186339.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_750_0_n1_125_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186340.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_750_0_n1_250_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186341.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_750_0_n1_500_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186342.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_800_0_n1_450_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186343.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_812_5_n1_187_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186344.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_812_5_n1_62_5_xsl_0_95.tnt_103/"
                           , "user.bjackson.186345.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_875_0_n1_0_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186346.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_875_0_n1_125_0_xsl_0_95.tnt_103/"
                           , "user.bjackson.186347.Herwigpp_UEEE3_CTEQ6L1_wA_c1n2_875_0_n1_375_0_xsl_0_95.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)


    # ------------------------------------------------------------------------------
    output_container_name = 'user.bjackson.signal_stop.part_1.merge2.tnt_103/'
    input_container_list = [
                             "user.bjackson.202632.MadGraphPythia_AUET2B_CTEQ6L1_SM_TT_directBL_100.tnt_103/"
                           , "user.bjackson.202633.MadGraphPythia_AUET2B_CTEQ6L1_SM_TT_directBL_200.tnt_103/"
                           , "user.bjackson.202634.MadGraphPythia_AUET2B_CTEQ6L1_SM_TT_directBL_300.tnt_103/"
                           , "user.bjackson.202635.MadGraphPythia_AUET2B_CTEQ6L1_SM_TT_directBL_400.tnt_103/"
                           , "user.bjackson.202636.MadGraphPythia_AUET2B_CTEQ6L1_SM_TT_directBL_500.tnt_103/"
                           , "user.bjackson.202637.MadGraphPythia_AUET2B_CTEQ6L1_SM_TT_directBL_600.tnt_103/"
                           , "user.bjackson.202638.MadGraphPythia_AUET2B_CTEQ6L1_SM_TT_directBL_700.tnt_103/"
                           , "user.bjackson.202639.MadGraphPythia_AUET2B_CTEQ6L1_SM_TT_directBL_800.tnt_103/"
                           , "user.bjackson.202640.MadGraphPythia_AUET2B_CTEQ6L1_SM_TT_directBL_900.tnt_103/"
                           , "user.bjackson.202641.MadGraphPythia_AUET2B_CTEQ6L1_SM_TT_directBL_1000.tnt_103/"
                           ]
    containerize(output_container_name, input_container_list)


# ==============================================================================
if __name__ == "__main__":
    main()
