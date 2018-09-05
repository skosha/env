"""""""""""""""""""""" Plugin configurations

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

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => CtrlP
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"let g:ctrlp_user_command = ['.git/', 'git --git-dir=%s/.git ls-files -oc --exclude-standard'] " use .gitignore to exclude caching of those files
if has('win32')
    let g:ctrlp_user_command = 'dir %s /-n /b /s /a-d' " Windows
else
    let g:ctrlp_user_command = 'find %s -type f'       " MacOSX/Linux
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

""""""""""""""""""""""""""""""
" => MRU plugin
""""""""""""""""""""""""""""""
let MRU_Max_Entries = 400
map <A-f> :MRU<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Git gutter (Git diff)
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
let g:gitgutter_enabled=0
nnoremap <A-g> :GitGutterToggle<cr>

""""""""""""""""""""""""""""""
" => YankStack
""""""""""""""""""""""""""""""
let g:yankstack_yank_keys = ['y', 'd']
nmap <Leader>p <Plug>yankstack_substitute_older_paste
nmap <Leader>P <Plug>yankstack_substitute_newer_paste

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Git-blame
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
nnoremap <Leader>gb :<C-u>call gitblame#echo()<CR>

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
" => Tagbar
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
nmap <A-t> :TagbarToggle<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Ag
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
if !has('win32') && executable('ag')
    set grepprg=ag
    let g:grep_cmd_opts = '--line-numbers --noheading --ignore-dir=log --ignore-dir=tmp'
    let g:ackprg = 'ag --nogroup --nocolor --column'
endif

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Rainbow Parantheses
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
if has("autocmd")
    augroup rainbowParantheses
        autocmd!
        " Rainbow parantheses
        au VimEnter * RainbowParenthesesToggle
        au Syntax * RainbowParenthesesLoadRound         " ()
        au Syntax * RainbowParenthesesLoadSquare        " []
        au Syntax * RainbowParenthesesLoadBraces        " {}
    augroup END
endif
