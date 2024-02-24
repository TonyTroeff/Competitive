namespace Solutions;

public record Line
{
    // We want the points always sorted horizontally.
    public Line(Point a, Point b)
    {
        if (a.X < b.X)
        {
            this.Start = a;
            this.End = b;
        }
        else
        {
            this.Start = b;
            this.End = a;
        }
    }
    
    public Point Start { get; }
    public Point End { get; }
}