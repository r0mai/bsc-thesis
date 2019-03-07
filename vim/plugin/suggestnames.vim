if exists("g:suggestnames#loaded")
  finish
endif
let g:suggestnames#loaded = "yes"

function! s:init()
  let s:path = expand('%:p:h') . '/suggest_names/suggest_names'
endfunction

function! s:suggest_names()
 "This is to ensure we are at the start

  normal wb

  let l:cursor_pos = getpos(".")
  let l:line = cursor_pos[1]
  let l:column = cursor_pos[2]
  let l:filename = expand("%:p")

  "FIXME: Find this dynamically
  let l:databasefilename = "varnames.json"
  let l:suggestions = system(s:path . " " . l:databasefilename . " " . l:filename . " " . l:line . " " . l:column)

  below 5 split SuggestNames__
  normal ggdG
  setlocal filetype=SuggestNames
  setlocal buftype=nofile
  call append(0, split(l:suggestions, '\v\n'))
endfunction

command! SuggestNames call s:suggest_names()

call s:init()
