from utils import KEYWORDS ,  TokenType , SYMBOLS

class Scanner:
  #initializing the first state of scanner
  def __init__(self,input_file):
    self.input_file=input_file
    self.line_number=0
    self.current_pos=0
    self.current_line=''
    self.tokens=[]
    self.errors=[]
    self.symbol_table={kew : kew for kew in sorted(KEYWORDS)}
    self.input_lines=[]
    self.in_comment=False
    self.comment_start_line=0
    self.comment_content_start=0
  

  def scan(self):
    #the whole process goes here
    try:
      with open(self.input_file,'r') as f:
        self.input_lines=f.readlines()
      
      for line in self.input_lines:
        self.line_number +=1
        self.current_line=line
        self.current_pos=0
        self.process_line()
      
      self.check_for_unclosed_comment()
      return self.tokens , self.errors , self.symbol_table

    except IOError:
      self.errors.append((0,f"unable to open the file : {self.input_file}"))
      return self.tokens , self.errors , self.symbol_table
  

  def process_line(self):
    #processing each line and realizing the errors and the tokens
    while self.current_pos < len(self.current_line):
      char = self.current_line[self.current_pos]

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
      if char=='*' and self._peek_next_char()=='/':
        self.in_comment=False
        self.current_pos+=2
      else:
        self.current_pos+=1
      return True

    #unmatched comments
    if char=='*' and self._peek_next_char()=='/':
      self.errors.append((self.line_number,'(*/,unmatched comment)'))
      self.current_pos+=2
      return True

    return False
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
    self._add_token(TokenType.NUM, num_str)


  def process_identifier():
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
  

  def process_symbol():
    None
  
  def process_invalid_char():
    None
  
  def skip_invalid_input():
    None
  
  def add_token():
    None
  
  def check_for_unclosed_comment():
    None
  
  def peek_next_char():
    None
  
  def has_more_chars():
    None


