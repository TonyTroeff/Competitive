namespace Task10;

using System.Diagnostics;

public static class Program
{
    public static void Main()
    {
        var costs = ReadCosts();

        var positionsA = Console.ReadLine()!.Split();
        var positionsB = Console.ReadLine()!.Split();
        
        var hierarchyA = ReadHierarchy(positionsA);
        var hierarchyB = ReadHierarchy(positionsB);

        SetIndices(hierarchyA);
        SetLeftMost(hierarchyA);
        var leftMostIndicesA = ExtractLeftMostIndices(hierarchyA);
        var keyRootsA = ExtractKeyRoots(leftMostIndicesA);
        var orderedValuesA = ExtractOrderedValues(hierarchyA);
        
        SetIndices(hierarchyB);
        SetLeftMost(hierarchyB);
        var leftMostIndicesB = ExtractLeftMostIndices(hierarchyB);
        var keyRootsB = ExtractKeyRoots(leftMostIndicesB);
        var orderedValuesB = ExtractOrderedValues(hierarchyB);

        var dp = new long[leftMostIndicesA.Length + 1, leftMostIndicesB.Length + 1];
        var reusableForest = new long[leftMostIndicesA.Length + 1, leftMostIndicesB.Length + 1];

        for (var k1 = 0; k1 < keyRootsA.Length; k1++)
        {
            for (var k2 = 0; k2 < keyRootsB.Length; k2++)
                dp[keyRootsA[k1], keyRootsB[k2]] = CalculateMinimumEditDistance(keyRootsA[k1], keyRootsB[k2], leftMostIndicesA, leftMostIndicesB, orderedValuesA, orderedValuesB, costs, dp, reusableForest);
        }

        var ans = dp[leftMostIndicesA.Length, leftMostIndicesB.Length];
        Console.WriteLine(ans);
    }

    private static long CalculateMinimumEditDistance(int i, int j, int[] leftMostIndicesA, int[] leftMostIndicesB, string[] orderedValuesA, string[] orderedValuesB, Costs costs, long[,] dp, long[,] forest)
    {
        int o1 = leftMostIndicesA[i - 1], o2 = leftMostIndicesB[j - 1];
        int q1 = o1 - 1, q2 = o2 - 1;

        forest[q1, q2] = 0;
        for (var k1 = leftMostIndicesA[i - 1]; k1 <= i; k1++) forest[k1, q2] = forest[k1 - 1, q2] + orderedValuesA[k1 - 1].Length * costs.Remove;
        for (var k2 = leftMostIndicesB[j - 1]; k2 <= j; k2++) forest[q1, k2] = forest[q1, k2 - 1] + orderedValuesB[k2 - 1].Length * costs.Add;

        for (var k1 = o1; k1 <= i; k1++)
        {
            for (var k2 = o2; k2 <= j; k2++)
            {
                if (o1 == leftMostIndicesA[k1 - 1] && o2 == leftMostIndicesB[k2 - 1])
                {
                    forest[k1, k2] = Math.Min(
                        Math.Min(forest[k1 - 1, k2] + orderedValuesA[k1 - 1].Length * costs.Remove, forest[k1, k2 - 1] + orderedValuesB[k2 - 1].Length * costs.Add),
                        forest[k1 - 1, k2 - 1] + CalculateMinimumEditDistance(orderedValuesA[k1 - 1], orderedValuesB[k2 - 1], costs));

                    dp[k1, k2] = forest[k1, k2];
                }
                else
                {
                    forest[k1, k2] = Math.Min(
                        Math.Min(forest[k1 - 1, k2] + orderedValuesA[k1 - 1].Length * costs.Remove, forest[k1, k2 - 1] + orderedValuesB[k2 - 1].Length * costs.Add),
                        forest[leftMostIndicesA[k1 - 1] - 1, leftMostIndicesB[k2 - 1] - 1] + dp[k1, k2]);
                }
            }
        }

        return forest[i, j];
    }

