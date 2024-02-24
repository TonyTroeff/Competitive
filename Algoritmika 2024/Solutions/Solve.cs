namespace Solutions;

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

public static class Solve
{
    public static double[] Problem1(double[] array, double minInclusive, double maxInclusive)
    {
        int startIndex = BinarySearchIndex(array, minInclusive, useLeft: true), endIndex = BinarySearchIndex(array, maxInclusive, useLeft: false);
        if (endIndex < startIndex) return Array.Empty<double>();

        return array.Skip(startIndex).Take(endIndex - startIndex + 1).ToArray();
    }

    private static int BinarySearchIndex<T>(T[] array, T value, bool useLeft)
        where T : IComparable<T>
    {
        int left = 0, right = array.Length - 1;
        while (left <= right)
        {
            int middle = left + (right - left) / 2;
            int comparisonResult = array[middle].CompareTo(value);
            if (comparisonResult == 0) return middle;

            if (comparisonResult == -1) left = middle + 1;
            else right = middle - 1;
        }

        return useLeft ? left : right;
    }

    public static (string Severity, string Device, string Damage) Problem2(string statusCodeInHexadecimal)
    {
        uint statusCode = Convert.ToUInt32(statusCodeInHexadecimal, 16);
        if (statusCode > byte.MaxValue) throw new InvalidOperationException("Status code should be a single byte according to the problem's description.");

        const uint severityBitsMask = (1U << 2) - 1;
        const uint deviceBitsMask = ((1U << 3) - 1) << 2;
        const uint damageBitsMask = ((1U << 3) - 1) << 5;

        uint severityCode = statusCode & severityBitsMask;
        uint deviceCode = (statusCode & deviceBitsMask) >> 2;
        uint damageCode = (statusCode & damageBitsMask) >> 5;
        return (Constants.Problem2.Severities[severityCode], Constants.Problem2.Devices[deviceCode], Constants.Problem2.Damages[damageCode]);
    }

    public static void Problem3(byte[][] bitmap, int row, int col, byte newColor)
    {
        if (row < 0 || row >= bitmap.Length || col < 0 || col >= bitmap[row].Length) throw new ArgumentException("Invalid coordinates were provided");

        var visited = new bool[bitmap.Length][];
        for (int i = 0; i < bitmap.Length; i++) visited[i] = new bool[bitmap[i].Length];

        byte originalColor = GetColor(bitmap, row, col);
        visited[row][col] = true;
        SetColor(bitmap, row, col, newColor);

        Dfs(bitmap, row, col, newColor, visited, originalColor);
    }

    private static readonly (int RowChange, int ColChange)[] _directions = [(1, 0), (0, 1), (-1, 0), (0, -1)];

    private static void Dfs(byte[][] bitmap, int row, int col, byte newColor, bool[][] visited, byte originalColor)
    {
        for (int i = 0; i < _directions.Length; i++)
        {
            int newRow = row + _directions[i].RowChange, newCol = col + _directions[i].ColChange;
            if (newRow >= 0 && newRow < bitmap.Length && newCol >= 0 && newCol < bitmap[newRow].Length && GetColor(bitmap, newRow, newCol) == originalColor && !visited[newRow][newCol])
            {
                visited[newRow][newCol] = true;
                SetColor(bitmap, newRow, newCol, newColor);

                Dfs(bitmap, newRow, newCol, newColor, visited, originalColor);
            }
        }
    }

    private static byte GetColor(byte[][] bitmap, int row, int col) => bitmap[row][col];
    private static void SetColor(byte[][] bitmap, int row, int col, byte newColor) => bitmap[row][col] = newColor;

    public static void Problem4(string pathToInputFile, string pathToMergeFile, string pathToOutputFile)
    {
        const int limit = 10000;
        
        var comparer = Comparer<int>.Create((x, y) => -1 * x.CompareTo(y));
        using var inputFileStream = new FileStream(pathToInputFile, FileMode.Open, FileAccess.Read);
        using var mergeFileStream = new FileStream(pathToMergeFile, FileMode.Create, FileAccess.ReadWrite);
        using var resultFileStream = new FileStream(pathToOutputFile, FileMode.Create, FileAccess.ReadWrite);
        
        using var inputStreamReader = new StreamReader(inputFileStream);
        using var mergeStreamWriter = new StreamWriter(mergeFileStream);
        using var resultStreamReader = new StreamReader(resultFileStream);

        int[] buffer = new int[limit];
        while (!inputStreamReader.EndOfStream)
        {
            int readBytes = 0;
            while (!inputStreamReader.EndOfStream && readBytes < buffer.Length)
            {
                if (!TryReadFromFile(inputStreamReader, out var value)) break;

                buffer[readBytes] = value;
                readBytes++;
            }

            Array.Sort(buffer, 0, readBytes, comparer);

            mergeFileStream.Seek(0, SeekOrigin.Begin);
            resultFileStream.Seek(0, SeekOrigin.Begin);
            
            int index = 0;
            bool couldReadFromBuffer = TryReadFromBuffer(buffer, readBytes, index, out var a);
            bool couldReadFromFile = TryReadFromFile(resultStreamReader, out var b);
            while (couldReadFromBuffer || couldReadFromFile)
            {
                if (!couldReadFromFile || a > b)
                {
                    mergeStreamWriter.WriteLine(a);
                    couldReadFromBuffer = TryReadFromBuffer(buffer, readBytes, ++index, out a);
                }
                else
                {
                    mergeStreamWriter.WriteLine(b);
                    couldReadFromFile = TryReadFromFile(resultStreamReader, out b);
                }
            }

            mergeStreamWriter.Flush();

            mergeFileStream.Seek(0, SeekOrigin.Begin);
            resultFileStream.Seek(0, SeekOrigin.Begin);
            mergeFileStream.CopyTo(resultFileStream);
        }
    }

