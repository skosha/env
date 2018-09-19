#!/usr/bin bash

if [ -d '~/env' ]; then

    [ -d ~/bin ] || mkdir ~/bin
    cp -af ~/env/bin/* ~/bin/

    [ -d ~/.fzf ] || mkdir ~/.fzf
    cp -af ~/env/fzf/* ~/.fzf/

    [ -d ~/.tmux ] || mkdir -p ~/.tmux
    [ -d ~/.tmuxp ] || mkdir -p ~/.tmuxp
    cp -af ~/env/tmuxp/* ~/.tmuxp/

    [ -d ~/.vim ] || mkdir ~/.vim
    cp -af ~/env/vim/* ~/.vim/

    [ -d ~/dot-config ] || mkdir ~/dot-config
    ln -s ~/env/dot-files/aliasrc ~/.dot-config/.aliasrc
    ln -s ~/env/dot-files/mostrc ~/.dot-config/.mostrc
    ln -s ~/env/dot-files/fzf.bash ~/.fzf.bash
    ln -s ~/env/dot-files/gitignore ~/.gitignore
    ln -s ~/env/dot-files/screenrc ~/.screenrc
    ln -s ~/env/dot-files/tmux.conf ~/.tmux.conf
    ln -s ~/env/dot-files/tmux-linux.conf ~/.tmux-linux.conf
    ln -s ~/env/dot-files/tmux-osx.conf ~/.tmux-osx.conf
    ln -s ~/env/dot-files/vimrc ~/.vimrc
    ln -s ~/env/dot-files/zshrc ~/.zshrc
    echo ~/env/dot-files/bashrc_cat >> ~/.bashrc
fi