    private static long CalculateMinimumEditDistance(string from, string to, Costs costs)
    {
        var dp = new long[from.Length + 1, to.Length + 1];
        for (var i = 1; i <= from.Length; i++) dp[i, 0] = i * costs.Remove;
        for (var j = 1; j <= to.Length; j++) dp[0, j] = j * costs.Add;
        
        for (var i = 1; i <= from.Length; i++)
        {
            for (var j = 1; j <= to.Length; j++)
            {
                if (from[i - 1] == to[j - 1]) dp[i, j] = dp[i - 1, j - 1];
                else dp[i, j] = Math.Min(dp[i - 1, j - 1] + costs.Change, Math.Min(dp[i - 1, j] + costs.Remove, dp[i, j - 1] + costs.Add));
            }
        }

        return dp[from.Length, to.Length];
    }

    private static Costs ReadCosts()
    {
        var addCost = int.Parse(Console.ReadLine()!);
        var changeCost = int.Parse(Console.ReadLine()!);
        var removeCost = int.Parse(Console.ReadLine()!);

        return new Costs(addCost, changeCost, removeCost);
    }

    private static HierarchyNode ReadHierarchy(string[] positions)
    {
        var connectionsCount = int.Parse(Console.ReadLine()!); // positions.Length - 1;
        Debug.Assert(connectionsCount == positions.Length - 1);

        var nodesByName = new Dictionary<string, HierarchyNode>();
        for (var i = 0; i < positions.Length; i++) nodesByName[positions[i]] = new HierarchyNode { Value = positions[i] };

        var children = new HashSet<string>();

        for (var i = 0; i < connectionsCount; i++)
        {
            var data = Console.ReadLine()!.Split();
            nodesByName[data[0]].Children.Add(nodesByName[data[1]]);
            children.Add(data[1]);
        }

        var candidateRoots = positions.Where(p => !children.Contains(p)).ToArray();
        Debug.Assert(candidateRoots.Length == 1);

        return nodesByName[candidateRoots[0]];
    }
    

    public static void SetIndices(HierarchyNode root) => SetIndices(root, 0);

    private static int SetIndices(HierarchyNode node, int index)
    {
        foreach (var child in node.Children) index = SetIndices(child, index);
        return node.Index = index + 1;
    }

    private static void SetLeftMost(HierarchyNode node)
    {
        if (node.Children.Count == 0) return;
        foreach (var child in node.Children) SetLeftMost(child);

        node.LeftMost = node.Children[0].LeftMost;
    }

    private static int[] ExtractLeftMostIndices(HierarchyNode root)
    {
        var result = new List<int>();
        ExtractLeftMostIndices(root, result);
        return result.ToArray();
    }

    private static void ExtractLeftMostIndices(HierarchyNode node, List<int> indices)
    {
        foreach (var child in node.Children) ExtractLeftMostIndices(child, indices);
        indices.Add(node.LeftMost.Index);
    }

    public static int[] ExtractKeyRoots(int[] leftMostIndices)
    {
        var result = new List<int>();
        for (var i = 0; i < leftMostIndices.Length; i++)
        {
            var add = true;
            for (var j = i + 1; j < leftMostIndices.Length; j++)
                if (leftMostIndices[i] == leftMostIndices[j]) { add = false; break; }
            
            if (add) result.Add(i + 1);
        }

        return result.ToArray();
    }

    public static string[] ExtractOrderedValues(HierarchyNode root)
    {
        var result = new List<string>();
        ExtractOrderedValues(root, result);
        return result.ToArray();
    }

    private static void ExtractOrderedValues(HierarchyNode node, List<string> values)
    {
        foreach (var child in node.Children) ExtractOrderedValues(child, values);
        values.Add(node.Value);
    }
}

public class Costs
{
    public Costs(int add, int change, int remove)
    {
        this.Add = add;
        this.Change = change;
        this.Remove = remove;
    }

    public int Add { get; }
    public int Change { get; }
    public int Remove { get; }
}

public class HierarchyNode
{
    private HierarchyNode? _leftMostChild;
    
    public string Value { get; set; }
    public int Index { get; set; }

    public HierarchyNode LeftMost
    {
        get => this._leftMostChild ?? this;
        set => this._leftMostChild = value;
    }
    public List<HierarchyNode> Children { get; } = new ();
}