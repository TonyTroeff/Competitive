namespace Task9;

using System.Diagnostics;

public static class Program
{
    public static void Main()
    {
        var n = int.Parse(Console.ReadLine()!);
        var m = int.Parse(Console.ReadLine()!);

        var graph = new Dictionary<int, Dictionary<int, GraphNode>>();
        for (var i = 0; i < n; i++) graph[i] = new Dictionary<int, GraphNode>();

        for (var i = 0; i < m; i++)
        {
            var data = Console.ReadLine()!.Split().Select(int.Parse).ToArray();
            graph[data[0]][data[1]] = new GraphNode(data[0], data[2]);
        }

        var start = int.Parse(Console.ReadLine()!);
        var minSpan = Solve(graph, start);

        var result = new List<Road>(capacity: n - 1);
        foreach (var (src, edges) in minSpan)
        {
            foreach (var (dest, node) in edges) result.Add(new Road(src, dest, node.Cost));
        }
        
        foreach (var road in result.OrderByDescending(x => x.Cost).ThenBy(x => x.From).ThenBy(x => x.To))
            Console.WriteLine(road.ToString());
    }

    private static Dictionary<int, Dictionary<int, GraphNode>> Solve(Dictionary<int, Dictionary<int, GraphNode>> graph, int start)
    {
        var minPredecessors = FindMinPredecessors(graph, start);

        var cycle = FindCycle(minPredecessors);

        if (cycle != null)
        {
            var cyclicNode = graph.Keys.Max() + 1;
            var newGraph = new Dictionary<int, Dictionary<int, GraphNode>> { [cyclicNode] = new () };

            foreach (var node in graph.Keys)
            {
                if (!cycle.Contains(node))
                    newGraph[node] = new Dictionary<int, GraphNode>();
            }

            var inEdges = new Dictionary<int, int>();
            var outEdges = new Dictionary<int, int>();
            foreach (var (src, edges) in graph)
            {
                foreach (var (dest, node) in edges)
                {
                    if (!cycle.Contains(src) && cycle.Contains(dest))
                    {
                        var newNode = new GraphNode(node.OriginalSource, node.Cost - graph[minPredecessors[dest]][dest].Cost);
                        if (!newGraph[src].ContainsKey(cyclicNode) || newNode < newGraph[src][cyclicNode])
                        {
                            newGraph[src][cyclicNode] = newNode;
                            inEdges[src] = dest;
                        }
                    }
                    else if (cycle.Contains(src) && !cycle.Contains(dest))
                    {
                        if (!newGraph[cyclicNode].ContainsKey(dest) || node < newGraph[cyclicNode][dest])
                        {
                            newGraph[cyclicNode][dest] = node;
                            outEdges[dest] = src;
                        }
                    }
                    else if (!cycle.Contains(src) && !cycle.Contains(dest)) newGraph[src][dest] = node;
                }
            }

            var intermediateSpan = Solve(newGraph, start);

            var result = new Dictionary<int, Dictionary<int, GraphNode>>();
            foreach (var node in graph.Keys) result[node] = new Dictionary<int, GraphNode>();

            var cycleBreakNode = -1;
            foreach (var (src, edges) in intermediateSpan)
            {
                foreach (var dest in edges.Keys)
                {
                    if (src == cyclicNode)
                    {
                        var originalOut = outEdges[dest];
                        result[originalOut][dest] = graph[originalOut][dest];
                    }
                    else if (dest == cyclicNode)
                    {
                        var originalIn = inEdges[src];
                        cycleBreakNode = originalIn;
                        result[src][originalIn] = graph[src][originalIn];
                    }
                    else
                    {
                        result[src][dest] = graph[src][dest];
                    }
                }
            }

            Debug.Assert(cycleBreakNode != -1);

            foreach (var node in cycle)
            {
                if (node == cycleBreakNode) continue;
                result[minPredecessors[node]][node] = graph[minPredecessors[node]][node];
            }

            return result;
        }
        else
        {
            var result = new Dictionary<int, Dictionary<int, GraphNode>>();
            foreach (var node in graph.Keys) result[node] = new Dictionary<int, GraphNode>();

            foreach (var (to, from) in minPredecessors)
            {
                if (to != start)
                    result[from][to] = graph[from][to];
            }

            return result;
        }
    }

    private static Dictionary<int, int> FindMinPredecessors(Dictionary<int, Dictionary<int, GraphNode>> graph, int start)
    {
        var lowestPredecessor = new Dictionary<int, int>();
        foreach (var node in graph.Keys) lowestPredecessor[node] = -1;

        foreach (var (src, edges) in graph)
        {
            foreach (var (dest, node) in edges)
            {
                if (dest == start) continue;
                
                if (lowestPredecessor[dest] == -1 || node < graph[lowestPredecessor[dest]][dest])
                    lowestPredecessor[dest] = src;
            }
        }

        foreach (var (node, prev) in lowestPredecessor)
        {
            var isRoot = node == start;
            var hasPredecessor = prev != -1;
            Debug.Assert(isRoot == !hasPredecessor);
        }

        return lowestPredecessor;
    }

    private static HashSet<int>? FindCycle(Dictionary<int, int> minPredecessors)
    {
        var prevVisited = new Dictionary<int, bool>();
        foreach (var node in minPredecessors.Keys) prevVisited[node] = false;

        var newVisited = new HashSet<int>();

        foreach (var node in minPredecessors.Keys)
        {
            if (prevVisited[node]) continue;

            var iter = node;
            while (iter != -1 && !prevVisited[iter] && !newVisited.Contains(iter))
            {
                newVisited.Add(iter);
                iter = minPredecessors[iter];
            }

            if (newVisited.Contains(iter))
            {
                var cycle = new HashSet<int>();
                var cycleStart = iter;

                do
                {
                    cycle.Add(iter);
                    iter = minPredecessors[iter];
                } while (iter != cycleStart);

                return cycle;
            }

            foreach (var newNode in newVisited) prevVisited[newNode] = true;
            newVisited.Clear();
        }

        return null;
    }
}

public class Road
{
    public Road(int from, int to, int cost)
    {
        this.From = from;
        this.To = to;
        this.Cost = cost;
    }

    public int From { get; }
    public int To { get; }
    public int Cost { get; }

    public override string ToString() => $"{this.From} {this.To} {this.Cost}";
}

public class GraphNode : IComparable<GraphNode>
{
    public GraphNode(int originalSource, int cost)
    {
        this.OriginalSource = originalSource;
        this.Cost = cost;
    }

    public int OriginalSource { get; }
    public int Cost { get; }

    public int CompareTo(GraphNode? other)
    {
        if (ReferenceEquals(this, other)) return 0;
        if (ReferenceEquals(null, other)) return 1;

        var costComparison = this.Cost.CompareTo(other.Cost);
        if (costComparison != 0) return costComparison;

        return this.OriginalSource.CompareTo(other.OriginalSource);
    }

    public static bool operator <(GraphNode? left, GraphNode? right) => Comparer<GraphNode>.Default.Compare(left, right) < 0;

    public static bool operator >(GraphNode? left, GraphNode? right) => Comparer<GraphNode>.Default.Compare(left, right) > 0;

    public static bool operator <=(GraphNode? left, GraphNode? right) => Comparer<GraphNode>.Default.Compare(left, right) <= 0;

    public static bool operator >=(GraphNode? left, GraphNode? right) => Comparer<GraphNode>.Default.Compare(left, right) >= 0;
}