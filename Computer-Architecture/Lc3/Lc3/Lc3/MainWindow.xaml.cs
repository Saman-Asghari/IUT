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

        public MainWindow()
        {
            InitializeComponent();
        }

        private void SaveAC_Click(object sender, RoutedEventArgs e)
        {
            LabelAddresses = new Dictionary<string,Tuple<int, int?>>();
            InstructionAddresses = new Dictionary<int, string>();
            string Text=AssemblySource.Text;
            Lines= Text.Split(new[] { "\r\n", "\r", "\n" }, StringSplitOptions.RemoveEmptyEntries);
            Decode(Lines);
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
    }
}