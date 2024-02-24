namespace Tests;

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using Solutions;
using Xunit;

public class SolutionTests
{
    private static Random _random = new ();
    
    [Theory]
    [MemberData(nameof(GetParamsForProblem1))]
    public void TestProblem1(double[] array, double min, double max, double[] expected)
    {
        var result = Solve.Problem1(array, min, max);
        Assert.Equal(expected, result);
    }

    [Theory]
    [MemberData(nameof(GetParamsForProblem2))]
    public void TestProblem2(string statusCode, string expectedSeverity, string expectedDevice, string expectedDamage)
    {
        var result = Solve.Problem2(statusCode);
        Assert.Equal(expectedSeverity, result.Severity);
        Assert.Equal(expectedDevice, result.Device);
        Assert.Equal(expectedDamage, result.Damage);
    }

    [Theory]
    [MemberData(nameof(GetParamsForProblem3))]
    public void TestProblem3(byte[][] bitmap, int row, int col, byte newColor, byte[][] expected)
    {
        Solve.Problem3(bitmap, row, col, newColor);
        Assert.Equal(expected, bitmap);
    }

    [Theory]
    [MemberData(nameof(GetParamsForProblem4))]
    public void TestProblem4(string inputFile, string mergeFile, string outputFile, int[] expectedResult)
    {
        Solve.Problem4(inputFile, mergeFile, outputFile);
        var result = File.ReadAllLines(outputFile).Select(int.Parse);

        try
        {
            Assert.Equal(expectedResult, result);
        }
        finally
        {
             File.Delete(inputFile);   
             File.Delete(mergeFile);   
             File.Delete(outputFile);   
        }
    }

    [Theory]
    [MemberData(nameof(GetParamsForProblem5))]
    public void TestProblem5(string[] array, int n, string expectedResult)
    {
        var result = Solve.Problem5(array, n);
        Assert.Equal(expectedResult, result);
    }

    [Theory]
    [MemberData(nameof(GetParamsForProblem6))]
    public void TestProblem6(long number, long[] expectedDivisors)
    {
        var result = Solve.Problem6(number);
        Assert.Equal(expectedDivisors, result);
    }

    [Theory]
    [MemberData(nameof(GetParamsForProblem7))]
    public void TestProblem7(Line firstRectangleDiagonal, Line secondRectangleDiagonal, double expectedResult)
    {
        var result = Solve.Problem7(firstRectangleDiagonal, secondRectangleDiagonal);
        Assert.Equal(expectedResult, result);
    }

    [Theory]
    [MemberData(nameof(GetParamsForProblem8))]
    public void TestProblem8(string html, string[] expectedResult)
    {
        var result = Solve.Problem8(html);
        Assert.Equal(expectedResult, result);
    }

    public static IEnumerable<object[]> GetParamsForProblem1()
    {
        yield return [new[] { -3.2, -1.99, 0, 1.01, 1.88, 2.07, 3.33, 4.44, 9 }, 0, 3, new[] { 0, 1.01, 1.88, 2.07 }];

        const int n1 = 10000;
        double[] arr1 = new double[n1];
        for (int i = 0; i < n1; i++) arr1[i] = _random.NextDouble() * (_random.Next(0, 9999) + 1);
        Array.Sort(arr1);

        foreach (var testCase in GenerateTestCases(arr1, 10)) yield return testCase;

        const int n2 = 10000;
        const double quotient2 = 1e-5;
        double[] arr2 = new double[n2];
        for (int i = 0; i < n2; i++) arr2[i] = i * quotient2;
        
        foreach (var testCase in GenerateTestCases(arr2, 10)) yield return testCase;

        yield return [arr2, arr2[0], arr2[^1], arr2];
        yield return [arr2, arr2[0] - quotient2, arr2[^1], arr2];
        yield return [arr2, arr2[0], arr2[^1] + quotient2, arr2];
        yield return [arr2, arr2[^1], arr2[0], Array.Empty<double>()];

        static IEnumerable<object[]> GenerateTestCases(double[] array, int testCasesCount)
        {
            for (int i = 0; i < testCasesCount; i++)
            {
                int startIndex = _random.Next(array.Length - 1), endIndex = _random.Next(startIndex + 1, n1), length = endIndex - startIndex + 1;
                double[] expected = new double[length];
                for (int j = 0; j < length; j++) expected[j] = array[startIndex + j];

                yield return [array, array[startIndex], array[endIndex], expected];
            }
        }
    }

    public static IEnumerable<object[]> GetParamsForProblem2()
    {
        for (int i = byte.MinValue; i <= byte.MaxValue; i++)
        {
            int[] bytes = ExtractLast8Bytes(i);
            yield return [Convert.ToString(i, 16), Constants.Problem2.Severities[bytes[6] * 2 + bytes[7]], Constants.Problem2.Devices[bytes[3] * 4 + bytes[4] * 2 + bytes[5]], Constants.Problem2.Damages[bytes[0] * 4 + bytes[1] * 2 + bytes[2]]];
        }

        static int[] ExtractLast8Bytes(int value)
        {
            int[] bytes = new int[8];
            for (int i = 0; i < 8 && value != 0; i++, value /= 2) bytes[^(i + 1)] = value % 2;

            return bytes;
        }
    }

