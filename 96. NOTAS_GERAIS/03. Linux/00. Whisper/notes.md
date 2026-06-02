tenho sempre de exportar a libraria para fazer uso do fasterwhisper. 

export LD_LIBRARY_PATH="$VIRTUAL_ENV/lib/python3.12/site-packages/nvidia/cublas/lib:$VIRTUAL_ENV/lib/python3.12/site-packages/nvidia/cuda_nvrtc/lib:$LD_LIBRARY_PATH"

tornei permanente neste pc com ao adicionar ao bashrc

echo 'export LD_LIBRARY_PATH="$HOME/whisperenv/lib/python3.12/site-packages/nvidia/cublas/lib:$HOME/whisperenv/lib/python3.12/site-packages/nvidia/cuda_nvrtc/lib:$LD_LIBRARY_PATH"' >> ~/.bashrc