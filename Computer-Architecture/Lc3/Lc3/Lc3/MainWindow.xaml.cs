using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Collections.Generic;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using static System.Net.Mime.MediaTypeNames;
using Microsoft.VisualBasic.FileIO;
using System.Configuration;

namespace Lc3
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        List<string> Instructions = new List<string> {"ADD","AND","BRn", "BRz", "BRp", "BRnz", "BRnp", "BRzp", "BR", "JMP","JSR","JSRR","LD","LDI","LDR","LEA","NOT","RET","RTI","ST","STI","STR","TRAP","ORG","HLT","END",};
        List<string> DataLabels = new List<string> { "DEC", "BIN", "HEX" }; 
        string DecodedCode = "";  //hold the last result here
        int CurrentLane = 0;    //used for handling org instruction
        Dictionary<string,Tuple<int,int?>> LabelAddresses;   //a map for holding the lables
        Dictionary<int, string> InstructionAddresses;
        string[] Lines;   //specially global for deleting the labels from it
        int[] R;
        int[] CC;
        int PC;
        string IR;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void SaveAC_Click(object sender, RoutedEventArgs e)
        {
            LabelAddresses = new Dictionary<string,Tuple<int, int?>>();
            InstructionAddresses = new Dictionary<int, string>();
            string Text=AssemblySource.Text;
            R=new int[8];
            CC=new int[3];
            Lines= Text.Split(new[] { "\r\n", "\r", "\n" }, StringSplitOptions.RemoveEmptyEntries);
            Decode(Lines);
            Excute(DecodedCode);
        }
        private void Decode(string[] lines)
        {
            FindingLabels(lines);
            for(int i = 0; i < Lines.Count(); i++)
            {
                List<string> WordsForEachLine = SplitString(Lines[i]);  //specify the words in each line
                if (WordsForEachLine[0] == "ORG")
                {
                    int TempNumber = Convert.ToInt32(DeletePartOfString(WordsForEachLine[1], "x"), 16);
                    CurrentLane = TempNumber;
                    CurrentLane--;
                    continue;
                }
                if (WordsForEachLine[0] == "ADD")
                {
                    CurrentLane++;
                    string Result =DecodingAdd(WordsForEachLine);
                    InstructionAddresses.Add(CurrentLane, Result);              //saving the address
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0] == "AND")
                {
                    CurrentLane++;               
                    string Result = DecodingAnd(WordsForEachLine);
                    InstructionAddresses.Add(CurrentLane, Result);    //saving the address
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0] == "NOT")
                {
                    CurrentLane++;
                    string Result = DecodingNot(WordsForEachLine);
                    InstructionAddresses.Add(CurrentLane, Result);
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0] == "LD")
                {
                    CurrentLane++;
                    string Result = DecodingLd(WordsForEachLine,CurrentLane);
                    InstructionAddresses.Add(CurrentLane, Result);
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0] == "LDI")
                {
                    CurrentLane++;
                    string Result = DecodingLdi(WordsForEachLine, CurrentLane);
                    InstructionAddresses.Add(CurrentLane, Result);
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0] == "LDR")
                {
                    CurrentLane++;
                    string Result = DecodingLdr(WordsForEachLine);
                    InstructionAddresses.Add(CurrentLane, Result);
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0] == "LEA")
                {
                    CurrentLane++;
                    string Result = DecodingLea(WordsForEachLine,CurrentLane);
                    InstructionAddresses.Add(CurrentLane, Result);
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0] == "ST")
                {
                    CurrentLane++;
                    string Result = DecodingSt(WordsForEachLine,CurrentLane);
                    InstructionAddresses.Add(CurrentLane, Result);
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0] == "STI")
                {
                    CurrentLane++;
                    string Result = DecodingSti(WordsForEachLine, CurrentLane);
                    InstructionAddresses.Add(CurrentLane, Result);
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0] == "STR")
                {
                    CurrentLane++;
                    string Result = DecodingStr(WordsForEachLine);
                    InstructionAddresses.Add(CurrentLane, Result);
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0].Contains("BR"))
                {
                    CurrentLane++;
                    string Result = DecodingBr(WordsForEachLine,CurrentLane);
                    InstructionAddresses.Add(CurrentLane, Result);
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0] == "JMP")
                {
                    CurrentLane++;
                    string Result = DecodingJmp(WordsForEachLine);
                    InstructionAddresses.Add(CurrentLane, Result);
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0] == "RET")
                {
                    CurrentLane++;
                    string Result = "1100000111000000";
                    InstructionAddresses.Add(CurrentLane, Result);
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0] == "JSR")
                {
                    CurrentLane++;
                    string Result = DecodingJsr(WordsForEachLine,CurrentLane);
                    InstructionAddresses.Add(CurrentLane, Result);
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0] == "JSRR")
                {
                    CurrentLane++;
                    string Result = DecodingJsrr(WordsForEachLine);
                    InstructionAddresses.Add(CurrentLane, Result);
                    DecodedCode += Result;
                }
                
                
                DecodedCode = DecodedCode + "\n";
            }

        }
        private void FindingLabels(string[] lines)
        {
            
            for(int i=0;i<lines.Count();i++)
            {
                List<string> WordsForEachLine = SplitString(lines[i]);  //specify the words in each line
                if (WordsForEachLine[0]=="ORG") 
                {
                    int TempNumber = Convert.ToInt32(DeletePartOfString(WordsForEachLine[1],"x"), 16);
                    CurrentLane = TempNumber;
                    CurrentLane--;
                    continue;
                }
                if (!(Instructions.Contains(WordsForEachLine[0])))  //found label
                {
                    CurrentLane++;
                    if (DataLabels.Contains(WordsForEachLine[1]))  //finding if it is data or function based
                    {
                        if (WordsForEachLine[1] == "HEX")
                        {
                            LabelAddresses.Add(WordsForEachLine[0], new Tuple<int, int?>(CurrentLane, Convert.ToInt32(WordsForEachLine[2])));
                        }
                        if (WordsForEachLine[1] == "BIN")
                        {
                            LabelAddresses.Add(WordsForEachLine[0], new Tuple<int, int?>(CurrentLane, Convert.ToInt32(WordsForEachLine[2])));
                        }
                        if (WordsForEachLine[1] == "DEC")
                        {
                            LabelAddresses.Add(WordsForEachLine[0], new Tuple<int, int?>(CurrentLane, Convert.ToInt32(WordsForEachLine[2])));
                        }
                    }
                    else   //it is a function label
                    {
                        LabelAddresses.Add(WordsForEachLine[0], new Tuple<int, int?>(CurrentLane, null));
                    }
                    Lines[i] = DeletePartOfString(Lines[i], WordsForEachLine[0]);                    

                }
                else
                {
                    CurrentLane++;
                }

                
            }
        }
        static string ConvertTo5BitBinary(int number)
        {
            if (number < 0 || number > 31)
            {
                throw new ArgumentOutOfRangeException("number", "The number must be in the range 0 to 31 for 5-bit binary.");
            }
            string binaryString = Convert.ToString(number, 2);
            binaryString = binaryString.PadLeft(5, '0');
            return binaryString;
        }
        static string ConvertTo3BitBinary(int number)
        {
            if (number < 0 || number > 7)
            {
                throw new ArgumentOutOfRangeException("number", "The number must be in the range 0 to 7 for 3-bit binary.");
            }
            string binaryString = Convert.ToString(number, 2);
            binaryString = binaryString.PadLeft(3, '0');
            return binaryString;
        }
        static string ConvertHexTo5BitBinary(string hexString)
        {
            int number = Convert.ToInt32(hexString, 16);
            string binaryString = Convert.ToString(number, 2);
            if (binaryString.Length > 5)
            {
                binaryString = binaryString.Substring(binaryString.Length - 5);
            }
            else
            {
                binaryString = binaryString.PadLeft(5, '0');
            }
            return binaryString;
        }
        static List<string> SplitString(string input)
        {
            string[] parts = input.Split(new char[] { ',', ' ' }, StringSplitOptions.RemoveEmptyEntries);
            List<string> result = new List<string>(parts);

            return result;
        }
        private string DeletePartOfString(string Str,string part)
        {
            string Temp = Str.Replace(part, "");
            return Temp;
        }
        static string ConvertTo11BitBinary(int number)
        {
            if (number < -1024 || number > 1023)
                throw new ArgumentOutOfRangeException(nameof(number), "Number must be between -1024 and 1023 inclusive.");
            if (number < 0)
            {
                number = (1 << 11) + number; // This adds 2048 to the negative number to wrap it within 11 bits
            }
            string binaryString = Convert.ToString(number, 2).PadLeft(11, '0');
            return binaryString;
        }
        static string ConvertTo6BitBinary(int number)
        {
            if (number < -32 || number > 31)
                throw new ArgumentOutOfRangeException(nameof(number), "Number must be between -32 and 31 inclusive.");
            if (number < 0)
            {
                number = (1 << 6) + number; // This adds 64 to the negative number to wrap it within 6 bits
            }
            string binaryString = Convert.ToString(number, 2).PadLeft(6, '0');
            return binaryString;
        }
        static string ConvertHexTo6BitBinary(string hex)
        {
            int number = Convert.ToInt32(hex, 16);
            if (number < 0 || number > 63)
                throw new ArgumentOutOfRangeException(nameof(number), "Number must be between 0 and 63 inclusive.");
            string binaryString = Convert.ToString(number, 2).PadLeft(6, '0');
            return binaryString;
        }
        static string ConvertTo9BitBinary(int number)
        {
            if (number < -256 || number > 255)
                throw new ArgumentOutOfRangeException(nameof(number), "Number must be between -256 and 255 inclusive.");
            if (number < 0)
            {
                number = (1 << 9) + number;
            }
            string binaryString = Convert.ToString(number, 2).PadLeft(9, '0');
            return binaryString;
        }
        private string DecodingAdd(List<string> Words)
        {
            string Result = "0001", temp1, temp2, temp3;
            int tempnum1, tempnum2, tempnum3;
            temp1 = DeletePartOfString(Words[1], "R");
            tempnum1 = int.Parse(temp1);
            Result += ConvertTo3BitBinary(tempnum1);
            temp2 = DeletePartOfString(Words[2], "R");
            tempnum2 = int.Parse(temp2);
            Result += ConvertTo3BitBinary(tempnum2);
            if (Words[3].Contains("#"))
            {
                Result += "1";
                temp3 = Words[3].Replace("#", "");
                tempnum3 = int.Parse(temp3);
                Result += ConvertTo5BitBinary(tempnum3);
            }
            else
            {
                if (Words[3].Contains("b"))
                {
                    Result += "1";
                    temp3 = Words[3].Replace("b", "");
                    Result += temp3;
                }
                else
                {
                    if (Words[3].Contains("x"))
                    {
                        Result += "1";
                        temp3 = Words[3].Replace("x", "");
                        Result += ConvertHexTo5BitBinary(temp3);
                       
                    }
                    else
                    {
                        Result += "000";
                        temp3 = Words[3].Replace("R", "");
                        tempnum3 = int.Parse(temp3);
                        Result += ConvertTo3BitBinary(tempnum3);
                    }
                }

            }
            return Result;
        }
        
        private string DecodingAnd(List<string> Words)
        {
            string Result = "0101", temp1, temp2, temp3;
            int tempnum1, tempnum2, tempnum3;
            temp1 = DeletePartOfString(Words[1], "R");
            tempnum1 = int.Parse(temp1);
            Result += ConvertTo3BitBinary(tempnum1);
            temp2 = DeletePartOfString(Words[2], "R");
            tempnum2 = int.Parse(temp2);
            Result += ConvertTo3BitBinary(tempnum2);
            if (Words[3].Contains("#"))
            {
                Result += "1";
                temp3 = Words[3].Replace("#", "");
                tempnum3 = int.Parse(temp3);
                Result += ConvertTo5BitBinary(tempnum3);
            }
            else
            {
                if (Words[3].Contains("b"))
                {
                    Result += "1";
                    temp3 = Words[3].Replace("b", "");
                    Result += temp3;
                }
                else
                {
                    if (Words[3].Contains("x"))
                    {
                        Result += "1";
                        temp3 = Words[3].Replace("x", "");
                        Result += ConvertHexTo5BitBinary(temp3);

                    }
                    else
                    {
                        Result += "000";
                        temp3 = Words[3].Replace("R", "");
                        tempnum3 = int.Parse(temp3);
                        Result += ConvertTo3BitBinary(tempnum3);
                    }
                }

            }
            return Result;
        }
        private string DecodingNot(List<string> Words)
        {
            string Result = "1001",temp1,temp2;
            int tempnum1, tempnum2;
            temp1 = DeletePartOfString(Words[1], "R");
            tempnum1 = int.Parse(temp1);
            Result += ConvertTo3BitBinary(tempnum1);
            temp2 = DeletePartOfString(Words[2], "R");
            tempnum2 = int.Parse(temp2);
            Result += ConvertTo3BitBinary(tempnum2);
            Result += "111111";
            return Result;
        }
        private string DecodingLd(List<string> Words,int line)
        {
            string Result="0010", temp1, temp2;
            int tempnum1;
            temp1 = DeletePartOfString(Words[1], "R");
            tempnum1 = int.Parse(temp1);
            Result += ConvertTo3BitBinary(tempnum1);
            int lineresult = LabelAddresses[Words[2]].Item1 - line;
            Result += ConvertTo9BitBinary(lineresult);
            return Result;
        }
        private string DecodingLdi(List<string> Words, int line)
        {
            string Result = "1010", temp1, temp2;
            int tempnum1;
            temp1 = DeletePartOfString(Words[1], "R");
            tempnum1 = int.Parse(temp1);
            Result += ConvertTo3BitBinary(tempnum1);
            int lineresult = LabelAddresses[Words[2]].Item1 - line;  // in this first i find the value of the key in fact the line address of the label then i subtract it from pc so then i can add it to pc
            Result += ConvertTo9BitBinary(lineresult);
            return Result;
        }
        private string DecodingLdr(List<string> Words)
        {
            string Result = "0110", temp1, temp2, temp3;
            int tempnum1, tempnum2,tempnum3;
            temp1 = DeletePartOfString(Words[1], "R");
            tempnum1 = int.Parse(temp1);
            Result += ConvertTo3BitBinary(tempnum1);
            temp2 = DeletePartOfString(Words[2], "R");
            tempnum2 = int.Parse(temp2);
            Result += ConvertTo3BitBinary(tempnum2);
            if (Words[3].Contains("#"))
            {
                temp3 = Words[3].Replace("#", "");
                tempnum3 = int.Parse(temp3);
                Result += ConvertTo6BitBinary(tempnum3);
            }
            else
            {
                if (Words[3].Contains("b"))
                {
                    temp3 = Words[3].Replace("b", "");
                    Result += temp3;
                }
                else
                {
                    temp3 = Words[3].Replace("x", "");
                    Result += ConvertHexTo6BitBinary(temp3);
                }
            }
            return Result;
        }
        private string DecodingLea(List<string> Words,int line)
        {
            string Result = "1110", temp1, temp2;
            int tempnum1;
            temp1 = DeletePartOfString(Words[1], "R");
            tempnum1 = int.Parse(temp1);
            Result += ConvertTo3BitBinary(tempnum1);
            int lineresult = LabelAddresses[Words[2]].Item1 - line;
            Result += ConvertTo9BitBinary(lineresult);
            return Result;
        }
        private string DecodingSt(List<string> Words,int line)
        {
            string Result = "0011", temp1, temp2;
            int tempnum1;
            temp1 = DeletePartOfString(Words[1], "R");
            tempnum1 = int.Parse(temp1);
            Result += ConvertTo3BitBinary(tempnum1);
            int lineresult = LabelAddresses[Words[2]].Item1 - line;
            Result += ConvertTo9BitBinary(lineresult);
            return Result;
        }
        private string DecodingSti(List<string> Words,int line)
        {
            string Result = "1011", temp1, temp2;
            int tempnum1;
            temp1 = DeletePartOfString(Words[1], "R");
            tempnum1 = int.Parse(temp1);
            Result += ConvertTo3BitBinary(tempnum1);
            int lineresult = LabelAddresses[Words[2]].Item1 - line;
            Result += ConvertTo9BitBinary(lineresult);
            return Result;
        }
        private string DecodingStr(List<string> Words)
        {
            string Result = "0111", temp1, temp2, temp3;
            int tempnum1, tempnum2, tempnum3;
            temp1 = DeletePartOfString(Words[1], "R");
            tempnum1 = int.Parse(temp1);
            Result += ConvertTo3BitBinary(tempnum1);
            temp2 = DeletePartOfString(Words[2], "R");
            tempnum2 = int.Parse(temp2);
            Result += ConvertTo3BitBinary(tempnum2);
            if (Words[3].Contains("#"))
            {
                temp3 = Words[3].Replace("#", "");
                tempnum3 = int.Parse(temp3);
                Result += ConvertTo6BitBinary(tempnum3);
            }
            else
            {
                if (Words[3].Contains("b"))
                {
                    temp3 = Words[3].Replace("b", "");
                    Result += temp3;
                }
                else
                {
                    temp3 = Words[3].Replace("x", "");
                    Result += ConvertHexTo6BitBinary(temp3);
                }
            }
            return Result;
        }

        private string DecodingBr(List<string> Words,int line)
        {
            string Result = "0000", temp1, temp2;
            int tempnum1, tempnum2;
            if (Words[0].Contains("n"))
            {
                Result += "1";
            }
            else
            {
                Result += "0";
            }
            if (Words[0].Contains("z"))
            {
                Result += "1";
            }
            else
            {
                Result += "0";
            }
            if (Words[0].Contains("p"))
            {
                Result += "1";
            }
            else
            {
                Result += "0";
            }
            int lineresult = LabelAddresses[Words[1]].Item1 - line;
            Result += ConvertTo9BitBinary(lineresult);
            return Result;
        }
        
        private string DecodingJmp(List<string> Words)
        {
            string Result = "1100000", temp1;
            int tempnum1;
            temp1 = DeletePartOfString(Words[1], "R");
            tempnum1 = int.Parse(temp1);
            Result += ConvertTo3BitBinary(tempnum1);
            Result += "000000";
            return Result;
        }

        private string DecodingJsr(List<string> Words,int line)
        {
            string Result = "01001", temp1;
            int tenmpnum1;
            int lineresult = LabelAddresses[Words[1]].Item1 - line;
            Result += ConvertTo11BitBinary(lineresult);
            return Result;
        }

        private string DecodingJsrr(List<string> Words)
        {
            string Result = "0100000", temp1;
            int tempnum1;
            temp1 = DeletePartOfString(Words[1], "R");
            tempnum1 = int.Parse(temp1);
            Result += ConvertTo3BitBinary(tempnum1);
            Result += "000000";
            return Result;
        }





        private void Excute(string Instructions)
        {
            var First = InstructionAddresses.First().Key;
            PC = First;
            while (PC != 12320)
            {
                string subinstruction = InstructionAddresses[PC].Substring(0,4);
                switch(subinstruction)
                {
                    case "0001":
                        ExcuteAdd(InstructionAddresses[PC]);
                        break;
                    case "0101":
                        ExcuteAnd(InstructionAddresses[PC]);
                        break;
                    case "1001":
                        ExcuteNot(InstructionAddresses[PC]);
                        break;

                        

                }
            }
        }

        private void ExcuteAdd(string Instruction)
        {
            string DR=Instruction.Substring(4,3);
            int DRreg = Convert.ToInt32(DR, 2);
            string SR1 = Instruction.Substring(7, 3);
            int SR1reg = Convert.ToInt32(SR1, 2);
            if (Instruction[10] == '0')
            {
                string SR2=Instruction.Substring(13, 3);
                int SR2reg = Convert.ToInt32(SR2, 2);
                R[DRreg]=R[SR1reg]+R[SR2reg];
                SetCC(R[DRreg]);
                PC++;
                return;
            }
            else
            {
                string Imm5 = Instruction.Substring(11, 5);
                int Number = Convert.ToInt32(Imm5, 2);
                R[DRreg] = R[SR1reg] + Number;
                SetCC(R[DRreg]);
                PC++;
                return;
            }
        }

        private void ExcuteAnd(string Instruction)
        {
            string DR = Instruction.Substring(4, 3);
            int DRreg = Convert.ToInt32(DR, 2);
            string SR1 = Instruction.Substring(7, 3);
            int SR1reg = Convert.ToInt32(SR1, 2);
            if (Instruction[10] == '0')
            {
                string SR2 = Instruction.Substring(13, 3);
                int SR2reg = Convert.ToInt32(SR2, 2);
                R[DRreg] = R[SR1reg] & R[SR2reg];
                SetCC(R[DRreg]);
                PC++;
                return;
            }
            else
            {
                string Imm5 = Instruction.Substring(11, 5);
                int Number = Convert.ToInt32(Imm5, 2);
                R[DRreg] = R[SR1reg] & Number;
                SetCC(R[DRreg]);
                PC++;
                return;
            }
        }
        
        private void ExcuteNot(string Instruction)
        {
            string DR = Instruction.Substring(4, 3);
            int DRreg = Convert.ToInt32(DR, 2);
            string SR1 = Instruction.Substring(7, 3);
            int SR1reg = Convert.ToInt32(SR1, 2);
            R[DRreg] = ~R[SR1reg];
            SetCC(R[DRreg]);
            PC++;
            return ;
        }

        private void SetCC(int Result)
        {
            if(Result == 0)
            {
                CC[0] = 0;
                CC[1] = 1;
                CC[2] = 0;
            }
            if(Result >0) 
            {
                CC[0] = 0;
                CC[1] = 0;
                CC[2] = 1;
            }
            if(Result < 0)
            {
                CC[0] = 1;
                CC[1] = 0;
                CC[2] = 0;
            }
        }
    }
}