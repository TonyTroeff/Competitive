namespace Task8;

public static class Program
{
    public static void Main()
    {
        var n = int.Parse(Console.ReadLine()!);
        var m = int.Parse(Console.ReadLine()!);

        var forward = new HashSet<int>[n];
        var backward = new HashSet<int>[n];
        for (var i = 0; i < n; i++)
        {
            forward[i] = new HashSet<int>();
            backward[i] = new HashSet<int>();
        }
        
        for (var i = 0; i < m; i++)
        {
            var data = Console.ReadLine()!.Split().Select(int.Parse).ToArray();
            forward[data[0]].Add(data[1]);
            backward[data[1]].Add(data[0]);
        }

        var pq = new PriorityQueue<int, int>();
        for (var i = 0; i < n; i++)
            if (backward[i].Count == 0) pq.Enqueue(i, i);

        var result = new List<int>(capacity: n);
        while (pq.Count > 0)
        {
            var current = pq.Dequeue();
            result.Add(current);
            
            foreach (var next in forward[current])
            {
                backward[next].Remove(current);
                if (backward[next].Count == 0) pq.Enqueue(next, next);
            }
        }
        
        if (result.Count != n) Console.WriteLine("circular dependency");
        else Console.WriteLine(string.Join(' ', result));
    }
}