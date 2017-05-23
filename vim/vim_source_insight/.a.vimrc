syntax enable
set undodir=~/.vimundo/
set hidden
" set mouse=a
set history=50
set nobackup

" Add a line at 81 column
set colorcolumn=81

nnoremap <leader><space> :nohlsearch<CR>

filetype plugin indent on
"set cindent
set tabstop=2
set shiftwidth=2
set softtabstop=2
set expandtab
set number
set showcmd
set showmatch
set smartcase
set incsearch
set hlsearch
:hi Search ctermbg=7
set autowrite
"set foldmethod=syntax
set fileencoding=utf-8
set fileencodings=utf-8,default,gb2312

" let g:solarized_termcolors=256

set background=dark
colorscheme badwolf

map f <Plug>(easymotion-prefix)

source $VIMRUNTIME/vimrc_example.vim

let g:pydiction_location = '~/.vim/bundle/pydiction/complete-dict'

set nobackup
set nowritebackup
set wildmenu

"""""""""" wesleyche/SrcExpl
source ~/.se.vimrc

"""""""""" TagList
" taglist configuration
let Tlist_Ctags_Cmd ='/usr/bin/ctags'
" Taglist plugin mapping
" noremap <silent> <Leader>t :TlistToggle<CR>
:noremap <F1> <c-w><c-p>
:noremap <F2> <c-w><c-w>
:noremap <F3> :TlistToggle<CR>:NERDTreeToggle<CR>:SrcExplToggle<CR><c-w><c-l>
:noremap <F4> :set nu!<CR>:set paste!<CR>
" Taglist plugin config
let Tlist_Use_Right_Window = 1
let Tlist_Inc_Winwidth = 0
let Tlist_WinWidth = 30
" let Tlist_GainFocus_On_ToggleOpen= 1
" let Tlist_Show_One_File = 1
let Tlist_Exit_OnlyWindow = 1
let Tlist_Use_SingleClick = 1
" let Tlist_Auto_Open = 1
" let Tlist_File_Fold_Auto_Close = 1
autocmd BufWritePost *.cpp :TlistUpdate
autocmd BufWritePost *.h :TlistUpdate
autocmd BufWritePost *.jce :TlistUpdate

"""""""""" NerdTree (and vimenter events)
" nnoremap <C-n> :NERDTreeToggle<CR>
autocmd vimenter *.cpp NERDTree
autocmd vimenter *.cpp Tlist
autocmd vimenter *.cpp SrcExpl
autocmd VimEnter *.cpp wincmd w

"autocmd BufNew   * wincmd p
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTreeType") && b:NERDTreeType == "primary") | q | endif

"""""""""" Function for NerdTree + Taglist (auto close when 2 windows)

function! CheckLeftBuffers()
  if tabpagenr('$') == 1
    let i = 1
    while i <= winnr('$')
      " echom getbufvar(winbufnr(i), '&buftype')
      if getbufvar(winbufnr(i), '&buftype') == 'help' ||
          \ getbufvar(winbufnr(i), '&buftype') == 'quickfix' ||
          \ exists('t:NERDTreeBufName') &&
          \   bufname(winbufnr(i)) == t:NERDTreeBufName ||
          \ bufname(winbufnr(i)) == '__Tag_List__' ||
          \ bufname(winbufnr(i)) == 'Source_Explorer' ||
          \ getwinvar(i, 'SrcExpl') == 1
        let i += 1
      else
        break
      endif
    endwhile
    if i == winnr('$') + 1
      qall
    endif
    unlet i
  endif
endfunction
autocmd BufEnter * call CheckLeftBuffers()

"""""""""" tabline

hi TabLine      ctermfg=Black  ctermbg=Green     cterm=NONE
hi TabLineFill  ctermfg=Black  ctermbg=Green     cterm=NONE
hi TabLineSel   ctermfg=White  ctermbg=DarkBlue  cterm=NONE

"""""""""" airline
let g:airline#extensions#tabline#enabled = 1
let g:airline_powerline_fonts = 1

set clipboard=unnamed