    private static bool TryReadFromBuffer(int[] buffer, int readBytes, int index, out int next)
    {
        if (index >= readBytes)
        {
            next = int.MinValue;
            return false;
        }

        next = buffer[index];
        return true;
    }

    private static bool TryReadFromFile(StreamReader reader, out int next)
    {
        if (reader.EndOfStream)
        {
            next = int.MinValue;
            return false;
        }

        string line = reader.ReadLine();
        next = int.Parse(line);
        return true;
    }
    
    public static string Problem5(string[] text, int n)
    {
        Comparer<int> comparer = Comparer<int>.Create((a, b) => -1 * a.CompareTo(b));
        PriorityQueue<string, int> heap = new PriorityQueue<string, int>(comparer);
        for (int i = 0; i < text.Length; i++)
        {
            heap.Enqueue(text[i], text[i].Length);
            if (i > n) heap.Dequeue();
        }

        heap.TryPeek(out var result, out _);
        return result;
    }

    public static long[] Problem6(long number)
    {
        number = Math.Abs(number);
        
        List<long> result = new List<long>();

        for (int i = 2; i <= number; i++)
        {
            while (number % i == 0)
            {
                if (result.Count == 0 || result[^1] != i) result.Add(i);
                number /= i;
            }
        }

        return result.ToArray();
    }

    public static double Problem7(Line firstRectangleDiagonal, Line secondRectangleDiagonal)
    {
        Rectangle firstRectangle = CalculateRectangle(firstRectangleDiagonal);
        Rectangle secondRectangle = CalculateRectangle(secondRectangleDiagonal);

        double intersectWidth = Math.Min(firstRectangle.Right, secondRectangle.Right) - Math.Max(firstRectangle.Left, secondRectangle.Left);
        double intersectHeight = Math.Min(firstRectangle.Top, secondRectangle.Top) - Math.Max(firstRectangle.Bottom, secondRectangle.Bottom);

        if (intersectWidth <= 0 || intersectHeight <= 0) return 0;
        return intersectWidth * intersectHeight;
    }

    private static Rectangle CalculateRectangle(Line diagonal)
    {
        // Each rectangle can be defined by its two diagonals - from top-left to bottom-right or from bottom-left to top-right.
        Point top, bottom;
        if (diagonal.Start.Y > diagonal.End.Y)
        {
            top = diagonal.Start;
            bottom = diagonal.End;
        }
        else
        {
            top = diagonal.End;
            bottom = diagonal.Start;
        }
        
        return new Rectangle
        {
            Top = top.Y,
            Bottom = bottom.Y,
            Left = diagonal.Start.X,
            Right = diagonal.End.X
        };
    }

    public static string[] Problem8(string html)
    {
        Stack<string> tags = new Stack<string>();
        List<string> result = new List<string>();

        int position = 0;
        while (position < html.Length)
        {
            if (html[position] == '<')
            {
                int tagStart = position;
                while (position < html.Length && html[position] != '>') position++;

                string tag = html.Substring(tagStart, position - tagStart + 1);
                if (IsComment(tag)) ExtractContent(tag.Substring(4, tag.Length - 7), result);
                else if (IsClosingTag(tag))
                {
                    string tagName = ExtractTagName(tag, 2);
                    
                    while (tags.Count > 0)
                    {
                        var poppedTag = tags.Pop();
                        if (poppedTag == tagName) break; 
                    }
                }
                else
                {
                    string tagName = ExtractTagName(tag, 1);
                    tags.Push(tagName);
                }

                position++;
            }
            else
            {
                int contentStart = position;
                while (position < html.Length && html[position] != '<') position++;
            
                if (tags.TryPeek(out var lastTag) && lastTag != "style") ExtractContent(html.Substring(contentStart, position - contentStart), result);
            }
        }

        return result.ToArray();
    }

    private static string ExtractTagName(string tag, int start)
    {
        var spaceIndex = tag.IndexOf(' ');
        if (spaceIndex == -1) return tag.Substring(start, tag.Length - 1 - start);
        return tag.Substring(start, spaceIndex - start);
    }
    private static bool IsClosingTag(string tag) => tag.Length >= 3 && tag[1] == '/';
    private static bool IsComment(string tag) => tag.Length >= 7 && tag[1] == '!' && tag[2] == '-' && tag[3] == '-' && tag[^3] == '-' && tag[^2] == '-';
    private static void ExtractContent(string text, List<string> result) => result.AddRange(text.Split().Where(x => !string.IsNullOrWhiteSpace(x)));
}