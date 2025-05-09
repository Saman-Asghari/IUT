class TokenType:
  #defining the types of token the scanner should recogonize 
    NUM = 'NUM'
    ID = 'ID'
    KEYWORD = 'KEYWORD'
    SYMBOL = 'SYMBOL'

#defining the keywords
KEYWORDS = {'break', 'else', 'if', 'int', 'repeat', 'return', 'until', 'void'}

#defining the symbols
SYMBOLS = {
    ':', ',', '[', ']', '{', '}', '+', '-', '*', '=', '/','+=',
    '*=', '/=' , '-=' ,'<', '>', '<=', '==', '!=', ';', '(', ')'
}
