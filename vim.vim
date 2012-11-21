map <F9> :wa<Return>:execute '!./build -j ' . g:Target<Return>
map <C-F9> :wa<Return>:execute '!./build -j ' . g:Target . ' clean'<Return>:execute '!./build ' . g:Target<Return>
map <F8> :Run<Return>
map <C-F8> :Debug<Return>
command! -nargs=1 SetRun let g:ToRun='<args>'
command! -nargs=1 SetTarget let g:Target='<args>'
command! -nargs=0 Run execute '!LD_LIBRARY_PATH="./bin/' . g:Target . '/.libs/" ./bin/' . g:Target . '/' . g:ToRun
command! -nargs=0 Debug execute '!LD_LIBRARY_PATH="./bin/' . g:Target . '/.libs/" gdb ./bin/' . g:Target . '/' . g:ToRun

let ToRun='test'
let Target='Debug'
