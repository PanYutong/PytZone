set nocompatible

filetype on
syntax on
filetype plugin indent on

execute pathogen#infect()

set smartindent
set hlsearch
set incsearch
nnoremap <leader><space> :nohlsearch<CR>

colo delek

au BufRead,BufNewFile *.txx set filetype=cpp
