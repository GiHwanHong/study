// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll			\
//   /main:TypeConvertTest /out:TypeConvertTest.exe TypeConvertTest.cs	\
//   && TypeConvertTest arg1 "arg2""
// End:
using System;

// // ������ ���� ��.
// struct MyStruct
// {
// 	public int Value { get; set; }
//     public MyStruct(int value)
//     {
// 		// ���� �ʱ�ȭ �Ǳ� ���� �Ӽ��� ������ �� �����ϴ�.
//         Value = value;
//     }
// }

// �⺻ �����ڸ� ��������� ȣ���� --> OK
struct MyStruct
{
	public int Value { get; set; }
    public MyStruct(int value)
        : this ()
    {
        Value = value;
    }
}

public struct Rectangle
{
    public int Width {get; set;}
    public int Height {get; set;}
    public Rectangle(int w, int h) : this()
    {
        Width = w; Height = h;
    }
    public void Draw()
    {
        Console.WriteLine("Rectangle::Draw() : {0}", this);
    }
    public override string ToString()
    {
        return string.Format("[Width = {0}; Height = {1}]", Width, Height);
    }
}
public struct Square
{
    public int Side { get; set; }
    public Square(int side)
		: this ()
	{
        Side = side;
    }
    public void Draw() {
        Console.WriteLine("Square::Draw() : {0}", this);
    }
	public override string ToString()
	{
		return string.Format("[Side = {0}]", Side);
	}
	public static explicit operator Rectangle (Square s)
	{
		Rectangle r = new Rectangle(s.Side, s.Side);
		return r;
	}
}

public class TypeConvertTest
{
	public static void Main()
	{
		Square s = new Square(15);
		s.Draw();

		Rectangle r = (Rectangle)s;
		r.Draw();
	}

}