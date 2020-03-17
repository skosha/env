syntax on
set t_Co=256
set background=dark

if has('win32')
    "colorscheme solarized
    "colorscheme one
    "colorscheme molokai
    "colorscheme inkpot
    "colorscheme jellybeans
    "colorscheme darkmate
    colorscheme PaperColor
else
    "colorscheme contrasty
    "colorscheme jellybeans
    colorscheme PaperColor
endif

" Set path to current and sub-directories only, will not search other system related directories
if has('win32')
    set path=./**
else
    set path=.,,**
endif
set path+=./**                  " Add the current directory to path

" tabs and indents
set autoindent                  " set auto indent on
set copyindent                  " copy the previous indentation on autoindenting
set smartindent                 " Set smart indent on
set shiftround                  " Round indent to nearest shiftwidth multiple
set smarttab                    " Set smart tabbing on
set shiftwidth=4                " Shiftwidth to be 4
set softtabstop=4
set expandtab                   " Expand tab to spaces
set tabstop=4                   " 1 tab = 4 spaces

set number                      " line numbers
set showmatch                   " Show the matching bracket
set matchtime=1                 " shorten the jump time for showmatch
set ignorecase                  " Ignore case in search
set smartcase                   " Ignore case in searches excepted if an uppercase letter is used
set hls                         " Highlight search
set incsearch                   " Incremental search
set matchpairs+=<:>             " Add < > to match pairs command
set ruler                       " Set ruler on
set backspace=indent,eol,start  " Backspace over everything
set autowrite                   " Auto write modified files
set autowriteall                " Auto write modified files
set autoread                    " Auto load files modified outside of Vim
set equalalways                 " Have all windows of equal size
set virtualedit=block           " Allow visual block mode to select blank spaces as well
set formatoptions+=M            " don't insert space when joining lines
set formatoptions+=j            " remove comment leader when joining lines with comments
set formatoptions+=n            " when editing text recognize numbered lists and indent them
set formatoptions+=2            " use the indent of the second line of para for the rest of the para
set formatoptions+=q            " allow formatting of comments with "gq"
set shortmess=filtIoOA          " shorten up messages
set report=0                    " always get report for all the line changes
set confirm                     " get a dialog when :q, :w, or :wq fails"
set startofline                 " Jump to non-blank start of line
set laststatus=2                " Always show the statusline
set hidden                      " Don't complain about unsaved files when switching buffers.
set gdefault                    " use g in substitute by default. Adding 'g' flag to the command will now toggle it
set lazyredraw                  " Don't redraw while executing macros (good performance co#nfig)
set ttyfast                     " Performance improvements
set foldcolumn=1                " Add a bit extra margin to the left
set mouse=a                     " use mouse in all modes

" Start scrolling three lines before the horizontal window border
set scrolloff=3

" Easy pasting to windows apps - http://vim.wikia.com/wiki/VimTip21
" yank always copies to unnamed register, so it is available in windows clipboard for other applications.
if !has('win32') && has("clipboard")
  set clipboard=unnamed " copy to the system clipboard

  if has("unnamedplus") " X11 support
    set clipboard+=unnamedplus
  endif
endif

if has('mac')
    " copy to clipboard with Ctrl-C
    map <C-x> :!pbcopy<CR>
    vmap <C-c> :w !pbcopy<CR><CR>
    " paste from clipboard with Ctrl-V
    set pastetoggle=<F2>
    "noremap <C-v> <F10><C-r>+<F10>
endif

" Default split to right and below
set splitbelow
set splitright

set viminfo+=!  " Save and restore global variables.

" Ignore bin files in file search
set wildignore+=*.o,*.d,*.a,*.obj,*.bak,*.exe,*.cfa,*.gz,*.zip,*.bin,*.db,*.dat,*.jpg,*.JPG,*.raw,*.tar,*.out,*.elf
set wildignore+=*.bmp,*.gif,*.ico,*.jpg,*.png,*.ico
set wildignore+=*.pdf,*.psd
set wildignore+=*~,*.pyc
if has('win32')
    set wildignore+=*\\.git\\*,*\\.hg\\*,*\\.svn\\*  " Windows ('noshellslash')
else
    set wildignore+=*/.git/*,*/.hg/*,*/.svn/*,*/.DS_Store     " Linux/MacOSX
    set wildignore+=*/tmp,*/dist,*/.nuxt
