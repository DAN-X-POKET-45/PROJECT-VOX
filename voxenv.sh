#Variáveis de ambiente
export PROJECT_VOX_PATH=~/PROJECT-VOX
export PROJECT_VOX_ENV_VERSION=1.0
export TERM=xterm-256color

#Entrada de diretórios
cd $PROJECT_VOX_PATH

#Inicializaçao do tmux
tmux new-session -d -s voxadm

#Criação das janelas
tmux rename-window -t voxadm:0  "PROJECT-VOX EDITOR"
tmux split-window -v -t voxadm:0 -d

#Seleção de layout
tmux select-layout -t voxadm:0 main-horizontal

#Vinculação ao tmux
tmux attach-session -t voxadm
