"""""""""""""""""""""" Plugin configurations

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => ack
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
if executable('ag')
  let g:ackprg = 'ag --nogroup --nocolor --column'
else
    let g:ack_default_options = ' -s -H --nocolor --nogroup --column --ignore-file=is:tags --ignore-file=is:cscope.out --ignore-dir=builds'
endif

let g:ackhighlight = 1

" bind K to grep word under cursor
nnoremap <Leader>k :Ack! "\b<C-R><C-W>\b"<CR>:cw<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Ale Lint
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
nmap _al <Plug>(ale_next_wrap)
" Only run linting when saving the file
let g:ale_lint_on_text_changed = 'never'
let g:ale_lint_on_enter = 0
let g:ale_sign_error = '⌦'
let g:ale_sign_warning = '∙∙'

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => vim-airline
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"" Show PASTE if in paste mode
let g:airline_detect_paste=1

" Show airline for tabs too
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#formatter = 'unique_tail'
let g:airline#extensions#tabline#tab_nr_type = 1

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => code_complete
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
let g:completekey = "<F4>"

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => CtrlP
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"let g:ctrlp_user_command = ['.git/', 'git --git-dir=%s/.git ls-files -oc --exclude-standard'] " use .gitignore to exclude caching of those files
if has('win32')
    let g:ctrlp_user_command = 'dir %s /-n /b /s /a-d' " Windows
else
    if executable ('fd')
        let g:ctrlp_user_command = 'fd --type f --color=never "" %s'
        let g:ctrlp_use_caching = 0
    else
        if executable('ag')
        " Use ag in CtrlP for listing files. Lightning fast and respects .gitignore
        let g:ctrlp_user_command = 'ag %s -l --nocolor -g ""'
        " ag is fast enough that CtrlP doesn't need to cache
        let g:ctrlp_use_caching = 0
        else
            let g:ctrlp_user_command = 'find %s -type f'       " MacOSX/Linux
        endif
    endif
endif

" CtrlP -> override <C-o> to provide options for how to open files
let g:ctrlp_arg_map = 1

let g:ctrlp_show_hidden = 1
let g:ctrlp_match_window = 'max:35'
let g:ctrlp_max_files = 0 " Set no max file limit
let g:ctrlp_switch_buffer = 'Et'
let g:ctrlp_lazy_update = 0
let g:ctrlp_working_path_mode = 'a'
let g:ctrlp_tabpage_position = 'ac'
let g:ctrlp_clear_cache_on_exit = 0     " Hit <F5> to refresh index
let g:ctrlp_extensions = ['mixed', 'changes', 'quickfix']
let g:ctrlp_cmd='CtrlPMixed'
let g:ctrlp_custom_ignore = '\v[\/]\.(git|hg|svn)$'
let g:ctrlp_custom_ignore = {
            \ 'dir':  '\v[\/]\.(git|hg|svn)$',
            \ 'file': '\v\.(exe|so|dll)$',
            \ 'link': 'SOME_BAD_SYMBOLIC_LINKS',
            \ }

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Easy Align
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Start interactive EasyAlign in visual mode (e.g. vipta)
xmap ta <Plug>(EasyAlign)

" Start interactive EasyAlign for a motion/text object (e.g. taip)
nmap ta <Plug>(EasyAlign)

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => fzf
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
nnoremap <silent> <Leader>] :Tags<CR>

command! FZFMru call fzf#run({
            \  'source':  v:oldfiles,
            \  'sink':    'e',
            \  'options': '-m -x +s',
            \  'down':    '40%' })

" Select Buffer
function! s:buflist()
    redir => ls
    silent ls
    redir END
    return split(ls, '\n')
endfunction

function! s:bufopen(e)
    execute 'buffer' matchstr(a:e, '^[ 0-9 ]*')
endfunction

nnoremap <silent> <Leader><Enter> :call fzf#run({
            \   'source':  reverse(<sid>buflist()),
            \   'sink':    function('<sid>bufopen'),
            \   'options': '+m',
            \   'down':    len(<sid>buflist()) + 2
            \ })<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Git-blame
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
nnoremap <Leader>gb :<C-u>call gitblame#echo()<CR>


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Git gutter (Git diff)
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
let g:gitgutter_enabled=0
let g:gitgutter_updatetime=750
nnoremap <A-g> :GitGutterToggle<cr>

""""""""""""""""""""""""""""""
" => headerguard
""""""""""""""""""""""""""""""
function! g:HeaderguardName()
    return "__" . toupper(expand('%:t:gs/[^0-9a-zA-Z_]/_/g')) . "__"
endfunction

function! g:HeaderguardLine3()
    return "#endif /* !" . g:HeaderguardName() . " */"
endfunction

""""""""""""""""""""""""""""""
" => vim-illuminate
""""""""""""""""""""""""""""""
hi illuminatedWord cterm=NONE ctermfg=white ctermbg=blue guibg=peru guifg=wheat
" Time in milliseconds (default 250)
let g:Illuminate_delay = 150

let g:mwDefaultHighlightingPalette = 'extended'

""""""""""""""""""""""""""""""
" => vim-lengthmatters
""""""""""""""""""""""""""""""
let g:lengthmatters_start_at_column = 121

""""""""""""""""""""""""""""""
" => vim-mark
""""""""""""""""""""""""""""""
let g:mwHistAdd = '/@'

nmap <Plug>IgnoreMarkSearchNext <Plug>MarkSearchNext
nmap <Plug>IgnoreMarkSearchPrev <Plug>MarkSearchPrev

nmap <Leader>1 <Plug>MarkSearchGroup1Next
nmap <Leader>! <Plug>MarkSearchGroup1Prev

nmap <Leader>2 <Plug>MarkSearchGroup2Next
nmap <Leader>" <Plug>MarkSearchGroup2Prev

nmap <Leader>3 <Plug>MarkSearchGroup3Next
nmap <Leader>£ <Plug>MarkSearchGroup3Prev

nmap <Leader>4 <Plug>MarkSearchGroup4Next
nmap <Leader>$ <Plug>MarkSearchGroup4Prev

nmap <Leader>5 <Plug>MarkSearchGroup5Next
nmap <Leader>% <Plug>MarkSearchGroup5Prev

nmap <Leader>6 <Plug>MarkSearchGroup6Next
nmap <Leader>^ <Plug>MarkSearchGroup6Prev

nmap <Leader>7 <Plug>MarkSearchGroup7Next
nmap <Leader>& <Plug>MarkSearchGroup7Prev

nmap <Leader>8 <Plug>MarkSearchGroup8Next
nmap <Leader>) <Plug>MarkSearchGroup8Prev

nmap <Leader>9 <Plug>MarkSearchGroup9Next
nmap <Leader>( <Plug>MarkSearchGroup9Prev

""""""""""""""""""""""""""""""
" => MRU plugin
""""""""""""""""""""""""""""""
let MRU_Max_Entries = 400

""""""""""""""""""""""""""""""
" => NERD Commenter
""""""""""""""""""""""""""""""
" Add spaces after comment delimiters by default
let g:NERDSpaceDelims = 1
" Allow commenting and inverting empty lines (useful when commenting a region)
let g:NERDCommentEmptyLines = 1
" Enable trimming of trailing whitespace when uncommenting
let g:NERDTrimTrailingWhitespace = 1

""""""""""""""""""""""""""""""
" => Notes
""""""""""""""""""""""""""""""
let g:notes_directories = ['~/Documents/Notes']
let g:notes_suffix = '.txt'

""""""""""""""""""""""""""""""
" => Peekaboo
""""""""""""""""""""""""""""""
let g:peekaboo_delay = 200  " wait for 200ms before sidebar appears

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Rainbow Parantheses
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
function! SetupRainbowParentheses()
    let l:custom_colors_light = map([
            \ 'DarkRed',
            \ 'LightBlue',
            \ 'Black',
            \ 'DarkGreen',
            \ 'DarkBlue',
            \ 'DarkMagenta',
        \ ], '[v:val, v:val]')
    let l:custom_colors_dark = map([
            \ 'DarkRed',
            \ 'DarkCyan',
            \ 'DarkGreen',
            \ 'DarkBlue',
            \ 'Magenta',
            \ 'Green',
            \ 'LightBlue',
            \ 'LightCyan',
            \ 'Yellow',
        \ ], '[v:val, v:val]')
    let g:rainbow#max_level = max([len(l:custom_colors_dark), len(l:custom_colors_light)])
    let g:rainbow#colors = { 'dark': l:custom_colors_dark, 'light': l:custom_colors_light  }
    RainbowParentheses
endfunction

let g:rainbow#pairs = [['(', ')'], ['[', ']'], ['{', '}']]
augroup rainbowParantheses
    autocmd!
    au VimEnter * call SetupRainbowParentheses()
augroup END

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => switch settings
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
let g:switch_mapping = '-'
let g:switch_custom_definitions = [
\   ['MON', 'TUE', 'WED', 'THU', 'FRI']
\ ]

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => majutsushi/tagbar settings
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
nmap <silent> <F7> :TagbarToggle<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => taglist settings
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
nnoremap <silent> <F8> :TlistToggle<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Tmux navigator
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
let g:tmux_navigator_no_mappings = 1

" Write the current buffer before navigating from Vim to tmux pane
let g:tmux_navigator_save_on_switch = 1

" Disable tmux navigator when zooming the Vim pane
let g:tmux_navigator_disable_when_zoomed = 1

nnoremap <silent> {Left-Mapping} :TmuxNavigateLeft<cr>
nnoremap <silent> {Down-Mapping} :TmuxNavigateDown<cr>
nnoremap <silent> {Up-Mapping} :TmuxNavigateUp<cr>
nnoremap <silent> {Right-Mapping} :TmuxNavigateRight<cr>
nnoremap <silent> {Previous-Mapping} :TmuxNavigatePrevious<cr>

""""""""""""""""""""""""""""""
" => Undo tree
""""""""""""""""""""""""""""""
nnoremap <F6> :UndotreeToggle<cr>

""""""""""""""""""""""""""""""
" => Undo Quit
""""""""""""""""""""""""""""""
let g:undoquit_mapping = '_u'

""""""""""""""""""""""""""""""
" => unicode
""""""""""""""""""""""""""""""
let g:enableUnicodeCompletion=1

""""""""""""""""""""""""""""""
" => YankStack
""""""""""""""""""""""""""""""
let g:yankstack_yank_keys = ['y', 'd']
nmap <Leader>p <Plug>yankstack_substitute_older_paste
nmap <Leader>P <Plug>yankstack_substitute_newer_paste