endif

" Use wild chars in Vim search
set wildmenu            " see :h 'wildmenu'
set wildmode=list:longest,full  " see :h 'wildmode' for all the possible values
set wildchar=<Tab>      " <Tab> to complete in cmdline.
set wildignorecase      " ignore case when completing file names and directories.

" diff mode
set diffopt=vertical,filler,context:10,foldcolumn:1

" Session configs
set sessionoptions-=options     " do not store global and local values in a session
set sessionoptions-=folds       " do not store folds
set sessionoptions+=blank       " blank windows
set sessionoptions+=buffers     " hidden and unloaded buffers
set sessionoptions+=curdir      " current directory
set sessionoptions-=help        " do not store help window
set sessionoptions+=tabpages    " all tab pages
set sessionoptions+=winsize     " window sizes
set sessionoptions+=winpos      " position of the whole Vim window

" [ completion options ]
set complete=.,w,b,t,i,u,k       " completion buffers
"            | | | | | | |
"            | | | | | | `-dict
"            | | | | | `-unloaded buffers
"            | | | | `-include files
"            | | | `-tags
"            | | `-other loaded buffers
"            | `-windows buffers
"            `-the current buffer
set completeopt=menuone " menu,menuone,longest,preview
set completeopt-=preview " dont show preview window

" Netrw config
let g:netrw_liststyle=1     " Long style listing
let g:netrw_keepdir=1       " Keep current directory immune from browsing directory
let g:netrw_sort_by="exten"

" magic/nomagic: changes special chars that can be used in search patterns
set magic
    " \v: 'very magic', make every character except a-zA-Z0-9 and '_' have special meaning
    " use \v and \V to switch 'very magic' on or off.
    " \m, \M: 'magic' mode.
    " use \m and \M to switch 'magic' on or off.

" Enable filetype plugins
filetype plugin on
filetype indent on

if has("autocmd")

    augroup trail_whitespace
        autocmd!
        " Automatically remove all trailing whitespace
        autocmd BufWritePre * :%s/\s\+$//e
    augroup END

    " automatically rebalance windows on vim resize
    augroup window_resize
        autocmd!
        autocmd VimResized * :wincmd =
    augroup END

    " netrw immediately activate when using [g]vim without any filenames, showing the current directory
    augroup VimStartup
        autocmd!
        autocmd VimEnter * if expand("%") == "" | e . | endif
    augroup END

    augroup numbertoggle
        autocmd!
        autocmd WinEnter,BufEnter,FocusGained,InsertLeave * :setlocal relativenumber
        autocmd WinLeave,BufLeave,FocusLost,InsertEnter   * :setlocal norelativenumber
    augroup END

    augroup cursorlineToggle
        autocmd!
        " set cursorline only in normal mode
        autocmd InsertLeave,WinEnter * set cursorline
        autocmd InsertLeave,WinEnter * set cursorcolumn
        autocmd InsertEnter,WinLeave * set nocursorline
        autocmd InsertEnter,WinLeave * set nocursorcolumn
    augroup END

    " Make sure that enter is never overriden in the quickfix window
    autocmd BufReadPost quickfix nnoremap <buffer> <CR> <CR>
endif

 " No Residue files
set noswapfile
set nobackup

" Disable writebackup because some tools have issues with it:
" https://github.com/neoclide/coc.nvim/issues/649
set nowritebackup

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Turn persistent undo on
"    means that you can undo even when you close a buffer/VIM
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
try
    if has("win32")
        set undodir=$HOME/vimfiles/temp_dirs/undodir
    else
        set undodir=$HOME/.vim/temp_dirs/undodir
    endif
    set undofile
