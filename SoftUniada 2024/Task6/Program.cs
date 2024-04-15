namespace Task6;

using System.Diagnostics;
using System.Text;

public static class Program
{
    public static void Main()
    {
        var input = Console.ReadLine()!;

        var freq = new int[10];
        foreach (var digit in input)
        {
            Debug.Assert(char.IsDigit(digit));
            freq[digit - '0']++;
        }
        
        var oddFreqCount = freq.Count(x => x % 2 != 0);
        if (!TryGetMiddleElement(freq, out var middleElement)) Console.WriteLine("No palindromic number available.");
        else
        {
            if (middleElement != -1) freq[middleElement]--;

            var sb = new StringBuilder(capacity: input.Length);
            for (var i = freq.Length - 1; i >= 0; i--)
            {
                for (var j = 0; j < freq[i]; j += 2) sb.Append(i);
            }

            var symmetryIndex = sb.Length - 1;
            if (middleElement != -1) sb.Append(middleElement);

            for (var i = symmetryIndex; i >= 0; i--) sb.Append(sb[i]);

            Console.WriteLine(sb.ToString());
        }
    }

    private static bool TryGetMiddleElement(int[] arr, out int index)
    {
        index = -1;
        var candidateIndex = index;

        for (var i = 0; i < arr.Length; i++)
        {
            if (arr[i] % 2 != 0)
            {
                if (candidateIndex != index) return false;
                candidateIndex = i;
            }
        }

        index = candidateIndex;
        return true;
    }
}