class TokenType:
  #Defining the types of token the scanner should recogonize 
    NUM = 'NUM'
    ID = 'ID'
    KEYWORD = 'KEYWORD'
    SYMBOL = 'SYMBOL'


KEYWORDS = {'break', 'else', 'if', 'int', 'repeat', 'return', 'until', 'void'}

SYMBOLS = {
    ':', ',', '[', ']', '{', '}', '+', '-', '*', '=', '/','+=',
    '*=', '/=' , '-=' ,'<', '>', '<=', '==', '!=', ';', '(', ')'
}