catch
endtry

" {{{ <A- key work-around for gnome terminals
let c='a'
while c <= 'z'
  exec "set <A-".c.">=\e".c
  exec "imap \e".c." <A-".c.">"
  let c = nr2char(1+char2nr(c))
endw

set ttimeout ttimeoutlen=50
" }}} <A- key workaround end

" Mappings {{{

let mapleader='\'

" `Ctrl-U` in insert mode deletes a lot. Use `Ctrl-G` u to first break undo,
" so that you can undo `Ctrl-U` without undoing what you typed before it.
inoremap <C-U> <C-G>u<C-U>

" Vim's auto indentation feature does not work properly with text copied from outisde of Vim. Press the <F2> key to toggle paste mode on/off.
nnoremap <F2> :set invpaste paste?<CR>
imap <F2> <C-O>:set invpaste paste?<CR>
set pastetoggle=<F2>

noremap <C-n> :call g:ToggleNuMode()<CR>

" Save file with C-s
nnoremap <silent><C-s> :w<CR>
inoremap <C-s> <ESC>:w<CR>

" Use '\,' to add a space
nmap <Leader>, i<Space><Esc>

" Add semi-colon at the end
nnoremap <Leader>; A;

" Use line diff
noremap <Leader>ldt :Linediff<CR>
noremap <Leader>ldo :LinediffReset<CR>

" Open last accessed tab
let g:lasttab = 1
nmap tl :exe "tabn ".g:lasttab<CR>
au TabLeave * let g:lasttab = tabpagenr()

" duplicate tab
noremap _t :tab split<CR>

" Disable F1 for help screen - I open this accidentally all the time!
nmap <F1> :echo<CR>
imap <F1> <C-o>:echo<CR>

" Use <F9> to toggle between open windows
nmap <F9> <C-w><C-w>

" Toggle back and forth between current and previous buffer
map <Leader>b :buffer#<cr>

" Y yanks from the cursor to the end of line as expected. See :help Y.
nnoremap Y y$

" Absolute movement for word-wrapped lines.
nnoremap j gj
nnoremap k gk

" Comment-ify the visually selected block using C style comments
vmap <Leader>* omxomy<ESC>`xO/*<ESC>`yo*/<ESC>

" search for visually highlighted text
" Visual mode pressing * or # searches for the current selection
" Super useful! From an idea by Michael Naumann
vnoremap <silent> * :<C-u>call VisualSelection('')<CR>/<C-R>=@/<CR><CR>
vnoremap <silent> # :<C-u>call VisualSelection('')<CR>?<C-R>=@/<CR><CR>

" clear the search buffer when hitting return
nnoremap <silent> <CR> :nohlsearch<cr>

