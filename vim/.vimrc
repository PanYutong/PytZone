set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
source ~/.vundle.vimrc
call vundle#end()            " required
filetype plugin indent on    " required

source ~/.a.vimrc
