#!/bin/bash

DATA_MC=''
IS_AF2='False'
IS_EGAMMA='True'
SAMPLE_NAME=''
VERSION='1'
IS_PRESEL='True'
PRESEL_FLAG='.'
while [ "$1" != "" ]; do
  case $1 in
    --data )        DATA_MC='data'
                    ;;
    --mc )          DATA_MC='mc'
                    ;;
    --af2 )         IS_AF2='True'
                    ;;
    --egamma )      IS_EGAMMA='True'
                    ;;
    --muon )        IS_EGAMMA='False'
                    ;;
    --sample-name ) shift
                    SAMPLE_NAME=$1
                    ;;
    --version )     shift
                    VERSION=$1
                    ;;
    --presel )      IS_PRESEL='True'
                    ;;
    --raw )         IS_PRESEL='False'
                    ;;
    --presel-flag ) shift
                    IS_PRESEL='True'
                    PRESEL_FLAG=$1
                    ;;
    * )             echo "$1 is an invalid flag"
  esac
  shift
done

if [[ "${SAMPLE_NAME}" == '' ]]
then
  echo "Invalid sample name"
  exit 0
fi

CONFIG_FILE="job_config.cut_flow.${SAMPLE_NAME}.yml"
echo "config file: ${CONFIG_FILE}"
##
##BASE_IN_FILE_PATH=/exports/project/data_d07_4/bjackson/
##if [[ "${DATA_MC}" == "data" ]]
##then
##  BASE_IN_FILE_PATH="${BASE_IN_FILE_PATH}/data12/"
##else
##  BASE_IN_FILE_PATH="${BASE_IN_FILE_PATH}/mc12/"
##fi
##echo "Setting in file path to:"
##echo "    ${BASE_IN_FILE_PATH}"

echo "" >> $CONFIG_FILE
echo "Type:             ${DATA_MC}" >> $CONFIG_FILE
echo "OutputLevel:      INFO" >> $CONFIG_FILE
echo "OutputDirectory:  /home/elhines/Susy_presel_12Feb/" >> $CONFIG_FILE
echo "OutputDirectory:  /disk/userdata00/atlas_data2/${USER}/SUSY/00.02.05/" >> $CONFIG_FILE
echo "NEventsMax:       -1" >> $CONFIG_FILE
echo "is_af2:           ${IS_AF2}" >> $CONFIG_FILE
echo "SuperVerboseInfo: False" >> $CONFIG_FILE
echo "PrintEventInfo:   False" >> $CONFIG_FILE
echo "Version:          ${VERSION}" >> $CONFIG_FILE
echo "CycleName:        SusyDiLeptonCutFlowCycle" >> $CONFIG_FILE
echo "SampleName:       ${SAMPLE_NAME}" >> $CONFIG_FILE
echo "" >> $CONFIG_FILE
if [ "$IS_PRESEL" == "True" ]; then
  echo "input_tree_name:  presel" >> $CONFIG_FILE
else
  echo "input_tree_name:  susy" >> $CONFIG_FILE
fi
echo "output_tree_name: output" >> $CONFIG_FILE
echo "is_egamma_stream: ${IS_EGAMMA}" >> $CONFIG_FILE
echo "" >> $CONFIG_FILE
echo "" >> $CONFIG_FILE

if [[ ${DATA_MC} == "data" ]]
then
  echo "UserConfigFile: ${SFRAME_DIR}/../run/tier3_configs/user_config.cut_flow.data.yml" >> $CONFIG_FILE
  if [[ "$IS_PRESEL" == "True" ]]; then
    REL_PATH_ON_SRM=user/bjackson/data_12_8TeV/
  else
    REL_PATH_ON_SRM=data12_8TeV/NTUP_SUSY/e1434_s1499_s1504_r3658_r3549_p1328/
  fi
else
  echo "UserConfigFile: ${SFRAME_DIR}/../run/tier3_configs/user_config.cut_flow.mc.yml" >> $CONFIG_FILE
  if [[ "$IS_PRESEL" == "True" ]]; then
    REL_PATH_ON_SRM=user/bjackson/mc12_8TeV/
  else
    REL_PATH_ON_SRM=mc12_8TeV/NTUP_SUSY/e1434_s1499_s1504_r3658_r3549_p1328/
  fi
fi

echo "InputFiles:" >> $CONFIG_FILE

NUM_FILES=0

XRD_COMMAND="xrd hn.at3f dirlist /srm/atlaslocalgroupdisk/${REL_PATH_ON_SRM} | sed 's%^.* \([^ ]*$\)%\1%' | sort | uniq | grep \"${PRESEL_FLAG}\.\" | grep ${SAMPLE_NAME}"
ds_list="   `xrd hn.at3f dirlist /srm/atlaslocalgroupdisk/${REL_PATH_ON_SRM} | sed 's%^.* \([^ ]*$\)%\1%' | sort | uniq | grep \"${PRESEL_FLAG}\.\" | grep ${SAMPLE_NAME}`"
echo "    xrd command:"
echo "        $XRD_COMMAND"
echo "-------------------------------------------------------------------------"
for ds_name in ${ds_list}
do
  # echo ${ds_name}
  if [[ "${ds_name}" =~ "/srm/.*" ]] ; then
    for in_file in `xrd hn.at3f dirlist ${ds_name} | grep .root*` ; do 
      if [[ "${in_file}" =~ "/srm/.*" ]] ; then
        echo "        Adding: root://hn.at3f/${in_file}"    
        echo " - root://hn.at3f/${in_file}" >> $CONFIG_FILE
        let NUM_FILES+=1
      fi
    done
  fi
done

echo "Found $NUM_FILES files"