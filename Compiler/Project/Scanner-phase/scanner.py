from utils import KEYWORDS ,  TokenType , SYMBOLS

#the class that scanns everything
class Scanner:
  #initializing the first state of scanner
  def __init__(self,input_file):
    self.input_file=input_file   #we save file here
    self.line_number=0    
    self.current_pos=0          #cursor
    self.current_line=''    # we save each line to process
    self.tokens=[]      #we save tokens here
    self.errors=[]      #we save errors here
    self.symbol_table={kew : kew for kew in sorted(KEYWORDS)}     #we load symbol table here
    self.input_lines=[]       #we save lines here
    self.in_comment=False       #some variable for comment handeling
    self.comment_start_line=0
    self.comment_content_start=0
  

  def scan(self):
    #the whole process goes here
    try:
      with open(self.input_file,'r') as f:
        self.input_lines=f.readlines()
      #we prcess each line and add the tokens and the errors here
      for line in self.input_lines:
        self.line_number +=1
        self.current_line=line
        self.current_pos=0
        self.process_line()
      
      self.check_for_unclosed_comment()
      return self.tokens , self.errors , self.symbol_table

    #if we couldn't read the file
    except IOError:
      self.errors.append((0,f"unable to open the file : {self.input_file}"))
      return self.tokens , self.errors , self.symbol_table
  

  def process_line(self):
    #processing each line and realizing the errors and the tokens
    while self.current_pos < len(self.current_line): #in this while loop we start from the begining of the line and go unitl end of it
      char = self.current_line[self.current_pos]
      #bunch of if statment to see what should it do for each char it read
      if self.skip_whitespace(char):
        continue

      if self.handel_comments(char):
        continue

      if char=='\n':
        break

      if char.isdigit():
        self.process_number()
      
      elif char.isalpha() or char == '_':
        self.process_identifier()
      
      elif char in SYMBOLS:
        self.process_symbol()
      
      else:
        self.process_invalid_char(char)


  #this function handels the things to be ignored
  def skip_whitespace(self,char):
    if char in {' ','\t','\v','\f','\r'}:
      self.current_pos += 1
      return True
    return False
  
  def handel_comments(self,char):
    #comment starts
    if not self.in_comment and char =='/' and self.peek_next_char()=='*':
      self.in_comment=True
      self.comment_start_line=self.line_number
      self.comment_content_start=self.current_pos+2
      self.current_pos+=2
      return True
    
    #comment end
    if self.in_comment:
      if char=='*' and self.peek_next_char()=='/':
        self.in_comment=False
        self.current_pos+=2
      else:
        self.current_pos+=1
      return True

    #unmatched comments
    if char=='*' and self.peek_next_char()=='/':
      self.errors.append((self.line_number,'(*/,unmatched comment)'))
      self.current_pos+=2
      return True

    return False
  
  #we process if the number is in a correct format or not here
  def process_number(self):
    start_pos = self.current_pos
    while self.has_more_chars() and self.current_line[self.current_pos].isdigit():
      self.current_pos+=1
        
    if self.has_more_chars() and self.current_line[self.current_pos].isalpha():
      invalid_part=self.current_line[start_pos:self.current_pos+1]
      self.errors.append((self.line_number, f'({invalid_part},Invalid number)'))
      self.skip_invalid_input(True)
      return
        
    num_str=self.current_line[start_pos:self.current_pos]
    self.add_token(TokenType.NUM, num_str)


  #we process the identifiers here
  def process_identifier(self):
    start_pos=self.current_pos
    while (self.has_more_chars() and (self.current_line[self.current_pos].isalnum() or self.current_line[self.current_pos]=='_')):
      self.current_pos+=1
    
    if (self.has_more_chars() and not self.current_line[self.current_pos].isspace() and self.current_line[self.current_pos] not in SYMBOLS and self.current_line[self.current_pos] not in {'/', '*'}):
      invalid_part=self.current_line[start_pos:self.current_pos+1]
      self.errors.append((self.line_number,f'({invalid_part} ,invalid input)'))
      self.skip_invalid_input(False)
      return

    id_str=self.current_line[start_pos:self.current_pos]

    if id_str in KEYWORDS:
      self.add_token(TokenType.KEYWORD,id_str)
    else:
      self.add_token(TokenType.ID,id_str)
      if id_str not in self.symbol_table:
        self.symbol_table[id_str] = id_str
  


  #in here we process the symbols 
  def process_symbol(self):
    char=self.current_line[self.current_pos]
    next_char=self.peek_next_char()
    if char == '=' and next_char =='#':  #invalid cause we dont have =#
      self.errors.append((self.line_number, '(=#, Invalid input)'))
      self.current_pos+=2 #we go to the 2 next char
      return

    if char == '/' and next_char == '/': #invalid cause we dont have /
      self.errors.append((self.line_number, '(/, Invalid input)'))
      self.errors.append((self.line_number, '(/, Invalid input)'))
      self.current_pos += 2
      return
    
    #we process the correct symbols here
    two_char = char + next_char if next_char else char
    if two_char in {'+=', '*=', '/=', '-=', '<=', '==', '!=', '/*', '*/'}:
      if two_char in SYMBOLS:
        self.add_token(TokenType.SYMBOL, two_char)
        self.current_pos += 2
        return
    
    if char in SYMBOLS:
      self.add_token(TokenType.SYMBOL, char)
      self.current_pos += 1
  


  #in this function we detect the invalid output
  def process_invalid_char(self,char):
    self.errors.append((self.line_number, f'({char}, Invalid input)'))
    self.current_pos += 1
    self.skip_invalid_input(False)
  
  #in this function we detect the invalid output
  def skip_invalid_input(self,is_invalid_number):
    if is_invalid_number:
      self.current_pos += 1 # we ignore this number and we want to skip this number so we should reach the end of the number


    #in this while loop we go until we reach the end of it        
    while self.has_more_chars():
      char = self.current_line[self.current_pos]
      if char.isspace() or char in SYMBOLS or char.isalnum():
        break
      self.current_pos += 1
  

  #in this function we add the token we found to the token list
  def add_token(self, token_type, token_value):
    self.tokens.append((self.line_number, (token_type, token_value)))
  


#this functin checks if the comment is closed or not(if not it saves in errors list)
  def check_for_unclosed_comment(self):
    if self.in_comment:
      comment_content = self.input_lines[self.comment_start_line - 1][self.comment_content_start:]
      preview = comment_content[:5]
      if len(preview) < len(comment_content):
        preview += "..."
      self.errors.append((self.comment_start_line, f'(/*{preview}, Unclosed comment)'))
    

#this function we only see the next char for token and error handeling
  def peek_next_char(self):
    if self.current_pos + 1 < len(self.current_line):
      return self.current_line[self.current_pos + 1]  #it returns the next char
    return None
  

  #this function checks if the word we want to process cross the end of line or not
  def has_more_chars(self):
    return self.current_pos < len(self.current_line)