" Map double-click to search the word under cursor
nnoremap <silent> <2-LeftMouse> :let @/='\V'.escape(expand('<cword>'), '\')<cr>:set hls<cr>

" Toggle scrollbind for all open windows in the tab
nnoremap <silent> <Leader>j :windo set scb!

" Use <Leader>hx to toggle between binary/hex
noremap <silent> <Leader>hx :call HexMe()<CR>

" replace ascii hex under cursor with its char equivalent
noremap <silent> _c :call Ascii2Char()<CR>

" replace char under cursor with its ascii hex equivalent
noremap <silent> _a :call Char2Ascii()<CR>

" Shortcuts for navigating quickfix list
noremap ]q :cnext<CR>
noremap [q :cprev<CR>
noremap ]Q :cnfile<CR>
noremap [Q :cpfile<CR>
noremap <Leader>q :cfirst<CR>
noremap <Leader>Q :clast<CR>
noremap <Leader>qo :cwindow<CR>
noremap <Leader>qc :cclose<CR>

" :W sudo saves the file
" (useful for handling the permission-denied error)
if !has("win32")
    command! W w !sudo tee % > /dev/null
endif

" Shortcut for toggling a diff in a window
nnoremap <Leader>a :call WinStartDiff()<CR>

" Add #if 0 ... #endif around a block of code
map ;' mz'aO#if 0<ESC>'zo#endif<ESC>

" Add #ifdef <> ... #endif around a block of code
map ;; mz'aO#ifdef <C-r>"<ESC>'zo#endif /* <C-r>" */<ESC>

" Add curly braces around a piece of code
map ;[ mz'aO{<ESC>lx<ESC>'zo}<ESC>'a=aB

map <Leader>cc :s/\/\/\(.*\)/\/\*\1 \*\/*<CR> */

" remove wrapped function call from expression
nnoremap ;ac diw%x<c-o>x<esc>

" save word under cursor to ~/word.txt
nmap ,p :call SaveWord()

" Remove the Windows ^M - when the encodings gets messed up
noremap ,m mmHmt:%s/<C-V><cr>//ge<cr>'tzt'm

" Bash like keys for the command line
cnoremap <C-A>        <Home>
cnoremap <C-E>        <End>
cnoremap <C-K>        <C-U>

" quickly edit your macro
nnoremap ;m  :<c-u><c-r>='let @'. v:register .' = '. string(getreg(v:register))<cr><c-f><left>

" }}}

" Visual settings {{{

" No annoying sound on errors
set noerrorbells
set novisualbell
set t_vb=
set tm=500

" Properly disable sound on errors on MacVim
if has("gui_macvim")
    autocmd GUIEnter * set vb t_vb=
endif

" Set print options
set popt=syntax:y,number:y,wrap:y,left:0pt

" Remove GUI options
if has('gui') && has('gui_running')
    set guicursor=a:blinkon0      "Disable cursor blink
    set guioptions-=m   "no menus
    set guioptions-=T   "no toolbars
    set guioptions-=r   "no right-side scrollbar
    set guioptions-=R   "no right-side scrollbar
    set guioptions-=l   "no left-side scrollbar
    set guioptions-=L   "no left-side scrollbar
    "set guioptions+=b  "show bottom scrollbar
    set guioptions-=b   "no bottom scrollbar
    "set guioptions+=F  " show footer
    set guioptions-=F   " no footer
    "set columns=115
    " Open maximized windows always
    au GUIEnter * simalt ~x
endif

" Set font
if has("gui") && has("mac")
    set fuopt+=maxhorz
    set macmeta
    set antialias
    set guifont=Monaco:h10
else
    set guifont=Lucida_Sans_Typewriter:h10
endif
set linespace=2

" Configure wrap
set wrap linebreak  " linebreak - Wrap at word boundary
set sidescroll=5
set listchars+=precedes:<,extends:>
set breakat+={}()"|<>&
set textwidth=0

" Tab names for non-GUI
if exists("+showtabline")
    set stal=2
    set tabline=%!MyTabLine()
    set guitablabel=%!MyTabLine()
    set showtabline=2
    highlight link TabNum Special
endif

" }}}

" Helper Functions {{{

" function to toggle the number mode
function! g:ToggleNuMode()
  if(&relativenumber == 1)
    set norelativenumber
  else
    set relativenumber
  endif
endfunc

let $in_hex=0
function! HexMe()
    set binary
    set noeol
    if $in_hex>0
        :%!xxd -r
        let $in_hex=0
    else
        :%!xxd
        let $in_hex=1
    endif
endfunction

function! Ascii2Char()
    " Save cursor position
    let l:save = winsaveview()
    " yank the current word into register 'l'
    exe 'normal! "ldiw'
    " check if its end of line
    let l:save_cursor = getcurpos()
    exe ":normal! o" . nr2char(@l)
    " yank the converted value and paste it at the previous cursor location
    exe 'normal! ^"ldw'
    call setpos('.', l:save_cursor)
    if col('.') == col('$')-1
        exe 'normal! "lp'
    else
        exe 'normal! "lP'
    endif
    " delete the new line
    exe 'normal! jdd'
    " Move cursor to original position
    call winrestview(l:save)
endfunction

function! Char2Ascii()
    " Save cursor position
    let l:save = winsaveview()
    " yank the char into register 'l'
    exe 'normal! "lx'
    " check if its end of line
    if col('.') == col('$')-1
        exe ":normal! a" . printf("0x%x", char2nr(@l))
    else
        exe ":normal! i" . printf("0x%x", char2nr(@l))
    endif
    " Move cursor to original position
    call winrestview(l:save)
endfunction

let $diff_started=0
function! WinStartDiff()
    if $diff_started>0
        let $diff_started=0
        :windo diffoff
    else
        let $diff_started=1
        :windo diffthis
    endif
endfunction

" Close all hidden buffers
function! DeleteHiddenBuffers()
  let tpbl=[]
  let closed = 0
  call map(range(1, tabpagenr('$')), 'extend(tpbl, tabpagebuflist(v:val))')
  for buf in filter(range(1, bufnr('$')), 'bufexists(v:val) && index(tpbl, v:val)==-1')
    if getbufvar(buf, '&mod') == 0
      silent execute 'bwipeout' buf
      let closed += 1
    endif
  endfor
  echo "Closed ".closed." hidden buffers"
endfunction

" Display number of open buffers
function! NumberOfOpenBuffers()
    echo len(getbufinfo({'buflisted':1}))
endfun

" rebuild cscope, make sure it is called from the right directory
function! RebuildCscope(total)
    " Kill all prev connections
    let l:x = 0
    while l:x != a:total
        silent execute 'cs kill '.l:x
        let l:x = l:x + 1
    endwhile

    if has('win32')
        execute '!.\cscope_sym.bat '.a:total
    else
        execute '!cscope_sym.sh '.a:total
    endif
    cs add cscope.out
endfunction

function! MyTabLine()
    let s = ''
    let wn = ''
    let t = tabpagenr()
    let i = 1
    while i <= tabpagenr('$')
        let buflist = tabpagebuflist(i)
        let winnr = tabpagewinnr(i)
        let s .= '%' . i . 'T'
        let s .= (i == t ? '%1*' : '%2*')
        let s .= ' '
        let wn = tabpagewinnr(i,'$')

        let s .= '%#TabNum#'
        let s .= i
        " let s .= '%*'
        let s .= (i == t ? '%#TabLineSel#' : '%#TabLine#')
        let bufnr = buflist[winnr - 1]
        let file = bufname(bufnr)
        let buftype = getbufvar(bufnr, 'buftype')
        if buftype == 'nofile'
            if file =~ '\/.'
                let file = substitute(file, '.*\/\ze.', '', '')
            endif
        else
            let file = fnamemodify(file, ':p:t')
        endif
        if file == ''
            let file = '[No Name]'
        endif
        let s .= ' ' . file . ' '
        let i = i + 1
    endwhile
    let s .= '%T%#TabLineFill#%='
    let s .= (tabpagenr('$') > 1 ? '%999XX' : 'X')
    return s
endfunction

function! VisualSelection(direction) range
    let l:saved_reg = @"
    execute "normal! vgvy"

    let l:pattern = escape(@", "\\/.*'$^~[]")
    let l:pattern = substitute(l:pattern, "\n$", "", "")

    if a:direction == 'gv'
        call CmdLine("Ack '" . l:pattern . "' " )
    elseif a:direction == 'replace'
        call CmdLine("%s" . '/'. l:pattern . '/')
    endif

    let @/ = l:pattern
    let @" = l:saved_reg
endfunction

function! s:GetVisualSelection()
  let [line_start, column_start] = getpos("'<")[1:2]
  let [line_end, column_end] = getpos("'>")[1:2]
  let lines = getline(line_start, line_end)
  if len(lines) == 0
    return ''
  endif
  let lines[-1] = lines[-1][: column_end - (&selection == 'inclusive' ? 1 : 2)]
  let lines[0] = lines[0][column_start - 1:]
  return join(lines, "\n")
endfunction

function! SaveWord()
   normal yiw
   exe ':!echo '.@0.' >> ~/word.txt'
endfunction

" declare function for moving left when closing a tab.
function! TabCloseLeft(cmd)
    if winnr('$') == 1 && tabpagenr('$') > 1 && tabpagenr() > 1 && tabpagenr() < tabpagenr('$')
        exec a:cmd | tabprevious
    else
        exec a:cmd
    endif
endfunction

" define :Q command
command! Q call TabCloseLeft('q!')

" override default quit command
cabbrev q <c-r>=(getcmdtype()==':' && getcmdpos()==1 ? 'Q' : 'q')<CR>

" Swap bytes
function! SwapBytes()
    " Save cursor position
    let l:save = winsaveview()
    normal 2l
    normal 2x
    " Move cursor to original position
    call winrestview(l:save)
    normal P
    call winrestview(l:save)
endfunction

let timer = timer_start(60000, 'SaveSession', {'repeat': 1})
function! SaveSession(timer)
    :if v:this_session != '' | exec "mks! " . v:this_session | endif
endfunction


" }}}


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" CSCOPE settings for vim
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"
" This file contains some boilerplate settings for vim's cscope interface,
" plus some keyboard mappings that I've found useful.
"
" USAGE:
" -- vim 6:     Stick this file in your ~/.vim/plugin directory (or in a
"               'plugin' directory in some other directory that is in your
"               'runtimepath'.
"
" -- vim 5:     Stick this file somewhere and 'source cscope.vim' it from
"               your ~/.vimrc file (or cut and paste it into your .vimrc).
"
" NOTE:
" These key maps use multiple keystrokes (2 or 3 keys).  If you find that vim
" keeps timing you out before you can complete them, try changing your timeout
" settings, as explained below.
"
" Happy cscoping,
"
" Jason Duell       jduell@alumni.princeton.edu     2002/3/7
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


" This tests to see if vim was configured with the '--enable-cscope' option
" when it was compiled.  If it wasn't, time to recompile vim...
if has('win32')
    "set csprg=C:\Work\Tools\my_gvim\cscope.exe
    set csprg=$HOME/.vim/vimfiles/cscope.exe
    "let $TMP="$HOME/.vim/vimfiles/temp_dirs/tmp"
elseif has('mac')
    set csprg=/usr/local/bin/cscope
else
    set csprg=/usr/bin/cscope
endif

let g:cscope_loaded = 0
if (g:cscope_loaded == 0)

    """"""""""""" Standard cscope/vim boilerplate

    let g:cscope_loaded = 1

    " use both cscope and ctag for 'ctrl-]', ':ta', and 'vim -t'
    set cscopetag

    " check cscope for definition of a symbol before checking ctags: set to 1
    " if you want the reverse search order.
    set cscopetagorder=0

    " show msg when any other cscope db added
    set cscopeverbose

    " Use relative path from cscope.out directory
    if has('win32')
        set nocscoperelative
    else
        set cscoperelative
    endif

    """"""""""""" My cscope/vim key mappings
    "
    " The following maps all invoke one of the following cscope search types:
    "
    "   's'   symbol: find all references to the token under cursor
    "   'g'   global: find global definition(s) of the token under cursor
    "   'c'   calls:  find all calls to the function name under cursor
    "   't'   text:   find all instances of the text under cursor
    "   'e'   egrep:  egrep search for the word under cursor
    "   'f'   file:   open the filename under cursor
    "   'i'   includes: find files that include the filename under cursor
    "   'd'   called: find functions that function under cursor calls
    "
    " Below are three sets of the maps: one set that just jumps to your
    " search result, one that splits the existing vim window horizontally and
    " diplays your search result in the new window, and one that does the same
    " thing, but does a vertical split instead (vim 6 only).
    "
    " I've used CTRL-\ and CTRL-@ as the starting keys for these maps, as it's
    " unlikely that you need their default mappings (CTRL-\'s default use is
    " as part of CTRL-\ CTRL-N typemap, which basically just does the same
    " thing as hitting 'escape': CTRL-@ doesn't seem to have any default use).
    " If you don't like using 'CTRL-@' or CTRL-\, , you can change some or all
    " of these maps to use other keys.  One likely candidate is 'CTRL-_'
    " (which also maps to CTRL-/, which is easier to type).  By default it is
    " used to switch between Hebrew and English keyboard mode.
    "
    " All of the maps involving the <cfile> macro use '^<cfile>$': this is so
    " that searches over '#include <time.h>" return only references to
    " 'time.h', and not 'sys/time.h', etc. (by default cscope will return all
    " files that contain 'time.h' as part of their name).


    " To do the first type of search, hit '\', followed by one of the
    " cscope search types above (s,g,c,t,e,f,i,d).  The result of your cscope
    " search will be displayed in the current window.  You can use CTRL-T to
    " go back to where you were before the search.
    "

    " symbol
    nmap <Leader>s :cs find s <C-R>=expand("<cword>")<CR><CR>
    " global
    nmap <Leader>g :cs find g <C-R>=expand("<cword>")<CR><CR>
    " calls
    nmap <Leader>c :cs find c <C-R>=expand("<cword>")<CR><CR>
    " called
    nmap <Leader>d :cs find d <C-R>=expand("<cword>")<CR><CR>
    " text
    nmap <Leader>t :cs find t <C-R>=expand("<cword>")<CR><CR>
    " egrep
    nmap <Leader>e :cs find e <C-R>=expand("<cword>")<CR><CR>
    " file
    nmap <Leader>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
    " includes
    nmap <Leader>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>

    vnoremap <leader>s :<C-u>cs find s <C-R>=<SID>GetVisualSelection()<CR><CR>
    vnoremap <leader>g :<C-u>cs find g <C-R>=<SID>GetVisualSelection()<CR><CR>
    vnoremap <leader>c :<C-u>cs find c <C-R>=<SID>GetVisualSelection()<CR><CR>
    vnoremap <leader>d :<C-u>cs find d <C-R>=<SID>GetVisualSelection()<CR><CR>
    vnoremap <leader>t :<C-u>cs find t <C-R>=<SID>GetVisualSelection()<CR><CR>

    " Using '\' + capital search types (s,g,c,t,e,f,i,d) opens the search item in new tab

    nmap <Leader>S :tab scs find s <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>G :tab scs find g <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>C :tab scs find c <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>D :tab scs find d <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>F :tab scs find f <C-R>=expand("<cfile>")<CR><CR>
    nmap <Leader>T :tab scs find t <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>E :tab scs find e <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>I :tab scs find i ^<C-R>=expand("<cfile>")<CR>$<CR>

    " Short cut key
	nmap <C-\><SPACE> :cs find<SPACE>
	nmap <C-@><SPACE> :tab scs find<SPACE>

    """"""""""""" key map timeouts
    "
    " By default Vim will only wait 1 second for each keystroke in a mapping.
    " You may find that too short with the above typemaps.  If so, you should
    " either turn off mapping timeouts via 'notimeout'.
    "
    "set notimeout
    "
    " Or, you can keep timeouts, by uncommenting the timeoutlen line below,
    " with your own personal favorite value (in milliseconds):
    "
    "set timeoutlen=4000
    "

    " Either way, since mapping timeout settings by default also set the
    " timeouts for multicharacter 'keys codes' (like <F1>), you should also
    " set ttimeout and ttimeoutlen: otherwise, you will experience strange
    " delays as vim waits for a keystroke after you hit ESC (it will be
    " waiting to see if the ESC is actually part of a key code like <F1>).
    "
    "set ttimeout
    "
    " personally, I find a tenth of a second to work well for key code
    " timeouts. If you experience problems and have a slow terminal or network
    " connection, set it higher.  If you don't set ttimeoutlen, the value for
    " timeoutlent (default: 1000 = 1 second, which is sluggish) is used.
    "
    "set ttimeoutlen=100

endif
