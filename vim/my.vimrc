set nocompatible              " be iMproved, required

silent! py3 pass

set rtp+=~/.vim/bundle/Vundle.vim

call vundle#begin()

Plugin 'Valloric/YouCompleteMe'

Plugin 'tomasr/molokai'

call vundle#end()            " required

syntax on

colorscheme molokai

" 修改leader键
let mapleader = ','
let g:mapleader = ','


noremap H ^
noremap L $


" When editing a file, always jump to the last cursor position
au BufWinLeave * mkview
au BufWinEnter * silent loadview

" 突出显示当前列
set cursorcolumn
" 突出显示当前行
set cursorline

set wildmenu
" Ignore compiled files
set wildignore=
set wildignore=*.o,*~,*.pyc,*.class,*.swp,*.bak,*.svn

" 显示当前的行号列号
set ruler
" 在状态栏显示正在输入的命令
set showcmd
" 左下角显示当前vim模式
set showmode

set number
set nowrap

" 相对行号: 行号变成相对，可以用 nj/nk 进行跳转
set relativenumber number
au FocusLost * :set norelativenumber number
au FocusGained * :set relativenumber
" 插入模式下用绝对行号, 普通模式下用相对
autocmd InsertEnter * :set norelativenumber number
autocmd InsertLeave * :set relativenumber
function! NumberToggle()
  if(&relativenumber == 1)
    set norelativenumber number
  else
    set relativenumber
  endif
endfunc
nnoremap <C-n> :call NumberToggle()<cr>

set smartindent
set autoindent

" tab相关变更
" 设置Tab键的宽度        [等同的空格个数]
set tabstop=4
" 每一次缩进对应的空格数
set shiftwidth=4
" 按退格键时可以一次删掉 4 个空格
set softtabstop=4
" insert tabs on the start of a line according to shiftwidth, not tabstop 按退格键时可以一次删掉 4 个空格
set smarttab

" 将Tab自动转化成空格[需要输入真正的Tab键时，使用 Ctrl+V + Tab]
set expandtab
" 缩进时，取整 use multiple of shiftwidth when indenting with '<' and '>'
set shiftround


" 进入搜索Use sane regexes"
nnoremap / /\v
vnoremap / /\v


" for # indent, python文件中输入新行时#号注释不切回行首
autocmd BufNewFile,BufRead *.py inoremap # X<c-h>#

" 复制选中区到系统剪切板中
vnoremap <leader>y "+y


" 具体编辑文件类型的一般设置，比如不要 tab 等
autocmd FileType python set tabstop=4 shiftwidth=4 expandtab ai
" autocmd FileType ruby,javascript,html,css,xml,cpp,markdown set tabstop=2 shiftwidth=2 softtabstop=2 exp
autocmd FileType cpp,markdown set tabstop=2 shiftwidth=2 softtabstop=2 expandtab ai
autocmd BufRead,BufNewFile *.md,*.mkd,*.markdown set filetype=markdown.mkd

" 设置可以高亮的关键字
if has("autocmd")
  " Highlight TODO, FIXME, NOTE, etc.
  if v:version > 701
    autocmd Syntax * call matchadd('Todo',  '\W\zs\(TODO\|FIXME\|CHANGED\|DONE\|XXX\|BUG\|HACK\)')
    autocmd Syntax * call matchadd('Debug', '\W\zs\(NOTE\|INFO\|IDEA\|NOTICE\)')
  endif
endif

