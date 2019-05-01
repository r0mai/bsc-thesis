if exists("g:suggestnames#loaded")
  finish
endif
let s:suggest_names_path = expand('<sfile>:p:h') . '/../../suggest_names/suggest_names'
let s:rename_path = expand('<sfile>:p:h') . '/../../suggest_names/suggest_names_rename'
let s:database_path = get(g:, 'suggest_names_database_path', $HOME . "/.suggest_names")
let g:suggestnames#loaded = "yes"

function! s:suggest_names()
 "This is to ensure we are at the start

  normal wb
  "Ensure that buffer is on-disk before continuing, so that we can validate
  "the contents.
  write

  let l:cursor_pos = getpos(".")
  let l:line = cursor_pos[1]
  let l:column = cursor_pos[2]
  let l:filename = expand("%:p")

  let l:databasefiles = split(globpath(s:database_path, '**/*.json'), '\n')
  echomsg "Calculating variable-name suggestions..."
  let l:suggestions = system(s:suggest_names_path . " " . join(l:databasefiles, " ") . " " . l:filename . " " . l:line . " " . l:column)

  below 5 split SuggestNames__
  normal ggdG
  setlocal filetype=SuggestNames
  setlocal buftype=nofile
  call append(0, split(l:suggestions, '\v\n'))
  normal gg
  execute 'nnoremap <buffer> <CR> :SuggestNamesAccept ' . l:filename . ' ' . l:line . ' ' . l:column . '<CR>'
endfunction

function! s:accept_suggestion(filename, line, column)
  let l:line=getline(".")
  let l:databasefiles = split(globpath(s:database_path, '**/*.json'), '\n')
  echomsg "Renaming variable to: " . l:line
  call system(s:rename_path . " " .
        \ "--filename=" . a:filename .
        \ " --line=" . a:line .
        \ " --column=" . a:column .
        \ " --name=" . l:line .
        \ " " .
        \ join(l:databasefiles, " "))
  quit
  checktime
endfunction

command! SuggestNames call s:suggest_names()
command! -nargs=+ SuggestNamesAccept call s:accept_suggestion(<f-args>)
