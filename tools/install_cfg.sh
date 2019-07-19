#!/bin/bash

TEMP_DIR=$HOME/config_tmp
ENV_DIR=$HOME/env

if [ -d '$ENV_DIR' ]; then
    git clone --recursive https://github.com/skosha/env.git $HOME/env
fi

# Unzip the files
if [ -f $1 ]; then
    ARCH_FILE=$(realpath $1)
    mkdir -p $TEMP_DIR && cd $TEMP_DIR
    case "$ARCH_FILE" in
        *.tar.bz2)   tar xjf "$ARCH_FILE"     ;;
        *.tar.gz)    tar xzf "$ARCH_FILE"     ;;
        *.bz2)       bunzip2 "$ARCH_FILE"     ;;
        *.rar)       unrar e "$ARCH_FILE"     ;;
        *.gz)        gunzip "$ARCH_FILE"      ;;
        *.tar)       tar xf "$ARCH_FILE"      ;;
        *.tbz2)      tar xjf "$ARCH_FILE"     ;;
        *.tgz)       tar xzf "$ARCH_FILE"     ;;
        *.zip)       unzip "$ARCH_FILE"       ;;
        *)           echo "'$ARCH_FILE' cannot be extracted by $SCRIPTNAME" ;;
    esac
    cd $HOME
fi

# Get this distro
DISTRO=$( cat /etc/*-release | tr [:upper:] [:lower:] | grep -Poi '(debian|ubuntu|red hat|centos)' | uniq )
if [ -z $DISTRO ]; then
    DISTRO='unknown'
fi
echo "Detected Linux distribution: $DISTRO"

# Get bin files from the env git repo
[ -d $HOME/bin ] || mkdir ~/bin
cp -af $ENV_DIR/bin/* $HOME/bin/
[ -f $HOME/bin/fzf ] || chmod +x $HOME/bin/fzf

[ -d $HOME/dot-files ] || mkdir $HOME/dot-files

ln -s $ENV_DIR/dot-files/aliasrc $HOME/.dot-files/.aliasrc
ln -s $ENV_DIR/dot-files/mostrc $HOME/.dot-files/.mostrc
ln -s $ENV_DIR/dot-files/gitignore $HOME/.gitignore
ln -s $ENV_DIR/dot-files/screenrc $HOME/.screenrc
ln -s $ENV_DIR/dot-files/zshrc $HOME/.zshrc

# Install fzf
[ -d $HOME/.fzf ] || mkdir $HOME/.fzf
cp -af $ENV_DIR/fzf/* $HOME/.fzf/
source $HOME/.fzf/install
ln -s $HOME/env/dot-files/fzf.bash $HOME/.fzf.bash

# Install tmux
command -v tmux > /dev/null 2>&1 ||
if [ "$DISTRO" == "ubuntu" ] ; then
    sudo apt-get install tmux
    [ -d $HOME/.tmux ] || mkdir -p $HOME/.tmux
    ln -s $ENV_DIR/dot-files/tmux.conf $HOME/.tmux.conf
    ln -s $ENV_DIR/dot-files/tmux-linux.conf $HOME/.tmux-linux.conf
    ln -s $ENV_DIR/dot-files/tmux-osx.conf $HOME/.tmux-osx.conf

    # Install tmuxp
    command -v tmuxp > /dev/null 2>&1 ||
    pip install --user tmuxp
    [ -d $HOME/.tmuxp ] || mkdir -p $HOME/.tmuxp
    cp -af $HOME/env/tmuxp/* $HOME/.tmuxp/

    # Install xsel, used by tmux-yank
    if [ "$DISTRO" == "ubuntu" ] ; then
        sudo apt-get install xsel
    fi

    # Tmux plugins and configs
    mkdir -p $HOME/.tmux
    cp -a $TEMP_DIR/.tmux/* $HOME/.tmux/*
    mkdir -p $HOME/tools/tmux_plugins
    cp -a $TEMP_DIR/tmux_plugins/* $HOME/tools/tmux_plugins/
fi

echo $HOME/env/dot-files/bashrc_cat >> $HOME/.bashrc

# Install vim config
mkdir -p $HOME/.vim
mkdir -p $HOME/.vim/temp_dirs/undodir
mkdir -p $HOME/.vim/bundle
git clone https://github.com/VundleVim/Vundle.vim.git $HOME/.vim/bundle/Vundle.vim
ln -s $ENV_DIR/dot-files/vimrc $HOME/.vimrc
vim +PluginInstall +qall
mkdir -p $HOME/.vim/plugin
ln -s $ENV_DIR/vim/plugin/* $HOME/.vim/plugin/*
cp -s $ENV_DIR/colors $HOME/.vim/
cp -a $TEMP_DIR/.vim/* $HOME/.vim/

# Install local
mkdir -p $HOME/.local
cp -a $TEMP_DIR/.local/* $HOME/.local/

# Install adb tools
sudo apt-get install android-tools-adb android-tools-fastboot
sudo usermod -a -G plugdev $USER

# Install synergy
command -v synergyc > /dev/null 2>&1 ||
if [ -f $TEMP_DIR/synergy-*.deb ] ; then
    PACKAGE_NAME=$(ls -d -1 $TEMP_DIR/synergy*)
    sudo apt -f install $PACKAGE_NAME
fi

# Gitignore
[ -f $DOT_DIR/.gitignore ] && git config --global core.excludesfile $CONFIG/.gitignore

# At the end, delete the temp directory
rm -rf $TEMP_DIR > /dev/null
