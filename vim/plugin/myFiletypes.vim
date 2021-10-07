if has("autocmd")
    augroup file_types
        autocmd!
        " Auto load vimrc once it changes, handy with Vundle
        autocmd BufWritePost .vimrc so %

        " Use tabs in Makefile
        autocmd FileType make setlocal noexpandtab

        " Don't let too long lines to be written in text format
        autocmd FileType txt setlocal wrapmargin=500

        autocmd FileType html set omnifunc=htmlcomplete#CompleteTags
        autocmd FileType vim set omnifunc=syntaxcomplete#Complete
        autocmd FileType css set omnifunc=csscomplete#CompleteCSS
        autocmd FileType xml set omnifunc=xmlcomplete#CompleteTags
        autocmd FileType php set omnifunc=phpcomplete#CompletePHP
        autocmd FileType c set omnifunc=ccomplete#Complete

        au FileType gitcommit
        \ setlocal spell textwidth=72 |
        \ startinsert

        " To jump between the '=' and ';' in an assignment using <S-%>. Useful for languages like C/C++ and Java.
        "autocmd FileType c,cpp,java set matchpairs+==:;
    augroup END
endif

""""""""""""""""""""""""""""""
" => Python section
""""""""""""""""""""""""""""""
let python_highlight_all = 1
if has("autocmd")
    " au FileType python syn keyword pythonDecorator True None False self
    au FileType python map <buffer> F :set foldmethod=indent<cr>
    au FileType python nnoremap <LocalLeader>= :0,$!yapf<CR>
    au BufNewFile,BufRead *.py
                \ set tabstop=4 |
                \ set softtabstop=4 |
                \ set shiftwidth=4 |
                \ set textwidth=79 |
                \ set expandtab |
                \ set autoindent |
                \ set shiftround |
                \ set fileformat=unix
endif

let g:vim_isort_map = '<C-i>'

let g:pymode_lint = 1
let g:pymode_lint_on_write = 0
let g:pymode_trim_whitespaces = 0

" Close the preview window with <C-Space>. As a corollary, close it from
" insert mode with <C-O><C-Space>, which flows very nicely.
nnoremap <C-Space> :pclose<CR>
nnoremap <NUL> :pclose<CR>

""""""""""""""""""""""""""""""
" => JS, HTML and CSS
""""""""""""""""""""""""""""""
if has("autocmd")
    au BufNewFile,BufRead *.js, *.html, *.css
                \ set tabstop=2
                \ set softtabstop=2
                \ set shiftwidth=2
endif

""""""""""""""""""""""""""""""
" => YAML
""""""""""""""""""""""""""""""
if has("autocmd")
    autocmd FileType yaml setlocal ts=2 sts=2 sw=2 expandtab
    autocmd FileType yaml setlocal indentkeys-=0# indentkeys-=<:>
endif

""""""""""""""""""""""""""""""
" => JSON
""""""""""""""""""""""""""""""
" json indent
command! -range -nargs=0 -bar IndentJson <line1>,<line2>!python -m json.tool
command! -range -nargs=0 -bar JsonIndent <line1>,<line2>!python -m json.tool

""""""""""""""""""""""""""""""
" => XML
""""""""""""""""""""""""""""""
"xml indent
command! IndentXml :silent %!xmllint --encode UTF-8 --format -
command! XmlIndent :silent %!xmllint --encode UTF-8 --format -"
