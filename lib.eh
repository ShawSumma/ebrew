type
  ExitCode @#
;

exit_code (n $) ExitCode __cast ExitCode n

exit (a ExitCode) $ __syscall 60 a 0 0 0 0 0

type
  AllocSize    @#
  ProgramBreak @#
;

alloc_size (n $) AllocSize __cast AllocSize n

initbrk (n AllocSize) ProgramBreak { __syscall 12 0 0 0 0 0 0 is i __syscall 12 __add n i 0 0 0 0 0 __cast ProgramBreak i }

strlen(a $) $ { 0 for i __peek __add i a then __add 1 i }

memcpy (a $ b $ n $) $ {
  n then
  n for m
  __poke a __peek b
  __store __addr a __add 1 a
  __store __addr b __add 1 b
  __sub 1 m
}

memcmp(a $ b $ n $) $ {
  1 is r
  { n then n for m
    __cond __e __peek a __peek b
      { __store __addr a __add 1 a
        __store __addr b __add 1 b
        __sub 1 m }
      { __store __addr r 0
        0 } }
  r
}

strncmp(a $ b $ n $) $ {
  1 is r
  { n then
    n for m
    __cond __e __peek a __peek b
      { __peek a then
        __store __addr a __add 1 a
        __store __addr b __add 1 b
        __sub 1 m }
      { __store __addr r 0
        0 } }
  r
}

strcmp(a $ b $) $ {
  1 is r
  { 1 for _
    __cond __e __peek a __peek b
      { __peek a then
        __store __addr a __add 1 a
        __store __addr b __add 1 b
        1 }
      { __store __addr r 0
        0 } }
  r
}

type
  Buffer    @#
  Stream    @#
  InOut     (s Stream p Buffer n $) $
  InBuffer  @#
  OutBuffer @#
  InStream  (p InBuffer  n $) $
  OutStream (p OutBuffer n $) $
;

stdin  InStream  __syscall 0 0 p n 0 0 0
stdout OutStream __syscall 1 1 p n 0 0 0
stderr OutStream __syscall 1 2 p n 0 0 0

in  InOut __cast InStream  s __cast InBuffer  p n
out InOut __cast OutStream s __cast OutBuffer p n

retry (io InOut s Stream p Buffer q Buffer) $ {
  0 is a
  { p for i
    io s i __sub i q is n
    { __e n __neg 1 then __store __addr a __neg 1 }
    n then __add n i } is b
  a else
  b
}

stream_in  (a InStream ) Stream __cast Stream __load __addr a
stream_out (a OutStream) Stream __cast Stream __load __addr a

buffer_in  (a InBuffer ) Buffer __cast Buffer a
buffer_out (a OutBuffer) Buffer __cast Buffer a

retry_in  (s InStream  p InBuffer  q InBuffer ) $ retry in  stream_in  s buffer_in  p buffer_in  q
retry_out (s OutStream p OutBuffer q OutBuffer) $ retry out stream_out s buffer_out p buffer_out q


































































































