#!/usr/bin/env bash
module purge
# >>> conda initialize >>>
# !! Contents within this block are managed by 'conda init' !!
__conda_setup="$('/mnt/storage/software/languages/anaconda/Anaconda3-2019.07/bin/conda' 'shell.bash' 'hook' 2> /dev/null)"
if [ $? -eq 0 ]; then
    eval "$__conda_setup"
else
    if [ -f "/mnt/storage/software/languages/anaconda/Anaconda3-2019.07/etc/profile.d/conda.sh" ]; then
        . "/mnt/storage/software/languages/anaconda/Anaconda3-2019.07/etc/profile.d/conda.sh"
    else
        export PATH="/mnt/storage/software/languages/anaconda/Anaconda3-2019.07/bin:$PATH"
    fi
fi
unset __conda_setup
# <<< conda initialize <<<

conda activate bm4d
module load build/gcc-7.2.0
rm -rf build
mkdir build
cd build
cmake -DOpenCV_DIR=$CONDA_PREIFX/lib/cmake/opencv4  ..
make
