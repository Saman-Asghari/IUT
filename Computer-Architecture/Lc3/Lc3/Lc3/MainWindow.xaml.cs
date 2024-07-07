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
using System.Buffers;
using System.IO;

namespace Lc3
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        List<string> Instructions = new List<string> {"ADD","AND","BRn", "BRz", "BRp", "BRnz", "BRnp", "BRzp", "BR","BRnzp", "JMP","JSR","JSRR","LD","LDI","LDR","LEA","NOT","RET","RTI","ST","STI","STR","TRAP","ORG","HLT","PUSH","POP","END",};
        List<string> DataLabels = new List<string> { "DEC", "BIN", "HEX" }; 
        string DecodedCode = "";  //hold the last result here
        int CurrentLane = 0;    //used for handling org instruction
        Dictionary<string,Tuple<int,int?>> LabelAddresses;   //a map for holding the lables
        Dictionary<int, string> InstructionAddresses;
        string[] Lines;   //specially global for deleting the labels from it
        int[] R;
        int[] CC;
        int PC;
        int EndOfProgram = 0;
        string IR;
        int Delay;
        Stack<int> RegStack;
        string PreviousTextN = string.Empty;
        string PreviousTextZ = string.Empty;
        string PreviousTextP = string.Empty;
        string PreviousTextR0 = string.Empty;
        string PreviousTextR1 =string.Empty;
        string PreviousTextR2 = string.Empty;
        string PreviousTextR3 = string.Empty;
        string PreviousTextR4 = string.Empty;
        string PreviousTextR5 = string.Empty;
        string PreviousTextR6 = string.Empty;
        string PreviousTextR7 = string.Empty;
        string PreviousTextPC = string.Empty;
        string PreviousTextIR = string.Empty;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void SaveAC_Click(object sender, RoutedEventArgs e)
        {
            LabelAddresses = new Dictionary<string,Tuple<int, int?>>();
            InstructionAddresses = new Dictionary<int, string>();
            RegStack= new Stack<int>();
            string Text=AssemblySource.Text;
            R=new int[8];
            CC=new int[3];
            Lines= Text.Split(new[] { "\r\n", "\r", "\n" }, StringSplitOptions.RemoveEmptyEntries);
            Decode(Lines);
            SaveStringToBinFile(DecodedCode, "Assembly.bin");
            Excute(DecodedCode);
            Console.WriteLine( "hellloo");
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
                if (WordsForEachLine[0] == "HLT")
                {
                    EndOfProgram=CurrentLane+1;
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
                if (WordsForEachLine[0] == "PUSH")
                {
                    CurrentLane++;
                    string Result=DecodingPush(WordsForEachLine);
                    InstructionAddresses.Add(CurrentLane, Result);
                    DecodedCode += Result;
                }
                if (WordsForEachLine[0] == "POP")
                {
                    CurrentLane++;
                    string Result=DecodingPop(WordsForEachLine);
                    InstructionAddresses.Add(CurrentLane,Result);
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
                    if (WordsForEachLine[0] == ";")
                    {
                        CurrentLane--;
                        continue;
                    }
                    if (DataLabels.Contains(WordsForEachLine[1]))  //finding if it is data or function based
                    {
                        if (WordsForEachLine[1] == "HEX")
                        {
                            LabelAddresses.Add(WordsForEachLine[0], new Tuple<int, int?>(CurrentLane, Convert.ToInt32(WordsForEachLine[2],16)));
                        }
                        if (WordsForEachLine[1] == "BIN")
                        {
                            LabelAddresses.Add(WordsForEachLine[0], new Tuple<int, int?>(CurrentLane, Convert.ToInt32(WordsForEachLine[2],2)));
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
        static int Convert9BitSignedBinaryToDecimal(string binaryString)
        {
            if (binaryString.Length != 9)
            {
                throw new ArgumentException("Input must be a 9-bit binary string.");
            }
            bool isNegative = binaryString[0] == '1';
            if (isNegative)
            {
                string magnitudeBinaryString = GetTwosComplement(binaryString);
                int magnitude = Convert.ToInt32(magnitudeBinaryString, 2);
                return -magnitude;
            }
            else
            {
                return Convert.ToInt32(binaryString, 2);
            }
        }

        static string GetTwosComplement(string binaryString)
        {
            char[] bits = binaryString.ToCharArray();
            bool foundOne = false;

            // Perform the two's complement
            for (int i = bits.Length - 1; i >= 0; i--)
            {
                if (foundOne)
                {
                    bits[i] = bits[i] == '1' ? '0' : '1';
                }
                else if (bits[i] == '1')
                {
                    foundOne = true;
                }
            }

            return new string(bits);
        }
        static string ConvertTo16BitBinary(int number)
        {
            if (number < -32768 || number > 32767)
            {
                throw new ArgumentOutOfRangeException(nameof(number), "The number must be between -32768 and 32767.");
            }

            if (number >= 0)
            {
                return Convert.ToString(number, 2).PadLeft(16, '0');
            }
            else
            {
                string binaryString = Convert.ToString(number, 2);
                if (binaryString.Length < 16)
                {
                    binaryString = binaryString.PadLeft(16, '1');
                }
                else if (binaryString.Length > 16)
                {
                    binaryString = binaryString.Substring(binaryString.Length - 16);
                }
                return binaryString;
            }
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

        private string DecodingPush(List<string> Words)
        {
            string Result = "1101", temp1;
            int tempnum1;
            temp1 = DeletePartOfString(Words[1], "R");
            tempnum1 = int.Parse(temp1);
            Result += ConvertTo3BitBinary(tempnum1);
            Result += "000000000";
            return Result;
        }
        private string DecodingPop(List<string> Words)
        {
            string Result = "1101", temp1;
            int tempnum1;
            temp1 = DeletePartOfString(Words[1], "R");
            tempnum1=int.Parse(temp1);
            Result+= ConvertTo3BitBinary(tempnum1);
            Result += "100000000";
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





        private async void Excute(string Instructions)
        {
            var First = InstructionAddresses.First().Key;
            PC = First;
            while (PC !=EndOfProgram)
            {
                //Thread.Sleep(5000);
                await Task.Delay(Delay);
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
                    case "0010":
                        ExcuteLd(InstructionAddresses[PC]);
                        break;
                    case "1010":
                        ExcuteLdi(InstructionAddresses[PC]);
                        break;
                    case "0110":
                        ExcuteLdr(InstructionAddresses[PC]);
                        break;
                    case "1110":
                        ExcuteLea(InstructionAddresses[PC]);
                        break;
                    case "0011":
                        ExcuteSt(InstructionAddresses[PC]);
                        break;
                    case "1011":
                        ExcuteSti(InstructionAddresses[PC]);
                        break;
                    case "0111":
                        ExcuteStr(InstructionAddresses[PC]);
                        break;
                    case "0000":
                        ExcuteBr(InstructionAddresses[PC]);
                        break;
                    case "1100":
                        ExcuteJmpOrRet(InstructionAddresses[PC]);
                        break;
                    case "0100":
                        ExcuteJsrOrJsrr(InstructionAddresses[PC]);
                        break;
                    case "1101":
                        ExcutePushOrPop(InstructionAddresses[PC]);
                        break;

                }
            }
        }

        private void ExcutePushOrPop(string Instruction)
        {
            if (Instruction[7] == '0')
            {
                string SR=Instruction.Substring(4, 3);
                int SRreg=Convert.ToInt32(SR,2);
                RegStack.Push(R[SRreg]);
                SetCC(R[SRreg]);
                IR = Instruction;
                SetPushStackUI(R[SRreg]);
                SetUI();
                PC++;
                return;
            }
            else
            {
                string SR = Instruction.Substring(4, 3);
                int SRreg = Convert.ToInt32(SR,2);
                int temp=RegStack.Pop();
                R[SRreg] =temp;
                SetCC(temp);
                IR = Instruction;
                SetPopStackUI();
                SetUI(); 
                PC++;
                return;
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
                IR = Instruction;
                SetUI();
                PC++;
                return;
            }
            else
            {
                string Imm5 = Instruction.Substring(11, 5);
                int Number = Convert.ToInt32(Imm5, 2);
                R[DRreg] = R[SR1reg] + Number;
                SetCC(R[DRreg]);
                IR = Instruction;
                SetUI();
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
                IR = Instruction;

                SetUI();
                PC++;
                return;
            }
            else
            {
                string Imm5 = Instruction.Substring(11, 5);
                int Number = Convert.ToInt32(Imm5, 2);
                R[DRreg] = R[SR1reg] & Number;
                SetCC(R[DRreg]);
                IR = Instruction;

                SetUI();
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
            IR = Instruction;

            SetUI();
            PC++;
            return ;
        }
        
        private void ExcuteLd(string Instruction)
        {
            string DR = Instruction.Substring(4, 3);
            int DRreg = Convert.ToInt32(DR, 2);
            string PCoffset= Instruction.Substring(7, 9);
            int labelAddress=PC+Convert9BitSignedBinaryToDecimal(PCoffset);
            int? TempNumber=null;
            foreach(var kvp in LabelAddresses)
            {
                if(kvp.Value.Item1 == labelAddress)
                {
                    TempNumber=kvp.Value.Item2;
                }
            }
            R[DRreg] = (int)TempNumber;
            SetCC(R[DRreg]);
            IR = Instruction;

            SetUI();
            PC++;
            return;
        }
        private void ExcuteLdi(string Instruction)
        {
            string DR = Instruction.Substring(4, 3);
            int DRreg = Convert.ToInt32(DR, 2);
            string PCoffset = Instruction.Substring(7, 9);
            int labelAddress = PC + Convert9BitSignedBinaryToDecimal(PCoffset);
            int? TempNumber = null;
            int? TempNumber2 = null;
            foreach (var kvp in LabelAddresses)
            {
                if (kvp.Value.Item1 == labelAddress)
                {
                    TempNumber = kvp.Value.Item2;
                }
            }

            foreach (var kvp2 in LabelAddresses) 
            {
                if( kvp2.Value.Item1 == TempNumber)
                {
                    TempNumber2=kvp2.Value.Item2;
                }
            }
            R[DRreg] = (int)TempNumber2;
            SetCC(R[DRreg]);
            IR = Instruction;

            SetUI();
            PC++;
            return;
        }
        private void ExcuteLdr(string Instruction)
        {
            string DR = Instruction.Substring(4, 3);
            int DRreg = Convert.ToInt32(DR, 2);
            string BaseReg = Instruction.Substring(7, 3);
            int Basereg = Convert.ToInt32(BaseReg, 2);
            string offset= Instruction.Substring(10, 6);
            int offsetNumber = Convert9BitSignedBinaryToDecimal(offset);
            int? TempNumber = null;
            foreach(var kvp in LabelAddresses) 
            {
                if (kvp.Value.Item1 == R[Basereg] + offsetNumber)
                {
                    TempNumber=kvp.Value.Item2;
                }
            }
            R[DRreg]= (int)TempNumber;
            SetCC(R[DRreg]);
            IR = Instruction;

            SetUI();
            PC++;
            return;
        }

        private void ExcuteLea(string Instruction)
        {
            string DR = Instruction.Substring(4, 3);
            int DRreg = Convert.ToInt32(DR, 2);
            string PCoffset = Instruction.Substring(7, 9);
            int labelAddress = PC + Convert9BitSignedBinaryToDecimal(PCoffset);
            R[DRreg]= (int)labelAddress;
            IR = Instruction;

            SetUI();
            PC++;
            return;
        }
        private void ExcuteSt(string Instruction)
        {
            string SR = Instruction.Substring(4, 3);
            int SRreg = Convert.ToInt32(SR, 2);
            string PCoffset = Instruction.Substring(7, 9);
            int labelAddress = PC + Convert9BitSignedBinaryToDecimal(PCoffset);
            int? help = R[SRreg];
            foreach (var key in new List<string>(LabelAddresses.Keys))
            {
                var tupleValue = LabelAddresses[key];
                if (tupleValue.Item1 == labelAddress)
                {
                    LabelAddresses[key] = Tuple.Create(tupleValue.Item1,help);
                }
            }
            IR = Instruction;

            SetUI();
            PC++;
            return;
        }

        private void ExcuteSti(string Instruction)
        {
            string SR = Instruction.Substring(4, 3);
            int SRreg = Convert.ToInt32(SR, 2);
            string PCoffset = Instruction.Substring(7, 9);
            int labelAddress = PC + Convert9BitSignedBinaryToDecimal(PCoffset);
            int? TempNumber = null;
            int? help = R[SRreg];
            foreach (var kvp in LabelAddresses)
            {
                if (kvp.Value.Item1 == labelAddress)
                {
                    TempNumber = kvp.Value.Item2;
                }
            }
            int? SearchValue = TempNumber;
            foreach (var key in new List<string>(LabelAddresses.Keys))
            {
                var tupleValue = LabelAddresses[key];
                if (tupleValue.Item1 == SearchValue)
                {
                    LabelAddresses[key] = Tuple.Create(tupleValue.Item1, help);
                }
            }
            IR = Instruction;

            SetUI() ;
            PC ++;
            return;
        }

        private void ExcuteStr(string Instruction)
        {
            string SR = Instruction.Substring(4, 3);
            int SRreg = Convert.ToInt32(SR, 2);
            string BaseReg = Instruction.Substring(7, 3);
            int Basereg = Convert.ToInt32(BaseReg, 2);
            string offset = Instruction.Substring(10, 6);
            int offsetNumber = Convert9BitSignedBinaryToDecimal(offset);
            int? help = R[SRreg];
            int TempNumber =offsetNumber+R[Basereg];
            int SearchValue = TempNumber;
            foreach (var key in new List<string>(LabelAddresses.Keys))
            {
                var tupleValue = LabelAddresses[key];
                if (tupleValue.Item1 == SearchValue)
                {
                    LabelAddresses[key] = Tuple.Create(tupleValue.Item1, help);
                }
            }
            IR = Instruction;

            SetUI();
            PC ++;
            return;
        }
        private void ExcuteBr(string Instruction)
        {
            int N = 1, Z = 1, P = 1;
            string PCoffset = Instruction.Substring(7, 9);
            switch (Instruction.Substring(4, 3))
            {
                case "000":
                    PC = PC + Convert9BitSignedBinaryToDecimal(PCoffset);
                    break;
                case "001":
                    if (CC[2] == 1)
                    {
                        PC = PC + Convert9BitSignedBinaryToDecimal(PCoffset);
                    }
                    else
                    {
                        PC++;
                    }
                    break;
                case "010":
                    if (CC[1] == 1) 
                    {
                        PC = PC + Convert9BitSignedBinaryToDecimal(PCoffset);
                    }
                    else
                    {
                        PC++;
                    }
                    break;
                case "100":
                    if (CC[0] == 1)
                    {
                        PC = PC + Convert9BitSignedBinaryToDecimal(PCoffset);
                    }
                    else
                    {
                        PC++;
                    }
                    break;
                case "011":
                    if (CC[1] == 1 || CC[2] == 1)
                    {
                        PC= PC + Convert9BitSignedBinaryToDecimal(PCoffset);
                    }
                    else
                    {
                        PC++;
                    }
                    break;
                case "101":
                    if (CC[0] == 1 || CC[2] == 1)
                    {
                        PC=PC+Convert9BitSignedBinaryToDecimal(PCoffset);
                    }
                    else
                    {
                        PC++;
                    }
                    break;
                case "110":
                    if (CC[0]==1|| CC[1] == 1)
                    {
                        PC=PC+ Convert9BitSignedBinaryToDecimal(PCoffset);
                    }
                    else
                    {
                        PC++;
                    }
                    break;
                case "111":
                    if (CC[0] == 1 || CC[1] == 1 || CC[2]==1) 
                    {
                        PC = PC + Convert9BitSignedBinaryToDecimal(PCoffset);
                    }
                    else
                    {
                        PC++;
                    }
                    break;
            }
            IR = Instruction;

            SetUI();
        }

        private void ExcuteJmpOrRet(string Instruction)
        {
            string BaseReg = Instruction.Substring(7, 3);
            int Basereg = Convert.ToInt32(BaseReg, 2);
            PC = R[Basereg];
            IR = Instruction;

            SetUI();
        }

        
        private void ExcuteJsrOrJsrr(string Instruction)
        {
            int temp=PC;
            if (Instruction[4] == '0')
            {
                string BaseReg = Instruction.Substring(7, 3);
                int Basereg = Convert.ToInt32(BaseReg, 2);
                PC = R[Basereg];
                R[7] = temp+1;
            }
            else
            {
                string offset=Instruction.Substring(5, 11);
                int offsetNum= Convert9BitSignedBinaryToDecimal(offset);
                PC=PC + offsetNum;
                R[7]=temp+1;
            }
            IR = Instruction;

            SetUI();
            return;
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
        static void SaveStringToBinFile(string data, string filePath)
        {
            byte[] byteArray = System.Text.Encoding.UTF8.GetBytes(data);

            using (FileStream fs = new FileStream(filePath, FileMode.Create, FileAccess.Write))
            {
                using (BinaryWriter writer = new BinaryWriter(fs))
                {
                    writer.Write(byteArray);
                }
            }
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void SetUI()
        {
            R0TextBox.Text = R[0].ToString() + " (" + ConvertTo16BitBinary(R[0])+")";
            R1TextBox.Text = R[1].ToString()+" (" + ConvertTo16BitBinary(R[1]) + ")";
            R2TextBox.Text = R[2].ToString() + " (" + ConvertTo16BitBinary(R[2]) + ")";
            R3TextBox.Text = R[3].ToString() + " (" + ConvertTo16BitBinary(R[3]) + ")";
            R4TextBox.Text = R[4].ToString() + " (" + ConvertTo16BitBinary(R[4]) + ")";
            R5TextBox.Text = R[5].ToString() + " (" + ConvertTo16BitBinary(R[5]) + ")";
            R6TextBox.Text = R[6].ToString() + " (" + ConvertTo16BitBinary(R[6]) + ")";
            R7TextBox.Text = R[7].ToString() + " (" + ConvertTo16BitBinary(R[7]) + ")";
            PCTextBox.Text = PC.ToString() + " (" + ConvertTo16BitBinary(PC) + ")";
            IRTextBox.Text = IR;
            NTextBox.Text = CC[0].ToString();
            ZTextBox.Text = CC[1].ToString();
            PTextBox.Text = CC[2].ToString();

        }

        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void SetDelay_Click(object sender, RoutedEventArgs e)
        {
            Delay=Convert.ToInt32(DelayNumber.Text);
            Delay = Delay * 1000;
        }

        private async void R1TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (R1TextBox.Text != PreviousTextR1)
            {
                R1Label.Background=new SolidColorBrush(Colors.Red);
                await Task.Delay(Delay/2);
                R1Label.Background=new SolidColorBrush(Colors.White);
            }
            
            PreviousTextR1 = R1TextBox.Text;
        }

        private async void R0TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (R0TextBox.Text != PreviousTextR0)
            {
                R0Label.Background = new SolidColorBrush(Colors.Red);
                await Task.Delay(Delay / 2);
                R0Label.Background = new SolidColorBrush(Colors.White);
            }

            PreviousTextR0 = R0TextBox.Text;
        }

        private async void R2TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (R2TextBox.Text != PreviousTextR2)
            {
                R2Label.Background = new SolidColorBrush(Colors.Red);
                await Task.Delay(Delay / 2);
                R2Label.Background = new SolidColorBrush(Colors.White);
            }

            PreviousTextR2 = R2TextBox.Text;
        }

        private async  void R3TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (R3TextBox.Text != PreviousTextR3)
            {
                R3Label.Background = new SolidColorBrush(Colors.Red);
                await Task.Delay(Delay / 2);
                R3Label.Background = new SolidColorBrush(Colors.White);
            }

            PreviousTextR3 = R3TextBox.Text;
        }

        private async void R4TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (R4TextBox.Text != PreviousTextR4)
            {
                R4Label.Background = new SolidColorBrush(Colors.Red);
                await Task.Delay(Delay / 2);
                R4Label.Background = new SolidColorBrush(Colors.White);
            }

            PreviousTextR4 = R4TextBox.Text;
        }

        private async void R5TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (R5TextBox.Text != PreviousTextR5)
            {
                R5Label.Background = new SolidColorBrush(Colors.Red);
                await Task.Delay(Delay / 2);
                R5Label.Background = new SolidColorBrush(Colors.White);
            }

            PreviousTextR5 = R5TextBox.Text;
        }

        private async void R6TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (R6TextBox.Text != PreviousTextR6)
            {
                R6Label.Background = new SolidColorBrush(Colors.Red);
                await Task.Delay(Delay / 2);
                R6Label.Background = new SolidColorBrush(Colors.White);
            }

            PreviousTextR6 = R6TextBox.Text;
        }

        private async void R7TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (R7TextBox.Text != PreviousTextR7)
            {
                R7Label.Background = new SolidColorBrush(Colors.Red);
                await Task.Delay(Delay / 2);
                R7Label.Background = new SolidColorBrush(Colors.White);
            }

            PreviousTextR7 = R7TextBox.Text;
        }

        private async void PCTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (PCTextBox.Text != PreviousTextPC)
            {
                PCLabel.Background = new SolidColorBrush(Colors.Red);
                await Task.Delay(Delay / 2);
                PCLabel.Background = new SolidColorBrush(Colors.White);
            }

            PreviousTextPC = PCTextBox.Text;
        }

        private async void IRTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (IRTextBox.Text != PreviousTextIR)
            {
                IRLabel.Background = new SolidColorBrush(Colors.Red);
                await Task.Delay(Delay / 2);
                IRLabel.Background = new SolidColorBrush(Colors.White);
            }

            PreviousTextIR = IRTextBox.Text;
        }

        private async void NTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (NTextBox.Text != PreviousTextN)
            {
                NLabel.Background = new SolidColorBrush(Colors.Red);
                await Task.Delay(Delay / 2);
                NLabel.Background = new SolidColorBrush(Colors.White);
            }

            PreviousTextN = NTextBox.Text;
        }

        private async void ZTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (ZTextBox.Text != PreviousTextZ)
            {
                ZLabel.Background = new SolidColorBrush(Colors.Red);
                await Task.Delay(Delay / 2);
                ZLabel.Background = new SolidColorBrush(Colors.White);
            }

            PreviousTextZ = ZTextBox.Text;
        }

        private async void PTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (PTextBox.Text != PreviousTextP)
            {
                PLabel.Background = new SolidColorBrush(Colors.Red);
                await Task.Delay(Delay / 2);
                PLabel.Background = new SolidColorBrush(Colors.White);
            }

            PreviousTextP = PTextBox.Text;
        }

        private void SetPushStackUI(int Number)
        {
            TextBlock textBlock = new TextBlock
            {
                Text = Number.ToString(),
                Margin = new Thickness(5),
                HorizontalAlignment = HorizontalAlignment.Center,
                Background = System.Windows.Media.Brushes.LightBlue,
                Padding = new Thickness(5)
            };

            MyStack.Children.Insert(0, textBlock);
        }
        private void SetPopStackUI() 
        {
            if (MyStack.Children.Count > 0)
            {
                MyStack.Children.RemoveAt(0);
            }
            else
            {
                MessageBox.Show("The stack is empty. Nothing to pop.", "Empty Stack", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
        }
    }
}