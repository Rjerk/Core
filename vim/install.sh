cp my.vimrc ~/.vimrc -f

git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim

git clone https://github.com/Valloric/YouCompleteMe ~/.vim/bundle/YouCompleteMe

cd ~/.vim/bundle/YouCompleteMe

git submodule update --init --recursive

python install.py --clang-completer

cd ~