    public static IEnumerable<object[]> GetParamsForProblem3()
    {
        byte[][] matrix =
        [
            [1, 0, 1],
            [0, 0, 0],
            [1, 0, 1]
        ];

        byte[][] expected =
        [
            [1, 2, 1],
            [2, 2, 2],
            [1, 2, 1]
        ];

        yield return [matrix, 1, 1, 2, expected];
    }

    public static IEnumerable<object[]> GetParamsForProblem4()
    {
        const int testCasesCount = 1;

        for (int i = 1; i <= testCasesCount; i++)
        {
            int length = 100000;
            int[] array = new int[length];
            for (int j = 0; j < length; j++) array[j] = _random.Next();

            var expectedResult = array.OrderDescending().ToArray();

            string inputFile = Path.GetTempFileName();
            File.WriteAllLines(inputFile, array.Select(x => x.ToString()));

            yield return [inputFile, Path.GetTempFileName(), Path.GetTempFileName(), expectedResult];
        }
    }

    public static IEnumerable<object[]> GetParamsForProblem5()
    {
        const int testsCasesCount = 100;

        for (int i = 0; i < testsCasesCount; i++)
        {
            int arrayLength = _random.Next(1, 100);
            int n = _random.Next(arrayLength / 10 + 1);

            string[] array = new string[arrayLength];
            StringBuilder sb = new StringBuilder(capacity: arrayLength);
            for (int j = 0; j < arrayLength; j++)
            {
                sb.Append((char)('a' + _random.Next(26)));
                array[j] = sb.ToString();
            }

            string expectedResult = array[n];
            _random.Shuffle(array);

            yield return [array, n, expectedResult];
        }
    }
    
    public static IEnumerable<object[]> GetParamsForProblem6()
    {
        yield return [2, new[] { 2L }];
        yield return [3, new[] { 3L }];
        yield return [4, new[] { 2L }];
        yield return [5, new[] { 5L }];
        yield return [6, new[] { 2L, 3L }];
        yield return [7, new[] { 7L }];
        yield return [16, new[] { 2L }];
        yield return [20, new[] { 2L, 5L }];
        yield return [24, new[] { 2L, 3L }];
        yield return [910, new[] { 2L, 5L, 7L, 13L }];
    }

    public static IEnumerable<object[]> GetParamsForProblem7()
    {
        IEnumerable<object[]>[] allCases = [
            GenerateTestCases(new Point { X = 0, Y = 0 }, new Point { X = 3, Y = 3 }, new Point { X = 2, Y = 2 }, new Point { X = 4, Y = 4 }, 1),
            GenerateTestCases(new Point { X = 0, Y = 0 }, new Point { X = 5, Y = 5 }, new Point { X = 1, Y = 2 }, new Point { X = 3, Y = 3 }, 2),
            GenerateTestCases(new Point { X = 0, Y = 2 }, new Point { X = 2, Y = 10 }, new Point { X = 1, Y = 5 }, new Point { X = 5, Y = 8 }, 3)
        ];
        return allCases.SelectMany(x => x);

        IEnumerable<object[]> GenerateTestCases(Point p1, Point p2, Point p3, Point p4, double expectedResult)
        {
            Point q1 = new () { X = p1.X, Y = p2.Y }, q2 = new () { X = p2.X, Y = p1.X };
            Line[] d1 = [new Line(p1, p2), new Line(p2, p1), new Line(q1, q2), new Line(q2, q1)];
            
            Point q3 = new () { X = p3.X, Y = p4.Y }, q4 = new () { X = p4.X, Y = p3.Y };
            Line[] d2 = [new Line(p3, p4), new Line(p4, p3), new Line(q3, q4), new Line(q4, q3)];

            for (int i = 0; i < d1.Length; i++)
            {
                for (int j = 0; j < d2.Length; j++)
                    yield return [d1[i], d2[j], expectedResult];
            }
        }
    }
    
    public static IEnumerable<object[]> GetParamsForProblem8()
    {
        yield return [
            """
            <!DOCTYPE html>
            <html>
            <body>
            
            <h1>My First Heading</h1>
            <p>My first paragraph.</p>
            
            </body>
            </html>
            """,
            new[] { "My", "First", "Heading", "My", "first", "paragraph." }
        ];

        yield return
        [
            """
            <a href="https://www.w3schools.com">This is a link</a>
            """,
            new[] { "This", "is", "a", "link" }
        ];

        yield return
        [
            """
            <table>
              <tr>
                <th>Company</th>
                <th>Contact</th>
                <th>Country</th>
              </tr>
              <tr>
                <td>Alfreds Futterkiste</td>
                <td>Maria Anders</td>
                <td>Germany</td>
              </tr>
              <tr>
                <td>Centro comercial</td>
                <td>Francisco</td>
                <td>Mexico</td>
              </tr>
            </table>
            """,
            new[] { "Company", "Contact", "Country", "Alfreds", "Futterkiste", "Maria", "Anders", "Germany", "Centro", "comercial", "Francisco", "Mexico" }
        ];

    }
}