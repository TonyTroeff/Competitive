namespace Task7;

public static class Program
{
    public static void Main()
    {
        var n = int.Parse(Console.ReadLine()!);
        var m = int.Parse(Console.ReadLine()!);

        var q = new Queue<long>();
        for (var i = 1; i <= 9; i++) q.Enqueue(i);
        
        List<long> ans = new ();
        while (q.Count > 0)
        {
            var current = q.Dequeue();
            
            if (n <= current && current <= m) Console.WriteLine(current);
            
            var lastDigit = current % 10;
            if (lastDigit != 0)
            {
                var next = current * 10 + lastDigit - 1;
                if (next <= m) q.Enqueue(next);
            }
            
            if (lastDigit != 9)
            {
                var next = current * 10 + lastDigit + 1;
                if (next <= m) q.Enqueue(next);
            }
        }
    }
}