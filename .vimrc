set cindent
set autoindent
set smartindent
set tabstop=4
set shiftwidth=4
set vb t_vb= 
set ruler
set incsearch
set hlsearch
set wildmenu
filetype on

nnoremap <leader><space> :nohlsearch<CR>

colorscheme badwolf

syntax enable
syntax on

au BufReadPost * if line("'\"") > 0|if line("'\"") <= line("$")|exe("norm '\"")|else|exe "norm$"|endif|endif
set t_ti= t_te=

set fileencodings=utf-8,gbk,ucs-bom,cp936
