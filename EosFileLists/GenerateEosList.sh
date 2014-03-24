#!/bin/sh
# ==============================================================================
# = 
# = Usage:
# =     source ../GenerateEosList.sh tnt_102 /eos/atlas/user/b/bjackson/tnt_102
# ==============================================================================

# ==============================================================================
EOS_LIST_PREFIX=${1}
EOS_PATH=${2}

# ------------------------------------------------------------------------------
echo "EOS_LIST_PREFIX: ${EOS_LIST_PREFIX}"
echo "EOS_PATH: ${EOS_PATH}"

# ------------------------------------------------------------------------------
function getDSTag {
  EOS_DIR=$1
  ds_tag=$(echo ${EOS_DIR} | sed "s#user\.bjackson\.\(.*\)\.tnt_.*#\1#g")
  echo $ds_tag
}

# ------------------------------------------------------------------------------
function getOutFileName {
  DS_TAG=$1
  out_file_name="${EOS_LIST_PREFIX}.${ds_tag}.txt"
  echo $out_file_name
}

# ------------------------------------------------------------------------------
for eos_dir in $(eos ls ${EOS_PATH}); do
  ds_tag=$(getDSTag ${eos_dir})
  out_file_name=$(getOutFileName ${ds_tag})

  if [[ -f ${out_file_name} ]] ; then
    echo "ERROR: File exists -- ${out_file_name}"
    echo "exiting!"
    return
  fi
done

# ------------------------------------------------------------------------------
total_num_eos_dirs=0
total_num_files=0
total_num_ds=0
for eos_dir in $(eos ls ${EOS_PATH}); do
  if [[ $eos_dir == *.txt ]] ; then
    continue
  fi

  # ds_tag=$(echo ${eos_dir} | sed "s#user\.bjackson\.\(.*\)\.tnt_.*#\1#g")
  # out_file_name="${EOS_LIST_PREFIX}.${ds_tag}.txt"
  ds_tag=$(getDSTag ${eos_dir})
  out_file_name=$(getOutFileName ${ds_tag})

  if [[ ! -f $out_file_name ]] ; then
    total_num_ds=$(( $total_num_ds + 1 ))
  fi

  echo "eos dir: $eos_dir"
  echo "ds tag: $ds_tag"
  echo "out file name: $out_file_name"

  for file_in_dir in $(eos ls ${EOS_PATH}/${eos_dir}); do
    if [[ ${file_in_dir} == *log.tgz* ]] ; then
      continue
    fi

    # echo "    root://eosatlas//${EOS_PATH}/${eos_dir}/${file_in_dir}"
    echo "root://eosatlas//${EOS_PATH}/${eos_dir}/${file_in_dir}" >> ${out_file_name}
    total_num_files=$(( $total_num_files + 1 ))
  done
  total_num_eos_dirs=$(( $total_num_eos_dirs + 1 ))
done

echo "total num files on eos: $total_num_files"
echo "total num eos dirs: $total_num_eos_dirs"
echo "total num data sets: $total_num_ds"
