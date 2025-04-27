

PIPELINE      :   SIMPLE_COMMAND  |   SIMPLE_COMMAND


SIMPLE_COMMAD :  WORD | REDIRECT_LIST

                 ;
REDIRECT_LIST    :<'       infile
                 | '>'       outfilr
                 | <<   heredoc
                 | >>    append
