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
        Dictionary<string,Tuple<int,int?>> LabelAdresses;   //a map for holding the lables
        string[] Lines;   //specially global for deleting the labels from it

        public MainWindow()
        {
            InitializeComponent();
        }

        private void SaveAC_Click(object sender, RoutedEventArgs e)
        {
            LabelAdresses = new Dictionary<string,Tuple<int, int?>>();
            string Text=AssemblySource.Text;
            Lines= Text.Split(new[] { "\r\n", "\r", "\n" }, StringSplitOptions.RemoveEmptyEntries);
            Decode(Lines);
        }
        private void Decode(string[] lines)
        {
            FindingLabels(lines);
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
                }
                if (!(Instructions.Contains(WordsForEachLine[0])))  //found label
                {
                    CurrentLane++;
                    if (DataLabels.Contains(WordsForEachLine[1]))  //finding if it is data or function based
                    {
                        if (WordsForEachLine[1] == "HEX")
                        {
                            LabelAdresses.Add(WordsForEachLine[0], new Tuple<int, int?>(CurrentLane, Convert.ToInt32(WordsForEachLine[2])));
                        }
                        if (WordsForEachLine[1] == "BIN")
                        {
                            LabelAdresses.Add(WordsForEachLine[0], new Tuple<int, int?>(CurrentLane, Convert.ToInt32(WordsForEachLine[2])));
                        }
                        if (WordsForEachLine[1] == "DEC")
                        {
                            LabelAdresses.Add(WordsForEachLine[0], new Tuple<int, int?>(CurrentLane, Convert.ToInt32(WordsForEachLine[2])));
                        }
                    }
                    else   //it is a function label
                    {
                        LabelAdresses.Add(WordsForEachLine[0], new Tuple<int, int?>(CurrentLane, null));
                    }
                    Lines[i] = DeletePartOfString(Lines[i], WordsForEachLine[0]);                    

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
    }
}